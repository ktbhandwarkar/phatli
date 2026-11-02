#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, head, total = 0;
    int a[100], visited[100] = {0};

    printf("Enter number of requests: ");
    scanf("%d", &n);

    if (n < 1 || n > 100)
        return 1;

    printf("Enter request queue:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nSeek sequence: %d", head);

    for (i = 0; i < n; i++)
    {
        int min = 100000, index = -1;

        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                int distance = abs(head - a[j]);

                if (distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        total += min;
        head = a[index];

        printf(" -> %d", head);
    }

    printf("\nTotal head movement = %d\n", total);

    return 0;
}