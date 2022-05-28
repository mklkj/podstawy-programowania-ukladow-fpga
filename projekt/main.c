#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"

#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"

const int N = 4; // 10, 20
const float MIN = -100; // -10^6
const float MAX = +100; // +10^6
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
    // AB
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            AB[i][j] = MIN + (float) rand() / (float) RAND_MAX * (MAX - MIN);
        }
    }

    // WK
    for (int i = 0; i < N + 1; ++i) {
        WK[i] = i;
    }

    // x
    for (int i = 0; i < N; i++) {
        x[i] = MIN + (float) rand() / (float) RAND_MAX * (MAX - MIN);
    }

    // B
    double B[N];
    double suma = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            suma += AB[i][j] * x[j];
        }
        B[i] = suma;
        suma = 0;
    }

    // AB
    for (int i = 0; i < N + 1; ++i) {
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
        for (j = n - 1; j > i; j--) s -= AB[i][WK[j]] * X[WK[j]];
        X[WK[i]] = s / AB[i][WK[i]];
    }
    return true;
}

void solve(double AB[N][N + 1], double x_solved[N], int WK[N]) {
    if (GCEliminujX(N, AB, WK) && GCObliczX(N, x_solved, AB, WK)) {
        printf("Solving succssed!\n");
    } else printf("Solving failed\n");
}

void check_result(const double x_original[N], const double x_solved[N]) {
    for (int i = 0; i < N; ++i) {
        if (x_original[i] == x_solved[i]) {
            printf("Position %d match - o: %f, s: %f\n", i, x_original[i], x_solved[i]);
        } else printf("Position %d not match! - o: %f, s: %f\n", i, x_original[i], x_solved[i]);
    }
}

#pragma clang diagnostic pop
