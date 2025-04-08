#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>
#define MAX 15

int n;

void interchange(char arr[], int i, int j) {
    char p = arr[i];
    arr[i] = arr[j];
    arr[j] = p;
}

void print(char arr[], int low, int up) {
    printf("\n");
    for (int i = 1; i <= n; i++) {
        if (i == low) {
            printf("[ ");
        }
        printf("%c", arr[i]);
        if (i != up - 1)
            printf(" ");
        if (i == up - 1)
            printf("]");
    }
}

int partition(char arr[], int low, int up) {
    char pivot = arr[low];
    int i = low + 1, j = up;
    while (i <= j) {
        while (arr[i] <= pivot) i++;
        while (arr[j] > pivot) j--;
        if (i < j) {
            interchange(arr, i, j);
            print(arr, low, up);
        }
    }
    arr[low] = arr[j];
    arr[j] = pivot;
    print(arr, low, up);
    printf(" j= %d", j);
    return j;
}

char select(char a[], int low, int up, int k) {
    int j;
    low = 1;
    up = n + 1;
    a[n + 1] = CHAR_MAX;
    while (low < up) {
        j = partition(a, low, up);
        if (k == j)
            return a[k];
        else if (k < j)
            up = j;
        else
            low = j + 1;
    }
    return '\0';
}

int main() {
    int k;
    char arr[MAX], m;
    struct timeval start, end;
    double t_ms, t_us, t_ns;
    long s, us;
    printf("Enter the no. of elements: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (int i = 1; i <= n; i++) {
        scanf(" %c", &arr[i]);
    }
    printf("Enter the no. of smallest element to be found: ");
    scanf("%d", &k);
    gettimeofday(&start, NULL);
    m = select(arr, 1, n, k);
    gettimeofday(&end, NULL);
    printf("\nThe %d th smallest element is %c\n", k, m);
    s = end.tv_sec - start.tv_sec;
    us = end.tv_usec - start.tv_usec;
    t_us = s * 1000000 + us;
    t_ms = t_us / 1000.0;
    t_ns = t_us * 1000.0;
    printf("\nExecution time of the select function:\n");
    printf("Milliseconds: %f ms\n", t_ms);
    return 0;
}
