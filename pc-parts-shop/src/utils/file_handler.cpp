#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "file_handler.h"
#include "../models/product.h"

void loadInventory(const std::string& filename, std::vector<Product>& inventory) {
    std::ifstream file(filename);
    
    // If file doesn't exist, create and populate it
    if (!file.good()) {
        std::cout << "Inventory file not found. Creating new inventory...\n";
        prepopulateInventory(filename);
        file.open(filename); // Reopen the newly created file
    }

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    Product product;
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> product.name >> product.price >> product.quantity >> product.category 
            >> product.specs.brand >> product.specs.manufacturer >> product.specs.series 
            >> product.specs.formFactor >> product.specs.capacity >> product.specs.speed 
            >> product.specs.socket >> product.specs.wattage >> product.specs.efficiency 
            >> product.specs.modularity >> product.specs.cooling;
            
        inventory.push_back(product);
    }
    
    file.close();
}

void updateInventory(const std::string& filename, const std::vector<Product>& inventory) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& product : inventory) {
        file << product.name << " " << product.price << " " << product.quantity << " " << product.category << std::endl;
    }
    file.close();
}

void prepopulateInventory(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error creating file: " << filename << std::endl;
        return;
    }

    // GPUs
    file << "RTX4090_ROG_STRIX 1599.99 10 GPU NVIDIA ASUS 40_Series - - - - - - - -\n";
    file << "RTX4080_GAMING_X 1199.99 15 GPU NVIDIA MSI 40_Series - - - - - - - -\n";
    file << "RX7900XTX_NITRO 999.99 12 GPU AMD SAPPHIRE RX_7000 - - - - - - - -\n";

    // CPUs
    file << "Ryzen_9_7950X 549.99 20 CPU AMD - Ryzen_9 - - - - - - - -\n";
    file << "i9_14900K 589.99 18 CPU Intel - Core_i9 - - - - - - - -\n";
    file << "Ryzen_7_7800X3D 449.99 25 CPU AMD - Ryzen_7 - - - - - - - -\n";

    // RAM
    file << "Corsair_Vengeance_32GB 159.99 30 RAM - Corsair - - 32GB 3600MHz - - - - -\n";
    file << "GSkill_Trident_64GB 299.99 15 RAM - GSkill - - 64GB 4000MHz - - - - -\n";

    // Storage
    file << "Samsung_990Pro_2TB 179.99 25 Storage - Samsung NVMe_M.2 - 2TB - - - - - -\n";
    file << "WD_Black_SN850X_1TB 129.99 35 Storage - WD NVMe_M.2 - 1TB - - - - - -\n";

    // Motherboards
    file << "ROG_X670E_HERO 499.99 10 Motherboard AMD ASUS - ATX - - AM5 - - - -\n";
    file << "MPG_Z790_EDGE 329.99 15 Motherboard Intel MSI - ATX - - LGA1700 - - - -\n";

    // PSUs
    file << "ROG_Thor_1200P 299.99 12 PSU - ASUS - - - - - 1200W Platinum Fully -\n";
    file << "RM850x 149.99 20 PSU - Corsair - - - - - 850W Gold Fully -\n";

    // Cases
    file << "Lian_Li_O11D_EVO 169.99 15 Case - Lian_Li - ATX - - - - - - -\n";
    file << "H7_Flow 129.99 25 Case - NZXT - ATX - - - - - - -\n";

    // Cooling
    file << "NH_D15 89.99 20 Cooling - Noctua - - - - - - - - Air_Cooler\n";
    file << "H150i_Elite 189.99 15 Cooling - Corsair - - - - - - - - 360mm_AIO\n";

    // Pre-builts
    file << "ROG_G35CZ 2499.99 5 Prebuilt - ASUS - - - - - - - - -\n";
    file << "HP_Omen_45L 1999.99 8 Prebuilt - HP - - - - - - - - -\n";

    file.close();
    std::cout << "Inventory file has been created and populated successfully.\n";
}