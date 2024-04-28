#ifndef ARRAY_STRING__H
#define ARRAY_STRING__H

#define MAX_WORD_SIZE 30
#define MAX_N_WORDS_IN_STRING 100
#define MAX_STRING_SIZE 200

extern char stringBuffer_[MAX_STRING_SIZE + 1];

//возвращает количество символов в строке не считая ноль-символ
size_t strlen_(const char *begin);

//возвращает указатель на первый элемент с кодом ch, расположенным
//на ленте памяти между адресами begin и end не включая end
//Если символ не найден, возвращается значение end
char *find(char *begin, char *end, int ch);

//возвращает указатель на первый символ, отличный от пробельных, расположенный на ленте памяти,
//начиная с begin и заканчивая ноль-символом. Если символ не найден, возвращается адрес первого ноль-символа
char *findNonSpace(char *begin);

//возвращает указатель на первый пробельный символ, расположенный на ленте памяти
//начиная с адреса begin или на первый ноль-символ
char *findSpace(char *begin);

//возвращает указатель на первый справа символ, отличный от пробельных, расположенный
//на ленте памяти, начиная с rbegin и заканчивая rend. Если символ не найден,
//возвращается адрес rend
char *findNonSpaceReverse(char *rbegin, const char *rend);

//возвращает указатель на первый пробельный символ справа, расположенный
//на ленте памяти, начиная с rbegin и заканчивая rend. Если символ не найден,
//возвращается адрес rend
char *findSpaceReverse(char *rbegin, const char *rend);

//возвращает отрицательное значение, если lhs располагается до rhs
//в лексикографическом порядке, значение 0, если lhs и rhs
//равны, иначе – положительное значение
int strcmp(const char *lhs, const char *rhs);

//записывает по адресу beginDestination
//фрагмент памяти, начиная с адреса beginSource до endSource.
//Возвращает указатель на следующий свободный фрагмент памяти в destination
char* copy(const char *beginSource, const char *endSource, char *beginDestination);

//записывает по адресу beginDestination элементы из фрагмента памяти начиная с beginSource
//заканчивая endSource, удовлетворяющие функции-предикату f. Функция
//возвращает указатель на следующий свободный для записи фрагмент в памяти
char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int));

//записывает по адресу beginDestination элементы из фрагмента памяти начиная с rbeginSource
//заканчивая rendSource, удовлетворяющие функции-предикату f.
//Функция возвращает значение beginDestination по окончанию работы функции
char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int));

//удаляет из строки все пробельные символы
void removeNonLetters(char *s);

//Преобразует строку, оставляя только один символ
//в каждой последовательности подряд идущих одинаковых символов
void removeAdjacentEqualLetters(char *s);

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

void processString(char *beginString);

void processStringEnd(char *beginString);

void replaceDigitsWithSpaces(char *s);

void replace(char *source, char *w1, char *w2);

int areWordsEqual(WordDescriptor w1, WordDescriptor w2);

int areWordsLexicographicallyOrdered(char *sentence);

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

extern BagOfWords bag_;
extern BagOfWords bag2_;

void getBagOfWords(BagOfWords *bag, char *s);

void printWordsReversed(BagOfWords *bag);

int isPalindrome(WordDescriptor* word);

int countPalindromes(char *sentence);

char *interleaveWords(char *s1, char *s2, char *result);

void changeWordOrder(char *s);

typedef enum WordBeforeFirstWordWithAReturnCode {
    EMPTY_STRING,
    NOT_FOUND_A_WORD_WITH_A,
    FIRST_WORD_WITH_A,
    WORD_FOUND
} WordBeforeFirstWordWithAReturnCode;

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char* s, WordDescriptor* word);

WordDescriptor getLastCommonWord(char* s1, char* s2);

void WordDescriptorToString(WordDescriptor word, char* dest);

bool areEqualWordsInString(char* s);

bool areIdenticalWordsInString(char* s);

void getWordExceptLast(char* source, char* dest);

WordDescriptor getPrecedingWord(char* s1, char* s2);

#endif //ARRAY_STRING__H