#include <stdio.h>

int main()
{
    int a[50], n, head;
    int i, j, temp, total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Sort requests
    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("\nSeek Sequence: %d", head);

    // Move towards higher tracks
    for(i = 0; i < n; i++)
    {
        if(a[i] >= head)
        {
            total += a[i] - head;
            head = a[i];
            printf(" -> %d", head);
        }
    }

    // Jump to the lowest request
    for(i = 0; i < n; i++)
    {
        if(a[i] < head)
        {
            total += head - a[i];
            head = a[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}