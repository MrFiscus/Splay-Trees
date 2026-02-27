#include "splay.h"
#include "customErrorClass.h"   

// default constructor
SplayTree::SplayTree()
{
    root = nullptr;
}

// aka Zig (Right rotation around x)
SplayTree::Node* SplayTree::rotateRight(Node* x)
{
    if (x == nullptr) throw MyException("error");

    Node* y = x->left;
    if (y == nullptr) throw MyException("error");

    // Move y's right subtree to x's left
    x->left = y->right;
    if (y->right != nullptr)
        y->right->parent = x;

    // Link y to x's parent
    y->parent = x->parent;

    if (x->parent != nullptr) {
        if (x->parent->left == x) x->parent->left = y;
        else x->parent->right = y;
    }

    // Put x on y's right
    y->right = x;
    x->parent = y;

    return y;
}

// aka Zag (Left rotation around x)
SplayTree::Node* SplayTree::rotateLeft(Node* x)
{
    if (x == nullptr) throw MyException("error");

    Node* y = x->right;
    if (y == nullptr) throw MyException("error");

    // Move y's left subtree to x's right
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;

    // Link y to x's parent
    y->parent = x->parent;

    if (x->parent != nullptr) {
        if (x->parent->left == x) x->parent->left = y;
        else x->parent->right = y;
    }

    // Put x on y's left
    y->left = x;
    x->parent = y;

    return y;
}

SplayTree::Node* SplayTree::splay(Node* root, int key)
{
    if (root == nullptr) return nullptr;

    Node header(0);
    header.left = nullptr;
    header.right = nullptr;
    header.parent = nullptr;

    Node* leftTreeMax = &header;
    Node* rightTreeMin = &header;

    // Make sure current root is treated as a real root (detached)
    root->parent = nullptr;

    while (true) {

        if (key < root->key) {

            if (root->left == nullptr) break;

            if (key < root->left->key) {
                root = rotateRight(root);
                root->parent = nullptr;
                if (root->left == nullptr) break;
            }

            rightTreeMin->left = root;
            if (rightTreeMin != &header) root->parent = rightTreeMin;
            rightTreeMin = root;

            root = root->left;
            root->parent = nullptr;
            rightTreeMin->left = nullptr;
        }
        else if (key > root->key) {

            if (root->right == nullptr) break;

            if (key > root->right->key) {
                root = rotateLeft(root);
                root->parent = nullptr;
                if (root->right == nullptr) break;
            }

            leftTreeMax->right = root;
            if (leftTreeMax != &header) root->parent = leftTreeMax;
            leftTreeMax = root;

            root = root->right;
            root->parent = nullptr;
            leftTreeMax->right = nullptr;
        }
        else {
            break;
        }
    }

    leftTreeMax->right = root->left;
    if (leftTreeMax->right != nullptr)
        leftTreeMax->right->parent = leftTreeMax;

    rightTreeMin->left = root->right;
    if (rightTreeMin->left != nullptr)
        rightTreeMin->left->parent = rightTreeMin;

    root->left = header.right;
    if (root->left != nullptr)
        root->left->parent = root;

    root->right = header.left;
    if (root->right != nullptr)
        root->right->parent = root;

    root->parent = nullptr;
    return root;
}

SplayTree::Node* SplayTree::insertNode(Node* root, int key)
{
    // Normal BST insert, track parent pointers
    if (root == nullptr) {
        return new Node(key);
    }

    Node* cur = root;
    Node* prev = nullptr;

    while (cur != nullptr) {
        prev = cur;
        if (key < cur->key) cur = cur->left;
        else if (key > cur->key) cur = cur->right;
        else {
            // Key already exists
            throw MyException("error");
        }
    }

    Node* newNode = new Node(key);
    newNode->parent = prev;

    if (key < prev->key) prev->left = newNode;
    else prev->right = newNode;

    // Splay inserted key to root
    return splay(root, key);
}

SplayTree::Node* SplayTree::deleteNode(Node* root, int key)
{
    if (root == nullptr) throw MyException("error");

    // Bring key (or closest) to root
    root = splay(root, key);

    // If key not found, throw
    if (root == nullptr || root->key != key) throw MyException("error");

    Node* leftSub = root->left;
    Node* rightSub = root->right;

    if (leftSub != nullptr) leftSub->parent = nullptr;
    if (rightSub != nullptr) rightSub->parent = nullptr;

    delete root;

    // If no left subtree, right becomes new root
    if (leftSub == nullptr) {
        return rightSub;
    }

    // Find maximum node in left subtree
    Node* m = leftSub;
    while (m->right != nullptr) m = m->right;

    // Splay that maximum to root of left subtree
    leftSub = splay(leftSub, m->key);

    // Attach right subtree
    leftSub->right = rightSub;
    if (rightSub != nullptr) rightSub->parent = leftSub;

    return leftSub;
}

SplayTree::Node* SplayTree::weightedSplay(Node* root, int key)
{
    if (root == nullptr) return nullptr;

    Node header(0);
    header.left = nullptr;
    header.right = nullptr;
    header.parent = nullptr;

    Node* leftTreeMax  = &header;
    Node* rightTreeMin = &header;

    root->parent = nullptr;

    while (true) {

        if (key < root->key) {

            if (root->left == nullptr) break;

            if (key < root->left->key) {
                Node* child = root->left;
                if (child != nullptr && child->weight >= root->weight) {
                    root = rotateRight(root);  
                    root->parent = nullptr;
                    if (root->left == nullptr) break;
                }
            }

            // link current root into right tree
            rightTreeMin->left = root;
            if (rightTreeMin != &header) root->parent = rightTreeMin;
            rightTreeMin = root;

            root = root->left;
            root->parent = nullptr;
            rightTreeMin->left = nullptr;
        }
        else if (key > root->key) {

            if (root->right == nullptr) break;

            // OPTION 1: rotate only if child weight >= parent weight
            if (key > root->right->key) {
                Node* child = root->right;
                if (child != nullptr && child->weight >= root->weight) {
                    root = rotateLeft(root);
                    root->parent = nullptr;
                    if (root->right == nullptr) break;
                }
            }

            // link current root into left tree
            leftTreeMax->right = root;
            if (leftTreeMax != &header) root->parent = leftTreeMax;
            leftTreeMax = root;

            root = root->right;
            root->parent = nullptr;
            leftTreeMax->right = nullptr;
        }
        else {
            break; // found key
        }
    }
 
    leftTreeMax->right = root->left;
    if (leftTreeMax->right != nullptr)
        leftTreeMax->right->parent = leftTreeMax;

    rightTreeMin->left = root->right;
    if (rightTreeMin->left != nullptr)
        rightTreeMin->left->parent = rightTreeMin;

    root->left = header.right;
    if (root->left != nullptr)
        root->left->parent = root;

    root->right = header.left;
    if (root->right != nullptr)
        root->right->parent = root;

    root->parent = nullptr;
    return root;
}

void SplayTree::insert(int key)
{
    root = insertNode(root, key);
}

void SplayTree::remove(int key)
{
    root = deleteNode(root, key);
}

bool SplayTree::search(int key)
{
    if (root == nullptr) throw MyException("error");

    root = weightedSplay(root, key);

    if (root == nullptr || root->key != key) 
    throw MyException("error");
    root-> weight++; 
    return true;
}

void SplayTree::printTree(Node* root, int space)
{
    const int COUNT = 10;

    if (root == nullptr)
        return;

    space += COUNT;

    printTree(root->right, space);

    for (int i = COUNT; i < space; i++)
        cout << " ";

    cout << root->key << "rootweight:" << root->weight << endl;

    printTree(root->left, space);
}

void SplayTree::display()
{
    if (root == nullptr) throw MyException("error");

    printTree(root, 0);
    cout << endl;
}