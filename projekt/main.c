#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include "stdio.h"
#include "time.h"
#include "stdlib.h"

int main() {
    srand(time(NULL));

    const int c = 3;

    float A[c][c];
    float x[c];
    float B[c];

    float suma = 0;

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < c; j++) {
            //A[i][j] = ((rand() % 200) - 100) / 10000.f;
            A[i][j] = -100 + (float) rand() / RAND_MAX * (100 - -100);
        }
    }
    for (int i = 0; i < c; i++) {
        x[i] = -100 + (float) rand() / RAND_MAX * (100 - -100);
        //x[i] = (rand() % 200) - 100;
    }

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < c; j++) {
            suma += A[i][j] * x[j];
        }
        B[i] = suma;
        suma = 0;
    }




    for (int i = 0; i < c; i++) {
        for (int j = 0; j < c; j++) {
            printf("%f | ", A[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < c; i++) {
        printf("| %f | \n", x[i]);
    }
    printf("Wynik ---------------------\n");
    for (int i = 0; i < c; i++) {
        printf("%.14f | \n", B[i]);
    }
    return 0;
}
