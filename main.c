#include <stdio.h>
#include <string.h>
#include "libs/algorithms/array/array.h"
#include "libs/data_structures/bitset/bitset.h"
#include "libs/data_structures/unordered_array_set/unordered_array_set.h"
#include "libs/data_structures/ordered_array_set/ordered_array_set.h"
#include "libs/data_structures/matrix/matrix.h"
#include "libs/data_structures/vector/vectorVoid.h"

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
}*/

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

void test() {
    test_swapRowsWithMinMax();
    test_sortRowsByMaxElement();
    test_sortColsByMinElement();
}

int main() {
    test();

    return 0;
}