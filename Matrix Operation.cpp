#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

// ============================================================
//                    MATRIX CLASS DEFINITION
// ============================================================
class Matrix {
private:
    int rows, cols;
    vector<vector<double> > data;

public:
    // ---------- Constructor ----------
    Matrix(int r, int c) {
        rows = r;
        cols = c;
        data.resize(rows, vector<double>(cols, 0.0));
    }

    // ---------- Default Constructor ----------
    Matrix() {
        rows = 0;
        cols = 0;
    }

    // ---------- Input Method ----------
    void input(string name) {
        cout << "Enter elements of Matrix " << name << ":" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "Element [" << i << "][" << j << "]: ";
                cin >> data[i][j];
            }
        }
    }

    // ---------- Display Method ----------
    void display(string name) {
        cout << name << ":" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << setw(8) << fixed << setprecision(2) << data[i][j] << "  ";
            }
            cout << endl;
        }
    }

    // ---------- Getter Methods ----------
    int getRows() { return rows; }
    int getCols() { return cols; }
    double getElement(int i, int j) { return data[i][j]; }
    void setElement(int i, int j, double value) { data[i][j] = value; }

    // ---------- Addition ----------
    Matrix add(Matrix &other) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // ---------- Subtraction ----------
    Matrix subtract(Matrix &other) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // ---------- Multiplication ----------
    Matrix multiply(Matrix &other) {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // ---------- Transpose ----------
    Matrix transpose() {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    // ---------- Get SubMatrix (for determinant/inverse) ----------
    Matrix getSubMatrix(int r, int c) {
        Matrix sub(rows - 1, cols - 1);
        int subi = 0;
        for (int i = 0; i < rows; i++) {
            if (i == r) continue;
            int subj = 0;
            for (int j = 0; j < cols; j++) {
                if (j == c) continue;
                sub.data[subi][subj] = data[i][j];
                subj++;
            }
            subi++;
        }
        return sub;
    }

    // ---------- Determinant (Recursive) ----------
    double determinant() {
        if (rows == 1 && cols == 1) {
            return data[0][0];
        }
        if (rows == 2 && cols == 2) {
            return (data[0][0] * data[1][1]) - (data[0][1] * data[1][0]);
        }

        double det = 0;
        int sign = 1;
        for (int j = 0; j < cols; j++) {
            Matrix sub = getSubMatrix(0, j);
            det += sign * data[0][j] * sub.determinant();
            sign = -sign;
        }
        return det;
    }

    // ---------- Cofactor ----------
    double cofactor(int i, int j) {
        Matrix sub = getSubMatrix(i, j);
        double sign = ((i + j) % 2 == 0) ? 1 : -1;
        return sign * sub.determinant();
    }

    // ---------- Adjoint ----------
    Matrix adjoint() {
        Matrix adj(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                adj.data[j][i] = cofactor(i, j);
            }
        }
        return adj;
    }

    // ---------- Inverse ----------
    Matrix inverse() {
        double det = determinant();
        if (det == 0) {
            cout << "\nERROR: Inverse does not exist (Determinant = 0)!" << endl;
            Matrix empty(0, 0);
            return empty;
        }
        Matrix adj = adjoint();
        Matrix inv(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                inv.data[i][j] = adj.data[i][j] / det;
            }
        }
        return inv;
    }
};

// ============================================================
//                    VALIDATION FUNCTIONS
// ============================================================
bool validateSameSize(Matrix &A, Matrix &B) {
    return (A.getRows() == B.getRows() && A.getCols() == B.getCols());
}

bool validateMultiplication(Matrix &A, Matrix &B) {
    return (A.getCols() == B.getRows());
}

bool validateSquare(Matrix &A) {
    return (A.getRows() == A.getCols());
}

// ============================================================
//                    DISPLAY MENU
// ============================================================
void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "       MATRIX OPERATION SYSTEM          " << endl;
    cout << "========================================" << endl;
    cout << "1. Add Matrices" << endl;
    cout << "2. Subtract Matrices" << endl;
    cout << "3. Multiply Matrices" << endl;
    cout << "4. Transpose Matrix" << endl;
    cout << "5. Determinant of Matrix" << endl;
    cout << "6. Inverse of Matrix" << endl;
    cout << "7. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice (1-7): ";
}

// ============================================================
//                    EXIT MESSAGE
// ============================================================
void displayExitMessage() {
    cout << "\n========================================" << endl;
    cout << "   Thank you for using Matrix Operation System!" << endl;
    cout << "              Exiting..." << endl;
    cout << "========================================" << endl;
}

// ============================================================
//                    MAIN FUNCTION
// ============================================================
int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {

        // ---------------- ADDITION ----------------
        case 1: {
            int r, c;
            cout << "\nEnter number of rows: ";
            cin >> r;
            cout << "Enter number of columns: ";
            cin >> c;

            Matrix A(r, c), B(r, c);
            A.input("A");
            cout << endl;
            B.input("B");

            if (!validateSameSize(A, B)) {
                cout << "\nERROR: Matrix dimensions must be equal for addition!" << endl;
                break;
            }

            Matrix C = A.add(B);
            cout << "\nMatrix A:" << endl;
            A.display("A");
            cout << endl;
            B.display("B");
            cout << "\nResult of Addition (A + B):" << endl;
            C.display("Result");
            break;
        }

        // ---------------- SUBTRACTION ----------------
        case 2: {
            int r, c;
            cout << "\nEnter number of rows: ";
            cin >> r;
            cout << "Enter number of columns: ";
            cin >> c;

            Matrix A(r, c), B(r, c);
            A.input("A");
            cout << endl;
            B.input("B");

            if (!validateSameSize(A, B)) {
                cout << "\nERROR: Matrix dimensions must be equal for subtraction!" << endl;
                break;
            }

            Matrix C = A.subtract(B);
            cout << "\nMatrix A:" << endl;
            A.display("A");
            cout << endl;
            B.display("B");
            cout << "\nResult of Subtraction (A - B):" << endl;
            C.display("Result");
            break;
        }

        // ---------------- MULTIPLICATION ----------------
        case 3: {
            int r1, c1, r2, c2;
            cout << "\nEnter number of rows of Matrix A: ";
            cin >> r1;
            cout << "Enter number of columns of Matrix A: ";
            cin >> c1;
            cout << "Enter number of rows of Matrix B: ";
            cin >> r2;
            cout << "Enter number of columns of Matrix B: ";
            cin >> c2;

            if (c1 != r2) {
                cout << "\nERROR: Matrix dimensions are not compatible for multiplication!" << endl;
                cout << "(A.columns must equal B.rows)" << endl;
                cout << "A.columns (" << c1 << ") != B.rows (" << r2 << ")" << endl;
                break;
            }

            Matrix A(r1, c1), B(r2, c2);
            A.input("A");
            cout << endl;
            B.input("B");

            Matrix C = A.multiply(B);
            cout << "\nMatrix A (" << r1 << "x" << c1 << "):" << endl;
            A.display("A");
            cout << endl;
            B.display("B");
            cout << "\nResult of Multiplication (A * B):" << endl;
            C.display("Result");
            break;
        }

        // ---------------- TRANSPOSE ----------------
        case 4: {
            int r, c;
            cout << "\nEnter number of rows: ";
            cin >> r;
            cout << "Enter number of columns: ";
            cin >> c;

            Matrix A(r, c);
            A.input("A");

            cout << "\nOriginal Matrix:" << endl;
            A.display("A");

            Matrix T = A.transpose();
            cout << "\nTranspose of Matrix:" << endl;
            T.display("Transpose");
            break;
        }

        // ---------------- DETERMINANT ----------------
        case 5: {
            int n;
            cout << "\nEnter size of matrix (n x n): ";
            cin >> n;

            Matrix A(n, n);
            A.input("A");

            if (!validateSquare(A)) {
                cout << "\nERROR: Determinant only defined for square matrices!" << endl;
                break;
            }

            cout << "\nMatrix A:" << endl;
            A.display("A");

            double det = A.determinant();
            cout << "\nDeterminant = " << det << endl;
            break;
        }

        // ---------------- INVERSE ----------------
        case 6: {
            int n;
            cout << "\nEnter size of matrix (n x n): ";
            cin >> n;

            Matrix A(n, n);
            A.input("A");

            if (!validateSquare(A)) {
                cout << "\nERROR: Inverse only defined for square matrices!" << endl;
                break;
            }

            cout << "\nMatrix A:" << endl;
            A.display("A");

            double det = A.determinant();
            cout << "\nDeterminant = " << det << endl;

            if (det == 0) {
                cout << "\nERROR: Inverse does not exist (Determinant = 0)!" << endl;
                break;
            }

            Matrix inv = A.inverse();
            cout << "\nInverse of Matrix:" << endl;
            inv.display("Inverse");
            break;
        }

        // ---------------- EXIT ----------------
        case 7:
            displayExitMessage();
            break;

        // ---------------- INVALID ----------------
        default:
            cout << "\nInvalid choice! Please enter a number between 1 and 7." << endl;
        }

    } while (choice != 7);

    return 0;
}
