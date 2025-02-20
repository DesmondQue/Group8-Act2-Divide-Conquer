// filepath: /pc-parts-shop/pc-parts-shop/src/models/product.h

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct Product {
    char name[100];
    float price;
    int quantity;
    
    // Main category (GPU, CPU, RAM, etc.)
    char category[50];
    
    // Subcategory fields
    struct {
        char brand[50];        // AMD, Nvidia, Intel etc.
        char manufacturer[50]; // For GPUs: ASUS, MSI, etc.
        char series[50];      // GPU series, CPU tier
        char formFactor[50];  // For cases, motherboards
        char capacity[50];    // For RAM, Storage
        char speed[50];       // For RAM
        char socket[50];      // For motherboards
        char wattage[50];     // For PSUs
        char efficiency[50];  // For PSUs
        char modularity[50];  // For PSUs
        char cooling[50];     // Cooling type
    } specs;
};

// Category constants
namespace Categories {
    const char GPU[] = "GPU";
    const char CPU[] = "CPU";
    const char RAM[] = "RAM";
    const char STORAGE[] = "Storage";
    const char MOTHERBOARD[] = "Motherboard";
    const char PSU[] = "PSU";
    const char CASE[] = "Case";
    const char COOLING[] = "Cooling";
    const char PREBUILT[] = "Prebuilt";
}

#endif // PRODUCT_H