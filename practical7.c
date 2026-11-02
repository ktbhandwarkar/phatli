#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int pipe1[2], pipe2[2];
    int pid, n;
    char filename[100];
    char buffer[100];

    pipe(pipe1);
    pipe(pipe2);

    pid = fork();

    if(pid == 0)
    {
        // Child process

        close(pipe1[1]);
        close(pipe2[0]);

        read(pipe1[0], filename, sizeof(filename));
        close(pipe1[0]);

        FILE *fp = fopen(filename, "r");

        if(fp == NULL)
        {
            char msg[] = "File not found!\n";
            write(pipe2[1], msg, strlen(msg));
        }
        else
        {
            while((n = fread(buffer, 1, sizeof(buffer), fp)) > 0)
            {
                write(pipe2[1], buffer, n);
            }

            fclose(fp);
        }

        close(pipe2[1]);
        exit(0);
    }
    else
    {
        // Parent process

        close(pipe1[0]);
        close(pipe2[1]);

        printf("Enter file name: ");
        scanf("%99s", filename);

        write(pipe1[1], filename, strlen(filename) + 1);
        close(pipe1[1]);

        printf("\nFile contents:\n");

        while((n = read(pipe2[0], buffer, sizeof(buffer))) > 0)
        {
            write(1, buffer, n);
        }

        close(pipe2[0]);

        wait(NULL);
    }

    return 0;
}