#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define MAX 50

int n;
int BinarySearch(char a[][MAX], int low, int high, char *x);
void display(char a[][MAX], int low, int high);

int main() {
    int i, result;
    char arr[MAX][MAX], key[MAX];

    printf("Enter the number of strings in the array: ");
    scanf("%d", &n);

    if (n > 0) {
        printf("Enter %d strings in ascending order:\n", n);
        for (i = 0; i < n; i++) {
            scanf("%s", arr[i]);
        }

        printf("Enter the string to be searched: ");
        scanf("%s", key);
        printf("\n");

        struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL); 

        result = BinarySearch(arr, 0, n - 1, key);

        gettimeofday(&end_time, NULL);  

        if (result == -1)
            printf("Element not found\n");
        else
            printf("Element found at position %d.\n", result + 1);

        double time_taken = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
                            (end_time.tv_usec - start_time.tv_usec) / 1000.0;

        printf("Time taken for BinarySearch: %.6f milliseconds\n", time_taken);
    }

    return 0;
}

int BinarySearch(char a[][MAX], int low, int high, char *x) {
    display(a, low, high);
    int mid;

    if (low > high) {
        return -1;
    }

    mid = (low + high) / 2;

    int cmp = strcmp(a[mid], x);
    if (cmp == 0)
        return mid;
    else if (cmp < 0)
        return BinarySearch(a, mid + 1, high, x);
    else
        return BinarySearch(a, low, mid - 1, x);
}

void display(char a[][MAX], int low, int high) {
    int i;
    printf("Current array state: ");
    for (i = 0; i < n; i++) {
        if (i == low)
            printf("[ ");
        printf("%s ", a[i]);
        if (i == high)
            printf("] ");
    }
    printf("\n");
    printf("low = %d, high = %d, mid = %d\n\n", low, high, (low + high) / 2);
}
