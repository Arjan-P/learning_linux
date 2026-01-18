#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <libgen.h>

// imporovement:
// for files -> dir case, use basename for target file
// add security checks if open / writes fail
int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s <src> <dest>\n", argv[0]);
    return 1;
  }
  else if(argc == 3)
  {
    // copy contents of argv[1] to argv[2]
    int src_file_fd = open(argv[1], O_RDONLY);
    int dest_file_fd = open(argv[2],
                         O_CREAT | O_WRONLY | O_TRUNC,
                         0644);

    char buffer[100];
    ssize_t n;
    while((n = read(src_file_fd, buffer, sizeof(buffer))) > 0)
    {
      write(dest_file_fd, buffer, n);
    }
    close(src_file_fd);
    close(dest_file_fd);
  }
  else
  {
    // copy contents of argv[1] ... argv[argc - 2] -> directory at argv[argc - 1]
    //
    // open directory, store fd.
    // for each file openat(directory fd, file).
    // read contents into file copy
    int dfd = open(argv[argc - 1], O_RDONLY | O_DIRECTORY);
    for(int i = 1; i < argc - 1; i++)
    {
      int src_file_fd = open(argv[i], O_RDONLY);
      char* filename = basename(argv[i]);
      int dest_file_fd = openat(dfd, filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
      
      char buffer[100];
      ssize_t n;
      while((n = read(src_file_fd, buffer, sizeof(buffer))) > 0)
      {
        write(dest_file_fd, buffer, n);
      }
      close(src_file_fd);
      close(dest_file_fd);
    }
    close(dfd);
  }
  return 0;
}
