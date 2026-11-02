#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main(int argc, char *argv[])
{
    int fd, n;
    char buffer[100];

    if(argc != 2)
    {
        printf("Use: ./p6 server OR ./p6 client\n");
        return 1;
    }

    // Process 1: Client
    if(strcmp(argv[1], "client") == 0)
    {
        char sentence[500];

        printf("Enter a sentence: ");
        fgets(sentence, sizeof(sentence), stdin);

        fd = open(FIFO1, O_WRONLY);
        write(fd, sentence, strlen(sentence));
        close(fd);

        fd = open(FIFO2, O_RDONLY);

        printf("\nResult received from server:\n");

        while((n = read(fd, buffer, sizeof(buffer))) > 0)
        {
            write(1, buffer, n);
        }

        close(fd);
    }

    // Process 2: Server
    else if(strcmp(argv[1], "server") == 0)
    {
        int chars = 0, words = 0, lines = 0;
        int inword = 0;
        char ch, last = '\0';

        mkfifo(FIFO1, 0666);
        mkfifo(FIFO2, 0666);

        printf("Server waiting for sentence...\n");

        fd = open(FIFO1, O_RDONLY);

        while((n = read(fd, buffer, sizeof(buffer))) > 0)
        {
            for(int i = 0; i < n; i++)
            {
                ch = buffer[i];
                chars++;
                last = ch;

                if(ch == '\n')
                    lines++;

                if(isspace((unsigned char)ch))
                    inword = 0;
                else if(inword == 0)
                {
                    words++;
                    inword = 1;
                }
            }
        }

        close(fd);

        if(chars > 0 && last != '\n')
            lines++;

        FILE *fp = fopen("result.txt", "w");

        fprintf(fp, "Characters = %d\n", chars);
        fprintf(fp, "Words = %d\n", words);
        fprintf(fp, "Lines = %d\n", lines);

        fclose(fp);

        fp = fopen("result.txt", "r");
        fd = open(FIFO2, O_WRONLY);

        while((n = fread(buffer, 1, sizeof(buffer), fp)) > 0)
        {
            write(fd, buffer, n);
        }

        fclose(fp);
        close(fd);

        unlink(FIFO1);
        unlink(FIFO2);

        printf("Result sent successfully.\n");
    }

    else
    {
        printf("Invalid option!\n");
    }

    return 0;
}