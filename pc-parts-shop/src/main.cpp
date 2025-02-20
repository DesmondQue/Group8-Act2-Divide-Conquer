#include <iostream>
#include "models/product.h"
#include "models/cart.h"
#include "models/inventory.h"
#include "utils/file_handler.h"
#include <vector>

void displayMenu() {
    std::cout << "\nWelcome to the PC Parts & Essentials Shop!" << std::endl;
    std::cout << "1. View Products" << std::endl;
    std::cout << "2. Add to Cart" << std::endl;
    std::cout << "3. View Cart" << std::endl;
    std::cout << "4. Checkout" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Please select an option: ";
}

int main() {
    const std::string filename = "../data/inventory.txt";
    std::vector<Product> inventory;
    Cart cart;

    // Load inventory from file
    loadInventory(filename, inventory);

    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Display all products
                for (const auto& product : inventory) {
                    std::cout << "\nName: " << product.name 
                              << "\nPrice: $" << product.price 
                              << "\nQuantity: " << product.quantity 
                              << "\nCategory: " << product.category << std::endl;
                }
                break;
            case 2:
                // Add product to cart
                if (inventory.empty()) {
                    std::cout << "No products available." << std::endl;
                } else {
                    std::string productName;
                    std::cout << "Enter product name: ";
                    std::cin >> productName;
                    
                    for (auto& product : inventory) {
                        if (strcmp(product.name, productName.c_str()) == 0 && product.quantity > 0) {
                            cart.addProduct(product);
                            product.quantity--;
                            std::cout << "Product added to cart." << std::endl;
                            // Update inventory file after purchase
                            updateInventory(filename, inventory);
                            break;
                        }
                    }
                }
                break;
            case 3:
                // View cart
                cart.printReceipt();
                break;
            case 4:
                // Checkout
                if (cart.products.empty()) {
                    std::cout << "Cart is empty!" << std::endl;
                } else {
                    std::cout << "\nFinal Receipt:" << std::endl;
                    cart.printReceipt();
                    cart.products.clear();
                    std::cout << "Thank you for your purchase!" << std::endl;
                }
                break;
            case 5:
                std::cout << "Thank you for visiting!" << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}