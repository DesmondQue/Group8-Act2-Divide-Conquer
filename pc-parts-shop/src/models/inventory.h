// filepath: /pc-parts-shop/pc-parts-shop/src/models/inventory.h

#ifndef INVENTORY_H
#define INVENTORY_H

#include "product.h"
#include <vector>
#include <string>

struct Inventory {
    std::vector<Product> products;

    void loadProductsFromFile(const std::string& filename);
    void updateProductQuantity(const std::string& productName, int quantity);
};

#endif // INVENTORY_H