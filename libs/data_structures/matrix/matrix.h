#ifndef ARRAY_MATRIX_H
#define ARRAY_MATRIX_H

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

//размещает в динамической памяти матрицу размером nRows на nCols, возвращает матрицу
matrix getMemMatrix(int nRows, int nCols);

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols,
//возвращает указатель на нулевую матрицу
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

//освобождает память, выделенную под хранение матрицы m
void freeMemMatrix(matrix *m);

//освобождает память, выделенную под хранение массива ms из nMatrices матриц
void freeMemMatrices(matrix *ms, int nMatrices);

//ввод матрицы m
void inputMatrix(matrix *m);

//ввод массива из nMatrices матриц, хранящейся по адресу ms
void inputMatrices(matrix *ms, int nMatrices);

//вывод матрицы m
void outputMatrix(matrix m);

//вывод массива из nMatrices матриц, хранящегося по адресу ms
void outputMatrices(matrix *ms, int nMatrices);

//обмен строк с порядковыми номерами i1 и i2 в матрице m
void swapRows(matrix m, int i1, int i2);

//обмен колонок с порядковыми номерами j1 и j2 в матрице m
void swapColumns(matrix m, int j1, int j2);

//выполняет сортировку вставками строк матрицы m
//по неубыванию значения функции criteria, применяемой для строк
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int));

//выполняет сортировку выбором столбцов матрицы m
//по неубыванию значения функции criteria, применяемой для столбцов
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int));

//возвращает значение ’истина’, если матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix *m);

//возвращает значение ’истина’, если матрицы m1 и m2 равны, ложь – в противном случае
bool areTwoMatricesEqual(matrix *m1, matrix *m2);

//возвращает значение ’истина’, если матрица m является единичной, ложь – в противном случае
bool isEMatrix(matrix *m);

//возвращает значение ’истина’, если матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix *m);

//транспонирует квадратную матрицу m
void transposeSquareMatrix(matrix *m);

//транспонирует матрицу m
void transposeMatrix(matrix *m);

//возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m);

//возвращает позицию максимального элемента матрицы m
position getMaxValuePos(matrix m);

//возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, int nRows, int nCols);

//возвращает указатель на нулевую матрицу массива из nMatrices матриц,
//размещенных в динамической памяти, построенных из элементов массива a
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols);

//меняет местами строки матрицы m, все элементы которой различны,
//в которых находятся максимальный и минимальный элементы
void swapRowsWithMinMax(matrix m);

//возвращает наибоьший элемент в строке матрицы
int getMax(int *a, int n);

//возвращает наменьший элемент в строке матрицы
int getMin(int *a, int n);

//упорядочивает строки матрицы по неубыванию наибольших элементов строк
void sortRowsByMaxElement(matrix m);

//Упорядочивает столбцы матрицы по неубыванию минимальных элементов столбцов
void sortColsByMinElement(matrix m);

//возвращает матрицу, являющуюся результатом умножения матрицы m1 на матрицу m2
matrix mulMatrices(matrix m1, matrix m2);

//заменяет матрицу m матрицей m^2, если она является симметричной
void getSquareOfMatrixIfSymmetric(matrix *m);

//возвращает значение ’истина’, если в a нет одинаковых элементов, ложь – в противном случае
bool isUnique(long long *a, int n);

//возвращает сумму элементов строки a длины n
long long getSum(int *a, int n);

//транспонирует матрицу, если среди сумм элементов строк матрицы нет равных
void transposeIfMatrixHasNotEqualSumOfRows(matrix *m);

//возвращает значение ’истина’, если матрицы взаимно обратны, ложь – в противном случае
bool isMutuallyInverseMatrices(matrix m1, matrix m2);

int max(int a, int b);

int min(int a, int b);

//возвращает сумму максимальных элементов всех псевдодиагоналей данной матрицы
long long findSumOfMaxesOfPseudoDiagonal(matrix m);

//возвращает минимальный элемент матрицы в выделенной области
int getMinInArea(matrix m);

//возвращает расстояние от точки до начала координат
float getDistance(int *a, int n);

//функция для сравнения расстояний от точек до начала координат
int compareDistances(int *point, int n);

//выполняет сортировку точек по неубыванию их расстояний до начала координат
void sortByDistances(matrix m);

int cmp_long_long(const void *pa, const void *pb);

//возвращает количество уникальных элементов в отсортированном массиве
int countNUnique(long long *a, int n);

//возвращает количество классов эквивалентности по суммам строк матрицы
int countEqClassesByRowsSum(matrix m);

//возвращает количество "особых" элементов матрицы, считая
//элемент "особым" , если он больше суммы остальных элементов своего столбца.
int getNSpecialElement(matrix m);

void swapPenultimateRow(matrix m);

bool isNonDescendingSorted(int *a, int n);

bool hasAllNonDescendingRows(matrix m);

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix);

int countValues(const int *a, int n, int value);

int countZeroRows(matrix m);

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix);

int maxNorm(matrix m);

void printMatrixsWithMinNorm(matrix *matrices, int nMatrices);

int getNSpecialElement2(matrix m);

double getScalarProduct(int *a, int *b, int n);

double getVectorLength(int *a, int n);

double getCosine(int *a, int *b, int n);

int getVectorIndexWithMaxAngle(matrix m, int *v);

long long getScalarProductRowAndCol(matrix m, int i, int j);

long long getSpecialScalarProduct(matrix m);

#endif //ARRAY_MATRIX_H