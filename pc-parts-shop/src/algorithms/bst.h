#ifndef BST_H
#define BST_H

#include "../models/product.h"

struct TreeNode {
    Product product;
    TreeNode* left;
    TreeNode* right;
};

class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(const Product& product);
    bool search(const std::string& productName, Product& foundProduct) const;
    void remove(const std::string& productName);
    void inOrderTraversal() const;

private:
    TreeNode* root;

    void insert(TreeNode*& node, const Product& product);
    bool search(TreeNode* node, const std::string& productName, Product& foundProduct) const;
    void remove(TreeNode*& node, const std::string& productName);
    void inOrderTraversal(TreeNode* node) const;
    void clear(TreeNode* node);
};

#endif // BST_H