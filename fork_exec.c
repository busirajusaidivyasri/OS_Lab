#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main()
{
	char command[100];
	pid_t pid;
	printf("Enter a Linux command: ");
	fgets(command, sizeof(command), stdin);
	command[strcspn(command,"\n")] = '\0';
	pid = fork();
	if(pid<0)
	{
		printf("Fork Failed!\n");
		return 1;
	}
	else if(pid == 0)
	{
		printf("\nChild Process\n");
		printf("Child PID: %d\n",getpid());
		execlp("sh", "sh", "-c", command,NULL);
		printf("Execution Failed!\n");
		exit(1);
	}
	else
	{
		printf("\nParent Process\n");
		printf("Parent PID: %d\n", getpid());
		printf("Child PID: %d\n", pid);
		wait(NULL);
		printf("\nChild Process Completed.\n");
	}
	return 0;
}

