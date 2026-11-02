#include <stdio.h>

int main()
{
    int a[50], n, head, size;
    int i, j, temp, total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue: ");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total number of tracks: ");
    scanf("%d", &size);

    // Sort requests in ascending order
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

    // Move to the last track
    total += (size - 1) - head;
    head = size - 1;
    printf(" -> %d", head);

    // Reverse direction
    for(i = n - 1; i >= 0; i--)
    {
        if(a[i] < head && a[i] < size)
        {
            total += head - a[i];
            head = a[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}