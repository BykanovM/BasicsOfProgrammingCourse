#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

