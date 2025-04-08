#include <stdio.h>
#include <windows.h>  // For high-resolution timing
#define MAX 50

typedef struct {
    int id;
    int value;
} Element;

void MergeSort(int low, int high);
void Merge(int low, int mid, int high);
void display(int low, int high);

Element a[MAX], b[MAX];
int n;

long long getTimeNanoseconds() {
    LARGE_INTEGER frequency, now;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&now);
    return (now.QuadPart * 1000000000LL) / frequency.QuadPart;
}

int main() {
    int i;
    long long start, end;

    printf("Enter the number of elements (products) in the array: ");
    scanf("%d", &n);

    printf("Enter %d elements (Product ID and price):\n", n);
    for (i = 1; i <= n; i++) {
        scanf("%d %d", &a[i].id, &a[i].value);
    }

    printf("Original array:\n");
    for (i = 1; i <= n; i++) {
        printf("[ %d: %d ] ", a[i].id, a[i].value);
    }
    printf("\n");

    start = getTimeNanoseconds();
    MergeSort(1, n);
    end = getTimeNanoseconds();

    printf("\nMergeSort execution time: %lld nanoseconds\n", end - start);

    printf("\nSorted array:\n");
    for (i = 1; i <= n; i++) {
        printf("[ %d: %d ] ", a[i].id, a[i].value);
    }
    printf("\n");

    return 0;
}

void MergeSort(int low, int high) {
    if (low < high) {
        printf("\nMergeSort called with low=%d, high=%d\n", low, high);
        display(low, high);

        int mid = (low + high) / 2;
        MergeSort(low, mid);
        MergeSort(mid + 1, high);

        long long start = getTimeNanoseconds();
        Merge(low, mid, high);
        long long end = getTimeNanoseconds();

        printf("Merge execution time: %lld nanoseconds\n", end - start);
    }
}

void Merge(int low, int mid, int high) {
    int i = low, h = low, j = mid + 1;

    while (h <= mid && j <= high) {
        if (a[h].value <= a[j].value) {
            b[i++] = a[h++];
        } else {
            b[i++] = a[j++];
        }
    }

    while (h <= mid) {
        b[i++] = a[h++];
    }

    while (j <= high) {
        b[i++] = a[j++];
    }

    for (i = low; i <= high; i++) {
        a[i] = b[i];
    }

    display(low, high);
    printf("low=%d, high=%d\n", low, high);
}

void display(int low, int high) {
    for (int i = low; i <= high; i++) {
        printf("[ %d: %d ] ", a[i].id, a[i].value);
    }
    printf("\n");
}
