#include "try.h"

// piping a value from parent to child

int main()
{
    int fd[2];
	// fd[0] -> read
	// fd[1] -> write
	int input = 42;
	int output;
    if (pipe(fd) < 0)
        return(1);
    
    int id = fork();

	// 0 means we are in the child process
	if(id != 0)
	{
		close(fd[0]);
		// writing to a specific fd that was defined by the pipe function
		if(write(fd[1], &input, sizeof(int)) < 0)
			return (1);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		// reading from that fd
		if(read(fd[0], &output , sizeof(int)) < 0)
			return(2);
		close(fd[0]);
		printf("got from parent process: %d\n", output);
	}
}