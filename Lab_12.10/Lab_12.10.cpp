#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int value;
    Node* left,
        * right;
};

Node* insertNode(Node*& root, int value, bool& found)
{
    Node* current = root, * parent = current;
    found = false;
    while (current != NULL && !found)
    {
        if (value == current->value)
        {
            found = true;
            return current;
        }
        else
        {
            parent = current;
            if (value < current->value)
                current = current->left;
            else
                current = current->right;
        }
    }
    current = new Node;
    current->value = value;
    current->left = NULL;
    current->right = NULL;
    found = false;
    if (parent != NULL)
    {
        if (value < parent->value)
            parent->left = current;
        else
            parent->right = current;
    }
    if (root == NULL)
        root = current;
    return current;
}

bool isFibonacciNumber(int n) {
    int a = 0, b = 1;
    while (b < n) {
        int temp = b;
        b = a + b;
        a = temp;
    }
    return (b == n);
}

int countNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void deleteTree(Node*& root) {
    if (root == NULL) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
    root = NULL;
}

int removeFibonacciSubtrees(Node*& root) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;

    bool isFibonacci = isFibonacciNumber(root->value);

    if (isFibonacci) {
        count += countNodes(root);
        deleteTree(root);
        return count;
    }

    count += removeFibonacciSubtrees(root->left);
    count += removeFibonacciSubtrees(root->right);

    return count;
}

void PrintTree(Node* root, int level)
{
    if (root != NULL)
    {
        PrintTree(root->right, level + 1);
        for (int i = 1; i <= level; i++)
            cout << "  ";
        cout << root->value << endl;
        PrintTree(root->left, level + 1);
    }
}

int main() {
    Node* root = NULL;

    ifstream inputFile("input.txt");
    int value;
    bool found;
    while (inputFile >> value) {
        insertNode(root, value, found);
    }
    inputFile.close();

    cout << "Start: " << endl;
    PrintTree(root, 0);
    cout << std::endl;

    int deletedNodesCount = removeFibonacciSubtrees(root);

    cout << "Count of deleted: " << deletedNodesCount << endl;

    cout << "After delete: " << endl;
    PrintTree(root, 0);

    return 0;
}
