#include <stdio.h>
#include <time.h>
#include <sys/time.h>

void strassenMultiply(int A[2][2], int B[2][2], int C[2][2]) {
    int P,Q,R,S,T,U,V; 
    P = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
    printf("P = %d\n", P);
    Q = (A[1][0] + A[1][1]) * B[0][0];
    printf("Q = %d\n", Q);
    R = A[0][0] * (B[0][1] - B[1][1]);
    printf("R = %d\n", R);
    S = A[1][1] * (B[1][0] - B[0][0]);
    printf("S = %d\n", S);
    T = (A[0][0] + A[0][1]) * B[1][1];
    printf("T = %d\n", T);
    U = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
    printf("U = %d\n", U);
    V = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
    printf("V = %d\n\n", V);
    C[0][0] = P + S - T + V;
    printf("C11 = %d\n", C[0][0]);
    C[0][1] = R + T;
    printf("C12 = %d\n", C[0][1]);
    C[1][0] = Q + S;
    printf("C21 = %d\n", C[1][0]);
    C[1][1] = P + R - Q + U;
    printf("C22 = %d\n\n", C[1][1]);
}

int main() {
    int A[2][2], B[2][2], C[2][2];
    struct timeval start, end;
    double t_ms, t_us;
    long s, us;
    printf("Enter elements of A:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    printf("Enter elements of B:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &B[i][j]);
        }
    }
    gettimeofday(&start, NULL);
    strassenMultiply(A, B, C);
    gettimeofday(&end, NULL);
    s = end.tv_sec - start.tv_sec;
    us = end.tv_usec - start.tv_usec;
    t_us = s * 1000000 + us;
    t_ms = t_us / 1000.0;
    printf("Resultant Matrix C is:\n");
    printf("%d %d\n", C[0][0], C[0][1]);
    printf("%d %d\n", C[1][0], C[1][1]);
    printf("\nExecution time of strassenMultiply function:\n");
    printf("Milliseconds: %f ms\n", t_ms);
    return 0;
}
