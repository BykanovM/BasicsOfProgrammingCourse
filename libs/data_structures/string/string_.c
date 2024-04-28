#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <memory.h>
#include <stdlib.h>
#include "../../data_structures/string/string_.h"

size_t strlen_(const char *begin) {
    const char *end = begin;
    while (*end != '\0') {
        end++;
    }

    return end - begin;
}

char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch) {
        begin++;
    }

    return begin;
}

char *findNonSpace(char *begin) {
    while (*begin != '\0' && isspace(*begin)) {
        begin++;
    }

    return begin;
}

char *findSpace(char *begin) {
    while (*begin != '\0' && !isspace(*begin)) {
        begin++;
    }

    return begin;
}

char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && isspace(*rbegin)) {
        rbegin--;
    }

    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && !isspace(*rbegin)) {
        rbegin--;
    }

    return rbegin;
}

int strcmp(const char *lhs, const char *rhs) {
    while (*lhs && *rhs && *lhs == *rhs) {
        lhs++;
        rhs++;
    }

    return *lhs - *rhs;
}

char *copy(const char *beginSource, const char *endSource, char *beginDestination) {
    size_t size = endSource - beginSource;
    memcpy(beginDestination, beginSource, size);
    return beginDestination + size;
}

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    while (beginSource != endSource) {
        if (f(*beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }

    return beginDestination;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)) {
    while (rbeginSource != rendSource) {
        if (f(*(rbeginSource - 1))) {
            *(beginDestination - 1) = *(rbeginSource - 1);
            beginDestination--;
        }
        rbeginSource--;
    }

    return beginDestination;
}

void removeNonLetters(char *s) {
    char *endSource = s + strlen_(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void removeAdjacentEqualLetters(char *s) {
    if (s == NULL || *s == '\0') {
        return;
    }

    char *destination = s;
    char *source = s + 1;

    while (*source != '\0') {
        if (*source != *destination) {
            *(++destination) = *source;
        }
        source++;
    }

    *(++destination) = '\0';
}

char stringBuffer_[MAX_STRING_SIZE + 1];

void freeString(char* string) {
    char* ptr = string;
    while (*ptr) {
        *ptr = '\0';
        ptr++;
    }
}

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end, stringBuffer_);

    char *recPosition = copyIfReverse(endStringBuffer - 1, stringBuffer_ - 1,
                                      word.begin, isdigit);
    copyIf(stringBuffer_, endStringBuffer, recPosition, isalpha);
}

void digitToEnd(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end, stringBuffer_);

    char *recPosition = copyIf(endStringBuffer - 1, word.begin - 1,
                               endStringBuffer, isdigit);
    copyIf(word.begin, endStringBuffer, recPosition, isalpha);
}

void processString(char *beginString) {
    char *beginSearch = beginString;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {
        digitToStart(word);
        beginSearch = word.end;
    }
}

void processStringEnd(char *beginString) {
    char *beginSearch = beginString;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {
        digitToEnd(word);
        beginSearch = word.end;
    }
}

void replaceDigitsWithSpaces(char *s) {
    char *bufferPtr = s;

    while (*s != '\0') {
        if (isdigit(*s)) {
            int digit = *s - '0';
            for (int j = 0; j < digit; j++) {
                *bufferPtr++ = ' ';
            }
        } else {
            *bufferPtr++ = *s;
        }
        s++;
    }

    *bufferPtr = '\0';
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};

    char *readPtr, *recPtr;

    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, source + strlen_(source), stringBuffer_);
        readPtr = stringBuffer_;
        recPtr = source;
    }

    while (*readPtr != '\0') {
        WordDescriptor currentWord;
        currentWord.begin = readPtr;
        currentWord.end = findSpace(readPtr);

        if (strcmp(currentWord.begin, word1.begin) == 0) {
            recPtr = copy(word2.begin, word2.end, recPtr);
            readPtr = currentWord.end;
        } else {
            recPtr = copy(currentWord.begin, currentWord.end, recPtr);
            readPtr = currentWord.end;
        }

        if (*readPtr != '\0') {
            *recPtr++ = *readPtr++;
        }
    }

    *recPtr = '\0';
}

int areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    while (w1.begin < w1.end && w2.begin < w2.end) {
        if (*w1.begin != *w2.begin) {
            return 0;
        }
        w1.begin++;
        w2.begin++;
    }
    if (w1.begin == w1.end && w2.begin == w2.end) {
        return 1;
    } else {
        return 0;
    }
}

int areWordsLexicographicallyOrdered(char *sentence) {
    WordDescriptor prevWord, currWord;
    prevWord.begin = sentence;
    prevWord.end = sentence;

    while (*prevWord.end != '\0') {
        while (*prevWord.end != '\0' && isspace(*prevWord.end)) {
            prevWord.end++;
        }
        if (*prevWord.end == '\0') {
            break;
        }

        currWord.begin = prevWord.end;
        while (*prevWord.end != '\0' && !isspace(*prevWord.end)) {
            prevWord.end++;
        }
        currWord.end = prevWord.end;

        if (!areWordsEqual(prevWord, currWord)) {
            return 0;
        }

        prevWord = currWord;
    }

    return 1;
}

BagOfWords bag_ = {.words = NULL, .size = 0};
BagOfWords bag2_ = {.words = NULL, .size = 0};

void getBagOfWords(BagOfWords *bag, char *s) {
    size_t i = 0;
    bag->size = 0;

    while (*s != '\0' && isspace(*s)) {
        s++;
    }

    while (*s != '\0') {
        bag->words[i].begin = s;

        while (*s != '\0' && !isspace(*s)) {
            s++;
        }
        bag->words[i].end = s;

        while (*s != '\0' && isspace(*s)) {
            s++;
        }

        i++;
    }

    bag->size = i;
}

void freeBag(BagOfWords* bag) {
    for (size_t i = 0; i < bag->size; i++) {
        bag->words[i].begin = NULL;
        bag->words[i].end = NULL;
    }

    bag->size = 0;
}

void printWordsReversed(BagOfWords *bag) {
    for (int i = bag->size - 1; i >= 0; i--) {
        for (char *p = bag->words[i].begin; p < bag->words[i].end; p++) {
            printf("%c", *p);
        }
        printf("\n");
    }
}

bool getWordReverse(char* r_begin, char* r_end, WordDescriptor* word) {
    if (word->begin == r_end)
        return false;

    word->end = findNonSpaceReverse(r_begin, r_end);

    word->begin = findNonSpaceReverse(r_begin, r_end);
    word->begin = word->begin == r_end ? word->begin : word->begin + 1;

    return true;
}

int getSeparateWord(char* begin_search, WordDescriptor* word) {
    word->begin = findNonSpace(begin_search);
    if (*word->begin == '\0')
        return false;

    word->end = findSpace(word->begin);

    if (ispunct(*(word->end - 1)))
        word->end--;

    return true;
}

int isPalindrome(WordDescriptor* word) {
    char* start = word->begin;
    char* end = word->end - 1;

    while (start < end) {
        if (*start != *end)
            return 0;

        start++;
        end--;
    }

    return 1;
}

int countPalindromes(char *sentence) {
    int count = 0;
    char *start = sentence;
    WordDescriptor word;

    while (getSeparateWord(start, &word)) {
        if (isPalindrome(&word))
            count++;

        if (ispunct(*(word.end)))
            word.end++;

        start = word.end;
    }

    return count;
}

char *interleaveWords(char *s1, char *s2, char *result) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *resultPtr = result;

    char *beginSearch1 = s1, *beginSearch2 = s2;
    while ((isW1Found = getWord(beginSearch1, &word1)), (isW2Found = getWord(beginSearch2, &word2)), isW1Found || isW2Found) {
        if (isW1Found) {
            while (word1.begin != word1.end) {
                *resultPtr++ = *word1.begin++;
            }
            *resultPtr++ = ' ';
            beginSearch1 = word1.end;
        }

        if (isW2Found) {
            while (word2.begin != word2.end) {
                *resultPtr++ = *word2.begin++;
            }
            *resultPtr++ = ' ';
            beginSearch2 = word2.end;
        }
    }

    *resultPtr = '\0';

    return result;
}

void changeWordOrder(char *s) {
    if (strlen_(s) == 0)
        return;

    char* rec_ptr = s;

    char* r_buffer_begin = copy(s, s + strlen_(s), stringBuffer_) - 1;
    char* r_buffer_end = stringBuffer_;

   WordDescriptor word;
    while (getWordReverse(r_buffer_begin, r_buffer_end, &word)) {
        rec_ptr = copy(word.begin, word.end + 1, rec_ptr);
        if (word.begin != r_buffer_end) {
            *rec_ptr++ = ' ';
        }

        r_buffer_begin = word.begin - 2;
    }

    *rec_ptr = '\0';

    freeString(stringBuffer_);
}

bool isLettersInWord(WordDescriptor word, char letters) {
    char* start = word.begin;

    while (start != word.end) {
        if (*start == letters)
            return true;

        start++;
    }

    return false;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char* s, WordDescriptor* word) {
    char* begin_search = s;

    WordDescriptor word1;
    if (!getWord(begin_search, &word1)) {
        return EMPTY_STRING;
    }
    begin_search = word1.end + 1;

    if (isLettersInWord(word1, 'a') || isLettersInWord(word1, 'A')) {
        return FIRST_WORD_WITH_A;
    }

    WordDescriptor word2;
    while (getWord(begin_search, &word2)) {
        if (isLettersInWord(word2, 'a') || isLettersInWord(word2, 'A')) {
            *word = word1;
            return WORD_FOUND;
        }

        word1 = word2;

        begin_search = word2.end + 1;
    }

    return NOT_FOUND_A_WORD_WITH_A;
}

bool isWordEqual(const WordDescriptor word1, const WordDescriptor word2) {
    char* begin1 = word1.begin;
    char* begin2 = word2.begin;

    while (begin1 < word1.end && begin2 < word2.end) {
        if (*begin1 != *begin2)
            return false;

        begin1++;
        begin2++;
    }

    if (word1.end - begin1 > 0 || word2.end - begin2 > 0)
        return false;

    return true;
}

bool getWordWithoutSpace(char* begin_search, WordDescriptor* word) {
    word->begin = findNonSpace(begin_search);
    if (*word->begin == '\0')
        return false;

    word->end = findSpace(word->begin) - 1;

    return true;
}

WordDescriptor getLastCommonWord(char* s1, char* s2) {
    char* begin_search_1 = s1;
    char* begin_search_2 = s2;

    while (getWordWithoutSpace(begin_search_1, &bag_.words[bag_.size])) {
        begin_search_1 = bag_.words[bag_.size].end + 1;
        bag_.size++;
    }

    while (getWordWithoutSpace(begin_search_2, &bag2_.words[bag2_.size])) {
        begin_search_2 = bag2_.words[bag2_.size].end + 1;
        bag2_.size++;
    }

    WordDescriptor word = {.begin = NULL, .end = NULL};
    for (int i = (int) bag_.size - 1; i >= 0; i--)
        for (int j = 0; j < bag2_.size; j++)
            if (isWordEqual(bag_.words[i], bag2_.words[j])) {
                word = bag_.words[i];

                freeBag(&bag_);
                freeBag(&bag2_);

                return word;
            }

    return word;
}

void WordDescriptorToString(WordDescriptor word, char* dest) {
    if (word.begin == NULL && word.end == NULL)
        return;

    while (word.begin <= word.end) {
        *dest = *word.begin;
        word.begin++;
        dest++;
    }

    *dest = '\0';
}

bool areEqualWordsInString(char* s) {
    char* begin_buff = stringBuffer_;

    copy(s, s + strlen_(s), stringBuffer_);

    while (getWordWithoutSpace(begin_buff, &bag_.words[bag_.size])) {
        begin_buff = bag_.words[bag_.size].end + 2;
        bag_.size++;
    }

    freeString(stringBuffer_);

    if (bag_.size <= 1)
        return 0;

    for (size_t i = 0; i < bag_.size; i++)
        for (size_t j = i + 1; j < bag_.size; j++)
            if (isWordEqual(bag_.words[i], bag_.words[j])) {
                freeBag(&bag_);
                return 1;
            }

    freeBag(&bag_);
    return 0;
}

int compareLetters(const void* s1, const void* s2) {
    return *(char *) s1 - *(char *) s2;
}

void sortWordLetters(WordDescriptor* word) {
    qsort(word->begin, word->end - word->begin,
          sizeof(char), compareLetters);
}

bool areIdenticalWordsInString(char* s) {
    char* begin_buff = stringBuffer_;

    copy(s, s + strlen_(s), stringBuffer_);

    while (getWordWithoutSpace(begin_buff, &bag_.words[bag_.size])) {
        begin_buff = bag_.words[bag_.size].end + 2;
        bag_.size++;
    }

    freeString(stringBuffer_);

    if (bag_.size <= 1)
        return 0;

    for (size_t i = 0; i < bag_.size; i++)
        sortWordLetters(&bag_.words[i]);

    for (size_t i = 0; i < bag_.size; i++)
        for (size_t j = i + 1; j < bag_.size; j++)
            if (isWordEqual(bag_.words[i], bag_.words[j])) {
                freeBag(&bag_);
                return 1;
            }

    freeBag(&bag_);

    return 0;
}

void getWordExceptLast(char* source, char* dest) {
    char* begin_search = source;

    while (getWordWithoutSpace(begin_search, &bag_.words[bag_.size])) {
        begin_search = bag_.words[bag_.size].end + 1;
        bag_.size++;
    }

    if (bag_.size == 0) {
        freeBag(&bag_);
        return;
    }

    WordDescriptor last_word = bag_.words[bag_.size - 1];
    char* rec_ptr = dest;

    for (size_t i = 0; i < bag_.size - 1; i++) {
        if (!isWordEqual(bag_.words[i], last_word)) {
            rec_ptr = copy(bag_.words[i].begin, bag_.words[i].end + 1, rec_ptr);
            if (i != bag_.size - 2)
                *rec_ptr++ = ' ';
        }
    }

    *rec_ptr = '\0';

    freeBag(&bag_);
}