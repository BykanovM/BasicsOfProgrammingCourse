#ifndef ARRAY_GENERATE_NUMS_H
#define ARRAY_GENERATE_NUMS_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ASCII_SHIFT 48

void generateNums(const char* filename) {
    int num[] = {1,2,3,4,5,6,7,8,9};

    FILE* file = fopen(filename, "r");

    char res[10] = "";
    char s[10] = "";
    fscanf(file, "%s", s);

    fclose(file);

    unsigned int len_s = strlen(s);

    char* rec_ptr = res;
    char* read_ptr = s;
    unsigned int i_ind = 0;
    unsigned int d_ind = len_s;

    while (i_ind != d_ind) {
        if (*read_ptr == 'I') {
            *rec_ptr = (char) (num[i_ind] + ASCII_SHIFT);
            i_ind++;
        } else {
            *rec_ptr = (char) (num[d_ind] + ASCII_SHIFT);
            d_ind--;
        }

        read_ptr++;
        rec_ptr++;
    }

    *rec_ptr = (char) (num[i_ind] + ASCII_SHIFT);

    file = fopen(filename, "w");

    fprintf(file, "%s", res);

    fclose(file);
}

void test_generateNumsEmptyFile() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\6_test_1.txt";

    FILE* file = fopen(filename, "w");
    fclose(file);

    generateNums(filename);

    file = fopen(filename, "r");

    int nums;
    fscanf(file, "%d", &nums);

    fclose(file);

    assert(nums == 1);
}

void test_generateNumsUnitLength() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\6_test_2.txt";

    FILE* file = fopen(filename, "w");

    fprintf(file, "I");

    fclose(file);

    generateNums(filename);

    file = fopen(filename, "r");

    int nums;
    fscanf(file, "%d", &nums);

    fclose(file);

    assert(nums == 12);
}


void test_generateNumsAverageLength() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\6_test_3.txt";

    FILE* file = fopen(filename, "w");

    fprintf(file, "IIID");

    fclose(file);

    generateNums(filename);

    file = fopen(filename, "r");

    int nums;
    fscanf(file, "%d", &nums);

    fclose(file);

    assert(nums == 12354);
}

void test_generateNumsMaxLength() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\6_test_4.txt";

    FILE* file = fopen(filename, "w");

    fprintf(file, "IIIIIIII");

    fclose(file);

    generateNums(filename);

    file = fopen(filename, "r");

    int nums;
    fscanf(file, "%d", &nums);

    fclose(file);

    assert(nums == 123456789);
}

void test_generateNums() {
    test_generateNumsEmptyFile();
    test_generateNumsUnitLength();
    test_generateNumsAverageLength();
    test_generateNumsMaxLength();
}

#endif //ARRAY_GENERATE_NUMS_H