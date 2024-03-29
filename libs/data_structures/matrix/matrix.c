#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
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