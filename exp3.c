#include <stdio.h>
#include <windows.h>  // For high-resolution timing
#define MAX 50

int a[MAX];
void MinMax(int i, int j, int* min, int* max);
void display(int i, int j, int min, int max);

// Timer utilities for Windows
LARGE_INTEGER frequency;

LONGLONG getMicroseconds(LARGE_INTEGER start, LARGE_INTEGER end) {
    return (end.QuadPart - start.QuadPart) * 1000000 / frequency.QuadPart;
}

int main() {
    int i, n, min, max;
    LARGE_INTEGER start, end;

    QueryPerformanceFrequency(&frequency);

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    printf("Enter %d elements: ", n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    printf("-----------------------------\n");
    printf("| %4s | %4s | %4s | %4s |\n", "i", "j", "min", "max");
    printf("-----------------------------\n");

    QueryPerformanceCounter(&start);
    MinMax(1, n, &min, &max);
    QueryPerformanceCounter(&end);

    LONGLONG elapsedMicroseconds = getMicroseconds(start, end);
    printf("\nMinMax execution time: %lld microseconds\n", elapsedMicroseconds);
    printf("The Maximum element is: %d\n", max);
    printf("The Minimum element is: %d\n", min);

    return 0;
}

void MinMax(int i, int j, int* min, int* max) {
    int mid, min1, max1;
    if (i == j) {
        *min = a[i];
        *max = a[i];
        display(i, j, *min, *max);
    } else if (i == j - 1) {
        if (a[i] >= a[j]) {
            *max = a[i];
            *min = a[j];
        } else {
            *max = a[j];
            *min = a[i];
        }
        display(i, j, *min, *max);
    } else {
        mid = (i + j) / 2;
        MinMax(i, mid, min, max);
        MinMax(mid + 1, j, &min1, &max1);
        if (*min > min1)
            *min = min1;
        if (*max < max1)
            *max = max1;
        display(i, j, *min, *max);
    }
}

void display(int i, int j, int min, int max) {
    printf("| %4d | %4d | %4d | %4d |\n", i, j, min, max);
    printf("-----------------------------\n");
}
