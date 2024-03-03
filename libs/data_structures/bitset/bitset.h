#ifndef ARRAY_BITSET_H
#define ARRAY_BITSET_H

#include <stdbool.h>
#include <stdint.h>

typedef struct bitset {
    uint32_t values;
    uint32_t max_value;
} bitset;

// возвращает пустое множество с универсумом 0, 1, ..., max_value
bitset bitset_create(unsigned max_value);

// возвращает множество, состоящее из элементов массива a размера size, и количеством элементов max_value
bitset bitset_create_from_array(const unsigned int a[], size_t size, unsigned max_value);

// возвращает true, если value является элементов set
// иначе false
bool bitset_in(bitset set, unsigned value);

// возвращает true, если set1 и set2 равны
// иначе false
bool bitset_isEqual(bitset set1, bitset set2);

// возвращает true, если subset является подмножеством set
// иначе false
bool bitset_isSubset(bitset subset, bitset set);

// вставка элемента value в множество set
void bitset_insert(bitset *set, unsigned value);

// удаление элемента value из множества set
void bitset_deleteElement(bitset *set, unsigned value);

// возвращает объединение множества set1 и set2
bitset bitset_union(bitset set1, bitset set2);

// возвращает пересечение множеств set1 и set2
bitset bitset_intersection(bitset set1, bitset set2);

// возвращает разность множеств set1 и set2
bitset bitset_difference(bitset set1, bitset set2);

// возвращает симметричную разность множеств set1 и set2
bitset bitset_symmetricDifference(bitset set1, bitset set2);

// возвращает дополнение множества set до универсума
bitset bitset_complement(bitset set);

// выводит множество set
void bitset_print(bitset set);

#endif //ARRAY_BITSET_H