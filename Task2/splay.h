#ifndef SPLAYTREEH_H
#define SPLAYTREEH_H

#include <iostream>
using namespace std;

class SplayTree {
    private:
        struct Node {
            int key;
            Node* left;
            Node* right;
            Node* parent;
            
            Node(int k) {
                key = k;
                left = nullptr;
                right = nullptr;
                parent=nullptr; 
            }
        };

        Node* root;

        Node* rotateRight(Node* x);
        Node* rotateLeft(Node* x);
        Node* splay(Node* root, int key);
        Node* insertNode(Node* root, int key);
        Node* deleteNode(Node* root, int key);
        Node* semiSplay(Node* root, int key, int k);
        
        void printTree(Node* root, int space);

    public:
        SplayTree();
        void insert(int key);
        void remove(int key);
        bool search(int key);
        void display();
};

#endif 
