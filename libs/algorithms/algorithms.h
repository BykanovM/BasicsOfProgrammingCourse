#ifndef UNTITLED1_ALGORITHMS_H
#define UNTITLED1_ALGORITHMS_H

void generateExpression(const char *file_name);

void evaluateExpression(const char *filename);

#define MAX_LENGTH_STRING 200

#define MAX_AMOUNT_SPORTSMAN 20

typedef struct sportsman {
    char name[MAX_LENGTH_STRING];
    double best_result;
} sportsman;

static void generate_name(char* s);

void generateTeam(const char* filename, const int n);

void sortSportsman(sportsman sm[], const int n);

void getBestTeam(const char* filename, const int n);

void printTeam(const char* filename);

#endif //UNTITLED1_ALGORITHMS_H