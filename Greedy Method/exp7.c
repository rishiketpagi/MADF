#include <stdio.h>
#include <limits.h>
#include <time.h>
void knapsack(int m, int n) {
    clock_t start, end; 
    double time_taken;
    start = clock(); 
    float x[n], wixi = 0.0, pixi = 0.0, u;
    float w[n], p[n], op[n];
    float f[10] = {0.5, 0.5, 0.34, 0.34, 0.25, 0.2, 0.16, 0.14, 0.125, 0.11};
int max, min, index, i, j;
 printf("Enter weights: ");
    for (i = 0; i < n; i++)
        scanf("%f", &w[i]);
 printf("Enter profits: ");
    for (i = 0; i < n; i++)
        scanf("%f", &p[i]);
    for (i = 0; i < n; i++) {
        wixi += f[i] * w[i];
        pixi += f[i] * p[i];
    }
    printf("\n-------------");
    for(i=0;i<n+1;i++)
        printf("---------");
    printf("\n");
    printf("            \t");
    for(i=0;i<n;i++)
        printf("|x%d\t ",i+1);
 printf("|wixi\t |pixi  |\n");
    printf("-------------");
    for(i=0;i<n+1;i++)
        printf("---------");
    printf("\n");
    printf("Fractional\t|");
    for (i = 0; i < n; i++)
        printf("%.2f\t |", f[i]);
    printf("%.2f\t |%.2f|\n", wixi, pixi);
    printf("-------------");
    for(i=0;i<n+1;i++)
        printf("---------");
    printf("\n");
    for (i = 0; i < n; i++)
        x[i] = 0.0;
    u = m;
    for (i = 0; i < n; i++) {
        max = INT_MIN;
        index = -1;
for (j = 0; j < n; j++) {
          if (p[j] > max && x[j] != 1) {
                max = p[j];
                index = j;
            }
        }
 if (index == -1 || w[index] > u)
            break;
        x[index] = 1.0;
        u -= w[index];
    }
 if (index != -1 && i < n)
x[index] = u / w[index];
    printf("Max. profit\t|");
    for (i = 0; i < n; i++)
  printf("%.1f\t |", x[i]);
    wixi = 0;
    pixi = 0;
    for (i = 0; i < n; i++) {
        wixi += x[i] * w[i];
        pixi += x[i] * p[i];
    }
printf("%.2f\t |%.2f|\n", wixi, pixi);
    printf("-------------");
    for(i=0;i<n+1;i++)
        printf("---------");
    printf("\n");
    for (i = 0; i < n; i++)
        x[i] = 0.0;
    u = m;
    for (i = 0; i < n; i++) {
        min = INT_MAX;
        index = -1;
 for (j = 0; j < n; j++) {
            if (w[j] < min && x[j] != 1) {
                min = w[j];
                index = j;
            }
        }
        if (index == -1 || w[index] > u)
            break;
        x[index] = 1.0;
        u -= w[index];
    }
 if (index != -1 && i < n)
        x[index] = u / w[index];
 printf("Least weight\t|");
    for (i = 0; i < n; i++)
  printf("%.1f\t |", x[i]);
    wixi = 0;
    pixi = 0;
    for (i = 0; i < n; i++) {
        wixi += x[i] * w[i];
        pixi += x[i] * p[i];
    }
printf("%.2f\t |%.2f|\n", wixi, pixi);
    printf("-------------");
    for(i=0;i<n+1;i++)
        printf("---------");
    printf("\n");
    for (i = 0; i < n; i++) {
        op[i] = p[i] / w[i];
        x[i] = 0.0;
    }
    u = m;
    for (i = 0; i < n; i++) {
        max = INT_MIN;
        index = -1;
for (j = 0; j < n; j++) {
        if (op[j] > max && x[j] != 1) {
                max = op[j];
                index = j;
            }
        }
 if (index == -1 || w[index] > u)
            break;
        x[index] = 1.0;
        u -= w[index];    }
    if (index != -1 && i < n)
        x[index] = u / w[index];
    printf("pi/wi:\t\t|");
    for (i = 0; i < n; i++)
  printf("%.1f\t |", x[i]);
    wixi = 0;
    pixi = 0;
    for (i = 0; i < n; i++) {
        wixi += x[i] * w[i];
        pixi += x[i] * p[i];
    }
    printf("%.2f\t |%.2f|\n", wixi, pixi);
    printf("-------------");
    for(i=0;i<n+1;i++)
        printf("---------");
    printf("\n");
    printf("Maximum Profit : %f\n", pixi);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by knapsack function: %f seconds\n", time_taken);
}

int main() {
    int m, n;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter the knapsack capacity: ");
    scanf("%d", &m);
    knapsack(m, n);
    return 0;
}
