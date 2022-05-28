#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include "stdio.h"
#include "time.h"
#include "stdlib.h"

int main() {
    srand(time(NULL));

    const int n = 4; // 10, 20
    const float min = -100; // 10^6
    const float max = +100; // 10^6

    float A[n][n];
    float x[n];

    float B[n];

    float suma = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = min + (float) rand() / RAND_MAX * (max - min);
        }
    }
    for (int i = 0; i < n; i++) {
        x[i] = min + (float) rand() / RAND_MAX * (max - min);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            suma += A[i][j] * x[j];
        }
        B[i] = suma;
        suma = 0;
    }




    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f | ", A[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        printf("| %f | \n", x[i]);
    }
    printf("Wynik ---------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%.14f | \n", B[i]);
    }
    return 0;
}

#pragma clang diagnostic pop