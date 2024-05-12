#ifndef ARRAY_VECTORVOID_H
#define ARRAY_VECTORVOID_H

#include <limits.h>

typedef struct vectorVoid {
    void *data; // указатель на нулевой элемент вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
    size_t baseTypeSize; // размер базового типа
} vectorVoid;

//возвращает структуру-дескриптор вектор из n значений, размер базового типа - baseTypeSize
vectorVoid createVectorV(size_t n, size_t baseTypeSize);

//изменяет количество памяти, выделенное под хранение элементов вектора
void reserveV(vectorVoid *v, size_t newCapacity);

//удаляет элементы из контейнера, но не освобождает выделенную память
void clearV(vectorVoid *v);

//освобождает память, выделенную под неиспользуемые элементы
void shrinkToFitV(vectorVoid *v);

//освобождает память, выделенную вектору
void deleteVectorV(vectorVoid *v);

//проверка на то, является ли вектор пустым
bool isEmptyV(vectorVoid *v);

//проверка на то, является ли вектор полным
bool isFullV(vectorVoid *v);

//записывает по адресу destination index-ый элемент вектора v
void getVectorValueV(vectorVoid *v, size_t index, void *destination);

//записывает на index-ый элемент вектора v значение, расположенное по адресу source
void setVectorValueV(vectorVoid *v, size_t index, const void *source);

//удаляет последний элемент из вектора
void popBackV(vectorVoid *v);

//добавляет элемент по адресу source в конец вектора v. Если вектор заполнен,
//увеличвает количество выделенной ему памяти в 2 раза, используя reserveV
void pushBackV(vectorVoid *v, void *source);

void generateFloat(const char* filename, int n);

void convertFloat(const char* filename);

typedef struct monomial {
    size_t degree;
    double coefficient;
} monomial;

void generatePolynomial(const char* filename);

double getMonomialValue(monomial mono, double x);

void removeTruePolynomial(const char* filename, double x);

void printPolynomial(const char* filename);

#endif //ARRAY_VECTORVOID_H