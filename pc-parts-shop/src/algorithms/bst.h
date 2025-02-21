#ifndef BST_H
#define BST_H

#include "../models/product.h"
#include <string>
#include <vector>
#include <cstring>

// Helper function to convert string to lowercase
std::string toLower(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

// Helper function to convert char array to lowercase string
std::string charArrayToLower(const char* str) {
    std::string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

struct Node {
    Product product;
    Node* left;
    Node* right;
    Node(Product p) : product(p), left(NULL), right(NULL) {}
};

class BST {
public:
    BST() : root(NULL) {}
    ~BST() { deleteTree(root); }

    void insert(const Product& product) {
        root = insertRec(root, product);
    }

    std::vector<Product> searchByString(const std::string& searchStr) {
        std::vector<Product> results;
        searchRec(root, toLower(searchStr), results);
        return results;
    }

private:
    Node* root;

    Node* insertRec(Node* node, const Product& product) {
        if (node == NULL) {
            return new Node(product);
        }
        
        if (strcmp(product.name, node->product.name) < 0) {
            node->left = insertRec(node->left, product);
        } else {
            node->right = insertRec(node->right, product);
        }
        return node;
    }
    //fuzzy search + bst implementation
    void searchRec(Node* node, const std::string& searchLower, std::vector<Product>& results) {
        if (node == nullptr) return;

        // Convert all char arrays to lowercase strings
        std::string name = charArrayToLower(node->product.name);
        std::string category = charArrayToLower(node->product.category);
        std::string brand = charArrayToLower(node->product.specs.brand);
        std::string manufacturer = charArrayToLower(node->product.specs.manufacturer);
        std::string series = charArrayToLower(node->product.specs.series);
        std::string formFactor = charArrayToLower(node->product.specs.formFactor);
        std::string capacity = charArrayToLower(node->product.specs.capacity);
        std::string speed = charArrayToLower(node->product.specs.speed);
        std::string socket = charArrayToLower(node->product.specs.socket);
        std::string wattage = charArrayToLower(node->product.specs.wattage);
        std::string efficiency = charArrayToLower(node->product.specs.efficiency);
        std::string modularity = charArrayToLower(node->product.specs.modularity);
        std::string cooling = charArrayToLower(node->product.specs.cooling);

        // Check if search string exists in any field
        if (name.find(searchLower) != std::string::npos ||
            category.find(searchLower) != std::string::npos ||
            brand.find(searchLower) != std::string::npos ||
            manufacturer.find(searchLower) != std::string::npos ||
            series.find(searchLower) != std::string::npos ||
            formFactor.find(searchLower) != std::string::npos ||
            capacity.find(searchLower) != std::string::npos ||
            speed.find(searchLower) != std::string::npos ||
            socket.find(searchLower) != std::string::npos ||
            wattage.find(searchLower) != std::string::npos ||
            efficiency.find(searchLower) != std::string::npos ||
            modularity.find(searchLower) != std::string::npos ||
            cooling.find(searchLower) != std::string::npos) {
            results.push_back(node->product);
        }

        searchRec(node->left, searchLower, results);
        searchRec(node->right, searchLower, results);
    }

    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};

#endif // BST_H