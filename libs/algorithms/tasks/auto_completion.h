#ifndef ARRAY_AUTO_COMPLETION_H
#define ARRAY_AUTO_COMPLETION_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../data_structures/string/string_.h"

#define MAX_REQUEST 128

typedef struct request {
    WordDescriptor sequence;
    int position;
} request;

typedef struct requests {
    request request[MAX_REQUEST];
    size_t size;
} requests;

void freeRequests(requests* rs) {
    for (int i = 0; i < rs->size; i++) {
        rs->request[i].position = 0;
        rs->request[i].sequence.begin = NULL;
        rs->request[i].sequence.end = NULL;
    }

    rs->size = 0;
}

void _printRequest(request* r) {
    printf("%d ", r->position);
    printWord(r->sequence);
}

void autoCompletion(const char* filename) {
    FILE* file = fopen(filename, "r");

    long long int n, q;
    fscanf(file, "%lld", &n);
    fscanf(file, "%lld", &q);

    bag_.size = 0;
    char* begin = stringBuffer_;
    for (int i = 0; i < n; i++) {
        fscanf(file, "%s", begin);
        getWordWithoutSpace(begin, &bag_.words[bag_.size]);
        begin = bag_.words[bag_.size].end + 1;
        bag_.size++;
    }

    requests rs = {.size = 0};
    for (int i = 0; i < q; i++) {
        fscanf(file, "%d", &rs.request[i].position);
        fscanf(file, "%s", begin);
        getWordWithoutSpace(begin, &rs.request[i].sequence);
        begin = rs.request[i].sequence.end + 1;
        rs.size++;
    }

    fclose(file);

    file = fopen(filename, "w");

    for (int i = 0; i < q; i++) {
        int amount = 0;
        for (int j = 0; j < n; j++) {
            if (isSubWord(rs.request[i].sequence, bag_.words[j])) {
                amount++;
                if (amount == rs.request[i].position) {
                    fprintf(file, "%d\n", j + 1);
                }
            }
        }
        if (amount < rs.request[i].position) {
            fprintf(file, "-1\n");
        }
    }

    fclose(file);

    freeString(stringBuffer_);
    freeBag(&bag_);
    freeRequests(&rs);
}

void test_autoCompletionEmptyFile() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\11_test_1.txt";

    FILE* file = fopen(filename, "w");

    int n = 0;
    int q = 0;
    fprintf(file, "%d %d \n", n, q);

    fclose(file);

    autoCompletion(filename);

    file = fopen(filename, "r");

    char res[100] = "";
    fgets(res, 100, file);

    fclose(file);

    assert(strcmp(res, "") == 0);
}

void test_autoCompletionZeroQ() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\11_test_2.txt";

    FILE* file = fopen(filename, "w");

    int n = 3;
    int q = 0;
    fprintf(file, "%d %d \n", n, q);
    fprintf(file, "aa\n");
    fprintf(file, "d\n");
    fprintf(file, "mamama\n");

    fclose(file);

    autoCompletion(filename);

    file = fopen(filename, "r");

    char res[100] = "";
    fgets(res, 100, file);

    fclose(file);

    assert(strcmp(res, "") == 0);
}

void test_autoCompletionDifferentElement() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\11_test_3.txt";

    FILE* file = fopen(filename, "w");

    int n = 10;
    int q = 3;
    fprintf(file, "%d %d \n", n, q);
    fprintf(file, "aa    \n");
    fprintf(file, "aaa   \n");
    fprintf(file, "aab   \n");
    fprintf(file, "ab    \n");
    fprintf(file, "abc   \n");
    fprintf(file, "ac    \n");
    fprintf(file, "ba    \n");
    fprintf(file, "daa   \n");
    fprintf(file, "dab   \n");
    fprintf(file, "dadba \n");
    fprintf(file, "4 a   \n");
    fprintf(file, "2 da   \n");
    fprintf(file, "4 da \n");

    fclose(file);

    autoCompletion(filename);

    file = fopen(filename, "r");

    int n1, n2, n3;
    fscanf(file, "%d\n", &n1);
    fscanf(file, "%d\n", &n2);
    fscanf(file, "%d\n", &n3);

    fclose(file);

    assert(n1 == 4);
    assert(n2 == 9);
    assert(n3 == -1);
}

void test_autoCompletion() {
    test_autoCompletionEmptyFile();
    test_autoCompletionZeroQ();
    test_autoCompletionDifferentElement();
}

#endif //ARRAY_AUTO_COMPLETION_H