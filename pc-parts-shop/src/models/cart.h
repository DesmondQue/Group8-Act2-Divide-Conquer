#ifndef CART_H
#define CART_H

#include "product.h"
#include <vector>
#include <iostream>
#include <string.h>

struct Cart {
    std::vector<Product> products;

    void addProduct(const Product& product) {
        products.push_back(product);
    }

    void removeProduct(int productNumber) {  
        std::vector<Product> temp;
        for (const auto& p : products) {
            if (p.productNumber != productNumber) {
                temp.push_back(p);
            }
        }
        products = temp;
    }
    
    void printReceipt() const {
        double total = 0.0;
        for (const auto& product : products) {
            total += product.price * product.quantity;
            std::cout << "#" << product.productNumber << " " 
                     << product.name << " - Quantity: " << product.quantity 
                     << " - Price: $" << product.price << std::endl;
        }
        std::cout << "Total: $" << total << std::endl;
    }
};

#endif 