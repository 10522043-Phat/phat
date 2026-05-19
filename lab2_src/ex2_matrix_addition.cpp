// Exercise 2 — Matrix addition: C = A + B
// Equation (1): c_ij = a_ij + b_ij,  i=0..m-1, j=0..n-1

#include <cassert>
#include "utils.h"

int main() {
    int m, n;
    std::cout << "Enter m: ";  std::cin >> m;
    std::cout << "Enter n: ";  std::cin >> n;
    assert(m > 0 && n > 0);
    srand(static_cast<unsigned>(time(nullptr)));

    // Allocate
    double** A = allocMatrix(m, n);
    double** B = allocMatrix(m, n);
    double** C = allocMatrix(m, n);   // zero

    // Initialise A, B with random values
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = randDouble();
            B[i][j] = randDouble();
        }

    // Print inputs
    std::cout << "\n--- Inputs ---\n";
    printMatrix("A", A, m, n);
    printMatrix("B", B, m, n);
    printMatrix("C (zero)", C, m, n);

    // Compute C = A + B  (sizes must match)
    assert(m == m && n == n);   // A, B, C all m x n — shown for habit
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];

    // Print result
    std::cout << "\n--- Result ---\n";
    printMatrix("C = A + B", C, m, n);

    // De-allocate
    freeMatrix(A, m);
    freeMatrix(B, m);
    freeMatrix(C, m);

    return 0;
}
