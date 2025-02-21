#include "bst.h"
#include <iostream>

struct Node {
    Product product;
    Node* left;
    Node* right;

    Node(Product p) : product(p), left(NULL), right(NULL) {}
};

class BST {
private:
    Node* root;

    void insert(Node*& node, Product product) {
        if (node == NULL) {
            node = new Node(product);
        } else if (product.price < node->product.price) {
            insert(node->left, product);
        } else {
            insert(node->right, product);
        }
    }

    bool search(Node* node, std::string productName) {
        if (node == NULL) {
            return false;
        }
        if (node->product.name == productName) {
            return true;
        }
        return search(node->left, productName) || search(node->right, productName);
    }

    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    BST() : root(NULL) {}

    ~BST() {
        deleteTree(root);
    }

    void insert(Product product) {
        insert(root, product);
    }

    bool search(std::string productName) {
        return search(root, productName);
    }
};