#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "algorithms.h"

void generateExpression(const char *file_name) {
    srand(time(NULL));

    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int x1 = rand() % 10;
    int x2 = rand() % 10;
    int x3 = rand() % 10;

    char operators[] = "+-*/";
    char op1 = operators[rand() % 4];
    char op2 = operators[rand() % 4];

    bool one_operation = rand() % 2;

    if (one_operation) {
        fprintf(file, "(%d %c %d)", x1, op1, x2);
    } else {
        fprintf(file, "(%d %c %d) %c %d", x1, op1, x2, op2, x3);
    }

    fclose(file);
}

void evaluateExpression(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int x1, x2, x3;
    char op1, op2;
    char open_bracket, close_bracket;
    float result;

    int amount_element = fscanf(file, "%c%d %c %d%c %c %d", &open_bracket, &x1, &op1, &x2, &close_bracket, &op2, &x3);

    bool two_operation = amount_element == 7 ? true : false;

    switch (op1) {
        case '+':
            result = x1 + x2;
            break;
        case '-':
            result = x1 - x2;
            break;
        case '*':
            result = x1 * x2;
            break;
        case '/':
            if (x2 == 0) {
                fprintf(stderr, "zero division");
                exit(1);
            }
            result = x1 / x2;
            break;
        default:
            fprintf(stderr, "unknown operation");
            exit(1);
    }

    if (two_operation) {
        switch (op2) {
            case '+':
                result += x3;
                break;
            case '-':
                result -= x3;
                break;
            case '*':
                result *= x3;
                break;
            case '/':
                if (x3 == 0) {
                    fprintf(stderr, "zero division");
                    exit(1);
                }
                result /= x3;
                break;
            default:
                fprintf(stderr, "unknown operation");
                exit(1);
        }
    }

    fseek(file, 0, SEEK_END);
    fprintf(file, " = %.2f", result);

    fclose(file);
}

#define MAX_LENGTH_STRING 200

#define MAX_AMOUNT_SPORTSMAN 20

static void generate_name(char* s) {
    int name_length = rand() % 30 + 5;

    char* rec_ptr = s;
    for (int i = 0; i < name_length; i++) {
        *rec_ptr = rand() % 26 + 97;
        rec_ptr++;
    }
    *rec_ptr = '\0';
}

void generateTeam(const char* filename, const int n) {
    srand(time(NULL));

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        sportsman s;
        generate_name(s.name);

        s.best_result = (double) rand() / 100;

        fwrite(&s, sizeof(sportsman),1, file);
    }

    fclose(file);
}

void sortSportsman(sportsman sm[], const int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sm[j].best_result < sm[j + 1].best_result) {
                sportsman temp = sm[j];
                sm[j] = sm[j + 1];
                sm[j + 1] = temp;
            }
        }
    }
}

void getBestTeam(const char* filename, const int n) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    sportsman* team = (sportsman*) malloc(MAX_AMOUNT_SPORTSMAN * sizeof(sportsman));

    sportsman* rec_ptr = team;
    int amount_sportsman = 0;
    while (fread(rec_ptr, sizeof(sportsman), 1, file) == 1) {
        rec_ptr ++;
        amount_sportsman++;
    }

    fclose(file);

    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    sortSportsman(team, amount_sportsman);

    int amount_in_team = amount_sportsman >= n ? n : amount_sportsman;

    for (int i = 0; i < amount_in_team; i++) {
        fwrite(team + i, sizeof(sportsman), 1, file);
    }

    free(team);
    fclose(file);
}

void printTeam(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    sportsman s;
    while (fread(&s, sizeof(sportsman), 1, file) == 1) {
        printf("%s %lf", s.name, s.best_result);
        printf("\n");
    }

    fclose(file);
}