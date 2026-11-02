#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void sort(int a[], int n)
{
    int i, j, temp;

    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

int main()
{
    int choice, n, a[50], i;
    pid_t pid;

    printf("\n1. Fork and Wait with Sorting");
    printf("\n2. Zombie Process");
    printf("\n3. Orphan Process");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        printf("Enter number of elements: ");
        scanf("%d", &n);

        printf("Enter elements: ");
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);

        pid = fork();

        if(pid == 0)
        {
            sort(a, n);

            printf("\nChild Process Sorted Array: ");
            for(i = 0; i < n; i++)
                printf("%d ", a[i]);

            printf("\nChild Completed\n");
            exit(0);
        }
        else if(pid > 0)
        {
            sort(a, n);

            printf("\nParent Process Sorted Array: ");
            for(i = 0; i < n; i++)
                printf("%d ", a[i]);

            wait(NULL);
            printf("\nParent Completed\n");
        }
        else
        {
            printf("Fork Failed\n");
        }
    }

    else if(choice == 2)
    {
        pid = fork();

        if(pid == 0)
        {
            printf("Child Process Exiting\n");
            exit(0);
        }
        else if(pid > 0)
        {
            printf("Parent Sleeping for 15 Seconds\n");
            sleep(15);
            printf("Parent Calling Wait\n");
            wait(NULL);
            printf("Zombie Process Removed\n");
        }
    }

    else if(choice == 3)
    {
        pid = fork();

        if(pid == 0)
        {
            printf("Child Started\n");
            printf("Old Parent ID: %d\n", getppid());

            sleep(5);

            printf("New Parent ID: %d\n", getppid());
            printf("Orphan Process Completed\n");
        }
        else if(pid > 0)
        {
            printf("Parent Process Exiting\n");
            exit(0);
        }
    }

    else
    {
        printf("Invalid Choice\n");
    }

    return 0;
}
