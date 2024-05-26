#ifndef ARRAY_FILTER_NUMS_H
#define ARRAY_FILTER_NUMS_H

#include <stdio.h>
#include <assert.h>
#include "../../data_structures/vector/vector.h"

void filterNums(const char* r_filename, const char* w_filename, const int n) {
    FILE* read_file = fopen(r_filename, "r");

    int x;
    vector v = createVector(16);
    while (fscanf(read_file, "%d ", &x) == 1) {
        if (x < n) {
            pushBack(&v, x);
        }
    }

    fclose(read_file);

    FILE* write_file = fopen(w_filename, "w");

    for (int i = 0; i < v.size; i++) {
        x = getVectorValue(&v, i);
        fprintf(write_file, "%d ", x);
    }

    fprintf(write_file, "\n");

    fclose(write_file);
}

void test_filterNums() {
    const char r_filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\9_r_test.txt";
    const char w_filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\9_w_test.txt";

    filterNums(r_filename, w_filename, 35);

    FILE* w_file = fopen(w_filename, "r+");

    int expected_results[] = {10, 20, 30};
    int result;
    int i = 0;

    while (fscanf(w_file, "%d", &result) == 1) {
        assert(result == expected_results[i]);
        i++;
    }

    fclose(w_file);
}

#endif //ARRAY_FILTER_NUMS_H