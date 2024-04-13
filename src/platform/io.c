#include "platform/io.h"
#include <stdio.h>
#include <stdlib.h>

#if defined (unix)
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#if defined(_WIN32)
int read_file(char **buffer, const char *path)
{
	fprintf("Error: read_file(char *buffer, const char *path) not implemented yet");
	return -1;
}
#elif defined(unix) || defined(__unix) || defined(__unix__)
int read_file(char **buffer, const char *path)
{
	FILE* fp;
	int fd;
	off_t file_size;
	struct stat st;
	
	fd = open(path, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Error: could not open file `%s`", path);
		return -1;
	}
	
	fp = fdopen(fd, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error: could not open file `%s`", path);
		close(fd);
		return -1;
	}
	
	/* Ensure that the file is a regular file */
	if ((fstat(fd, &st) != 0) || (!S_ISREG(st.st_mode))) {
		fprintf(stderr, "Error: could not read file `%s`", path);
		fclose(fp);
		close(fd);
		return -1;
	}
	
	if (fseeko(fp, 0 , SEEK_END) != 0) {
		fprintf(stderr, "Error: could not read file `%s`", path);
		fclose(fp);
		close(fd);
		return -1;
	}
	
	file_size = ftello(fp);
	if (file_size == -1) {
		fprintf(stderr, "Error: could not read file `%s`", path);
		fclose(fp);
		close(fd);
		return -1;
	}
	
	*buffer = (char*)malloc(file_size);
	if (*buffer == NULL) {
		fprintf(stderr, "Error: could not create file buffer `%s`", path);
		fclose(fp);
		close(fd);
		return -1;
	}
	rewind(fp);
	size_t s = fread(*buffer, sizeof(char), file_size, fp);
	(*buffer)[s] = 0;

	fclose(fp);
	close(fd);
	return s;
}
#endif