// Exercise 1 — Vector addition: t = v + w
// Equation (1): t_i = v_i + w_i,  i = 0,...,m-1

#include <cassert>
#include "utils.h"

int main() {
    int m;
    std::cout << "Enter m: ";
    std::cin >> m;
    assert(m > 0);
    srand(static_cast<unsigned>(time(nullptr)));

    // Allocate
    double* v = new double[m];
    double* w = new double[m];
    double* t = new double[m]();   // zero

    // Initialise v, w with random values
    for (int i = 0; i < m; i++) {
        v[i] = randDouble();
        w[i] = randDouble();
    }

    // Print inputs
    std::cout << "\n--- Inputs ---\n";
    printVector("v", v, m);
    printVector("w", w, m);
    printVector("t (zero)", t, m);

    // Compute t = v + w
    assert(m == m);   // sizes must match (trivially true; shown for habit)
    for (int i = 0; i < m; i++)
        t[i] = v[i] + w[i];

    // Print result
    std::cout << "\n--- Result ---\n";
    printVector("t = v + w", t, m);

    // De-allocate
    delete[] v;
    delete[] w;
    delete[] t;

    return 0;
}
