#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../models/product.h"

void loadInventory(const std::string& filename, std::vector<Product>& products);
void updateInventory(const std::string& filename, const std::vector<Product>& products);
void prepopulateInventory(const std::string& filename);

#endif // FILE_HANDLER_H