#include "splay.h"

int main() {
    SplayTree tree;

    tree.insert(57);
    tree.insert(31);
    tree.insert(72);
    tree.insert(44);
    tree.insert(69);
    tree.insert(83);

    cout << "Tree after insertions: ";
    cout << "---------------------" << endl;
    tree.display();

    tree.search(44);
    cout << "Tree after semi splaying then stopping after 2 rotations: ";
    cout << "----------------------" << endl;
    tree.display();

    tree.remove(31);
    cout << "Tree after deleting 31: ";
    tree.display();

    return 0;
}
