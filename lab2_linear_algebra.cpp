#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <iomanip>

// ── memory helpers ──────────────────────────────────────────────────────────

double** allocMatrix(int rows, int cols) {
    double** M = new double*[rows];
    for (int i = 0; i < rows; i++)
        M[i] = new double[cols]();   // zero-initialised
    return M;
}

void freeMatrix(double** M, int rows) {
    for (int i = 0; i < rows; i++)
        delete[] M[i];
    delete[] M;
}

// ── random helper ───────────────────────────────────────────────────────────

double randDouble() {
    return (rand() % 200 - 100) / 10.0;   // range [-10, 10)
}

// ── print helpers ────────────────────────────────────────────────────────────

void printVector(const char* name, double* v, int m) {
    std::cout << name << " (size " << m << "):\n  [";
    for (int i = 0; i < m; i++)
        std::cout << std::setw(7) << std::fixed << std::setprecision(2)
                  << v[i] << (i < m - 1 ? "  " : "");
    std::cout << " ]\n";
}

void printMatrix(const char* name, double** A, int rows, int cols) {
    std::cout << name << " (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; i++) {
        std::cout << "  [";
        for (int j = 0; j < cols; j++)
            std::cout << std::setw(7) << std::fixed << std::setprecision(2)
                      << A[i][j] << (j < cols - 1 ? "  " : "");
        std::cout << " ]\n";
    }
}

// ── linear algebra operations ────────────────────────────────────────────────

// t = v + w  (equation 1, vectors)
void vecAdd(double* v, double* w, double* t, int m) {
    for (int i = 0; i < m; i++)
        t[i] = v[i] + w[i];
}

// C = A + B  (equation 1, matrices — same dimensions required)
void matAdd(double** A, int Arows, int Acols,
            double** B, int Brows, int Bcols,
            double** C) {
    assert(Arows == Brows && "matAdd: row mismatch");
    assert(Acols == Bcols && "matAdd: col mismatch");
    for (int i = 0; i < Arows; i++)
        for (int j = 0; j < Acols; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// u = A * v  (equation 2, matrix-vector — A is mxn, v is n)
void matVecMul(double** A, int m, int n, double* v, int vsize, double* u) {
    assert(n == vsize && "matVecMul: column/vector-size mismatch");
    for (int i = 0; i < m; i++) {
        u[i] = 0.0;
        for (int k = 0; k < n; k++)
            u[i] += A[i][k] * v[k];
    }
}

// E = A * B  (equation 3, matrix-matrix — A is mxl, B is lxn)
void matMul(double** A, int Am, int Al,
            double** B, int Bl, int Bn,
            double** E) {
    assert(Al == Bl && "matMul: inner dimension mismatch");
    for (int i = 0; i < Am; i++)
        for (int j = 0; j < Bn; j++) {
            E[i][j] = 0.0;
            for (int k = 0; k < Al; k++)
                E[i][j] += A[i][k] * B[k][j];
        }
}

// alpha = v · w  (equation 4)
double dotProduct(double* v, double* w, int m) {
    double alpha = 0.0;
    for (int i = 0; i < m; i++)
        alpha += v[i] * w[i];
    return alpha;
}

// ── main ─────────────────────────────────────────────────────────────────────

int main() {
    int m, n;
    std::cout << "Enter m: ";  std::cin >> m;
    std::cout << "Enter n: ";  std::cin >> n;

    assert(m > 0 && n > 0 && "m and n must be positive");

    srand(static_cast<unsigned>(time(nullptr)));

    // ── allocate ──────────────────────────────────────────────────────────
    // vectors
    double* v = new double[m];
    double* w = new double[m];
    double* t = new double[m]();   // zero-initialised
    double* u = new double[m]();   // zero-initialised

    // matrices
    double** A = allocMatrix(m, m);   // m x m
    double** B = allocMatrix(m, m);   // m x m
    double** C = allocMatrix(m, n);   // m x n  (= A+B, so n must equal m)
    double** D = allocMatrix(n, m);   // n x m
    double** E = allocMatrix(m, m);   // m x m  (= C * D)

    // ── initialise with random values ─────────────────────────────────────
    for (int i = 0; i < m; i++) {
        v[i] = randDouble();
        w[i] = randDouble();
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++) {
            A[i][j] = randDouble();
            B[i][j] = randDouble();
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            D[i][j] = randDouble();
    // t, u, C, E already zero-initialised via ()

    // ── print initial values ──────────────────────────────────────────────
    std::cout << "\n=== Initial values ===\n";
    printVector("v", v, m);
    printVector("w", w, m);
    printVector("t (zero)", t, m);
    printVector("u (zero)", u, m);
    printMatrix("A", A, m, m);
    printMatrix("B", B, m, m);
    printMatrix("C (zero)", C, m, n);
    printMatrix("D", D, n, m);
    printMatrix("E (zero)", E, m, m);

    // ── compute ───────────────────────────────────────────────────────────
    // t = v + w  (both R^m)
    vecAdd(v, w, t, m);

    // C = A + B  (A, B ∈ R^(m×m); C ∈ R^(m×n) → requires n == m)
    assert(n == m && "C = A+B requires n == m (A,B are m×m, C is m×n)");
    matAdd(A, m, m, B, m, m, C);

    // u = C * t  (C ∈ R^(m×n), t ∈ R^m → requires n == m, already asserted)
    matVecMul(C, m, n, t, m, u);

    // E = C * D  (C ∈ R^(m×n), D ∈ R^(n×m) → E ∈ R^(m×m))
    matMul(C, m, n, D, n, m, E);

    // alpha = v · u  (both R^m)
    double alpha = dotProduct(v, u, m);

    // ── print results ─────────────────────────────────────────────────────
    std::cout << "\n=== Results ===\n";
    printVector("t = v + w", t, m);
    printMatrix("C = A + B", C, m, n);
    printVector("u = C * t", u, m);
    printMatrix("E = C * D", E, m, m);
    std::cout << std::fixed << std::setprecision(6)
              << "alpha = v . u = " << alpha << "\n";

    // ── MATLAB verification snippet ───────────────────────────────────────
    std::cout << "\n=== MATLAB verification (copy-paste) ===\n";
    std::cout << "v = [";
    for (int i = 0; i < m; i++) std::cout << v[i] << (i<m-1?"; ":"");
    std::cout << "];\n";
    std::cout << "w = [";
    for (int i = 0; i < m; i++) std::cout << w[i] << (i<m-1?"; ":"");
    std::cout << "];\n";
    std::cout << "A = [";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) std::cout << A[i][j] << (j<m-1?" ":"");
        std::cout << (i<m-1?"; ":"");
    }
    std::cout << "];\n";
    std::cout << "B = [";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) std::cout << B[i][j] << (j<m-1?" ":"");
        std::cout << (i<m-1?"; ":"");
    }
    std::cout << "];\n";
    std::cout << "D = [";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) std::cout << D[i][j] << (j<m-1?" ":"");
        std::cout << (i<n-1?"; ":"");
    }
    std::cout << "];\n";
    std::cout << "t = v + w;\n";
    std::cout << "C = A + B;\n";
    std::cout << "u = C * t;\n";
    std::cout << "E = C * D;\n";
    std::cout << "alpha = dot(v, u);\n";
    std::cout << "disp(alpha)\n";

    // ── de-allocate ───────────────────────────────────────────────────────
    delete[] v;
    delete[] w;
    delete[] t;
    delete[] u;
    freeMatrix(A, m);
    freeMatrix(B, m);
    freeMatrix(C, m);
    freeMatrix(D, n);
    freeMatrix(E, m);

    return 0;
}
