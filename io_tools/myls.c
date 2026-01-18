#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

/*
	opendir:
       DIR *opendir(const char *name);

	readdir:
       struct dirent *readdir(DIR *dirp);

*/

int main(int argc, char* argv[])
{
	for(int i = 1; i < argc; i++)
	{
		DIR* dir = opendir(argv[i]);
		struct dirent *entry;
		while((entry = readdir(dir)))
		{
			printf("%s ", entry->d_name);
		}
		closedir(dir);
		printf("\n");
	}
	return 0;
}
