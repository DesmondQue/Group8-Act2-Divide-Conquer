#ifndef BST_H
#define BST_H

#include "../models/product.h"
#include <vector>
#include <map>
#include <string>

struct BSTNode {
    Product product;
    std::string key;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(const Product& p, const std::string& k) 
        : product(p), key(k), left(nullptr), right(nullptr) {}
};

class FieldBST {
private:
    BSTNode* root;
    
    BSTNode* insert(BSTNode* node, const Product& product, const std::string& key) {
        if (!node) return new BSTNode(product, key);
        
        if (key < node->key) {
            node->left = insert(node->left, product, key);
        } 
        else if (key > node->key) {
            node->right = insert(node->right, product, key);
        }
        else {
            node->right = insert(node->right, product, key);
        }
        return node;
    }

    void searchExact(BSTNode* node, const std::string& key, std::vector<Product>& results) const {
        if (!node) return;
        
        if (key < node->key) {
            searchExact(node->left, key, results);
        }
        else {
            // if current node matches -> add it
            if (node->key == key) {
                results.push_back(node->product);
            }
            
            // continue searching right subtree for more matches
            searchExact(node->right, key, results);
            
            // only search left if were at a matching node 
            if (node->key == key) {
                searchExact(node->left, key, results);
            }
        }
    }

    void deleteTree(BSTNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    FieldBST() : root(nullptr) {}
    ~FieldBST() { deleteTree(root); }
    
    void insert(const Product& product, const std::string& key) {
        root = insert(root, product, key);
    }
    
    std::vector<Product> search(const std::string& key) const {
        std::vector<Product> results;
        searchExact(root, key, results);
        return results;
    }
};

class BST {
private:
    std::map<std::string, FieldBST> fieldTrees;

    std::string toLowerCase(const std::string& str) const {
        std::string lower;
        for (char c : str) {
            if (c >= 'A' && c <= 'Z') {
                lower += (c + ('a' - 'A'));
            } else {
                lower += c;
            }
        }
        return lower;
    }

    std::string getFieldValue(const Product& product, const std::string& field) const {
        if (field == "brand") return product.specs.brand;
        if (field == "manufacturer") return product.specs.manufacturer;
        if (field == "series") return product.specs.series;
        if (field == "formFactor") return product.specs.formFactor;
        if (field == "capacity") return product.specs.capacity;
        if (field == "speed") return product.specs.speed;
        if (field == "socket") return product.specs.socket;
        if (field == "wattage") return product.specs.wattage;
        if (field == "efficiency") return product.specs.efficiency;
        if (field == "modularity") return product.specs.modularity;
        if (field == "cooling") return product.specs.cooling;
        if (field == "category") return product.category;
        if (field == "name") return product.name;
        return "";
    }

public:
    void insert(const Product& product) {
        // create separate BST for each searchable field
        std::string fields[] = {
            "brand", "manufacturer", "series", "formFactor",
            "capacity", "speed", "socket", "wattage",
            "efficiency", "modularity", "cooling", "category", "name"
        };

        for (const auto& field : fields) {
            std::string value = toLowerCase(getFieldValue(product, field));
            if (!value.empty()) {
                fieldTrees[field].insert(product, value);
            }
        }
    }

    std::vector<Product> search(const std::string& field, const std::string& term) const {
        auto it = fieldTrees.find(field);
        if (it != fieldTrees.end()) {
            return it->second.search(toLowerCase(term));
        }
        return std::vector<Product>();
    }
};

#endif