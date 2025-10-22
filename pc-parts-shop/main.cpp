#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>

struct Product {
    int productNumber;
    char name[100];
    float price;
    int quantity;
    char category[50];
    
    struct {
        char brand[50];
        char manufacturer[50];
        char series[50];
        char formFactor[50];
        char capacity[50];
        char speed[50];
        char socket[50];
        char wattage[50];
        char efficiency[50];
        char modularity[50];
        char cooling[50];
    } specs;
};

void prepopulateInventory(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error creating file: " << filename << std::endl;
        return;
    }

    file << "111 RTX4090_ROG_STRIX 89599.44 10 GPU NVIDIA ASUS 40_Series - - - - - - - -\n";
    file << "222 RTX4080_GAMING_X 67199.44 15 GPU NVIDIA MSI 40_Series - - - - - - - -\n";
    file << "333 RX7900XTX_NITRO 55999.44 12 GPU AMD SAPPHIRE RX_7000 - - - - - - - -\n";
    file << "444 Ryzen_9_7950X 30799.44 20 CPU AMD AMD Ryzen_9 - - - - - - - -\n";
    file << "555 i9_14900K 33039.44 18 CPU Intel Intel Core_i9 - - - - - - - -\n";
    file << "666 Ryzen_7_7800X3D 25199.44 25 CPU AMD AMD Ryzen_7 - - - - - - - -\n";
    file << "777 Corsair_Vengeance_32GB 8959.44 30 RAM Corsair Corsair DDR5 - 32GB 3600MHz - - - - -\n";
    file << "888 GSkill_Trident_64GB 16799.44 15 RAM GSkill GSkill DDR5 - 64GB 4000MHz - - - - -\n";
    file << "999 Samsung_990Pro_2TB 10079.44 25 Storage Samsung Samsung NVMe_M.2 - 2TB - - - - - -\n";
    file << "100 WD_Black_SN850X_1TB 7279.44 35 Storage WD WD NVMe_M.2 - 1TB - - - - - -\n";
    file << "110 ROG_X670E_HERO 27999.44 10 Motherboard ASUS ASUS - ATX - - AM5 - - - -\n";
    file << "120 MPG_Z790_EDGE 18479.44 15 Motherboard MSI MSI - ATX - - LGA1700 - - - -\n";
    file << "130 ROG_Thor_1200P 16799.44 12 PSU ASUS ASUS - - - - - 1200W Platinum Fully -\n";
    file << "140 RM850x 8399.44 20 PSU Corsair Corsair - - - - - 850W Gold Fully -\n";
    file << "150 RM1000x 10079.44 18 PSU Corsair Corsair - - - - - 1000W Gold Fully -\n";

    file.close();
}

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

void displayMenu() {
    system("cls");
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "   G8 | PC Parts Inventory System" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "[1] Search Products" << std::endl;
    std::cout << "[2] Display All Products" << std::endl;
    std::cout << "[3] Add New Product" << std::endl;
    std::cout << "[4] Edit Product" << std::endl;
    std::cout << "[5] Delete Product" << std::endl;
    std::cout << "[6] Exit" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Please select an option: ";
}

std::string toLowerCase(const char* str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

bool containsSubstring(const char* text, const std::string& searchTerm) {
    std::string lowerText = toLowerCase(text);
    std::string lowerSearch = searchTerm;
    std::transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
    return lowerText.find(lowerSearch) != std::string::npos;
}

std::vector<Product> searchProducts(const std::vector<Product>& inventory, const std::string& searchTerm) {
    std::vector<Product> results;
    
    for (const auto& product : inventory) {
        if (containsSubstring(product.name, searchTerm) ||
            containsSubstring(product.category, searchTerm) ||
            containsSubstring(product.specs.brand, searchTerm) ||
            containsSubstring(product.specs.manufacturer, searchTerm) ||
            containsSubstring(product.specs.series, searchTerm) ||
            containsSubstring(product.specs.formFactor, searchTerm) ||
            containsSubstring(product.specs.capacity, searchTerm) ||
            containsSubstring(product.specs.speed, searchTerm) ||
            containsSubstring(product.specs.socket, searchTerm) ||
            containsSubstring(product.specs.wattage, searchTerm) ||
            containsSubstring(product.specs.efficiency, searchTerm) ||
            containsSubstring(product.specs.modularity, searchTerm) ||
            containsSubstring(product.specs.cooling, searchTerm)) {
            results.push_back(product);
        }
    }
    
    return results;
}

void displayProducts(const std::vector<Product>& products) {
    if (products.empty()) {
        std::cout << "No products found." << std::endl;
        return;
    }

    for (const auto& product : products) {
        std::cout << "#" << product.productNumber << " | " << product.name 
                  << " | PHP " << std::fixed << std::setprecision(2) << product.price 
                  << " | Qty: " << product.quantity 
                  << " | " << product.specs.brand << " " << product.specs.series << std::endl;
    }
    std::cout << "\n[Press Enter to continue]";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayProductDetails(const Product& product) {
    std::cout << "\n---------------------------------------" << std::endl;
    std::cout << "Product #: " << product.productNumber << std::endl;
    std::cout << "Name: " << product.name << std::endl;
    std::cout << "Price: PHP " << std::fixed << std::setprecision(2) << product.price << std::endl;
    std::cout << "Quantity: " << product.quantity << std::endl;
    std::cout << "Category: " << product.category << std::endl;
    std::cout << "Brand: " << product.specs.brand << std::endl;
    std::cout << "Manufacturer: " << product.specs.manufacturer << std::endl;
    std::cout << "Series: " << product.specs.series << std::endl;
    std::cout << "---------------------------------------" << std::endl;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

int getNextProductNumber(const std::vector<Product>& inventory) {
    int maxNumber = 0;
    for (const auto& product : inventory) {
        if (product.productNumber > maxNumber) {
            maxNumber = product.productNumber;
        }
    }
    return maxNumber + 1;
}

int main() {
    const std::string filename = "data/inventory.txt";
    std::vector<Product> inventory;

    loadInventory(filename, inventory);

    int choice;
    do {
        displayMenu();
        while (!(std::cin >> choice)) {
            clearInputBuffer();
            std::cout << "Invalid input. Please enter a number: ";
        }
        clearInputBuffer();

        switch (choice) {
            case 1: {
                system("cls");
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "        G8 | Search Products" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "Enter search term: ";
                
                std::string searchTerm;
                std::getline(std::cin, searchTerm);
                
                auto searchResults = searchProducts(inventory, searchTerm);
                
                if (searchResults.empty()) {
                    std::cout << "\nNo products found matching '" << searchTerm << "'" << std::endl;
                    std::cout << "[Press Enter to continue]";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                system("cls");
                std::cout << "Found " << searchResults.size() << " product(s) matching '" << searchTerm << "':\n";
                std::cout << "---------------------------------------\n";
                displayProducts(searchResults);
                break;
            }
            case 2: {
                system("cls");
                std::cout << "All Available Products:\n";
                std::cout << "---------------------------------------\n";
                displayProducts(inventory);
                break;
            }
            case 3: {
                system("cls");
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "        G8 | Add New Product" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                
                Product newProduct;
                newProduct.productNumber = getNextProductNumber(inventory);
                
                std::cout << "Product Number (auto-generated): " << newProduct.productNumber << std::endl;
                
                std::cout << "Enter product name: ";
                std::cin.getline(newProduct.name, 100);
                
                std::cout << "Enter price (max 500,000): ";
                while (!(std::cin >> newProduct.price) || newProduct.price < 0 || newProduct.price > 500000) {
                    clearInputBuffer();
                    if (newProduct.price > 500000) {
                        std::cout << "Price exceeds maximum limit of 500,000. Please enter a valid price: ";
                    } else {
                        std::cout << "Invalid price. Please enter a valid number: ";
                    }
                }
                clearInputBuffer();
                
                std::cout << "Enter quantity (max 1,000): ";
                while (!(std::cin >> newProduct.quantity) || newProduct.quantity < 0 || newProduct.quantity > 1000) {
                    clearInputBuffer();
                    if (newProduct.quantity > 1000) {
                        std::cout << "Quantity exceeds maximum limit of 1,000. Please enter a valid quantity: ";
                    } else {
                        std::cout << "Invalid quantity. Please enter a valid number: ";
                    }
                }
                clearInputBuffer();
                
                std::cout << "Enter category: ";
                std::cin.getline(newProduct.category, 50);
                
                std::cout << "Enter brand: ";
                std::cin.getline(newProduct.specs.brand, 50);
                
                std::cout << "Enter manufacturer: ";
                std::cin.getline(newProduct.specs.manufacturer, 50);
                
                std::cout << "Enter series: ";
                std::cin.getline(newProduct.specs.series, 50);
                
                inventory.push_back(newProduct);
                updateInventory(filename, inventory);
                
                std::cout << "\nProduct added successfully!" << std::endl;
                std::cout << "[Press Enter to continue]";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            case 4: {
                system("cls");
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "        G8 | Edit Product" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                
                int productNumber;
                std::cout << "Enter product number to edit: ";
                while (!(std::cin >> productNumber)) {
                    clearInputBuffer();
                    std::cout << "Invalid input. Please enter a valid product number: ";
                }
                clearInputBuffer();
                
                bool found = false;
                for (auto& product : inventory) {
                    if (product.productNumber == productNumber) {
                        found = true;
                        
                        std::cout << "\nCurrent product details:";
                        displayProductDetails(product);
                        
                        std::cout << "\nEnter new details (press Enter to keep current value):\n";
                        
                        std::cout << "Name [" << product.name << "]: ";
                        char input[100];
                        std::cin.getline(input, 100);
                        if (input[0] != '\0') strcpy(product.name, input);
                        
                        std::cout << "Price [" << product.price << "]: ";
                        std::cin.getline(input, 100);
                        if (input[0] != '\0') {
                            try {
                                product.price = std::stof(input);
                            } catch (...) {
                                std::cout << "Invalid price, keeping current value." << std::endl;
                            }
                        }
                        
                        std::cout << "Quantity [" << product.quantity << "]: ";
                        std::cin.getline(input, 100);
                        if (input[0] != '\0') {
                            try {
                                product.quantity = std::stoi(input);
                            } catch (...) {
                                std::cout << "Invalid quantity, keeping current value." << std::endl;
                            }
                        }
                        
                        std::cout << "Category [" << product.category << "]: ";
                        std::cin.getline(input, 100);
                        if (input[0] != '\0') strcpy(product.category, input);
                        
                        std::cout << "Brand [" << product.specs.brand << "]: ";
                        std::cin.getline(input, 100);
                        if (input[0] != '\0') strcpy(product.specs.brand, input);
                        
                        std::cout << "Manufacturer [" << product.specs.manufacturer << "]: ";
                        std::cin.getline(input, 100);
                        if (input[0] != '\0') strcpy(product.specs.manufacturer, input);
                        
                        std::cout << "Series [" << product.specs.series << "]: ";
                        std::cin.getline(input, 100);
                        if (input[0] != '\0') strcpy(product.specs.series, input);
                        
                        updateInventory(filename, inventory);
                        
                        std::cout << "\nProduct updated successfully!" << std::endl;
                        break;
                    }
                }
                
                if (!found) {
                    std::cout << "Product not found." << std::endl;
                }
                
                std::cout << "[Press Enter to continue]";
                std::cin.get();
                break;
            }
            case 5: {
                system("cls");
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "        G8 | Delete Product" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                
                int productNumber;
                std::cout << "Enter product number to delete: ";
                while (!(std::cin >> productNumber)) {
                    clearInputBuffer();
                    std::cout << "Invalid input. Please enter a valid product number: ";
                }
                clearInputBuffer();
                
                bool found = false;
                for (auto it = inventory.begin(); it != inventory.end(); ++it) {
                    if (it->productNumber == productNumber) {
                        found = true;
                        
                        std::cout << "\nProduct to delete:";
                        displayProductDetails(*it);
                        
                        std::cout << "\nAre you sure you want to delete this product? (y/n): ";
                        char confirm;
                        std::cin >> confirm;
                        clearInputBuffer();
                        
                        if (confirm == 'y' || confirm == 'Y') {
                            inventory.erase(it);
                            updateInventory(filename, inventory);
                            
                            std::cout << "Product deleted successfully!" << std::endl;
                        } else {
                            std::cout << "Deletion cancelled." << std::endl;
                        }
                        break;
                    }
                }
                
                if (!found) {
                    std::cout << "Product not found." << std::endl;
                }
                
                std::cout << "[Press Enter to continue]";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            case 6:
                system("cls");
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "  Thank you for using our system!" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "             MADE BY" << std::endl << std::endl;
                std::cout << "   QUE, ADRIAN | QUE, DESMOND" << std::endl;
                std::cout << "      VALENTINO, FERDINAND" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                std::cout << "[Press Enter to continue]";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 6);

    return 0;
}
