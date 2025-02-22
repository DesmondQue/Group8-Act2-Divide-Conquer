#include <iostream>
#include "models/cart.h"
#include "models/inventory.h"
#include "utils/file_handler.h"
#include <vector>
#include "algorithms/bst.h"
#include "algorithms/merge_sort.h"
#include "algorithms/quick_sort.h"

void displayMenu() {
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "       G8 | PC Parts & Essentials" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "[1] Search Products" << std::endl;
    std::cout << "[2] Display All Products" << std::endl;
    std::cout << "[3] Add to Cart" << std::endl;
    std::cout << "[4] View Cart" << std::endl;
    std::cout << "[5] Clear Cart" << std::endl;
    std::cout << "[6] Checkout" << std::endl;
    std::cout << "[7] Exit" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Please select an option: ";
}


void displaySearchSortOptions() {
    std::cout << "\n---------------------------------------" << std::endl;
    std::cout << " G8 | Sort Search Results (QSort & MSort)" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "[1] Price (Ascending)" << std::endl;
    std::cout << "[2] Price (Descending)" << std::endl;
    std::cout << "[3] Quantity (Ascending)" << std::endl;
    std::cout << "[4] Quantity (Descending)" << std::endl;
    std::cout << "[5] Return to Main Menu" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Sort by: ";
}

void displayProducts(const std::vector<Product>& products) {
    if (products.empty()) {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "No products found." << std::endl;
        return;
    }

    for (const auto& product : products) {
        std::cout << "\n---------------------------------------" << std::endl;
        std::cout << "Product #: " << product.productNumber << std::endl;
        std::cout << "Name: " << product.name 
                  << "\nPrice: PHP " << product.price 
                  << "\nQuantity: " << product.quantity 
                  << "\nCategory: " << product.category
                  << "\nBrand: " << product.specs.brand 
                  << "\nManufacturer: " << product.specs.manufacturer 
                  << "\nSeries: " << product.specs.series << std::endl;
    }
}

void cartHeader(){
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "        G8 | Shopping Cart" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void searchProductsMenu(){
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "        G8 | Search Products (BST)" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "Select search field:" << std::endl;
                std::cout << "[1] Brand (AMD, Nvidia, Intel, etc.)" << std::endl;
                std::cout << "[2] Manufacturer (ASUS, MSI, etc.)" << std::endl;
                std::cout << "[3] Series (40 Series, Ryzen 7, etc.)" << std::endl;
                std::cout << "[4] Form Factor (ATX, ITX, etc.)" << std::endl;
                std::cout << "[5] Capacity (32GB, 1TB, etc.)" << std::endl;
                std::cout << "[6] Speed (3600MHz, etc.)" << std::endl;
                std::cout << "[7] Socket (AM5, LGA1700, etc.)" << std::endl;
                std::cout << "[8] Wattage (850W, 1000W, etc.)" << std::endl;
                std::cout << "[9] Efficiency (Gold, Platinum, etc.)" << std::endl;
                std::cout << "[10] Modularity (Fully, Semi, etc.)" << std::endl;
                std::cout << "[11] Cooling Type (Air, AIO, etc.)" << std::endl;
                std::cout << "[12] Category (GPU, CPU, etc.)" << std::endl;
                std::cout << "[13] Product Name" << std::endl;
                std::cout << "[14] Return to Main Menu" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
}

int main() {
    const std::string filename = "data/inventory.txt";
    std::vector<Product> inventory;
    Cart cart;
    BST productTree;

    // load inventory from file
    loadInventory(filename, inventory);

    // populate BST with inventory
    for (const auto& product : inventory) {
        productTree.insert(product);
    }

    int choice;
    do {
        displayMenu();
        while (!(std::cin >> choice)) {
            clearInputBuffer();
            std::cout << "Invalid input. Please enter a number: ";
        }
        clearInputBuffer();

        switch (choice) { // BST for each field/subcategory
            case 1: {
                searchProductsMenu();
                std::cout << "Enter choice: ";
                
                int searchChoice;
                std::cin >> searchChoice;
                clearInputBuffer();
                
                if (searchChoice == 14) break;
                
                std::string field;
                switch(searchChoice) {
                    case 1: field = "brand"; break;
                    case 2: field = "manufacturer"; break;
                    case 3: field = "series"; break;
                    case 4: field = "formFactor"; break;
                    case 5: field = "capacity"; break;
                    case 6: field = "speed"; break;
                    case 7: field = "socket"; break;
                    case 8: field = "wattage"; break;
                    case 9: field = "efficiency"; break;
                    case 10: field = "modularity"; break;
                    case 11: field = "cooling"; break;
                    case 12: field = "category"; break;
                    case 13: field = "name"; break;
                    default:
                        std::cout << "Invalid choice." << std::endl;
                        break;
                }
                
                std::cout << "Enter search term: ";
                std::string searchTerm;
                std::getline(std::cin, searchTerm);
                
                auto searchResults = productTree.search(field, searchTerm);
                if (searchResults.empty()) {
                    std::cout << "\nNo products found matching '" << searchTerm << "' in " << field << std::endl;
                    break;
                }

                std::cout << "\nSearch Results:\n";
                displayProducts(searchResults);

                int sortChoice;
                do {
                    displaySearchSortOptions();
                    while (!(std::cin >> sortChoice)) {
                        clearInputBuffer();
                        std::cout << "Invalid input. Please enter a number: ";
                    }
                    clearInputBuffer();

                    std::vector<Product> sortedResults = searchResults;
                    switch(sortChoice) {
                        case 1: {
                            // ascending price  using merge sort
                            mergeSort(&sortedResults[0], 0, sortedResults.size() - 1, SortKey::PRICE);
                            displayProducts(sortedResults);
                            break;
                        }
                        case 2: {
                            // descending price using quick sort
                            Product* arr = sortedResults.data();
                            int n = sortedResults.size();
                            quickSort(arr, 0, n - 1, SortKey::PRICE);

                            for (int i = 0; i < n/2; i++) {
                                swap(&arr[i], &arr[n-1-i]);
                            }
                            displayProducts(sortedResults);
                            break;
                        }
                        case 3: {
                            // descending quantity using merge sort
                            mergeSort(&sortedResults[0], 0, sortedResults.size() - 1, SortKey::QUANTITY);
                            displayProducts(sortedResults);
                            break;
                        }   
                        case 4: {
                            // ascending quantity using quick sort
                            Product* arr = sortedResults.data();
                            int n = sortedResults.size();
                            quickSort(arr, 0, n - 1, SortKey::QUANTITY); 
                            for (int i = 0; i < n/2; i++) {
                                swap(&arr[i], &arr[n-1-i]);
                            }
                            displayProducts(sortedResults);
                            break;
                        }                  
                        case 5:
                            break;
                        default:
                        std::cout << "---------------------------------------" << std::endl;
                            std::cout << "Invalid sorting option\n";
                    }
                } while (sortChoice != 5);
                break;
            }
            case 2: {
                // display all products
                std::cout << "\nAll Available Products:\n";
                displayProducts(inventory);
                break;
            }
            case 3: { //add to cart
                if (inventory.empty()) {
                    cartHeader();
                    std::cout << "No products available." << std::endl;
                } else {
                    int productNumber;
                    cartHeader();
                    std::cout << "Enter product number: ";
                    while (!(std::cin >> productNumber)) {
                        clearInputBuffer();
                        std::cout << "Invalid input. Please enter a valid product number: ";
                    }
                    clearInputBuffer();
                    
                    bool found = false;
                    for (auto& product : inventory) {
                        if (product.productNumber == productNumber && product.quantity > 0) {
                            int requestedQuantity;
                            std::cout << "Available quantity: " << product.quantity << std::endl;
                            std::cout << "Enter quantity to add to cart: ";
                            while (true) {
                                if (!(std::cin >> requestedQuantity)) {
                                    clearInputBuffer();
                                    std::cout << "Invalid input. Please enter a number: ";
                                    continue;
                                }
                                if (requestedQuantity <= 0) {
                                    std::cout << "Please enter a positive quantity: ";
                                    continue;
                                }
                                if (requestedQuantity > product.quantity) {
                                    std::cout << "Not enough stock. Available: " << product.quantity << "\nEnter quantity: ";
                                    continue;
                                }
                                break;
                            }
                            clearInputBuffer();

                            // temp product to store requested quantity
                            Product tempProduct = product;
                            tempProduct.quantity = requestedQuantity;
                            cart.addProduct(tempProduct);
                            
                            std::cout << "Product added to cart." << std::endl;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        std::cout << "Product not found or out of stock." << std::endl;
                    }
                }
                break;
            }
            case 4: // view cart
                cart.printReceipt();
                break;
            case 5: { // clear cart
                if (cart.products.empty()) {
                    std::cout << "Cart is already empty!" << std::endl;
                } else {
                    cart.products.clear();
                    std::cout << "Cart has been cleared." << std::endl;
                }
                break;
            }
            case 6: { //checkout
                if (cart.products.empty()) {
                    std::cout << "Cart is empty!" << std::endl;
                } else {
                    // Update both inventory and BST
                    productTree = BST(); // Clear existing BST
                    for (const auto& cartProduct : cart.products) {
                        for (auto& invProduct : inventory) {
                            if (cartProduct.productNumber == invProduct.productNumber) {
                                invProduct.quantity -= cartProduct.quantity;
                                break;
                            }
                        }
                    }
                    
                    // Repopulate BST with updated inventory
                    for (const auto& product : inventory) {
                        productTree.insert(product);
                    }
                    
                    std::cout << "\nFinal Receipt:" << std::endl;
                    cart.printReceipt();
                    updateInventory(filename, inventory);
                    cart.products.clear();
                    std::cout << "Thank you for your purchase!" << std::endl;
                }
                break;
            }
            case 7: // exit
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "     Thank you, Please come again!" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "            MADE BY GROUP 8" << std::endl << std::endl;
                std::cout << "              DELOS REYES" << std::endl;
                std::cout << "               FRANCISCO" << std::endl;
                std::cout << "                QUE, A." << std::endl;
                std::cout << "                QUE, D." << std::endl;
                std::cout << "---------------------------------------" << std::endl << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    } while (choice != 7);

    return 0;
}