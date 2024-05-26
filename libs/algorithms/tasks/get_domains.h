#ifndef ARRAY_GET_DOMAINS_H
#define ARRAY_GET_DOMAINS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../data_structures/string/string_.h"

#define MAX_LENGTH_DOMAIN 128
#define MAX_DOMAIN 64

typedef struct domain {
    char name[MAX_LENGTH_DOMAIN];
    int amount;
} domain;

typedef struct domains {
    domain data[MAX_DOMAIN];
    size_t size;
} domains;

int getWordToDot(char* begin_search, WordDescriptor* word) {
    word->begin = findNonSpace(begin_search);
    if (*word->begin == '\0') {
        return 0;
    }

    size_t len = strlen_(begin_search);
    word->end = find(word->begin, word->begin + len, '.');

    if (word->end == word->begin + len || *word->end == '\n') {
        word->end -= 2;
    }

    return 1;
}

void pushDomainInDomains(domains* ds, domain* d) {
    ds->data[ds->size].amount = d->amount;
    copy(d->name, d->name + strlen_(d->name) + 1, ds->data[ds->size].name);
    ds->size++;
}

void mergeEqualDomains(domains* ds) {
    for (int i = 0; i < ds->size; i++) {
        for (int j = i + 1; j < ds->size; j++) {
            if (strcmp(ds->data[i].name, ds->data[j].name) == 0 && ds->data[i].amount >= 0 && ds->data[j].amount >= 0) {
                ds->data[i].amount += ds->data[j].amount;
                ds->data[j].amount = -1;
            }

        }
    }
}

void _getDomains(char* s, domains* ds) {
    char* read_ptr = s;

    WordDescriptor amount_as_text, name_domain;
    getWordWithoutSpace(read_ptr, &amount_as_text);
    read_ptr = amount_as_text.end + 1;
    getWordWithoutSpace(read_ptr, &name_domain);

    int k = 1;
    int amount = 0;
    read_ptr = amount_as_text.end;
    while (read_ptr >= amount_as_text.begin) {
        amount += k * (*read_ptr - '0');
        k *= 10;
        read_ptr--;
    }

    read_ptr = name_domain.begin;
    bag_.size = 0;
    while (getWordToDot(read_ptr, &bag_.words[bag_.size])) {
        read_ptr = bag_.words[bag_.size].end + 1;
        bag_.size++;
    }

    for (int i = 0; i < bag_.size; i++) {
        domain d = {.amount = amount};

        char* begin = d.name;
        begin = copy(bag_.words[i].begin, bag_.words[i].end + 1, begin);
        for (int j = i + 1; j < bag_.size; j++) {
            begin = copy(bag_.words[j].begin, bag_.words[j].end + 1, begin);
        }

        pushDomainInDomains(ds, &d);
    }

    freeBag(&bag_);
}

void getDomains(const char* filename) {
    FILE* file = fopen(filename, "r");

    domains ds = {.size = 0};

    while (fgets(stringBuffer_, 256, file)) {
        _getDomains(stringBuffer_, &ds);
        freeString(stringBuffer_);
    }

    mergeEqualDomains(&ds);

    fclose(file);

    file = fopen(filename, "w");

    for (int i = 0; i < ds.size; i++) {
        if (ds.data[i].amount >= 0) {
            fprintf(file, "%d %s\n", ds.data[i].amount, ds.data[i].name);
        }
    }

    fclose(file);
}

void test_getDomainEmptyFile() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\4_test_1.txt";

    FILE* file = fopen(filename, "w");
    fclose(file);

    getDomains(filename);

    file = fopen(filename, "r");

    char dest[100] = "";
    fscanf(file, "%s", dest);

    fclose(file);

    assert(strcmp(dest, "") == 0);
}

void test_getDomainsOneDomain() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\4_test_2.txt";

    FILE* file = fopen(filename, "w");

    char s[100] = "900 discuss.codeforces.com";
    fprintf(file, "%s\n", s);

    fclose(file);

    getDomains(filename);

    file = fopen(filename, "r");

    char dest1[100] = "";
    char dest2[100] = "";
    char dest3[100] = "";
    fgets(dest1, sizeof(dest1), file);
    fgets(dest2, sizeof(dest2), file);
    fgets(dest3, sizeof(dest3), file);

    fclose(file);

    assert(strcmp(dest1, "900 discuss.codeforces.com\n") == 0);
    assert(strcmp(dest2, "900 codeforces.com\n") == 0);
    assert(strcmp(dest3, "900 com\n") == 0);
}

void test_getDomainsMoreDomain() {
    const char filename[] = "C:\\Users\\bykan\\Desktop\\Lab20\\4_test_3.txt";

    FILE* file = fopen(filename, "w");

    char s1[100] = "900 discuss.codeforces.com";
    char s2[100] = "69 mail.com";
    fprintf(file, "%s\n", s1);
    fprintf(file, "%s\n", s2);

    fclose(file);

    getDomains(filename);

    file = fopen(filename, "r");

    char dest1[100] = "";
    char dest2[100] = "";
    char dest3[100] = "";
    char dest4[100] = "";
    fgets(dest1, sizeof(dest1), file);
    fgets(dest2, sizeof(dest2), file);
    fgets(dest3, sizeof(dest3), file);
    fgets(dest4, sizeof(dest4), file);

    fclose(file);

    assert(strcmp(dest1, "900 discuss.codeforces.com\n") == 0);
    assert(strcmp(dest2, "900 codeforces.com\n") == 0);
    assert(strcmp(dest3, "969 com\n") == 0);
    assert(strcmp(dest4, "69 mail.com\n") == 0);
}

void test_getDomains() {
    test_getDomainEmptyFile();
    test_getDomainsOneDomain();
    test_getDomainsMoreDomain();
}

#endif //ARRAY_GET_DOMAINS_H