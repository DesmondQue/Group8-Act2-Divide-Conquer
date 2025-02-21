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
        iss >> product.productNumber >> product.name >> product.price >> product.quantity 
            >> product.category >> product.specs.brand >> product.specs.manufacturer 
            >> product.specs.series >> product.specs.formFactor >> product.specs.capacity 
            >> product.specs.speed >> product.specs.socket >> product.specs.wattage 
            >> product.specs.efficiency >> product.specs.modularity >> product.specs.cooling;
            
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
        file << product.productNumber << " "
             << product.name << " " 
             << product.price << " " 
             << product.quantity << " " 
             << product.category << " "
             << product.specs.brand << " "
             << product.specs.manufacturer << " "
             << product.specs.series << " "
             << product.specs.formFactor << " "
             << product.specs.capacity << " "
             << product.specs.speed << " "
             << product.specs.socket << " "
             << product.specs.wattage << " "
             << product.specs.efficiency << " "
             << product.specs.modularity << " "
             << product.specs.cooling << "\n";
    }
    file.close();
}

void prepopulateInventory(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error creating file: " << filename << std::endl;
        return;
    }

    // GPUs
    file << "111 RTX4090_ROG_STRIX 89599.44 10 GPU NVIDIA ASUS 40_Series - - - - - - - -\n";
    file << "222 RTX4080_GAMING_X 67199.44 15 GPU NVIDIA MSI 40_Series - - - - - - - -\n";
    file << "333 RX7900XTX_NITRO 55999.44 12 GPU AMD SAPPHIRE RX_7000 - - - - - - - -\n";

    // CPUs
    file << "444 Ryzen_9_7950X 30799.44 20 CPU AMD AMD Ryzen_9 - - - - - - - -\n";
    file << "555 i9_14900K 33039.44 18 CPU Intel Intel Core_i9 - - - - - - - -\n";
    file << "666 Ryzen_7_7800X3D 25199.44 25 CPU AMD AMD Ryzen_7 - - - - - - - -\n";

    // RAM 
    file << "777 Corsair_Vengeance_32GB 8959.44 30 RAM Corsair Corsair DDR5 - 32GB 3600MHz - - - - -\n";
    file << "888 GSkill_Trident_64GB 16799.44 15 RAM GSkill GSkill DDR5 - 64GB 4000MHz - - - - -\n";

    // Storage
    file << "999 Samsung_990Pro_2TB 10079.44 25 Storage Samsung Samsung NVMe_M.2 - 2TB - - - - - -\n";
    file << "100 WD_Black_SN850X_1TB 7279.44 35 Storage WD WD NVMe_M.2 - 1TB - - - - - -\n";

    // Motherboards
    file << "110 ROG_X670E_HERO 27999.44 10 Motherboard ASUS ASUS - ATX - - AM5 - - - -\n";
    file << "120 MPG_Z790_EDGE 18479.44 15 Motherboard MSI MSI - ATX - - LGA1700 - - - -\n";

    // PSUs
    file << "130 ROG_Thor_1200P 16799.44 12 PSU ASUS ASUS - - - - - 1200W Platinum Fully -\n";
    file << "140 RM850x 8399.44 20 PSU Corsair Corsair - - - - - 850W Gold Fully -\n";

    // Cases
    file << "150 Lian_Li_O11D_EVO 9519.44 15 Case Lian_Li Lian_Li - ATX - - - - - - -\n";
    file << "160 H7_Flow 7279.44 25 Case NZXT NZXT - ATX - - - - - - -\n";

    // Cooling
    file << "170 NH_D15 5039.44 20 Cooling Noctua Noctua - - - - - - - - Air_Cooler\n";
    file << "180 H150i_Elite 10639.44 15 Cooling Corsair Corsair - - - - - - - - 360mm_AIO\n";

    // Pre-builts
    file << "190 ROG_G35CZ 139999.44 5 Prebuilt ASUS ASUS - - - - - - - - -\n";
    file << "200 HP_Omen_45L 111999.44 8 Prebuilt HP HP - - - - - - - - -\n";

    file.close();
    std::cout << "Inventory file has been created and populated successfully.\n";
}