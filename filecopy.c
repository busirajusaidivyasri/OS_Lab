#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
int main(int argc, char *argv[])
{
	int source_fd , dest_fd;
	char buffer[BUFFER_SIZE];
	ssize_t bytesRead, bytesWritten;

	if (argc != 3)
	{
		printf("Usage: %s <source_file> <destination_file>\n",argv[0]);
		return 1;
	}

	source_fd = open(argv[1], O_RDONLY);
	if(source_fd == -1)
	{
		perror("Error opening source file");
		return 1;
	}

	dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(dest_fd == -1)
	{
		perror("Error opening destination file");
		close(source_fd);
		return 1;
	}
	
	while((bytesRead = read(source_fd, buffer, BUFFER_SIZE))>0)
	{
		bytesWritten = write(dest_fd, buffer , bytesRead);
		if(bytesWritten != bytesRead)
		{
			perror("Write Error");
			close(source_fd);
			close(dest_fd);
			return 1;
		}
	}

	if(bytesRead < 0)
	{
		perror("Read Error");
	}

	close(source_fd);
	close(dest_fd);

	printf("File copied successsfully.\n");
	return 0;
}

