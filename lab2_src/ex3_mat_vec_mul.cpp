// Exercise 3 — Matrix-vector multiplication: u = C * t
// Equation (2): u_i = sum_{k=0}^{n-1} C_ik * t_k,  i=0..m-1
//
// Setup: t = v + w  (exercise 1),  C = A + B  (exercise 2, requires n == m)

#include <cassert>
#include "utils.h"

int main() {
    int m;
    // C is m x m (result of A+B where A,B are m x m), so one size is enough.
    std::cout << "Enter m: ";
    std::cin >> m;
    assert(m > 0);
    srand(static_cast<unsigned>(time(nullptr)));

    // Allocate vectors
    double* v = new double[m];
    double* w = new double[m];
    double* t = new double[m]();   // zero
    double* u = new double[m]();   // zero

    // Allocate matrices (A, B, C all m x m)
    double** A = allocMatrix(m, m);
    double** B = allocMatrix(m, m);
    double** C = allocMatrix(m, m);   // zero

    // Initialise
    for (int i = 0; i < m; i++) {
        v[i] = randDouble();
        w[i] = randDouble();
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++) {
            A[i][j] = randDouble();
            B[i][j] = randDouble();
        }

    // Print inputs
    std::cout << "\n--- Inputs ---\n";
    printVector("v", v, m);
    printVector("w", w, m);
    printMatrix("A", A, m, m);
    printMatrix("B", B, m, m);
    printVector("u (zero)", u, m);

    // Step 1: t = v + w
    for (int i = 0; i < m; i++)
        t[i] = v[i] + w[i];

    // Step 2: C = A + B
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            C[i][j] = A[i][j] + B[i][j];

    // Step 3: u = C * t  (C is m x m, t is m x 1)
    assert(m == m);   // columns of C must equal size of t
    for (int i = 0; i < m; i++) {
        u[i] = 0.0;
        for (int k = 0; k < m; k++)
            u[i] += C[i][k] * t[k];
    }

    // Print results
    std::cout << "\n--- Results ---\n";
    printVector("t = v + w", t, m);
    printMatrix("C = A + B", C, m, m);
    printVector("u = C * t", u, m);

    // De-allocate
    delete[] v;
    delete[] w;
    delete[] t;
    delete[] u;
    freeMatrix(A, m);
    freeMatrix(B, m);
    freeMatrix(C, m);

    return 0;
}
