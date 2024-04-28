#include <stdio.h>
#include <ctype.h>
#include <memory.h>
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

char stringBuffer_[100];

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

void printWordsReversed(BagOfWords *bag) {
    for (int i = bag->size - 1; i >= 0; i--) {
        for (char *p = bag->words[i].begin; p < bag->words[i].end; p++) {
            printf("%c", *p);
        }
        printf("\n");
    }
}