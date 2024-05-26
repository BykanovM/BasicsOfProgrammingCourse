#ifndef ARRAY_REARRANGE_STRINGS_H
#define ARRAY_REARRANGE_STRINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../data_structures/string/string_.h"

void _rearrangeString(const char* s, char* res, const int a[], const int n) {
    for (int i = 0; i < n; i++) {
        res[i] = s[a[i]];
    }
}

void rearrangeString(const char* filename) {
    FILE* file = fopen(filename, "r");

    char s[1024] = "";
    fscanf(file, "%s", s);

    size_t len = strlen_(s);
    int* numbers = (int *) malloc(len * sizeof(int));

    for (int i = 0; i < len; i++) {
        fscanf(file, "%d", numbers + i);
    }

    fclose(file);

    char res[1024] = "";
    _rearrangeString(s, res, numbers, len);

    file = fopen(filename, "w");

    fprintf(file, "%s", res);

    fclose(file);

    free(numbers);
}

void test_rearrangeStringEmptyFile() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\8_test_1.txt";

    FILE* file = fopen(filename, "w");
    fclose(file);

    rearrangeString(filename);

    file = fopen(filename, "r");

    char res[100] = "";
    fscanf(file, "%s", res);

    fclose(file);

    assert(strcmp(res, "") == 0);
}


void test_rearrangeStringOneElement() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\8_test_2.txt";

    FILE* file = fopen(filename, "w");

    fprintf(file, "s\n");
    fprintf(file, "0");

    fclose(file);

    rearrangeString(filename);

    file = fopen(filename, "r");

    char res[100] = "";
    fscanf(file, "%s", res);

    fclose(file);

    assert(strcmp(res, "s") == 0);
}


void test_rearrangeStringMoreElement() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\8_test_3.txt";

    FILE* file = fopen(filename, "w");

    fprintf(file, "abap\n");
    fprintf(file, "0 3 2 1");

    fclose(file);

    rearrangeString(filename);

    file = fopen(filename, "r");

    char res[100] = "";
    fscanf(file, "%s", res);

    fclose(file);

    assert(strcmp(res, "apab") == 0);
}

void test_rearrangeString() {
    test_rearrangeStringEmptyFile();
    test_rearrangeStringOneElement();
    test_rearrangeStringMoreElement();
}

#endif //ARRAY_REARRANGE_STRINGS_H