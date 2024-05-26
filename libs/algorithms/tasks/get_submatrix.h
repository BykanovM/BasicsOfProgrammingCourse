#ifndef ARRAY_GET_SUBMATRIX_H
#define ARRAY_GET_SUBMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../data_structures/matrix/matrix.h"

int getSubmatrix(matrix mat) {
    int m = mat.nRows;
    int n = mat.nCols;
    int res = 0;

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mat.values[i][j]) {
                mat.values[i][j] += mat.values[i - 1][j];
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int stack[n];
        int top = -1;
        int sums[n + 1];
        sums[0] = 0;

        for (int j = 0; j < n; j++) {
            while (top != -1 && mat.values[i][stack[top]] >= mat.values[i][j]) {
                top--;
            }
            if (top != -1) {
                int k = stack[top];
                sums[j + 1] = sums[k + 1] + mat.values[i][j] * (j - k);
            } else {
                sums[j + 1] = mat.values[i][j] * (j + 1);
            }
            stack[++top] = j;
        }

        for (int j = 0; j <= n; j++) {
            res += sums[j];
        }
    }

    return res;
}

void test_getSubmatrixEmptyMatrix() {
    matrix m = createMatrixFromArray((int[]) {}, 0, 0);

    int result = getSubmatrix(m);

    freeMemMatrix(&m);

    assert(result == 0);
}

void test_getSubmatrixUnitMatrix() {
    matrix m = createMatrixFromArray((int[]) {1}, 1, 1);

    int result = getSubmatrix(m);

    freeMemMatrix(&m);

    assert(result == 1);
}

void test_getSubmatrixMoreElement() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 1,
                                                 1, 1, 0,
                                                 1, 1, 0}, 3, 3);

    int result = getSubmatrix(m);

    freeMemMatrix(&m);

    assert(result == 13);
}

void test_getSubmatrix() {
    test_getSubmatrixEmptyMatrix();
    test_getSubmatrixUnitMatrix();
    test_getSubmatrixMoreElement();
}

#endif //ARRAY_GET_SUBMATRIX_H