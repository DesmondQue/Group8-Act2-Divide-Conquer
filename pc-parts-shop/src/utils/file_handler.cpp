#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "file_handler.h"
#include "../models/product.h"

void loadInventory(const std::string& filename, std::vector<Product>& inventory) {
    std::ifstream file(filename);
    
    if (!file.good()) {
        std::cout << "Inventory file not found. Creating new inventory...\n";
        prepopulateInventory(filename);
        file.open(filename); 
    }

    if (!file) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    Product product;
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> product.id >> product.name >> product.type >> product.quantity;
        inventory.push_back(product);
    }
    
    file.close();
}

void updateInventory(const std::string& filename, const std::vector<Product>& inventory) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& product : inventory) {
        file << product.id << " "
             << product.name << " " 
             << product.type << " "
             << product.quantity << "\n";
    }
    file.close();
}

void prepopulateInventory(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error creating file: " << filename << std::endl;
        return;
    }

    // Format: ID Name Type Quantity
    file << "111 RTX4090_ROG_STRIX GPU 10\n";
    file << "222 RTX4080_GAMING_X GPU 15\n";
    file << "333 RX7900XTX_NITRO GPU 12\n";
    file << "444 Ryzen_9_7950X CPU 20\n";
    file << "555 i9_14900K CPU 18\n";
    file << "666 Ryzen_7_7800X3D CPU 25\n";
    file << "777 Corsair_Vengeance_32GB RAM 30\n";
    file << "888 GSkill_Trident_64GB RAM 15\n";
    file << "999 Samsung_990Pro_2TB Storage 25\n";
    file << "100 WD_Black_SN850X_1TB Storage 35\n";
    file << "110 ROG_X670E_HERO Motherboard 10\n";
    file << "120 MPG_Z790_EDGE Motherboard 15\n";
    file << "130 ROG_Thor_1200P PSU 12\n";
    file << "140 RM850x PSU 20\n";
    file << "150 RM1000x PSU 18\n";
    file << "160 Lian_Li_O11D_EVO Case 15\n";
    file << "170 H7_Flow Case 25\n";
    file << "180 NH_D15 Cooling 20\n";
    file << "190 H150i_Elite Cooling 15\n";
    file << "200 ROG_G35CZ Prebuilt 5\n";

    file.close();
    std::cout << "Inventory file has been created and populated successfully.\n";
}