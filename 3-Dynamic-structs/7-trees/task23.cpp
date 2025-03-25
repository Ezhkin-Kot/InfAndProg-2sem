#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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

void deleteNode(tree *&root, tree *node)
{
    if (!node) return;

    tree *parent = node->parent;

    // Node without child
    if (!node->left && !node->right)
    {
        if (parent)
        {
            if (parent->left == node) parent->left = nullptr;
            else parent->right = nullptr;
        }
        delete node;
    }
    // Node with one child
    else if (!node->left || !node->right)
    {
        tree *child = (node->left) ? node->left : node->right;

        if (parent)
        {
            if (parent->left == node) parent->left = child;
            else parent->right = child;
        }
        else
        {
            root = child;
        }
        child->parent = parent;
        delete node;
    }
    // Node with two children
    else
    {
        tree *succ = node->right;
        while (succ->left) succ = succ->left;

        node->data = succ->data;
        deleteNode(root, succ);
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

void findLeaves(tree *tr, std::vector<tree *> &leaves)
{
    if (!tr) return;
    if (!tr->left && !tr->right)
        leaves.push_back(tr);
    findLeaves(tr->left, leaves);
    findLeaves(tr->right, leaves);
}

void deleteMidLeafGrandparent(tree *tr)
{
    std::vector<tree *> leaves;
    findLeaves(tr, leaves);

    if (!leaves.empty())
    {
        std::sort(leaves.begin(), leaves.end(), [](tree *a, tree *b) {
            return a->data < b->data;
        });

        tree *midLeaf = leaves[leaves.size() / 2];

        if (midLeaf->parent && midLeaf->parent->parent)
        {
            std::cout << "Deleting grandparent of " << midLeaf->data << ": " << midLeaf->parent->parent->data << std::endl;
            deleteNode(tr, midLeaf->parent->parent);
        }
    }
}

int main()
{
    tree *tr = setTree();

    std::cout << "Tree: " << std::endl;
    printTree(tr);
    std::cout << std::endl;

    deleteMidLeafGrandparent(tr);
    std::cout << "Tree after deleting mid leaf's grandparent: " << std::endl;
    printTree(tr);
    std::cout << std::endl;

    return 0;
}

// Example: 10 5 15 2 7 12 20 6 8 13 18
// 30 15 50 10 20 40 60 5 12 18 22 35 45 55 65

