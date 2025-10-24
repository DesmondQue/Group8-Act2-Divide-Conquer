// filepath: /pc-parts-shop/pc-parts-shop/src/models/product.h

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct Product {
    int id;
    char name[100];
    char type[50];
    int quantity;
};

#endif