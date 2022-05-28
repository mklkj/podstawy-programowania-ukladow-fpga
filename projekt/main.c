#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include "stdio.h"
#include "time.h"
#include "stdlib.h"

const int n = 4; // 10, 20
const float min = -100; // 10^6
const float max = +100; // 10^6

void generate_matrix_values(float A[n][n], float x[n], float B[n]);

void print_result(float A[n][n], float x[n], float B[n]);

void solve(float A[n][n], float B[n], float x_solved[n]);

void check_result(float x_original[n], float x_solved[n]);

int main() {
    srand(time(NULL));

    float A[n][n];
    float x[n];
    float B[n];

    float x_solved[n];

    generate_matrix_values(A, x, B);
    solve(A, B, x_solved);
    check_result(x, x_solved);
    print_result(A, x, B);

    return 0;
}

void generate_matrix_values(float A[n][n], float x[n], float B[n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = min + (float) rand() / RAND_MAX * (max - min);
        }
    }

    for (int i = 0; i < n; i++) {
        x[i] = min + (float) rand() / RAND_MAX * (max - min);
    }

    float suma = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            suma += A[i][j] * x[j];
        }
        B[i] = suma;
        suma = 0;
    }
}

void solve(float A[n][n], float B[n], float x_solved[n]) {
    // metoda gaussa z wyborem elementu głównego
    // todo
}

void check_result(float x_original[n], float x_solved[n]) {
    // todo
}

void print_result(float A[n][n], float x[n], float B[n]) {
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
}

#pragma clang diagnostic pop
