#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include "models/inventory.h"
#include "utils/file_handler.h"
#include <vector>
#include <limits>

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
        // Convert ID to string for searching
        std::string idStr = std::to_string(product.id);
        
        if (containsSubstring(product.name, searchTerm) ||
            containsSubstring(product.type, searchTerm) ||
            containsSubstring(idStr.c_str(), searchTerm)) {
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
        std::cout << "ID: " << product.id << " | " << product.name 
                  << " | Type: " << product.type 
                  << " | Qty: " << product.quantity << std::endl;
    }
    std::cout << "\n[Press Enter to continue]";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayProductDetails(const Product& product) {
    std::cout << "\n---------------------------------------" << std::endl;
    std::cout << "ID: " << product.id << std::endl;
    std::cout << "Name: " << product.name << std::endl;
    std::cout << "Type: " << product.type << std::endl;
    std::cout << "Quantity: " << product.quantity << std::endl;
    std::cout << "---------------------------------------" << std::endl;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}


int getNextProductNumber(const std::vector<Product>& inventory) {
    int maxNumber = 0;
    for (const auto& product : inventory) {
        if (product.id > maxNumber) {
            maxNumber = product.id;
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
                
                // Check if search term is empty
                if (searchTerm.empty()) {
                    std::cout << "\nError: Search term cannot be empty." << std::endl;
                    std::cout << "[Press Enter to continue]";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                
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
                newProduct.id = getNextProductNumber(inventory);
                
                std::cout << "ID (auto-generated): " << newProduct.id << std::endl;
                
                // Product name with space validation
                bool validName = false;
                while (!validName) {
                    std::cout << "Enter product name (no spaces, use _ or - instead): ";
                    std::cin.getline(newProduct.name, 100);
                    
                    // Check for spaces
                    bool hasSpace = false;
                    for (int i = 0; newProduct.name[i] != '\0'; i++) {
                        if (newProduct.name[i] == ' ') {
                            hasSpace = true;
                            break;
                        }
                    }
                    
                    if (hasSpace) {
                        std::cout << "Error: Product name cannot contain spaces. Use underscores (_) or hyphens (-) instead.\n";
                    } else if (newProduct.name[0] == '\0') {
                        std::cout << "Error: Product name cannot be empty.\n";
                    } else {
                        validName = true;
                    }
                }
                
                // Display type selection menu
                std::cout << "\nSelect product type:" << std::endl;
                std::cout << "[1] GPU" << std::endl;
                std::cout << "[2] CPU" << std::endl;
                std::cout << "[3] RAM" << std::endl;
                std::cout << "[4] Storage" << std::endl;
                std::cout << "[5] Motherboard" << std::endl;
                std::cout << "[6] PSU" << std::endl;
                std::cout << "[7] Case" << std::endl;
                std::cout << "[8] Cooling" << std::endl;
                std::cout << "[9] Prebuilt" << std::endl;
                std::cout << "Choose type (1-9): ";
                
                int typeChoice;
                while (!(std::cin >> typeChoice) || typeChoice < 1 || typeChoice > 9) {
                    clearInputBuffer();
                    std::cout << "Invalid choice. Please enter a number between 1-9: ";
                }
                clearInputBuffer();
                
                // Set type based on choice
                switch (typeChoice) {
                    case 1: strcpy(newProduct.type, "GPU"); break;
                    case 2: strcpy(newProduct.type, "CPU"); break;
                    case 3: strcpy(newProduct.type, "RAM"); break;
                    case 4: strcpy(newProduct.type, "Storage"); break;
                    case 5: strcpy(newProduct.type, "Motherboard"); break;
                    case 6: strcpy(newProduct.type, "PSU"); break;
                    case 7: strcpy(newProduct.type, "Case"); break;
                    case 8: strcpy(newProduct.type, "Cooling"); break;
                    case 9: strcpy(newProduct.type, "Prebuilt"); break;
                }
                
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
                
                int productId;
                std::cout << "Enter product ID to edit: ";
                while (!(std::cin >> productId)) {
                    clearInputBuffer();
                    std::cout << "Invalid input. Please enter a valid product ID: ";
                }
                clearInputBuffer();
                
                bool found = false;
                for (auto& product : inventory) {
                    if (product.id == productId) {
                        found = true;
                        
                        std::cout << "\nCurrent product details:";
                        displayProductDetails(product);
                        
                        std::cout << "\nEnter new details (press Enter to keep current value):\n";
                        
                        // Name with space validation
                        bool validEdit = false;
                        while (!validEdit) {
                            std::cout << "Name (no spaces, use _ or -) [" << product.name << "]: ";
                            char input[100];
                            std::cin.getline(input, 100);
                            
                            if (input[0] == '\0') {
                                // User pressed Enter, keep current value
                                validEdit = true;
                            } else {
                                // Check for spaces
                                bool hasSpace = false;
                                for (int i = 0; input[i] != '\0'; i++) {
                                    if (input[i] == ' ') {
                                        hasSpace = true;
                                        break;
                                    }
                                }
                                
                                if (hasSpace) {
                                    std::cout << "Error: Product name cannot contain spaces. Use underscores (_) or hyphens (-) instead.\n";
                                } else {
                                    strcpy(product.name, input);
                                    validEdit = true;
                                }
                            }
                        }
                        
                        // Type selection with menu
                        std::cout << "Change Type? (y for YES/others for NO) [Current: " << product.type << "]: ";
                        char changeType;
                        std::cin >> changeType;
                        clearInputBuffer();
                        
                        if (changeType == 'y' || changeType == 'Y') {
                            std::cout << "\nSelect new product type:" << std::endl;
                            std::cout << "[1] GPU" << std::endl;
                            std::cout << "[2] CPU" << std::endl;
                            std::cout << "[3] RAM" << std::endl;
                            std::cout << "[4] Storage" << std::endl;
                            std::cout << "[5] Motherboard" << std::endl;
                            std::cout << "[6] PSU" << std::endl;
                            std::cout << "[7] Case" << std::endl;
                            std::cout << "[8] Cooling" << std::endl;
                            std::cout << "[9] Prebuilt" << std::endl;
                            std::cout << "Choose type (1-9): ";
                            
                            int typeChoice;
                            while (!(std::cin >> typeChoice) || typeChoice < 1 || typeChoice > 9) {
                                clearInputBuffer();
                                std::cout << "Invalid choice. Please enter a number between 1-9: ";
                            }
                            clearInputBuffer();
                            
                            switch (typeChoice) {
                                case 1: strcpy(product.type, "GPU"); break;
                                case 2: strcpy(product.type, "CPU"); break;
                                case 3: strcpy(product.type, "RAM"); break;
                                case 4: strcpy(product.type, "Storage"); break;
                                case 5: strcpy(product.type, "Motherboard"); break;
                                case 6: strcpy(product.type, "PSU"); break;
                                case 7: strcpy(product.type, "Case"); break;
                                case 8: strcpy(product.type, "Cooling"); break;
                                case 9: strcpy(product.type, "Prebuilt"); break;
                            }
                        }
                        
                        std::cout << "Quantity (press Enter to keep current) [" << product.quantity << "]: ";
                        char quantityInput[100];
                        std::cin.getline(quantityInput, 100);
                        if (quantityInput[0] != '\0') {
                            try {
                                product.quantity = std::stoi(quantityInput);
                            } catch (...) {
                                std::cout << "Invalid quantity, keeping current value." << std::endl;
                            }
                        }
                        
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
                
                int productId;
                std::cout << "Enter product ID to delete: ";
                while (!(std::cin >> productId)) {
                    clearInputBuffer();
                    std::cout << "Invalid input. Please enter a valid product ID: ";
                }
                clearInputBuffer();
                
                bool found = false;
                for (auto it = inventory.begin(); it != inventory.end(); ++it) {
                    if (it->id == productId) {
                        found = true;
                        
                        std::cout << "\nProduct to delete:";
                        displayProductDetails(*it);
                        
                        std::cout << "\nAre you sure you want to delete this product? (y for YES/others for NO): ";
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
                std::cout << "   Are you sure you want to exit?" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "Confirm exit (y for YES/others for NO): ";
                char exitConfirm;
                std::cin >> exitConfirm;
                clearInputBuffer();
                
                if (exitConfirm == 'y' || exitConfirm == 'Y') {
                    system("cls");
                    std::cout << "---------------------------------------" << std::endl;
                    std::cout << "  Thank you for using our system!" << std::endl;
                    std::cout << "---------------------------------------" << std::endl;
                    std::cout << "             MADE BY" << std::endl << std::endl;
                    std::cout << "   QUE, ADRIAN | QUE, DESMOND" << std::endl;
                    std::cout << "      VALENTINO, FERDINAND" << std::endl;
                    std::cout << "---------------------------------------" << std::endl;
                } else {
                    std::cout << "Exit cancelled. Returning to menu..." << std::endl;
                    std::cout << "[Press Enter to continue]";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    choice = 0; // Reset choice to continue loop
                }
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                std::cout << "[Press Enter to continue]";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 6);

    return 0;
}