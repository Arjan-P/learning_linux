#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*
	open():
       int open(const char *path, int flags, ...
                   mode_t mode  );
	read():
       ssize_t read(size_t count;
                    int fd, void buf[count], size_t count);
*/

int main(int argc, char* argv[])
{
	// open a file description for files provided
	for(int i = 1; i < argc; i++)
	{
		int fd = open(argv[i], O_RDONLY);
		if(fd < 0)
		{
			continue;
		}

		char buffer[100];
		ssize_t n;
		while((n = read(fd, buffer, sizeof(buffer))) > 0)		// try to read 100 byte chunks at a time
		{
			write(STDOUT_FILENO, buffer, n);	// write bytes read to output file
		}
		close(fd);
	}
	return 0;
}
