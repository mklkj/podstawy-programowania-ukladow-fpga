#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"

#define N 20
const float MIN = -1000000;
const float MAX = +1000000;
const double EPS = 0.0000000001; // dokładność porównania z zerem

void generate_matrix_values(double AB[N][N + 1], double x[N], int WK[N]);

void solve(double AB[N][N + 1], double x_solved[N], int WK[N]);

void check_result(const double x_original[N], const double x_solved[N]);

int main() {
    srand(time(NULL));

    double AB[N][N + 1];
    double x[N];
    int WK[N + 1];

    double x_solved[N];

    generate_matrix_values(AB, x, WK);
    solve(AB, x_solved, WK);
    check_result(x, x_solved);

    return 0;
}

void generate_matrix_values(double AB[N][N + 1], double x[N], int WK[N]) {
    int i, j;

    // AB
    printf("Macierz A\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            AB[i][j] = MIN + (float) rand() / (float) RAND_MAX * (MAX - MIN);
            printf("| %5f |", AB[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // WK
    for (i = 0; i < N + 1; ++i) {
        WK[i] = i;
    }

    // x
    printf("Wektor X (oryginalny)\n");
    for (i = 0; i < N; i++) {
        x[i] = MIN + (float) rand() / (float) RAND_MAX * (MAX - MIN);
        printf("%5f \n", x[i]);
    }
    printf("\n");

    // B
    printf("Wektor B (obliczony)\n");
    double B[N];
    double suma = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            suma += AB[i][j] * x[j];
        }
        B[i] = suma;
        printf("%5f\n", B[i]);
        suma = 0;
    }
    printf("\n");

    // AB
    for (i = 0; i < N + 1; ++i) {
        AB[i][N] = B[i];
    }
}

bool GCEliminujX(int n, double AB[][N + 1], int WK[]) {
    int i, j, k, tmp;
    double m;

    for (i = 0; i < n - 1; i++) {
        for (k = i, j = i + 1; j < n; j++)
            if (fabs(AB[i][WK[k]]) < fabs(AB[i][WK[j]])) k = j;
        tmp = WK[k];
        WK[k] = WK[i];
        WK[i] = tmp;
        if (fabs(AB[i][WK[i]]) < EPS) return false;
        for (j = i + 1; j < n; j++) {
            m = -AB[j][WK[i]] / AB[i][WK[i]];
            for (k = i + 1; k <= n; k++) {
                AB[j][WK[k]] += m * AB[i][WK[k]];
            }
        }
    }
    return true;
}

bool GCObliczX(int n, double X[], double AB[][N + 1], const int WK[]) {
    int i, j;
    double s;

    for (i = n - 1; i >= 0; i--) {
        if (fabs(AB[i][WK[i]]) < EPS) return false;
        s = AB[i][n];
        for (j = n - 1; j > i; j--) {
            s -= AB[i][WK[j]] * X[WK[j]];
        }
        X[WK[i]] = s / AB[i][WK[i]];
    }
    return true;
}

void solve(double AB[N][N + 1], double x_solved[N], int WK[N]) {
    GCEliminujX(N, AB, WK) && GCObliczX(N, x_solved, AB, WK);
}

void check_result(const double x_original[N], const double x_solved[N]) {
    int i;

    printf("Wektor X' (obliczony)\n");
    for (i = 0; i < N; i++) {
        printf("%5f \n", x_solved[i]);
    }
    printf("\n");

    printf("Porownanie\n");
    for (i = 0; i < N; ++i) {
        printf("%3e\n", x_original[i] - x_solved[i]);
    }
}

#pragma clang diagnostic pop
