#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../../data_structures/matrix/matrix.h"

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    if (values == NULL) {
        fprintf(stderr, "bad alloc\n");
        exit(1);
    }
    for (int i = 0; i < nRows; i++) {
        values[i] = (int *) malloc(sizeof(int) * nCols);
        if (values[i] == NULL) {
            fprintf(stderr, "bad alloc\n");
            exit(1);
        }
    }

    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    if (ms == NULL) {
        fprintf(stderr, "bad alloc\n");
        exit(1);
    }
    for (int i = 0; i < nMatrices; i++) {
        ms[i] = getMemMatrix(nRows, nCols);
    }

    return ms;
}

void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }
    free(m->values);
    m->nRows = 0;
    m->nCols = 0;
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
    free(ms);
}

void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            scanf("%d", &m->values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(&ms[i]);
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d\t", m.values[i][j]);
        }
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
        printf("\n");
    }
}

void swapRows(matrix m, int i1, int i2) {
    assert((i1 >= 0 && i1 < m.nRows) && "i1 out of bounds");
    assert((i2 >= 0 && i2 < m.nRows) && "i2 out of bounds");

    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}

void swapColumns(matrix m, int j1, int j2) {
    assert((j1 >= 0 && j1 < m.nCols) && "j1 out of bound");
    assert((j2 >= 0 && j2 < m.nCols) && "j2 out of bounds");

    int temp;
    for (int i = 0; i < m.nRows; i++) {
        temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int *criteriaValues = (int *) malloc(sizeof(int) * m.nRows);
    if (criteriaValues == NULL) {
        fprintf(stderr, "bad alloc\n");
        exit(1);
    }
    for (int i = 0; i < m.nRows; i++) {
        criteriaValues[i] = criteria(m.values[i], m.nCols);
    }
    for (int i = 1; i < m.nRows; i++) {
        int key = criteriaValues[i];
        int *tempRow = m.values[i];
        int j = i - 1;
        while (j >= 0 && criteriaValues[j] > key) {
            criteriaValues[j + 1] = criteriaValues[j];
            m.values[j + 1] = m.values[j];
            j = j - 1;
        }
        criteriaValues[j + 1] = key;
        m.values[j + 1] = tempRow;
    }
    free(criteriaValues);
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int *criteriaValues = (int *) malloc(sizeof(int) * m.nCols);
    if (criteriaValues == NULL) {
        fprintf(stderr, "bad alloc\n");
        exit(1);
    }
    for (int j = 0; j < m.nCols; j++) {
        int *col = (int *) malloc(sizeof(int) * m.nRows);
        if (col == NULL) {
            fprintf(stderr, "bad alloc\n");
            exit(1);
        }
        for (int i = 0; i < m.nRows; i++) {
            col[i] = m.values[i][j];
        }
        criteriaValues[j] = criteria(col, m.nRows);
        free(col);
    }
    for (int i = 0; i < m.nCols - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < m.nCols; j++) {
            if (criteriaValues[j] < criteriaValues[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            for (int k = 0; k < m.nRows; k++) {
                int temp = m.values[k][i];
                m.values[k][i] = m.values[k][minIndex];
                m.values[k][minIndex] = temp;
            }
            int tempCriteria = criteriaValues[i];
            criteriaValues[i] = criteriaValues[minIndex];
            criteriaValues[minIndex] = tempCriteria;
        }
    }

    free(criteriaValues);
}

bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols) {
        return 0;
    }
    size_t dataSize = sizeof(int) * m1->nRows * m1->nCols;

    return memcmp(m1->values[0], m2->values[0], dataSize) == 0;
}

bool isEMatrix(matrix *m) {
    if (!isSquareMatrix(m)) {
        return 0;
    }
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (i == j) {
                if (m->values[i][j] != 1) {
                    return 0;
                }
            } else {
                if (m->values[i][j] != 0) {
                    return 0;
                }
            }
        }
    }

    return 1;
}

bool isSymmetricMatrix(matrix *m) {
    if (!isSquareMatrix(m)) {
        return 0;
    }
    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return 0;
            }
        }
    }

    return 1;
}

void transposeSquareMatrix(matrix *m) {
    if (!isSquareMatrix(m)) {
        fprintf(stderr, "not square matrix\n");
        return;
    }
    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            int temp = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = temp;
        }
    }
}

void transposeMatrix(matrix *m) {
    matrix transposed;
    transposed.nRows = m->nCols;
    transposed.nCols = m->nRows;
    transposed.values = (int **) malloc(sizeof(int *) * transposed.nRows);
    if (transposed.values == NULL) {
        fprintf(stderr, "bad alloc\n");
        return;
    }
    for (int i = 0; i < transposed.nRows; i++) {
        transposed.values[i] = (int *) malloc(sizeof(int) * transposed.nCols);
        if (transposed.values[i] == NULL) {
            fprintf(stderr, "bad alloc\n");
            for (int j = 0; j < i; j++) {
                free(transposed.values[j]);
            }
            free(transposed.values);
            return;
        }
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            transposed.values[j][i] = m->values[i][j];
        }
    }

    for (int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }
    free(m->values);

    m->nRows = transposed.nRows;
    m->nCols = transposed.nCols;
    m->values = transposed.values;
}

position getMinValuePos(matrix m) {
    int minValue = m.values[0][0];
    position minPos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < minValue) {
                minValue = m.values[i][j];
                minPos.rowIndex = i;
                minPos.colIndex = j;
            }
        }
    }

    return minPos;
}

position getMaxValuePos(matrix m) {
    int maxValue = m.values[0][0];
    position maxPos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > maxValue) {
                maxValue = m.values[i][j];
                maxPos.rowIndex = i;
                maxPos.colIndex = j;
            }
        }
    }

    return maxPos;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m.values[i][j] = a[k++];
        }
    }

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (size_t k = 0; k < nMatrices; k++) {
        for (size_t i = 0; i < nRows; i++) {
            for (size_t j = 0; j < nCols; j++) {
                ms[k].values[i][j] = values[l++];
            }
        }
    }

    return ms;
}

void swapRowsWithMinMax(matrix m) {
    position minPos = getMinValuePos(m);
    position maxPos = getMaxValuePos(m);
    swapRows(m, minPos.rowIndex, maxPos.rowIndex);
}

int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }

    return max;
}

int getMin(int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
    }

    return min;
}

void sortRowsByMaxElement(matrix m) {
    int *maxValues = (int *)malloc(m.nRows * sizeof(int));
    for (int i = 0; i < m.nRows; i++) {
        maxValues[i] = getMax(m.values[i], m.nCols);
    }

    for (int i = 0; i < m.nRows - 1; i++) {
        for (int j = 0; j < m.nRows - i - 1; j++) {
            if (maxValues[j] > maxValues[j + 1]) {
                swapRows(m, j, j + 1);
                int temp = maxValues[j];
                maxValues[j] = maxValues[j + 1];
                maxValues[j + 1] = temp;
            }
        }
    }

    free(maxValues);
}

void sortColsByMinElement(matrix m) {
    int *minValues = (int *)malloc(m.nCols * sizeof(int));
    for (int j = 0; j < m.nCols; j++) {
        int *col = (int *)malloc(m.nRows * sizeof(int));
        for (int i = 0; i < m.nRows; i++) {
            col[i] = m.values[i][j];
        }
        minValues[j] = getMin(col, m.nRows);
        free(col);
    }

    for (int j = 0; j < m.nCols - 1; j++) {
        for (int k = 0; k < m.nCols - j - 1; k++) {
            if (minValues[k] > minValues[k + 1]) {
                swapColumns(m, k, k + 1);
                int temp = minValues[k];
                minValues[k] = minValues[k + 1];
                minValues[k + 1] = temp;
            }
        }
    }

    free(minValues);
}

matrix mulMatrices(matrix m1, matrix m2) {
    assert(m1.nCols == m2.nRows);

    matrix result = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            result.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }

    return result;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (!isSymmetricMatrix(m)) {
        fprintf(stderr, "matrix is not symmetric\n");
        return;
    }

    matrix squaredMatrix = mulMatrices(*m, *m);

    freeMemMatrix(m);

    *m = squaredMatrix;
}

bool isUnique(long long *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                return 0;
            }
        }
    }

    return 1;
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix *m) {
    int n = m->nRows;
    long long rowSums[n];
    for (int i = 0; i < n; i++) {
        rowSums[i] = getSum(m->values[i], m->nCols);
    }

    if (isUnique(rowSums, n)) {
        transposeMatrix(m);
    }
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    matrix product = mulMatrices(m1, m2);

    bool result = isEMatrix(&product);

    freeMemMatrix(&product);

    return result;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a > b ? b : a;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int rows = m.nRows;
    int cols = m.nCols;

    int maxValues[rows + cols - 2];
    for (int i = 0; i < rows + cols - 2; i++) {
        maxValues[i] = INT_MIN;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            int diagIndex = i - j + cols - 1;
            maxValues[diagIndex] = max(maxValues[diagIndex], m.values[i][j]);
        }
    }

    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < i; j++) {
            int diagIndex = rows - 1 + j - i;
            maxValues[diagIndex] = max(maxValues[diagIndex], m.values[i][j]);
        }
    }

    long long sum = 0;
    for (int i = 0; i < rows + cols - 2; i++) {
        sum += maxValues[i];
    }

    return sum;
}

int getMinInArea(matrix m) {
    position maxPos = getMaxValuePos(m);
    int row = maxPos.rowIndex;
    int col = maxPos.colIndex;

    int minVal = m.values[row][col];

    for (int i = row - 1, j_left = col - 1, j_right = col + 1; i >= 0; i--, j_left--, j_right++) {
        if (j_left < 0) {
            j_left = 0;
        }
        if (j_right >= m.nCols) {
            j_right = m.nCols;
        }
        for (int n = j_left; n < j_right; n++) {
            minVal = min(m.values[i][n], minVal);
        }
    }

    return minVal;
}

float getDistance(int *a, int n) {
    float distance = 0.0;
    for (int i = 0; i < n; ++i) {
        distance += a[i] * a[i];
    }
    return sqrt(distance);
}

int compareDistances(int *point, int n) {
    return getDistance(point, n);
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, compareDistances);
}

int cmp_long_long(const void *pa, const void *pb) {
    const long long *a = pa;
    const long long *b = pb;
    return (*a > *b) - (*a < *b);
}

int countNUnique(long long *a, int n) {
    if (n == 0) {
        return 0;
    }
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1]) {
            count++;
        }
    }

    return count;
}

int countEqClassesByRowsSum(matrix m) {
    int nRows = m.nRows;
    int nCols = m.nCols;

    long long *rowSums = (long long *)malloc(sizeof(long long) * nRows);
    if (rowSums == NULL) {
        fprintf(stderr, "bad alloc\n");
        exit(1);
    }

    for (int i = 0; i < nRows; i++) {
        long long sum = 0;
        for (int j = 0; j < nCols; j++) {
            sum += m.values[i][j];
        }
        rowSums[i] = sum;
    }

    qsort(rowSums, nRows, sizeof(long long), cmp_long_long);

    int uniqueSumCount = countNUnique(rowSums, nRows);

    free(rowSums);

    return uniqueSumCount;
}

int getNSpecialElement(matrix m) {
    int nSpecial = 0;

    for (int j = 0; j < m.nCols; j++) {
        int colSum = 0;
        int maxElement = m.values[0][j];

        for (int i = 0; i < m.nRows; i++) {
            colSum += m.values[i][j];
            if (m.values[i][j] > maxElement) {
                maxElement = m.values[i][j];
            }
        }

        if (maxElement > (colSum - maxElement)) {
            nSpecial++;
        }
    }

    return nSpecial;
}

void swapPenultimateRow(matrix m) {
    if (m.nRows < 2 || m.nCols < 1) {
        fprintf(stderr, "Matrix size is too small\n");
        return;
    }

    int minCol = 0;
    int minVal = m.values[0][0];
    for (int j = 1; j < m.nCols; j++) {
        if (m.values[m.nRows - 1][j] < minVal) {
            minVal = m.values[m.nRows - 1][j];
            minCol = j;
        }
    }

    int temp = m.values[m.nRows - 2][minCol];

    for (int i = 0; i < m.nCols; i++) {
        m.values[m.nRows - 2][i] = m.values[i][minCol];
    }

    m.values[m.nRows - 2][m.nCols - 2] = temp;
}

bool isNonDescendingSorted(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}

bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        if (!isNonDescendingSorted(m.values[i], m.nCols)) {
            return false;
        }
    }
    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int count = 0;
    for (int i = 0; i < nMatrix; i++) {
        if (hasAllNonDescendingRows(ms[i])) {
            count++;
        }
    }

    return count;
}

int countValues(const int *a, int n, int value) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == value) {
            count++;
        }
    }
    return count;
}

int countZeroRows(matrix m) {
    int count = 0;
    for (int i = 0; i < m.nRows; i++) {
        int isZeroRow = 1;
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] != 0) {
                isZeroRow = 0;
                break;
            }
        }
        if (isZeroRow) {
            count++;
        }
    }
    return count;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int maxZeroRows = 0;
    for (int i = 0; i < nMatrix; i++) {
        int zeroRows = countZeroRows(ms[i]);
        if (zeroRows > maxZeroRows) {
            maxZeroRows = zeroRows;
        }
    }
    for (int i = 0; i < nMatrix; i++) {
        if (countZeroRows(ms[i]) == maxZeroRows) {
            printf("Matrix %d:\n", i + 1);
            for (int j = 0; j < ms[i].nRows; j++) {
                for (int k = 0; k < ms[i].nCols; k++) {
                    printf("%d ", ms[i].values[j][k]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}

int maxNorm(matrix m) {
    int maxAbs = 0;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            int absValue = abs(m.values[i][j]);
            if (absValue > maxAbs) {
                maxAbs = absValue;
            }
        }
    }

    return maxAbs;
}

void printMatrixsWithMinNorm(matrix *matrices, int nMatrices) {
    if (nMatrices == 0) {
        printf("No matrices provided.\n");
        return;
    }

    int minNorm = maxNorm(matrices[0]);
    printf("Matrices with minimum norm:\n");
    for (int i = 0; i < nMatrices; i++) {
        int norm = maxNorm(matrices[i]);
        if (norm < minNorm) {
            minNorm = norm;
        }
    }

    for (int i = 0; i < nMatrices; i++) {
        if (maxNorm(matrices[i]) == minNorm) {
            printf("Matrix %d:\n", i + 1);
            for (int j = 0; j < matrices[i].nRows; j++) {
                for (int k = 0; k < matrices[i].nCols; k++) {
                    printf("%d ", matrices[i].values[j][k]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}

int getNSpecialElement2(matrix m) {
    int count = 0;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            bool isSpecial = true;
            for (int k = 0; k < j; k++) {
                if (m.values[i][k] >= m.values[i][j]) {
                    isSpecial = false;
                    break;
                }
            }
            for (int k = j + 1; k < m.nCols; k++) {
                if (m.values[i][k] <= m.values[i][j]) {
                    isSpecial = false;
                    break;
                }
            }
            if (isSpecial) {
                count++;
            }
        }
    }
    return count;
}

double getScalarProduct(int *a, int *b, int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }

    return result;
}

double getVectorLength(int *a, int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += a[i] * a[i];
    }

    return sqrt(result);
}

double getCosine(int *a, int *b, int n) {
    double scalarProduct = getScalarProduct(a, b, n);
    double lengthA = getVectorLength(a, n);
    double lengthB = getVectorLength(b, n);
    if (lengthA == 0 || lengthB == 0) {
        return 0.0;
    }

    return scalarProduct / (lengthA * lengthB);
}

int getVectorIndexWithMaxAngle(matrix m, int *v) {
    int maxIndex = 0;
    double maxCosine = -1;
    for (int i = 1; i < m.nRows; i++) {
        double currentCosine = getCosine(m.values[i], v, m.nCols);
        if (currentCosine > maxCosine) {
            maxCosine = currentCosine;
            maxIndex = i;
        }
    }

    return maxIndex;
}

long long getScalarProductRowAndCol(matrix m, int i, int j) {
    long long scalarProduct = 0;
    for (int k = 0; k < m.nCols; k++) {
        scalarProduct += (long long)m.values[i][k] * m.values[k][j];
    }

    return scalarProduct;
}

long long getSpecialScalarProduct(matrix m) {
    int maxRow = 0;
    int minCol = 0;
    int maxElement = INT_MIN;
    int minElement = INT_MAX;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > maxElement) {
                maxElement = m.values[i][j];
                maxRow = i;
            }
            if (m.values[i][j] < minElement) {
                minElement = m.values[i][j];
                minCol = j;
            }
        }
    }

    return getScalarProductRowAndCol(m, maxRow, minCol);
}

void generateRandomMatrixFile(const char* filename, size_t n) {
    srand(time(NULL));

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    fprintf(file, "%lld\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", rand() % 10);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}

void transposeMatrixInFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    size_t n;
    fscanf(file, "%lld", &n);

    matrix matrix = getMemMatrix((int) n , (int) n);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &matrix.values[i][j]);

    fclose(file);

    transposeSquareMatrix(&matrix);

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", matrix.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    freeMemMatrix(&matrix);
}

void generateNonSymmetricMatrix(const char* filename) {
    srand(time(NULL));

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int n = rand() % 2 + 2;
    fwrite(&n, sizeof(int), 1, file);

    int amount_matrix = rand() % 3 + 1;

    for (int k = 0; k < amount_matrix; k++) {
        int matrix[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = rand() % 100;
            }
        }
        fwrite(matrix, sizeof(int), n * n, file);
    }

    fclose(file);
}

int isSymmetric(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] != matrix[j][i])
                return 0;

    return 1;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void transpose(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(&matrix[i][j], &matrix[j][i]);
}

void transposeNonSymmetricMatrix(const char* filename) {
    FILE* file = fopen(filename, "r+b");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return;
    }

    int n;
    if (fread(&n, sizeof(int), 1, file) != 1) {
        printf("Ошибка при чтении порядка матрицы.\n");
        fclose(file);
        return;
    }

    while(1) {
        int matrix[n][n];
        size_t read_count = fread(matrix, sizeof(int), n * n, file);
        if (read_count != n * n) {
            if (feof(file)) {
                break;
            } else {
                printf("Ошибка при чтении матрицы.\n");
                break;
            }
        }

        if (!isSymmetric(n, matrix)) {
            transpose(n, matrix);
            fseek(file, -(long int)read_count * sizeof(int), SEEK_CUR);
            fwrite(matrix, sizeof(int), read_count, file);
            fseek(file, (long int)read_count * sizeof(int), SEEK_CUR);
        }
    }

    fclose(file);
}

void printBinFileMatrix(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int n;
    fread(&n, sizeof(int), 1, file);

    if (n == 0)
        return;

    while (!feof(file)) {
        int matrix[n][n];
        if (fread(matrix, sizeof(int), n * n, file) != n * n)
            break;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    fclose(file);
}