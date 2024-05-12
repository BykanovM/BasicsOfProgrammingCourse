#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../../data_structures/vector/vectorVoid.h"

vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    vectorVoid V;
    V.size = 0;
    V.baseTypeSize = baseTypeSize;
    if (n > 0) {
        V.data = (int *) malloc(n * baseTypeSize);
        if (V.data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }
    } else {
        V.data = NULL;
    }
    V.capacity = n;

    return V;
}

void reserveV(vectorVoid *v, size_t newCapacity) {
    if (newCapacity == 0) {
        free(v->data);
        v->data = NULL;
    } else if (newCapacity > v->capacity) {
        void *newData = realloc(v->data, newCapacity * v->baseTypeSize);
        if (newData == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }
        v->data = newData;
        v->capacity = newCapacity;
    } else if (newCapacity < v->size) {
        v->size = newCapacity;
    }
}

void clearV(vectorVoid *v) {
    v->size = 0;
}

void shrinkToFitV(vectorVoid *v) {
    v->capacity = v->size;
}

void deleteVectorV(vectorVoid *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

bool isEmptyV(vectorVoid *v) {
    return v->size == 0;
}

bool isFullV(vectorVoid *v) {
    return v->size == v->capacity;
}

void getVectorValueV(vectorVoid *v, size_t index, void *destination) {
    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void setVectorValueV(vectorVoid *v, size_t index, const void *source) {
    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void popBackV(vectorVoid *v) {
    if (isEmptyV(v)) {
        fprintf(stderr, "Vector is empty");
        exit(1);
    }
    v->size--;
}

void pushBackV(vectorVoid *v, void *source) {
    if (v->capacity == 0) {
        reserveV(v, 1);
    }
    if (isFullV(v)) {
        reserveV(v, v->capacity * 2);
    }
    setVectorValueV(v, v->size, source);
    v->size++;
}

void generateFloat(const char* filename, int n) {
    srand(time(NULL));

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (size_t i = 0; i < n; i++)
        fprintf(file, "%f ", 10.0 * rand() / RAND_MAX);

    fclose(file);
}


void convertFloat(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    vectorVoid v = createVectorV(0, sizeof(float));

    while (!feof(file)) {
        float x;
        fscanf(file, "%f", &x);

        pushBackV(&v, &x);
    }

    fclose(file);

    file = fopen(filename, "w");

    for (size_t i = 0; i < v.size; i++) {
        float x;
        getVectorValueV(&v, i, &x);
        fprintf(file, "%.2f ", x);
    }

    deleteVectorV(&v);
    fclose(file);
}

void generatePolynomial(const char* filename) {
    srand(time(NULL));

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int amount_polynomial = rand() % 5 + 2;

    for (int k = 0; k < amount_polynomial; k++) {
        int amount_monomial = rand() % 5 + 1;

        monomial mono;
        for (int i = 0; i <= amount_monomial; i++) {
            mono.degree = amount_monomial - i;
            mono.coefficient = 2.0 * rand() / RAND_MAX - 1.0;

            fwrite(&mono, sizeof(monomial), 1, file);
        }
    }

    fclose(file);
}


double getMonomialValue(monomial mono, double x) {
    return pow(x, mono.degree) * mono.coefficient;
}


void removeTruePolynomial(const char* filename, double x) {
    vectorVoid v = createVectorV(16, sizeof(monomial));

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    monomial mono;
    while (fread(&mono, sizeof(monomial), 1, file) == 1)
        pushBackV(&v, &mono);

    fclose(file);

    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    monomial m;
    vectorVoid temp = createVectorV(8, sizeof(monomial));
    double result = 0;
    for (size_t i = 0; i < v.size; i++) {
        getVectorValueV(&v, i, &m);
        pushBackV(&temp, &m);
        result += getMonomialValue(m, x);

        if (m.degree == 0) {
            if (fabs(result) >= 0.001) {
                monomial temp_mono;
                for (size_t j = 0; j < temp.size; j++) {
                    getVectorValueV(&temp, j, &temp_mono);
                    fwrite(&temp_mono, sizeof(monomial), 1, file);
                }
            }

            clearV(&temp);
            result = 0;
        }
    }

    deleteVectorV(&v);
    deleteVectorV(&temp);

    fclose(file);
}


void printPolynomial(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    monomial mono;
    while (fread(&mono, sizeof(monomial), 1, file) == 1) {
        printf("%5.2lf * x^%lld + ", mono.coefficient, mono.degree);

        if (mono.degree == 0)
            printf("\b\b \n");
    }

    fclose(file);
}