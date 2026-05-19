// Exercise 4 — Matrix-matrix multiplication: E = C * D
// Equation (3): e_ij = sum_{k=0}^{m-1} C_ik * D_kj,  i=0..m-1, j=0..m-1
//
// C in R^(m x m)  (from A+B),  D in R^(n x m),  E in R^(m x m)
// Multiplication C*D is valid when cols(C) == rows(D), i.e. m == n.

#include <cassert>
#include "utils.h"

int main() {
    int m, n;
    std::cout << "Enter m: ";  std::cin >> m;
    std::cout << "Enter n: ";  std::cin >> n;
    assert(m > 0 && n > 0);
    // For C*D to be valid: cols(C)==rows(D) → m == n
    assert(m == n && "E = C*D requires n == m (cols of C must equal rows of D)");
    srand(static_cast<unsigned>(time(nullptr)));

    // Allocate
    double** A = allocMatrix(m, m);
    double** B = allocMatrix(m, m);
    double** C = allocMatrix(m, m);   // zero  (will be A+B)
    double** D = allocMatrix(n, m);
    double** E = allocMatrix(m, m);   // zero

    // Initialise A, B, D with random values
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++) {
            A[i][j] = randDouble();
            B[i][j] = randDouble();
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            D[i][j] = randDouble();

    // Print inputs
    std::cout << "\n--- Inputs ---\n";
    printMatrix("A", A, m, m);
    printMatrix("B", B, m, m);
    printMatrix("C (zero)", C, m, m);
    printMatrix("D", D, n, m);
    printMatrix("E (zero)", E, m, m);

    // Step 1: C = A + B
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            C[i][j] = A[i][j] + B[i][j];

    // Step 2: E = C * D  (C is m x m, D is n x m → need m == n)
    assert(m == n);   // inner dimensions must match
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++) {
            E[i][j] = 0.0;
            for (int k = 0; k < m; k++)
                E[i][j] += C[i][k] * D[k][j];
        }

    // Print results
    std::cout << "\n--- Results ---\n";
    printMatrix("C = A + B", C, m, m);
    printMatrix("E = C * D", E, m, m);

    // De-allocate
    freeMatrix(A, m);
    freeMatrix(B, m);
    freeMatrix(C, m);
    freeMatrix(D, n);
    freeMatrix(E, m);

    return 0;
}
