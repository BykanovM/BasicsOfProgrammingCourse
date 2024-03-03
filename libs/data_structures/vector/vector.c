#include <stdio.h>
#include <malloc.h>
#include "../../data_structures/vector/vector.h"

vector createVector(size_t n) {
    vector vector;
    vector.size = n;
    if (n > 0) {
        vector.data = (int *) malloc(n * sizeof(int));
        if (vector.data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }
    } else {
        vector.data = NULL;
    }
    vector.capacity = n;

    return vector;
}

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0) {
        free(v->data);
        v->data = NULL;
    } else if (newCapacity > v->capacity) {
        int *newData = (int *) realloc(v->data, newCapacity * sizeof(int));
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

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    v->capacity = v->size;
}

void deleteVector(vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}