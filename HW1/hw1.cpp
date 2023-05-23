#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int MATRIX_SIZE = 4;

//印出矩陣
void printMatrix(int* matrix[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "------------------------------" << endl;
}

// 複製矩陣內容
void copyMatrix(int* src[MATRIX_SIZE], int* dest[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            dest[i][j] = src[i][j];
        }
    }
}

// 查找最大值和最小值
void findMinMaxValues(int* matrix[MATRIX_SIZE]) {
    int minVal = matrix[0][0];
    int maxVal = matrix[0][0];
    pair<int, int> minIdx = {0, 0};
    pair<int, int> maxIdx = {0, 0};

    // 查找最大值和最小值以及它們的索引
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
                minIdx = {i, j};
            }
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
                maxIdx = {i, j};
            }
        }
    }

    // 輸出最大值和最小值及其索引
    cout << "Minimum value: " << minVal << " at index (" << minIdx.first << ", " << minIdx.second << ")" << endl;
    cout << "Maximum value: " << maxVal << " at index (" << maxIdx.first << ", " << maxIdx.second << ")" << endl;
    cout << "------------------------------" << endl;
}

// 轉置矩陣
void transposeMatrix(int* matrix[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = i + 1; j < MATRIX_SIZE; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

// 順時針轉90度
void rotateMatrix(int* matrix[MATRIX_SIZE]) {
    int** temp = new int*[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        temp[i] = new int[MATRIX_SIZE];
    }

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            temp[j][MATRIX_SIZE - 1 - i] = matrix[i][j];
        }
    }

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = temp[i][j];
        }
    }

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        delete[] temp[i];
    }
    delete[] temp;
}

// Get Row
vector<int> GetRow(int* matrix[MATRIX_SIZE], int rowIndex) {
    vector<int> row(MATRIX_SIZE);
    for (int j = 0; j < MATRIX_SIZE; ++j) {
        row[j] = matrix[rowIndex][j];
    }
    return row;
}

// 印出row
void printRow(const vector<int>& row) {
    for (int value : row) {
        cout << value << " ";
    }
    cout << endl;
    cout << "------------------------------" << endl;
}

// Get Column
vector<int> GetColumn(int* matrix[MATRIX_SIZE], int colIndex) {
    vector<int> column(MATRIX_SIZE);
    for (int j = 0; j < MATRIX_SIZE; ++j) {
        column[j] = matrix[j][colIndex];
    }
    return column;
}

// 印出Column
void printCol(const vector<int>& column) {
    for (int value : column) {
        cout << value << " ";
    }
    cout << endl;
    cout << "------------------------------" << endl;
}

// Get Diagonal
vector<int> GetDiagonal(int* matrix[MATRIX_SIZE]) {
    vector<int> diagonal(MATRIX_SIZE);
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        diagonal[i] = matrix[i][i];
    }
    return diagonal;
}

// 印出 Diagonal
void printDia(const vector<int>& diagonal) {
    for (int value : diagonal) {
        cout << value << " ";
    }
    cout << endl;
    cout << "------------------------------" << endl;
}

// Get Inverse Diagonal
vector<int> GetInverseDiagonal(int* matrix[MATRIX_SIZE]) {
    vector<int> inverse_diagonal(MATRIX_SIZE);
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        inverse_diagonal[i] = matrix[i][MATRIX_SIZE-i-1];
    }
    return inverse_diagonal;
}

// 印出 Inverse Diagonal
void printInvD(const vector<int>& invdiagonal) {
    for (int value : invdiagonal) {
        cout << value << " ";
    }
    cout << endl;
    cout << "------------------------------" << endl;
}

// 3*3determinant
int determinant3x3(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
    return a * e * i + b * f * g + c * d * h - c * e * g - b * d * i - a * f * h;
}

// 4*4determinant
int determinant(int* matrix[MATRIX_SIZE]) {
    int result = 0; //初始化result
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        int sign = (i % 2 == 0) ? 1 : -1; //使用變數 sign 記錄當前代數余子式的符號，當列的編號為偶數時，sign為1，否則為-1
        int sub_determinant = determinant3x3(
            matrix[1][(i + 1) % MATRIX_SIZE], matrix[1][(i + 2) % MATRIX_SIZE], matrix[1][(i + 3) % MATRIX_SIZE],
            matrix[2][(i + 1) % MATRIX_SIZE], matrix[2][(i + 2) % MATRIX_SIZE], matrix[2][(i + 3) % MATRIX_SIZE],
            matrix[3][(i + 1) % MATRIX_SIZE], matrix[3][(i + 2) % MATRIX_SIZE], matrix[3][(i + 3) % MATRIX_SIZE]
        );  //呼叫 determinant3x3 函數計算當前代數余子式的值，並儲存在變數 sub_determinant 中。
        result += sign * matrix[0][i] * sub_determinant; //用展開定理
    }
    return result;
}

// 計算cofactor matrix
void getCofactor(int* matrix[MATRIX_SIZE], int* temp[MATRIX_SIZE], int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// 計算逆矩陣
bool inverseMatrix(int* matrix[MATRIX_SIZE], double* inverse[MATRIX_SIZE]) {
    int det = determinant(matrix);
    if (det == 0) {
        cout << "This matrix is singular, cannot find its inverse." << endl;
        return false;
    }
    int** temp = new int*[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        temp[i] = new int[MATRIX_SIZE];
    }

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            getCofactor(matrix, temp, i, j, MATRIX_SIZE);
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            inverse[j][i] = (double)(sign * determinant(temp)) / (double)det;
        }
    }

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        delete[] temp[i];
    }
    delete[] temp;

    return true;
}

// 印出逆矩陣
void printInverseMatrix(double* inverse[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            cout << inverse[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------------------------" << endl;
}

int main() {
    // 動態分配二維陣列
    int** matrix = new int*[MATRIX_SIZE];
    int** transpose = new int*[MATRIX_SIZE];
    int** rotate = new int*[MATRIX_SIZE];
    double** inverse = new double*[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        matrix[i] = new int[MATRIX_SIZE];
        transpose[i] = new int[MATRIX_SIZE];
        rotate[i] = new int[MATRIX_SIZE];
        inverse[i] = new double[MATRIX_SIZE];
    }

    

    // 填充隨機數據
    srand(time(0));
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }

    cout << "matrix:" << endl;
    printMatrix(matrix);

    // 印出最大最小值及index
    findMinMaxValues(matrix);

    //印出transpose
    copyMatrix(matrix, transpose); //使matrix的值先複製到transpose
    transposeMatrix(transpose);
    cout << "traspose:" << endl;
    printMatrix(transpose);

    //印出Rot90
    copyMatrix(matrix, rotate); //使matrix的值先複製到rotate
    rotateMatrix(rotate);
    cout << "Rot90:" << endl;
    printMatrix(rotate);
    
    // 印出ROW
    int rowIndex = 1; // 以第1行為例（從0開始計數）
    vector<int> row = GetRow(matrix, rowIndex);
    cout << "NO. " << rowIndex << " row:" << endl;
    printRow(row);

    // 印出COLUMN
    int colIndex = 2; // 以第1列為例（從0開始計數）
    vector<int> col = GetColumn(matrix, colIndex);
    cout << "NO. " << colIndex << " column:" << endl;
    printCol(col);

    // 印出DIAGONAL
    vector<int> dia = GetDiagonal(matrix);
    cout << "diagonal:" << endl;
    printDia(dia);
    
    // 印出Inverse DIAGONAL
    vector<int> invdia = GetInverseDiagonal(matrix);
    cout << "inverse diagonal:" << endl;
    printInvD(invdia);

    // 印出determinant
    int det = determinant(matrix);
    cout << "determinant: " << det << std::endl;
    cout << "------------------------------" << endl;

    // 印出inverse matrix
    if (inverseMatrix(matrix, inverse)) {
        cout << "Inverse matrix:" << endl;
        printInverseMatrix(inverse);
    }

    // 釋放記憶體
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        delete[] matrix[i];
        delete[] transpose[i];
        delete[] rotate[i];
        delete[] inverse[i];
    }
    delete[] matrix;
    delete[] transpose;
    delete[] rotate;
    delete[] inverse;

    return 0;
}
