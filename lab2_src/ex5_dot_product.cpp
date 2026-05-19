// Exercise 5 — Dot product: alpha = v · u
// Equation (4): alpha = sum_{i=0}^{m-1} v_i * u_i
//
// Full chain: t = v+w, C = A+B, u = C*t, then alpha = v · u

#include <cassert>
#include <iomanip>
#include "utils.h"

int main() {
    int m;
    std::cout << "Enter m: ";
    std::cin >> m;
    assert(m > 0);
    srand(static_cast<unsigned>(time(nullptr)));

    // Allocate vectors
    double* v = new double[m];
    double* w = new double[m];
    double* t = new double[m]();   // zero
    double* u = new double[m]();   // zero

    // Allocate matrices (A, B, C all m x m; D is m x m since n == m required)
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

    // Step 1: t = v + w
    for (int i = 0; i < m; i++)
        t[i] = v[i] + w[i];

    // Step 2: C = A + B
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            C[i][j] = A[i][j] + B[i][j];

    // Step 3: u = C * t
    assert(m == m);
    for (int i = 0; i < m; i++) {
        u[i] = 0.0;
        for (int k = 0; k < m; k++)
            u[i] += C[i][k] * t[k];
    }

    // Step 4: alpha = v · u  (both size m)
    assert(m == m);
    double alpha = 0.0;
    for (int i = 0; i < m; i++)
        alpha += v[i] * u[i];

    // Print results
    std::cout << "\n--- Intermediate Results ---\n";
    printVector("t = v + w", t, m);
    printMatrix("C = A + B", C, m, m);
    printVector("u = C * t", u, m);
    std::cout << "\n--- Final Result ---\n";
    std::cout << std::fixed << std::setprecision(6)
              << "alpha = v . u = " << alpha << "\n";

    // MATLAB verification snippet
    std::cout << "\n--- MATLAB verification ---\n";
    std::cout << "v=["; for(int i=0;i<m;i++) std::cout<<v[i]<<(i<m-1?";":""); std::cout<<"];\n";
    std::cout << "w=["; for(int i=0;i<m;i++) std::cout<<w[i]<<(i<m-1?";":""); std::cout<<"];\n";
    std::cout << "A=[";
    for(int i=0;i<m;i++){for(int j=0;j<m;j++) std::cout<<A[i][j]<<(j<m-1?" ":""); std::cout<<(i<m-1?";":"");}
    std::cout<<"];\n";
    std::cout << "B=[";
    for(int i=0;i<m;i++){for(int j=0;j<m;j++) std::cout<<B[i][j]<<(j<m-1?" ":""); std::cout<<(i<m-1?";":"");}
    std::cout<<"];\n";
    std::cout << "t=v+w; C=A+B; u=C*t; alpha=dot(v,u); disp(alpha)\n";

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
