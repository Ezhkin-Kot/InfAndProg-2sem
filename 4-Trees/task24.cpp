#include <iostream>
#include <sstream>

struct tree
{
    int data;
    tree *right;
    tree *left;
    tree *parent;
};

tree *treeRoot(int x)
{
    tree *newTree = new tree;
    newTree->data = x;
    newTree->left = newTree->right = NULL;
    newTree->parent = NULL;
    return newTree;
}

void insertNode(tree *&tr, int x)
{
    tree *n = treeRoot(x);
    if (!tr) tr = n; // Set root
    else
    {
        tree *y = tr;
        while (y)
        {
            if (n->data > y->data) // Right branch
                if (y->right)
                {
                    y = y->right;
                }
                else
                {
                    // Set right child
                    n->parent = y;
                    y->right = n;
                    break;
                }
            else if (n->data < y->data) // Left branch
                if (y->left)
                {
                    y = y->left;
                }
                else
                {
                    // Set left child
                    n->parent = y;
                    y->left = n;
                    break;
                }
            else
            {
                break;
            }
        }
    }
}

tree *setTree()
{
    tree *tr = nullptr;

    std::string nums;
    std::cout << "Enter numbers: ";
    getline(std::cin, nums);

    std::stringstream ss(nums);
    std::string x;
    while (ss >> x)
    {
        insertNode(tr, std::stoi(x));
    }

    return tr;
}

void printTree(tree *tr)
{
    // Symmetric bypass
    if (tr)
    {
        printTree(tr->left);
        std::cout << tr->data << " ";
        printTree(tr->right);
    }
}

void printNodesWithOnlyLeftChild(tree *tr)
{
    if (!tr) return;

    if (tr->left && !tr->right)
    {
        std::cout << tr->data << std::endl;
    }

    printNodesWithOnlyLeftChild(tr->left);
    printNodesWithOnlyLeftChild(tr->right);
}

void printTree2(tree *tr, int depth = 0)
{
    if (tr)
    {
        printTree2(tr->right, depth + 1);
        std::cout << std::string(depth * 4, ' ') << tr->data << std::endl;
        printTree2(tr->left, depth + 1);
    }
}

int main()
{
    tree *tr = setTree();

    std::cout << "Tree: " << std::endl;
    printTree(tr);
    std::cout << std::endl;

    std::cout << "Nodes with only left child: " << std::endl;
    printNodesWithOnlyLeftChild(tr);

    return 0;
}

// Example: 10 5 15 2 7 12 20 16 6
//
