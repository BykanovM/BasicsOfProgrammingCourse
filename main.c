#include <stdio.h>
//#include <string.h>
#include <ctype.h>
#include <memory.h>
#include "libs/algorithms/array/array.h"
#include "libs/data_structures/bitset/bitset.h"
#include "libs/data_structures/unordered_array_set/unordered_array_set.h"
#include "libs/data_structures/ordered_array_set/ordered_array_set.h"
#include "libs/data_structures/matrix/matrix.h"
#include "libs/data_structures/string/string_.h"

/*// тесты с битовыми множествами
typedef unsigned int uint;

// тест на наличие элемента в множестве
void test_bitset_in_1() {
    bitset set = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    uint value = 3;

    bool index = bitset_in(set, value);

    assert(index == 1);
}


void test_bitset_in_2() {
    bitset set = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    uint value = 4;

    bool index = bitset_in(set, value);

    assert(index == 0);
}


void test_bitset_in() {
    test_bitset_in_1();
    test_bitset_in_2();
}


// тест на является ли множество подмножеством другого множества
void test_bitset_isSubset_1() {
    bitset subset = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set = bitset_create_from_array((uint[]) {1, 2, 3, 4, 5, 6}, 6, 10);

    assert(bitset_isSubset(subset, set));
}


void test_bitset_isSubset_2() {
    bitset subset = bitset_create_from_array((uint[]) {1, 2, 10}, 3, 10);
    bitset set = bitset_create_from_array((uint[]) {1, 2, 3, 4, 5, 6}, 6, 10);

    assert(!bitset_isSubset(subset, set));
}


void test_bitset_isSubset_3() {
    bitset subset = bitset_create_from_array((uint[]) {}, 0, 10);
    bitset set = bitset_create_from_array((uint[]) {1, 2, 3, 4, 5, 6}, 6, 10);

    assert(bitset_isSubset(subset, set));
}


void test_bitset_isSubset_4() {
    bitset subset = bitset_create_from_array((uint[]) {1, 2, 3, 4, 5, 6}, 6, 10);
    bitset set = bitset_create_from_array((uint[]) {1, 2, 3, 4, 5, 6}, 6, 10);

    assert(bitset_isSubset(subset, set));
}


void test_bitset_isSubset() {
    test_bitset_isSubset_1();
    test_bitset_isSubset_2();
    test_bitset_isSubset_3();
    test_bitset_isSubset_4();
}


// тест на вставку элемента в множество
void test_bitset_insert_1() {
    bitset set = bitset_create_from_array((uint[]) {7, 8}, 2, 10);
    uint value = 4;

    bitset_insert(&set, value);

    bitset check_set = bitset_create_from_array((uint[]) {4, 7, 8}, 3, 3);

    assert(bitset_isEqual(set, check_set));
}


void test_bitset_insert_2() {
    bitset set = bitset_create_from_array((uint[]) {7, 8}, 2, 10);
    uint value = 7;

    bitset_insert(&set, value);

    bitset check_set = bitset_create_from_array((uint[]) {7, 8}, 2, 2);

    assert(bitset_isEqual(set, check_set));
}


void test_bitset_insert() {
    test_bitset_insert_1();
    test_bitset_insert_2();
}


// тест на удаление элемента
void test_bitset_deleteElement_1() {
    bitset set = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    uint value = 3;

    bitset_deleteElement(&set, value);

    bitset check_set = bitset_create_from_array((uint[]) {1, 2}, 2, 10);

    assert(bitset_isEqual(set, check_set));
}


void test_bitset_deleteElement_2() {
    bitset set = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    uint value = 5;

    bitset_deleteElement(&set, value);

    bitset check_set = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 2);

    assert(bitset_isEqual(set, check_set));
}

void test_bitset_deleteElement() {
    test_bitset_deleteElement_1();
    test_bitset_deleteElement_2();
}


// тест на объединение множеств
void test_bitset_union_1() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {3, 4, 5}, 3, 10);

    bitset res_set = bitset_union(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {1, 2, 3, 4, 5}, 5, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_union_2() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {4, 5, 6}, 3, 10);

    bitset res_set = bitset_union(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {1, 2, 3, 4, 5, 6}, 6, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_union_3() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);

    bitset res_set = bitset_union(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_union_4() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {}, 0, 10);

    bitset res_set = bitset_union(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_union() {
    test_bitset_union_1();
    test_bitset_union_2();
    test_bitset_union_3();
    test_bitset_union_4();
}


// тест на пересечение множеств
void test_bitset_intersection_1() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {2, 3, 4}, 3, 10);

    bitset res_set = bitset_intersection(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {2, 3}, 2, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_intersection_2() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {4, 5, 6}, 3, 10);

    bitset res_set = bitset_intersection(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {}, 0, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_intersection_3() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);

    bitset res_set = bitset_intersection(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_intersection() {
    test_bitset_intersection_1();
    test_bitset_intersection_2();
    test_bitset_intersection_3();
}


// тест на разность двух множеств
void test_bitset_difference_1() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 3, 7}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {3}, 1, 10);

    bitset res_set = bitset_difference(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {1, 7}, 2, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_difference_2() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 3, 7}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {}, 0, 10);

    bitset res_set = bitset_difference(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {1, 3, 7}, 3, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_difference_3() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 3, 7}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {1, 3, 7}, 3, 10);

    bitset res_set = bitset_difference(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {}, 0, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_difference() {
    test_bitset_difference_1();
    test_bitset_difference_2();
    test_bitset_difference_3();
}


// тест на симметричную разность двух множеств
void test_symmetricDifference_1() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {2, 3, 4}, 3, 10);

    bitset res_set = bitset_symmetricDifference(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {1, 4}, 2, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_symmetricDifference_2() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {4, 5, 6}, 3, 10);

    bitset res_set = bitset_symmetricDifference(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {1, 2, 3, 4, 5, 6}, 6, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_symmetricDifference_3() {
    bitset set1 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);
    bitset set2 = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);

    bitset res_set = bitset_symmetricDifference(set1, set2);

    bitset check_set = bitset_create_from_array((uint[]) {}, 0, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_symmetricDifference() {
    test_symmetricDifference_1();
    test_symmetricDifference_2();
    test_symmetricDifference_3();
}


// тест на дополнение множества
void test_bitset_complement_1() {
    bitset set = bitset_create_from_array((uint[]) {1, 2, 3}, 3, 10);

    bitset res_set = bitset_complement(set);

    bitset check_set = bitset_create_from_array((uint[]) {0, 4, 5, 6, 7, 8, 9, 10}, 8, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_complement_2() {
    bitset set = bitset_create_from_array((uint[]) {}, 0, 10);

    bitset res_set = bitset_complement(set);

    bitset check_set = bitset_create_from_array((uint[]) {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 11, 12);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_complement_3() {
    bitset set = bitset_create_from_array((uint[]) {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 11, 10);

    bitset res_set = bitset_complement(set);

    bitset check_set = bitset_create_from_array((uint[]) {}, 0, 10);

    assert(bitset_isEqual(res_set, check_set));
}


void test_bitset_complement() {
    test_bitset_complement_1();
    test_bitset_complement_2();
    test_bitset_complement_3();
}


void test_bitset() {
    test_bitset_in();
    test_bitset_isSubset();
    test_bitset_insert();
    test_bitset_deleteElement();
    test_bitset_union();
    test_bitset_intersection();
    test_bitset_difference();
    test_symmetricDifference();
    test_bitset_complement();
}


// тест для упорядоченных множеств



// тест на наличие элемента в множестве
void test_ordered_array_set_in_1() {
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    int value = 3;

    size_t index = ordered_array_set_in(&set, value);

    assert(index == 2);

    ordered_array_set_delete(&set);
}


void test_ordered_array_set_in_2() {
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    int value = 5;

    size_t index = ordered_array_set_in(&set, value);

    assert(index == 3);

    ordered_array_set_delete(&set);
}


void test_ordered_array_set_in() {
    test_ordered_array_set_in_1();
    test_ordered_array_set_in_2();
}


// тест является ли множество подномножеством другого множества
void test_ordered_array_set_isSubset_1() {
    ordered_array_set subset = ordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(ordered_array_set_isSubset(subset, set));

    ordered_array_set_delete(&subset);
    ordered_array_set_delete(&set);
}


void test_ordered_array_set_isSubset_2() {
    ordered_array_set subset = ordered_array_set_create_from_array((int[]) {4, 5, 3}, 3);
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(ordered_array_set_isSubset(subset, set));

    ordered_array_set_delete(&subset);
    ordered_array_set_delete(&set);
}


void test_ordered_array_set_isSubset_3() {
    ordered_array_set subset = ordered_array_set_create_from_array((int[]) {5, 3, 2, 4, 1, 6}, 6);
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(ordered_array_set_isSubset(subset, set));

    ordered_array_set_delete(&subset);
    ordered_array_set_delete(&set);
}


void test_ordered_array_set_isSubset_4() {
    ordered_array_set subset = ordered_array_set_create_from_array((int[]) {10}, 1);
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(!ordered_array_set_isSubset(subset, set));

    ordered_array_set_delete(&subset);
    ordered_array_set_delete(&set);
}


void test_ordered_array_set_isSubset() {
    test_ordered_array_set_isSubset_1();
    test_ordered_array_set_isSubset_2();
    test_ordered_array_set_isSubset_3();
    test_ordered_array_set_isSubset_4();
}


// тест на вставку элемента в множество
void test_ordered_array_set_insert_1() {
    ordered_array_set set = ordered_array_set_create(10);
    int value1 = 2;
    int value2 = 1;
    int value3 = 3;

    ordered_array_set_insert(&set, value1);
    ordered_array_set_insert(&set, value2);
    ordered_array_set_insert(&set, value3);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);

    assert(ordered_array_set_isEqual(set, check_set));

    ordered_array_set_delete(&set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_insert_2() {
    ordered_array_set set = ordered_array_set_create(10);
    int value1 = 7;
    int value2 = 11;
    int value3 = 2;
    int value4 = 2;

    ordered_array_set_insert(&set, value1);
    ordered_array_set_insert(&set, value2);
    ordered_array_set_insert(&set, value3);
    ordered_array_set_insert(&set, value4);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {2, 7, 11}, 3);

    assert(ordered_array_set_isEqual(set, check_set));

    ordered_array_set_delete(&set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_insert() {
    test_ordered_array_set_insert_1();
    test_ordered_array_set_insert_2();
}


// тест на удаление элемента из множества
void test_ordered_array_set_deleteElement_1() {
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {3, 6, 5, 2}, 4);
    int value = 2;

    ordered_array_set_deleteElement(&set, value);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {3, 6, 5}, 3);

    assert(ordered_array_set_isEqual(set, check_set));

    ordered_array_set_delete(&set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_deleteElement_2() {
    ordered_array_set set = ordered_array_set_create_from_array((int[]) {3, 6, 5, 2}, 4);
    int value = 2;

    ordered_array_set_deleteElement(&set, value);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {3, 6, 5}, 3);

    assert(ordered_array_set_isEqual(set, check_set));

    ordered_array_set_delete(&set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_deleteElement() {
    test_ordered_array_set_deleteElement_1();
    test_ordered_array_set_deleteElement_2();
}


// тест на объединение множеств
void test_ordered_array_set_union_1() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {3, 4, 1}, 3);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {2, 4, 5}, 3);

    ordered_array_set res_set = ordered_array_set_union(set1, set2);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5}, 5);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&set1);
    ordered_array_set_delete(&set2);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_union_2() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {3, 4, 1}, 3);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {3, 4, 1}, 3);

    ordered_array_set res_set = ordered_array_set_union(set1, set2);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {1, 3, 4}, 3);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&set1);
    ordered_array_set_delete(&set2);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_union_3() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {13, 7, 8}, 3);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {}, 0);

    ordered_array_set res_set = ordered_array_set_union(set1, set2);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {7, 13, 8}, 3);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&set1);
    ordered_array_set_delete(&set2);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_union() {
    test_ordered_array_set_union_1();
    test_ordered_array_set_union_2();
    test_ordered_array_set_union_3();
}


// тест на пересечение двух множеств
void test_ordered_array_set_intersection_1() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {2, 3, 4}, 3);

    ordered_array_set res_set = ordered_array_set_intersection(set1, set2);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {2, 3}, 2);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&set1);
    ordered_array_set_delete(&set2);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_intersection_2() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {4, 5, 6}, 3);

    ordered_array_set res_set = ordered_array_set_intersection(set1, set2);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {}, 0);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&set1);
    ordered_array_set_delete(&set2);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_intersection() {
    test_ordered_array_set_intersection_1();
    test_ordered_array_set_intersection_2();
}


// тест на разность множеств
void test_ordered_array_set_difference_1() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {2, 3, 6}, 3);

    ordered_array_set res_set = ordered_array_set_difference(set1, set2);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {1, 4, 5}, 3);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&set1);
    ordered_array_set_delete(&set2);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_difference_2() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {7, 8, 9}, 3);

    ordered_array_set res_set = ordered_array_set_difference(set1, set2);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&set1);
    ordered_array_set_delete(&set2);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_difference() {
    test_ordered_array_set_difference_1();
    test_ordered_array_set_difference_2();
}


// тест на симметричную разность
void test_ordered_array_set_symmetricDifference_1() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {2, 3, 6, 7, 10, 12}, 6);

    ordered_array_set res_set = ordered_array_set_symmetricDifference(set1, set2);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {1, 4, 5, 7, 10, 12}, 6);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&set1);
    ordered_array_set_delete(&set2);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_symmetricDifference_2() {
    ordered_array_set set1 = ordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    ordered_array_set set2 = ordered_array_set_create_from_array((int[]) {4, 5, 6}, 3);

    ordered_array_set res_set = ordered_array_set_symmetricDifference(set1, set2);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&set1);
    ordered_array_set_delete(&set2);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_symmetricDifference() {
    test_ordered_array_set_symmetricDifference_1();
    test_ordered_array_set_symmetricDifference_2();
}


// тест на дополнение множества
void test_ordered_array_set_complement_1() {
    ordered_array_set subset = ordered_array_set_create_from_array((int[]) {1, 2, 4}, 3);
    ordered_array_set universum = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    ordered_array_set res_set = ordered_array_set_complement(subset, universum);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {3, 5, 6}, 3);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&subset);
    ordered_array_set_delete(&universum);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_complement_2() {
    ordered_array_set subset = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);
    ordered_array_set universum = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    ordered_array_set res_set = ordered_array_set_complement(subset, universum);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {}, 0);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&subset);
    ordered_array_set_delete(&universum);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_complement_3() {
    ordered_array_set subset = ordered_array_set_create_from_array((int[]) {}, 0);
    ordered_array_set universum = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    ordered_array_set res_set = ordered_array_set_complement(subset, universum);

    ordered_array_set check_set = ordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(ordered_array_set_isEqual(res_set, check_set));

    ordered_array_set_delete(&subset);
    ordered_array_set_delete(&universum);
    ordered_array_set_delete(&res_set);
    ordered_array_set_delete(&check_set);
}


void test_ordered_array_set_complement() {
    test_ordered_array_set_complement_1();
    test_ordered_array_set_complement_2();
    test_ordered_array_set_complement_3();
}


void test_ordered_array_set() {
    test_ordered_array_set_in();
    test_ordered_array_set_isSubset();
    test_ordered_array_set_insert();
    test_ordered_array_set_deleteElement();
    test_ordered_array_set_union();
    test_ordered_array_set_intersection();
    test_ordered_array_set_difference();
    test_ordered_array_set_symmetricDifference();
    test_ordered_array_set_complement();
}


// тесты для неупорядоченного множества



// тест на наличие элемента в множестве
void test_unordered_array_set_in_1() {
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    int value = 2;

    size_t index = unordered_array_set_in(&set, value);

    assert(index == 1);

    unordered_array_set_delete(&set);
}


void test_unordered_array_set_in_2() {
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {10, 1, 4}, 3);
    int value = 5;

    size_t index = unordered_array_set_in(&set, value);

    assert(index == 3);

    unordered_array_set_delete(&set);
}


void test_unordered_array_set_in() {
    test_unordered_array_set_in_1();
    test_unordered_array_set_in_2();
}


// тест на является ли одно множество подмножеством другого
void test_unordered_array_set_isSubset_1() {
    unordered_array_set subset = unordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(unordered_array_set_isSubset(subset, set));

    unordered_array_set_delete(&subset);
    unordered_array_set_delete(&set);
}


void test_unordered_array_set_isSubset_2() {
    unordered_array_set subset = unordered_array_set_create_from_array((int[]) {4, 5, 3}, 3);
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(unordered_array_set_isSubset(subset, set));

    unordered_array_set_delete(&subset);
    unordered_array_set_delete(&set);
}


void test_unordered_array_set_isSubset_3() {
    unordered_array_set subset = unordered_array_set_create_from_array((int[]) {5, 3, 2, 4, 1, 6}, 6);
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(unordered_array_set_isSubset(subset, set));

    unordered_array_set_delete(&subset);
    unordered_array_set_delete(&set);
}


void test_unordered_array_set_isSubset_4() {
    unordered_array_set subset = unordered_array_set_create_from_array((int[]) {10}, 1);
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(!unordered_array_set_isSubset(subset, set));

    unordered_array_set_delete(&subset);
    unordered_array_set_delete(&set);
}


void test_unordered_array_set_isSubset() {
    test_unordered_array_set_isSubset_1();
    test_unordered_array_set_isSubset_2();
    test_unordered_array_set_isSubset_3();
    test_unordered_array_set_isSubset_4();
}


// тест на вставку элемента
void test_unordered_array_set_insert_1() {
    unordered_array_set set = unordered_array_set_create(10);
    int value1 = 1;
    int value2 = 7;
    int value3 = 5;

    unordered_array_set_insert(&set, value1);
    unordered_array_set_insert(&set, value2);
    unordered_array_set_insert(&set, value3);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {1, 7, 5}, 3);

    assert(unordered_array_set_isEqual(set, check_set));

    unordered_array_set_delete(&set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_insert_2() {
    unordered_array_set set = unordered_array_set_create(10);
    int value1 = 3;
    int value2 = 7;
    int value3 = 7;
    int value4 = 8;

    unordered_array_set_insert(&set, value1);
    unordered_array_set_insert(&set, value2);
    unordered_array_set_insert(&set, value3);
    unordered_array_set_insert(&set, value4);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {3, 7, 8}, 3);

    assert(unordered_array_set_isEqual(set, check_set));

    unordered_array_set_delete(&set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_insert() {
    test_unordered_array_set_insert_1();
    test_unordered_array_set_insert_2();
}


// тест на удаление элемента из множества
void test_unordered_array_set_deleteElement_1() {
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    int delete_value = 2;

    unordered_array_set_deleteElement(&set, delete_value);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {1, 3}, 2);

    assert(unordered_array_set_isEqual(set, check_set));

    unordered_array_set_delete(&set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_deleteElement_2() {
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {4, 12, 3}, 3);
    int delete_value1 = 4;
    int delete_value2 = 12;
    int delete_value3 = 3;

    unordered_array_set_deleteElement(&set, delete_value1);
    unordered_array_set_deleteElement(&set, delete_value2);
    unordered_array_set_deleteElement(&set, delete_value3);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {}, 0);

    assert(unordered_array_set_isEqual(set, check_set));

    unordered_array_set_delete(&set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_deleteElement() {
    test_unordered_array_set_deleteElement_1();
    test_unordered_array_set_deleteElement_2();
}


// тест на объединение неупорядоченных множеств
void test_unordered_array_set_union_1() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {1, 3}, 2);

    unordered_array_set res_set = unordered_array_set_union(set1, set2);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);

    assert(unordered_array_set_isEqual(res_set, check_set));

    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
    unordered_array_set_delete(&res_set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_union_2() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {5, 7, 8}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {}, 0);

    unordered_array_set res_set = unordered_array_set_union(set1, set2);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {5, 7, 8}, 3);

    assert(unordered_array_set_isEqual(res_set, check_set));

    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
    unordered_array_set_delete(&res_set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_union() {
    test_unordered_array_set_union_1();
    test_unordered_array_set_union_2();
}


// тест на пересечение множеств
void test_unordered_array_set_intersection_1() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 3, 4}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {3, 4, 5}, 3);

    unordered_array_set res_set = unordered_array_set_intersection(set1, set2);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {3, 4}, 2);

    assert(unordered_array_set_isEqual(res_set, check_set));

    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
    unordered_array_set_delete(&res_set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_intersection_2() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {4, 5, 6}, 3);

    unordered_array_set res_set = unordered_array_set_intersection(set1, set2);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {}, 0);

    assert(unordered_array_set_isEqual(res_set, check_set));

    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
    unordered_array_set_delete(&res_set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_intersection() {
    test_unordered_array_set_intersection_1();
    test_unordered_array_set_intersection_2();
}


// тест на вычитание одного множества из другого
void test_unordered_array_set_difference_1() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {4, 5, 6}, 3);

    unordered_array_set res_set = unordered_array_set_difference(set1, set2);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);

    assert(unordered_array_set_isEqual(res_set, check_set));

    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
    unordered_array_set_delete(&res_set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_difference_2() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {7}, 1);

    unordered_array_set res_set = unordered_array_set_difference(set1, set2);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    assert(unordered_array_set_isEqual(res_set, check_set));

    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
    unordered_array_set_delete(&res_set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_difference_3() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {3, 2, 1}, 3);

    unordered_array_set res_set = unordered_array_set_difference(set1, set2);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {}, 0);

    assert(unordered_array_set_isEqual(res_set, check_set));

    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
    unordered_array_set_delete(&res_set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_difference() {
    test_unordered_array_set_difference_1();
    test_unordered_array_set_difference_2();
    test_unordered_array_set_difference_3();
}


// тест на симметричную разность двух множеств
void test_unordered_array_set_symmetricDifference_1() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 3, 4}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {3, 4, 5}, 3);

    unordered_array_set res_set = unordered_array_set_symmetricDifference(set1, set2);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {1, 5}, 2);

    assert(unordered_array_set_isEqual(res_set, check_set));

    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
    unordered_array_set_delete(&res_set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_symmetricDifference_2() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]) {4, 5, 6}, 3);

    unordered_array_set res_set = unordered_array_set_symmetricDifference(set1, set2);

    unordered_array_set check_set = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 6, 5}, 6);

    assert(unordered_array_set_isEqual(res_set, check_set));

    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
    unordered_array_set_delete(&res_set);
    unordered_array_set_delete(&check_set);
}


void test_unordered_array_set_symmetricDifference() {
    test_unordered_array_set_symmetricDifference_1();
    test_unordered_array_set_symmetricDifference_2();
}


// тест на дополнение множества до универсума
void test_unordered_array_set_complement_1() {
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {1, 2, 3}, 3);
    unordered_array_set universum = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    unordered_array_set res_set = unordered_array_set_complement(set, universum);

    assert(unordered_array_set_isSubset(res_set, universum));

    unordered_array_set_delete(&set);
    unordered_array_set_delete(&universum);
    unordered_array_set_delete(&res_set);
}


void test_unordered_array_set_complement_2() {
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);
    unordered_array_set universum = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    unordered_array_set res_set = unordered_array_set_complement(set, universum);

    assert(unordered_array_set_isSubset(res_set, universum));

    unordered_array_set_delete(&set);
    unordered_array_set_delete(&universum);
    unordered_array_set_delete(&res_set);
}


void test_unordered_array_set_complement_3() {
    unordered_array_set set = unordered_array_set_create_from_array((int[]) {}, 0);
    unordered_array_set universum = unordered_array_set_create_from_array((int[]) {1, 2, 3, 4, 5, 6}, 6);

    unordered_array_set res_set = unordered_array_set_complement(set, universum);

    assert(unordered_array_set_isSubset(res_set, universum));

    unordered_array_set_delete(&set);
    unordered_array_set_delete(&universum);
    unordered_array_set_delete(&res_set);
}


void test_unordered_array_set_complement() {
    test_unordered_array_set_complement_1();
    test_unordered_array_set_complement_2();
    test_unordered_array_set_complement_3();
}


void test_unordered_array_set() {
    test_unordered_array_set_in();
    test_unordered_array_set_isSubset();
    test_unordered_array_set_deleteElement();
    test_unordered_array_set_union();
    test_unordered_array_set_intersection();
    test_unordered_array_set_difference();
    test_unordered_array_set_symmetricDifference();
    test_unordered_array_set_complement();
}


void test() {
    test_bitset();
    test_ordered_array_set();
    test_unordered_array_set();
}


void test_pushBack_emptyVector() {
    vector v = createVector(0);
    assert(isEmpty(&v));
    pushBack(&v, 4);
    assert(!isEmpty(&v));
    assert(getVectorValue(&v, 0) == 4);
    deleteVector(&v);
}

void test_pushBack_fullVector() {
    vector v = createVector(5);
    for (int i = 0; i < 5; i++) {
        pushBack(&v, i);
    }
    assert(isFull(&v));
    pushBack(&v, 6);
    assert(getVectorValue(&v, 5) == 6);
    deleteVector(&v);
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_atVector_notEmptyVector() {
    vector v = createVector(5);
    for (size_t i = 0; i < 5; ++i) {
        pushBack(&v, i);
    }
    int *element = atVector(&v, 1);
    assert(*element == 1);
    deleteVector(&v);
}

void test_atVector_requestToLastElement() {
    vector v = createVector(5);
    for (size_t i = 0; i < 5; ++i) {
        pushBack(&v, i);
    }
    int *element = atVector(&v, v.size - 1);
    assert(*element == 4);
    deleteVector(&v);
}

void test_back_oneElementInVector() {
    vector v = createVector(1);
    pushBack(&v, 42);
    int *element = back(&v);
    assert(*element == 42);
    deleteVector(&v);
}

void test_front_oneElementInVector() {
    vector v = createVector(1);
    pushBack(&v, 42);
    int *element = front(&v);
    assert(*element == 42);
    deleteVector(&v);
}

void test() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    test_back_oneElementInVector();
    test_front_oneElementInVector();
}

void test_swapRows() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );

    int *row1 = m.values[0];
    int *row2 = m.values[1];
    int *row3 = m.values[2];

    swapRows(m, 0, 2);

    assert(m.values[0] == row3);
    assert(m.values[2] == row1);

    freeMemMatrix(&m);
}

void test_swapColumns() {
    int nRows = 3;
    int nCols = 3;
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            nRows, nCols
    );

    int col1[nRows], col2[nRows], col3[nRows];
    for (int i = 0; i < nRows; i++) {
        col1[i] = m.values[i][0];
        col2[i] = m.values[i][1];
        col3[i] = m.values[i][2];
    }

    swapColumns(m, 0, 2);

    for (int i = 0; i < nRows; i++) {
        assert(m.values[i][0] == col3[i]);
        assert(m.values[i][2] == col1[i]);
    }

    freeMemMatrix(&m);
}

int rowSumCriteria(int *row, int nCols) {
    int sum = 0;
    for (int i = 0; i < nCols; i++) {
        sum += row[i];
    }

    return sum;
}

void test_insertionSortRowsMatrixByRowCriteria() {
    int nRows = 4;
    int nCols = 3;
    matrix m = createMatrixFromArray(
            (int[]) {
                    4, 5, 6,
                    1, 2, 3,
                    7, 8, 9,
                    10, 11, 12,
            },
            nRows, nCols
    );

    int expectedOrder[] = {1, 4, 7, 10};

    insertionSortRowsMatrixByRowCriteria(m, rowSumCriteria);

    for (int i = 0; i < nRows; i++) {
        assert(m.values[i][0] == expectedOrder[i]);
    }

    freeMemMatrix(&m);
}

int colSumCriteria(int *col, int nRows) {
    int sum = 0;
    for (int i = 0; i < nRows; ++i) {
        sum += col[i];
    }
    return sum;
}

void test_selectionSortColsMatrixByColCriteria() {
    int nRows = 3;
    int nCols = 3;
    matrix m = createMatrixFromArray(
            (int[]) {
                    4, 1, 7,
                    5, 2, 8,
                    6, 3, 9,
            },
            nRows, nCols
    );

    int expectedOrder[] = {1, 4, 7};

    selectionSortColsMatrixByColCriteria(m, colSumCriteria);

    for (int i = 0; i < nCols; i++) {
        assert(m.values[0][i] == expectedOrder[i]);
    }

    freeMemMatrix(&m);
}

void test_isSquareMatrix() {
    int nRows1 = 3;
    int nCols1 = 3;
    matrix m1 = getMemMatrix(nRows1, nCols1);
    assert(isSquareMatrix(&m1) == 1);

    int nRows2 = 2;
    int nCols2 = 3;
    matrix m2 = getMemMatrix(nRows2, nCols2);
    assert(isSquareMatrix(&m2) == 0);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_areTwoMatricesEqual() {
    int nRows = 3;
    int nCols = 3;
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 1,
                    2, 1, 2,
                    1, 2, 1,
            },
            nRows, nCols
    );
    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 1,
                    2, 1, 2,
                    1, 2, 1,
            },
            nRows, nCols
    );
    assert(areTwoMatricesEqual(&m1, &m2) == 1);

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    4, 1, 7,
                    5, 2, 8,
                    6, 3, 9,
            },
            nRows, nCols
    );
    matrix m4 = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9,
            },
            nRows, nCols
    );
    assert(areTwoMatricesEqual(&m3, &m4) == 0);

    matrix m5 = createMatrixFromArray(
            (int[]) {
                    1, 4,
                    2, 5,
                    3, 6,
            },
            3, 2
    );
    matrix m6 = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
            },
            2, 3
    );

    assert(areTwoMatricesEqual(&m5, &m6) == 0);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
    freeMemMatrix(&m4);
    freeMemMatrix(&m5);
    freeMemMatrix(&m6);
}

void test_isEMatrix() {
    int nRows = 3;
    int nCols = 3;
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,
            },
            nRows, nCols
    );
    assert(isEMatrix(&m1) == 1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9,
            },
            nRows, nCols
    );
    assert(isEMatrix(&m2) == 0);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_isSymmetricMatrix() {
    int nRows = 3;
    int nCols = 3;
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 4,
                    2, 1, 6,
                    4, 6, 1,
            },
            nRows, nCols
    );
    assert(isSymmetricMatrix(&m1) == 1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9,
            },
            nRows, nCols
    );
    assert(isSymmetricMatrix(&m2) == 0);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_transposeSquareMatrix() {
    int n = 3;
    matrix m = getMemMatrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m.values[i][j] = i * n + j;
        }
    }

    transposeSquareMatrix(&m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            assert(m.values[i][j] == j * n + i);
        }
    }

    freeMemMatrix(&m);
}

void test_transposeMatrix() {
    int nRows = 3;
    int nCols = 4;
    matrix m = getMemMatrix(nRows, nCols);
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            m.values[i][j] = i * nCols + j;
        }
    }

    transposeMatrix(&m);

    assert(m.nRows == nCols);
    assert(m.nCols == nRows);
    for (int i = 0; i < nCols; ++i) {
        for (int j = 0; j < nRows; ++j) {
            assert(m.values[i][j] == j * nCols + i);
        }
    }

    freeMemMatrix(&m);
}

void test_getMinValuePos() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    4, 1, 7,
                    5, 2, 8,
                    6, 3, 9,
            },
            3, 3
    );

    position expectedPos = {0, 1};
    position minPos = getMinValuePos(m);

    assert(minPos.rowIndex == expectedPos.rowIndex && minPos.colIndex == expectedPos.colIndex);

    freeMemMatrix(&m);
}

void test_getMaxValuePos() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    4, 1, 7,
                    5, 2, 8,
                    6, 3, 9,
            },
            3, 3
    );

    position expectedPos = {2, 2};
    position maxPos = getMaxValuePos(m);

    assert(maxPos.rowIndex == expectedPos.rowIndex && maxPos.colIndex == expectedPos.colIndex);

    freeMemMatrix(&m);
}

void test() {
    test_swapRows();
    test_swapColumns();
    test_insertionSortRowsMatrixByRowCriteria();
    test_selectionSortColsMatrixByColCriteria();
    test_isSquareMatrix();
    test_areTwoMatricesEqual();
    test_isEMatrix();
    test_isSymmetricMatrix();
    test_transposeSquareMatrix();
    test_transposeMatrix();
    test_getMinValuePos();
    test_getMaxValuePos();
}

void test_swapRowsWithMinMax() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 8, 6,
                    5, 7, 9,
            },
            3, 3
    );

    position minPos1 = {0, 0};
    position maxPos1 = {2, 2};

    swapRowsWithMinMax(m1);

    assert(m1.values[minPos1.rowIndex][2] == 9);
    assert(m1.values[maxPos1.rowIndex][0] == 1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    5, 2, 3,
                    4, 8, 6,
                    1, 7, 9,
            },
            3, 3
    );

    position minPos2 = {2, 0};
    position maxPos2 = {2, 2};

    swapRowsWithMinMax(m2);

    assert(m2.values[minPos2.rowIndex][2] == 9);
    assert(m2.values[maxPos2.rowIndex][0] == 1);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_sortRowsByMaxElement() {
    matrix m1 = getMemMatrix(3, 3);
    m1.values[0][0] = 5; m1.values[0][1] = 2; m1.values[0][2] = 3;
    m1.values[1][0] = 4; m1.values[1][1] = 8; m1.values[1][2] = 6;
    m1.values[2][0] = 1; m1.values[2][1] = 7; m1.values[2][2] = 9;

    sortRowsByMaxElement(m1);

    assert(m1.values[0][0] == 5 && m1.values[0][1] == 2 && m1.values[0][2] == 3);
    assert(m1.values[1][0] == 4 && m1.values[1][1] == 8 && m1.values[1][2] == 6);
    assert(m1.values[2][0] == 1 && m1.values[2][1] == 7 && m1.values[2][2] == 9);

    matrix m2 = getMemMatrix(3, 3);
    m2.values[0][0] = 1; m2.values[0][1] = 7; m2.values[0][2] = 9;
    m2.values[1][0] = 4; m2.values[1][1] = 8; m2.values[1][2] = 6;
    m2.values[2][0] = 5; m2.values[2][1] = 2; m2.values[2][2] = 3;

    sortRowsByMaxElement(m2);

    assert(m2.values[0][0] == 5 && m2.values[0][1] == 2 && m2.values[0][2] == 3);
    assert(m2.values[1][0] == 4 && m2.values[1][1] == 8 && m2.values[1][2] == 6);
    assert(m2.values[2][0] == 1 && m2.values[2][1] == 7 && m2.values[2][2] == 9);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_sortColsByMinElement() {
    matrix m = getMemMatrix(3, 3);
    m.values[0][0] = 3; m.values[0][1] = 5; m.values[0][2] = 2;
    m.values[1][0] = 2; m.values[1][1] = 5; m.values[1][2] = 1;
    m.values[2][0] = 6; m.values[2][1] = 1; m.values[2][2] = 4;

    sortColsByMinElement(m);

    assert(m.values[0][0] == 5 && m.values[0][1] == 2 && m.values[0][2] == 3);
    assert(m.values[1][0] == 5 && m.values[1][1] == 1 && m.values[1][2] == 2);
    assert(m.values[2][0] == 1 && m.values[2][1] == 4 && m.values[2][2] == 6);

    freeMemMatrix(&m);
}

void test_getSquareOfMatrixIfSymmetric() {
    matrix m = getMemMatrix(3, 3);
    m.values[0][0] = 1; m.values[0][1] = 2; m.values[0][2] = 3;
    m.values[1][0] = 2; m.values[1][1] = 4; m.values[1][2] = 5;
    m.values[2][0] = 3; m.values[2][1] = 5; m.values[2][2] = 6;

    getSquareOfMatrixIfSymmetric(&m);

    assert(m.values[0][0] == 14 && m.values[0][1] == 25 && m.values[0][2] == 31);
    assert(m.values[1][0] == 25 && m.values[1][1] == 45 && m.values[1][2] == 56);
    assert(m.values[2][0] == 31 && m.values[2][1] == 56 && m.values[2][2] == 70);

    freeMemMatrix(&m);
}

void test_transposeIfMatrixHasNotEqualSumOfRows() {
    matrix m1 = createMatrixFromArray((int[]){
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    }, 3, 3);

    transposeIfMatrixHasNotEqualSumOfRows(&m1);

    assert(m1.values[0][0] == 1 && m1.values[0][1] == 4 && m1.values[0][2] == 7);
    assert(m1.values[1][0] == 2 && m1.values[1][1] == 5 && m1.values[1][2] == 8);
    assert(m1.values[2][0] == 3 && m1.values[2][1] == 6 && m1.values[2][2] == 9);

    matrix m2 = createMatrixFromArray((int[]){
            1, 4, 7,
            2, 5, 5,
            1, 4, 9
    }, 3, 3);

    transposeIfMatrixHasNotEqualSumOfRows(&m2);

    assert(m2.values[0][0] == 1 && m2.values[0][1] == 4 && m2.values[0][2] == 7);
    assert(m2.values[1][0] == 2 && m2.values[1][1] == 5 && m2.values[1][2] == 5);
    assert(m2.values[2][0] == 1 && m2.values[2][1] == 4 && m2.values[2][2] == 9);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_isMutuallyInverseMatrices() {
    matrix m1 = createMatrixFromArray((int[]){
            1, 0,
            0, 1
    }, 2, 2);

    matrix m2 = createMatrixFromArray((int[]){
            1, 0,
            0, 1
    }, 2, 2);

    bool mutuallyInverse = isMutuallyInverseMatrices(m1, m2);

    assert(mutuallyInverse);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_findSumOfMaxesOfPseudoDiagonal() {
    matrix m = createMatrixFromArray((int[]){
            3, 2, 5, 4,
            1, 3, 6, 3,
            3, 2, 1, 2
    }, 3, 4);

    long long sum = findSumOfMaxesOfPseudoDiagonal(m);

    assert(sum == 20);

    freeMemMatrix(&m);
}

void test_getMinInArea() {
    matrix m = createMatrixFromArray((int[]){
            10, 7, 5, 6,
            3, 11, 8, 9,
            4, 1, 12, 2
    }, 3, 4);

    assert(getMinInArea(m) == 5);

    freeMemMatrix(&m);
}

void testSortByDistances() {
    int points[][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
            {10, 11, 12}
    };
    size_t nPoints = sizeof(points) / sizeof(points[0]);

    matrix m = createMatrixFromArray((int *)points, nPoints, 3);

    sortByDistances(m);

    float prevDistance = 0.0;
    for (size_t i = 0; i < nPoints; ++i) {
        float distance = getDistance(points[i], 3);
        assert(distance >= prevDistance);
        prevDistance = distance;
    }

    freeMemMatrix(&m);
}

void test_countEqClassesByRowsSum() {
    matrix m = createMatrixFromArray(
            (int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                     1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                     3, 3, 4, 5, 6, 7, 8, 9, 10, 1},
            3, 10
    );

    int eqClasses = countEqClassesByRowsSum(m);

    assert(eqClasses == 2);

    freeMemMatrix(&m);
}

void test_getNSpecialElement() {
    matrix m = createMatrixFromArray(
            (int[]) {3, 5, 5, 4,
                     2, 3, 6, 7,
                     12, 2, 1, 2},
            3, 4
    );

    int nSpecial = getNSpecialElement(m);

    assert(nSpecial == 2);

    freeMemMatrix(&m);
}

void test_swapPenultimateRow() {
    matrix m = createMatrixFromArray(
            (int[]) {1, 2, 3,
                     4, 5, 6,
                     7, 8, 1},
            3, 3
    );

    swapPenultimateRow(m);

    assert(m.values[1][0] == 1);
    assert(m.values[1][1] == 4);
    assert(m.values[1][2] == 7);

    freeMemMatrix(&m);
}

void test_countNonDescendingRowsMatrices() {
    int data1[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    int data2[3][3] = {
            {1, 2, 3},
            {6, 5, 4},
            {9, 8, 7}
    };

    matrix m1 = createMatrixFromArray((int *)data1, 3, 3);
    matrix m2 = createMatrixFromArray((int *)data2, 3, 3);

    int count1 = countNonDescendingRowsMatrices(&m1, 1);
    int count2 = countNonDescendingRowsMatrices(&m2, 1);

    assert(count1 == 1);
    assert(count2 == 0);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_countZeroRows() {
    matrix m1 = createMatrixFromArray(
            (int[]) {1, 2, 3,
                     4, 5, 6,
                     7, 8, 9},
            3, 3
    );
    assert(countZeroRows(m1) == 0);
    freeMemMatrix(&m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {1, 2, 3,
                     0, 0, 0,
                     7, 8, 9},
            3, 3
    );
    assert(countZeroRows(m2) == 1);
    freeMemMatrix(&m2);

    matrix m3 = createMatrixFromArray(
            (int[]) {0, 0, 0,
                     0, 0, 0,
                     7, 8, 9},
            3, 3
    );
    assert(countZeroRows(m3) == 2);
    freeMemMatrix(&m3);
}

void test_getNSpecialElement2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {2, 3, 5, 5, 4,
                     6, 2, 3, 8, 12,
                     12, 12, 2, 1, 2},
            3, 5
    );
    assert(getNSpecialElement2(m1) == 4);
    freeMemMatrix(&m1);
}

void test_getVectorIndexWithMaxAngle() {
    matrix m1 = createMatrixFromArray(
            (int[]) {1, 5, 4,
                     6, 2, 3,
                     2, 5, 2},
            3, 3
    );
    int v[3] = {1, 1, 1};
    assert(getVectorIndexWithMaxAngle(m1, v) == 1);
}

void test_getSpecialScalarProduct() {
    matrix m = createMatrixFromArray(
            (int[]) {1, 2, 3,
                     4, 5, 6,
                     7, 8, 9},
            3, 3
    );
    long long result = getSpecialScalarProduct(m);
    assert(result == 102);
}

void test() {
    test_swapRowsWithMinMax();
    test_sortRowsByMaxElement();
    test_sortColsByMinElement();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasNotEqualSumOfRows();
    test_isMutuallyInverseMatrices();
    test_findSumOfMaxesOfPseudoDiagonal();
    test_getMinInArea();
    testSortByDistances();
    test_countEqClassesByRowsSum();
    test_getNSpecialElement();
    test_swapPenultimateRow();
    test_countNonDescendingRowsMatrices();
    test_countZeroRows();
    test_getNSpecialElement2();
    test_getVectorIndexWithMaxAngle();
    test_getSpecialScalarProduct();
}*/

void test_strlen_() {
    const char *empty_str = "";
    assert(strlen_(empty_str) == 0);

    const char *str1 = "Hello";
    assert(strlen_(str1) == 5);

    const char *str2 = "Test";
    assert(strlen_(str2) == 4);

    const char *str3 = "   ";
    assert(strlen_(str3) == 3);
}

void test_find() {
    char str1[] = "Hello";
    char *result1 = find(str1, str1 + 5, 'e');
    assert(*result1 == 'e');

    char *result2 = find(str1, str1 + 5, 'x');
    assert(result2 == str1 + 5);

    char str2[] = "World";
    char *result3 = find(str2, str2 + 5, 'o');
    assert(*result3 == 'o');
}

void test_findNonSpace() {
    char str1[] = "   ";
    char *result1 = findNonSpace(str1);
    assert(*result1 == '\0');

    char str2[] = "   Hello";
    char *result2 = findNonSpace(str2);
    assert(*result2 == 'H');

    char str3[] = "\t\tWorld";
    char *result3 = findNonSpace(str3);
    assert(*result3 == 'W');
}

void test_findSpace() {
    char str1[] = "   ";
    char *result1 = findSpace(str1);
    assert(*result1 == ' ');

    char str2[] = "Hello";
    char *result2 = findSpace(str2);
    assert(*result2 == '\0');

    char str3[] = "   World";
    char *result3 = findSpace(str3);
    assert(*result3 == ' ');

    char str4[] = "\t\t\n";
    char *result4 = findSpace(str4);
    assert(*result4 == '\t');
}

void test_findNonSpaceReverse() {
    char str1[] = "   ";
    char *result1 = findNonSpaceReverse(str1 + 2, str1);
    assert(result1 == str1);

    char str2[] = "  Hello";
    char *result2 = findNonSpaceReverse(str2 + 6, str2);
    assert(*result2 == 'o');

    char str3[] = "World";
    char *result3 = findNonSpaceReverse(str3 + 5, str3);
    assert(result3 == str3 + 5);

    char str4[] = " \t\n";
    char *result4 = findNonSpaceReverse(str4 + 2, str4);
    assert(result4 == str4);
}

void test_findSpaceReverse() {
    char str1[] = "   ";
    char *result1 = findSpaceReverse(str1 + 2, str1);
    assert(result1 == str1 + 2);

    char str2[] = "Hello   ";
    char *result2 = findSpaceReverse(str2 + 6, str2);
    assert(result2 == str2 + 6);

    char str3[] = "World";
    char *result3 = findSpaceReverse(str3 + 5, str3);
    assert(result3 == str3);
}

void test_strcmp() {
    const char *str1 = "";
    const char *str2 = "";
    assert(strcmp(str1, str2) == 0);

    const char *str3 = "";
    const char *str4 = "Hello";
    assert(strcmp(str3, str4) < 0);

    const char *str5 = "World";
    const char *str6 = "";
    assert(strcmp(str5, str6) > 0);

    const char *str7 = "Hello";
    const char *str8 = "Hello";
    assert(strcmp(str7, str8) == 0);

    const char *str9 = "Hello";
    const char *str10 = "World";
    assert(strcmp(str9, str10) < 0);
}

void test_copy() {
    const char *source1 = "";
    char destination1[10] = "Hello";
    char *result1 = copy(source1, source1, destination1);
    assert(result1 == destination1);

    const char *source2 = "World";
    char destination2[10] = "Hello";
    char *result2 = copy(source2, source2 + 5, destination2 + 5);
    assert(strcmp(destination2 + 5, "WorldHello") == 0);
    assert(result2 == destination2 + 10);
}

void test_copyIf() {
    char source1[] = "Hello123World";
    char destination1[20] = "";
    char *result1 = copyIf(source1, source1 + 13, destination1, isalpha);
    assert(strcmp(destination1, "HelloWorld") == 0);
    assert(result1 == destination1 + 10);

    char source2[] = "12345abc";
    char destination2[20] = "";
    char *result2 = copyIf(source2, source2 + 8, destination2, isdigit);
    assert(strcmp(destination2, "12345") == 0);
    assert(result2 == destination2 + 5);
}

void test_copyIfReverse() {
    char source1[] = "Hello123World";
    char destination1[20] = "__________";
    char *result1 = copyIfReverse(source1 + 13, source1, destination1 + 10, isalpha);
    assert(strcmp(destination1, "HelloWorld") == 0);
    assert(result1 == destination1);

    char source2[] = "12345abc";
    char destination2[20] = "__________";
    char *result2 = copyIfReverse(source2 + 8, source2, destination2 + 5, isdigit);
    assert(strcmp(destination2, "12345_____") == 0);
    assert(result2 == destination2);
}

void assertString(const char *expected, char *got, const char *fileName, const char *funcName, int line) {
    if (strcmp(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else {
        fprintf(stderr, "%s - OK\n", funcName);
    }
}

#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __func__, __LINE__)

void test_removeNonLetters() {
    char s1[] = "Hi 123\tWorld\n!";
    removeNonLetters(s1);
    ASSERT_STRING("Hi123World!", s1);

    char s2[] = " \t\n\r\v\f";
    removeNonLetters(s2);
    ASSERT_STRING("", s2);

    char s3[] = "HelloWorld";
    removeNonLetters(s3);
    ASSERT_STRING("HelloWorld", s3);
}

void test_removeAdjacentEqualLetters() {
    char s1[] = "AAAAAA";
    removeAdjacentEqualLetters(s1);
    ASSERT_STRING("A", s1);

    char s2[] = "abcdefgh";
    removeAdjacentEqualLetters(s2);
    ASSERT_STRING("abcdefgh", s2);

    char s3[] = "";
    removeAdjacentEqualLetters(s3);
    ASSERT_STRING("", s3);

    char s4[] = "Hello World!";
    removeAdjacentEqualLetters(s4);
    ASSERT_STRING("Helo World!", s4);
}

void test_processString() {
    char s1[] = "Hello123 World456!";
    processString(s1);
    ASSERT_STRING("123Hello 456World!", s1);

    char s2[] = "This is a test string without digits.";
    processString(s2);
    ASSERT_STRING("This is a test string without digits.", s2);

    char s3[] = "1234567890";
    processString(s3);
    ASSERT_STRING("1234567890", s3);

    char s4[] = "";
    processString(s4);
    ASSERT_STRING("", s4);
}

void test_processStringEnd() {
    char s1[] = "123Hello 456World!";
    processString(s1);
    ASSERT_STRING("Hello123 World456!", s1);

    char s2[] = "This is a test string without digits.";
    processString(s2);
    ASSERT_STRING("This is a test string without digits.", s2);

    char s3[] = "1234567890";
    processString(s3);
    ASSERT_STRING("1234567890", s3);

    char s4[] = "";
    processString(s4);
    ASSERT_STRING("", s4);
}

void test_replaceDigitsWithSpaces() {
    char s1[] = "Hello1World1!";
    replaceDigitsWithSpaces(s1);
    ASSERT_STRING("Hello World !", s1);

    char s2[] = "2";
    replaceDigitsWithSpaces(s2);
    ASSERT_STRING("  ", s2);

    char s3[] = "Hello World!";
    replaceDigitsWithSpaces(s3);
    ASSERT_STRING("Hello World!", s3);

    char s4[] = "";
    replaceDigitsWithSpaces(s4);
    ASSERT_STRING("", s4);
}

void test_replace() {
    char source[] = "Hello world! Hello people! Hello everyone!";
    char expected[] = "Hi world! Hi people! Hi everyone!";
    char w1[] = "Hello";
    char w2[] = "Hi";

    replace(source, w1, w2);
    ASSERT_STRING(expected, source);
}

void test_areWordsLexicographicallyOrdered() {
    char sentence1[] = "apple banana cherry date";
    char sentence2[] = "apple banana date cherry";
    assert(areWordsLexicographicallyOrdered(sentence1) == 1);
    assert(areWordsLexicographicallyOrdered(sentence2) == 0);
}

void test_printWordsReversed() {
    char s1[] = "";
    printWordsReversed(s1);
    ASSERT_STRING("", s1);

    char s2[] = "word";
    printWordsReversed(s2);
    ASSERT_STRING("word", s2);

    char s3[] = "w o r";
    printWordsReversed(s3);
    ASSERT_STRING("r o w", s3);

    char s4[] = "Hello World";
    printWordsReversed(s4);
    ASSERT_STRING("World Hello", s4);
}

void test_countPalindromes() {
    char sentence[] = "level, rotor, car, world";
    int expected = 2;
    int actual = countPalindromes(sentence);
    assert(actual == expected);
}

void test_interleaveWords() {
    char s1[] = "apple banana cherry";
    char s2[] = "orange lemon";
    char expected[] = "apple orange banana lemon cherry ";

    char result[33];
    interleaveWords(s1, s2, result);

    ASSERT_STRING(expected, result);
}

void test_changeWordOrder() {
    char s1[] = "";
    changeWordOrder(s1);
    ASSERT_STRING("", s1);

    char s2[] = "hello world";
    changeWordOrder(s2);
    ASSERT_STRING("world hello", s2);

    char s3[] = "word";
    changeWordOrder(s3);
    ASSERT_STRING("word", s3);
}

void test_getWordBeforeFirstWordWithA() {
    WordDescriptor word;
    char s1[] = "";
    assert(getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING);
    char s2[] = "ABC";
    assert(getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A);
    char s3[] = "BC A";
    assert(getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND);
    char got[20];
    copy(word.begin, word.end, got);
    got[word.end - word.begin] = '\0';
    ASSERT_STRING("bc", got);
    char s4[] = "B Q WE YR OW IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

void test_getLastCommonWord() {
    char s1[] = "Hello World";
    char s2[] = "World Around";

    char dest1[MAX_WORD_SIZE] = "";
    WordDescriptor word1 = getLastCommonWord(s1, s2);

    WordDescriptorToString(word1, dest1);

    ASSERT_STRING("World", dest1);

    char s3[] = "Hello World";
    char s4[] = "Hi Globe";

    char dest2[MAX_WORD_SIZE] = "";
    WordDescriptor word2 = getLastCommonWord(s3, s4);

    assert(word2.begin == NULL && word2.end == NULL);
}

void test_areEqualWordsInString() {
    char s1[] = "";
    assert(!areEqualWordsInString(s1));

    char s2[] = "word";
    assert(!areEqualWordsInString(s2));

    char s3[] = "Duplicate not in string";
    assert(!areEqualWordsInString(s3));

    char s4[] = "duplicate duplicate";
    assert(areEqualWordsInString(s4));
}

void test_areIdenticalWordsInString() {
    char s1[] = "";
    assert(!areIdenticalWordsInString(s1));

    char s2[] = "word";
    assert(!areIdenticalWordsInString(s2));

    char s3[] = "Duplicate not in string";
    assert(!areIdenticalWordsInString(s3));

    char s4[] = "duplicate etacilpud";
    assert(areIdenticalWordsInString(s4));
}

void test_getWordExceptLast() {
    char source1[] = "";
    char dest1[40] = "";

    getWordExceptLast(source1, dest1);

    ASSERT_STRING("", dest1);

    char source2[] = "word";
    char dest2[40] = "";

    getWordExceptLast(source2, dest2);

    ASSERT_STRING("", dest2);

    char source3[] = "word map";
    char dest3[40] = "";

    getWordExceptLast(source3, dest3);

    ASSERT_STRING("word", dest3);

    char source4[] = "word map is map";
    char dest4[40] = "";

    getWordExceptLast(source4, dest4);

    ASSERT_STRING("word is", dest4);
}

void test_getPrecedingWord() {
    char s1[] = "";
    char s2[] = "";

    char dest1[40] = "";
    WordDescriptor word1 = getPrecedingWord(s1, s2);

    WordDescriptorToString(word1, dest1);

    ASSERT_STRING("", dest1);

    char s3[] = "A B C";
    char s4[] = "Hello World";

    char dest2[40] = "";
    WordDescriptor word2 = getPrecedingWord(s3, s4);

    WordDescriptorToString(word2, dest2);

    ASSERT_STRING("", dest2);

    char s5[] = "Hello World";
    char s6[] = "Cool 3D World";

    char dest3[40] = "";
    WordDescriptor word3 = getPrecedingWord(s5, s6);

    WordDescriptorToString(word3, dest3);

    ASSERT_STRING("Hello", dest3);
}

void test_removePalindromeWord() {
    char s1[] = "";
    removePalindromeWord(s1);
    ASSERT_STRING("", s1);

    char s2[] = "Hello World";
    removePalindromeWord(s2);
    ASSERT_STRING("Hello World", s2);

    char s3[] = "a b c d";
    removePalindromeWord(s3);
    ASSERT_STRING("", s3);

    char s4[] = "radar level rotor";
    removePalindromeWord(s4);
    ASSERT_STRING("", s4);
}

void test_balanceString() {
    char s1[100] = "";
    size_t n1 = 0;

    char s2[100] = "";
    size_t n2 = 0;

    balanceString(s1, n1, s2, n2);

    ASSERT_STRING("", s1);
    ASSERT_STRING("", s2);

    char s3[100] = "";
    size_t n3 = 0;

    char s4[100] = "hello world";
    size_t n4 = 2;

    balanceString(s3, n3, s4, n4);

    ASSERT_STRING(" hello world", s3);
    ASSERT_STRING("hello world", s4);

    char s5[100] = "hello world";
    size_t n5 = 2;

    char s6[100] = "hi globe";
    size_t n6 = 2;

    balanceString(s5, n5, s6, n6);

    ASSERT_STRING("hello world", s5);
    ASSERT_STRING("hi globe", s6);

    char s7[100] = "hello";
    size_t n7 = 1;

    char s8[100] = "cool 3d world";
    size_t n8 = 3;

    balanceString(s7, n7, s8, n8);

    ASSERT_STRING("hello 3d world", s7);
    ASSERT_STRING("cool 3d world", s8);
}

void test_isEveryWordLetterInString() {
    char string1[] = "";
    WordDescriptor word1;
    getWord("", &word1);

    assert(!isEveryWordLetterInString(string1, word1));

    char string2[] = "word";
    WordDescriptor word2;
    getWord("", &word2);

    assert(!isEveryWordLetterInString(string2, word2));

    char string3[] = "";
    WordDescriptor word3;
    getWord("word", &word3);

    assert(!isEveryWordLetterInString(string3, word3));

    char string4[] = "abc";
    WordDescriptor word4;
    getWord("word", &word4);

    assert(!isEveryWordLetterInString(string4, word4));

    char string5[] = "world";
    WordDescriptor word5;
    getWord("word", &word5);

    assert(isEveryWordLetterInString(string5, word5));
}

void test() {
    /*test_strlen_();
    test_find();
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();
    test_strcmp();
    test_copy();
    test_copyIf();
    test_copyIfReverse();*/
    test_removeNonLetters();
    test_removeAdjacentEqualLetters();
    test_processString();
    test_processStringEnd();
    test_replaceDigitsWithSpaces();
    test_replace();
    test_areWordsLexicographicallyOrdered();
    test_printWordsReversed();
    test_countPalindromes();
    test_interleaveWords();
    test_changeWordOrder();
    test_getWordBeforeFirstWordWithA();
    test_getLastCommonWord();
    test_areEqualWordsInString();
    test_areIdenticalWordsInString();
    test_getWordExceptLast();
    test_getPrecedingWord();
    test_removePalindromeWord();
    test_balanceString();
    test_isEveryWordLetterInString();
}

int main() {
    test();

    return 0;
}