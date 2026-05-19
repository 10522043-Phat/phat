#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// ── memory ───────────────────────────────────────────────────────────────────

inline double** allocMatrix(int rows, int cols) {
    double** M = new double*[rows];
    for (int i = 0; i < rows; i++)
        M[i] = new double[cols]();
    return M;
}

inline void freeMatrix(double** M, int rows) {
    for (int i = 0; i < rows; i++)
        delete[] M[i];
    delete[] M;
}

// ── random ───────────────────────────────────────────────────────────────────

inline double randDouble() {
    return (rand() % 200 - 100) / 10.0;   // [-10, 10)
}

// ── print ────────────────────────────────────────────────────────────────────

inline void printVector(const char* name, double* v, int m) {
    std::cout << name << " (size " << m << "):\n  [";
    for (int i = 0; i < m; i++)
        std::cout << std::setw(7) << std::fixed << std::setprecision(2)
                  << v[i] << (i < m - 1 ? "  " : "");
    std::cout << " ]\n";
}

inline void printMatrix(const char* name, double** A, int rows, int cols) {
    std::cout << name << " (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; i++) {
        std::cout << "  [";
        for (int j = 0; j < cols; j++)
            std::cout << std::setw(7) << std::fixed << std::setprecision(2)
                      << A[i][j] << (j < cols - 1 ? "  " : "");
        std::cout << " ]\n";
    }
}
