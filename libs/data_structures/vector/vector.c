#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../../data_structures/vector/vector.h"

vector createVector(size_t n) {
    vector v;
    v.size = 0;
    if (n > 0) {
        v.data = (int *) malloc(n * sizeof(int));
        if (v.data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }
    } else {
        v.data = NULL;
    }
    v.capacity = n;

    return v;
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

bool isEmpty(vector *v) {
    return v->size == 0;
}

bool isFull(vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i) {
    return v->data[i];
}

void pushBack(vector *v, int x) {
    if (v->capacity == 0) {
        reserve(v, 1);
    }
    if (isFull(v)) {
        reserve(v, v->capacity * 2);
    }
    v->data[v->size++] = x;
}

void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "Vector is empty");
        exit(1);
    }
    v->size--;
}

int *atVector(vector *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "IndexError: a[%zu] is not exists", index);
        exit(1);
    }

    return &(v->data[index]);
}

int *back(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "Vector is empty");
        exit(1);
    }

    return &(v->data[v->size - 1]);
}

int *front(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "Vector is empty");
        exit(1);
    }

    return &(v->data[0]);
}

void generateNumbersArray(const char* filename) {
    srand(time(NULL));

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int amount_numbers = (int) rand() % 10 + 1;

    for (int i = 0; i < amount_numbers; i++) {
        int x = rand() % 200 - 100;
        fwrite(&x, sizeof(int), 1, file);
    }

    fclose(file);
}


void rearrangeNumbers(const char* filename) {
    vector positive_numbers = createVector(2);
    vector negative_numbers = createVector(2);

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int current_number;
    while (fread(&current_number, sizeof(int), 1, file) == 1) {
        if (current_number >= 0) {
            pushBack(&positive_numbers, current_number);
        } else {
            pushBack(&negative_numbers, current_number);
        }
    }

    fclose(file);

    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (int i = 0; i < positive_numbers.size; i++) {
        fwrite(positive_numbers.data + i, sizeof(int), 1, file);
    }

    for (int i = 0; i < negative_numbers.size; i++) {
        fwrite(negative_numbers.data + i, sizeof(int), 1, file);
    }

    deleteVector(&positive_numbers);
    deleteVector(&negative_numbers);
    fclose(file);
}


void printNumbersArray(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int x;
    while(fread(&x, sizeof(int), 1, file))
        printf("%d ", x);
    printf("\n");

    fclose(file);
}