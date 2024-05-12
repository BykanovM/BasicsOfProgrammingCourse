#ifndef ARRAY_PRODUCTUPDATE_H
#define ARRAY_PRODUCTUPDATE_H

#define MAX_LENGTH_STRING 200

typedef struct product {
    char product_name[MAX_LENGTH_STRING];
    int unit_price;
    int total_cost;
    int quantity;
} product;

typedef struct order {
    char order_name[MAX_LENGTH_STRING];
    int quantity;
} order;

void generateProductAndOrder(const char* filename1, const char* filename2);

void updateProduct(const char* filename1, const char* filename2);

void printProductAndOrder(const char* filename1, const char* filename2);

#endif //ARRAY_PRODUCTUPDATE_H