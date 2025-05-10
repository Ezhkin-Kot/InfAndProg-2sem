#include <iostream>
#include <sstream>

#define BLACK 0
#define RED 1

class RBTree
{
private:
    struct Node
    {
        int value;
        Node *left;
        Node *right;
        Node *parent;
        bool color; // RED or BLACK
        Node(int value) : value(value), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
    };

    Node *root; // Root of the tree
    Node *nil; // Sentinel node representing null leaves

    Node *grandparent(Node *node)
    {
        if (node->parent->parent)
        {
            return node->parent->parent;
        }
        return nil;
    }

    Node *uncle(Node *node) // Sibling of the parent
    {
        Node *g = grandparent(node);
        if (g == nil)
        {
            return nil;
        }
        return (node->parent == g->left) ? g->right : g->left;
    }

    Node *sibling(Node *node)
    {
        if (node && node->parent)
        {
            if (node == node->parent->left)
            {
                return node->parent->right;
            }
            return node->parent->left;
        }
        return nil;
    }

    // Moves node's right child up and node down to the left child of that right child
    void rotateLeft(Node *node)
    {
        Node *child = node->right;
        node->right = child->left;

        if (node->left != nil)
        {
            node->left->parent = node;
        }

        child->parent = node->parent;

        if (node->parent == nil)
        {
            root = child;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = child;
        }
        else
        {
            node->parent->right = child;
        }

        child->left = node;
        node->parent = child;
    }

    // Moves node's left child up and node down to the right child of that left child
    void rotateRight(Node *node)
    {
        Node *child = node->left;
        node->left = child->right;

        if (node->right != nil)
        {
            node->right->parent = node;
        }

        child->parent = node->parent;

        if (node->parent == nil)
        {
            root = child;
        }
        else if (node == node->parent->right)
        {
            node->parent->right = child;
        }
        else
        {
            node->parent->left = child;
        }

        child->right = node;
        node->parent = child;
    }

    // Helper methods for insertion method
    // Case 1: Node is root
    void insertCase1(Node *node)
    {
        if (node->parent == nil)
        {
            node->color = BLACK;
        }
        else
        {
            insertCase2(node);
        }
    }

    // Case 2: Parent is red
    void insertCase2(Node *node)
    {
        if (node->parent->color == RED)
        {
            insertCase3(node);
        }
    }

    // Case 3: Parent and uncle are red
    void insertCase3(Node *node)
    {
        Node *u = uncle(node);
        Node *g = grandparent(node);

        if (u != nil && u->color == RED && node->parent->color == RED)
        {
            node->parent->color = BLACK;
            u->color = BLACK;
            g->color = RED;
            insertCase1(g);
        }
        else
        {
            insertCase4(node);
        }
    }

    // Case 4: Node is right child of left parent or left child of right parent, rotate to convert to case 5
    void insertCase4(Node *node)
    {
        Node *g = grandparent(node);

        if (node == node->parent->right && node->parent == g->left)
        {
            rotateLeft(node->parent);
            node = node->left;
        }
        else if (node == node->parent->left && node->parent == g->right)
        {
            rotateRight(node->parent);
            node = node->right;
        }
        insertCase5(node);
    }

    // Case 5: Parent is left child of grandparent - right rotate grandparent, else left rotate
    void insertCase5(Node *node)
    {
        Node *g = grandparent(node);
        node->parent->color = BLACK;
        g->color = RED;

        if (node == node->parent->left && node->parent == g->left)
        {
            rotateRight(g);
        }
        else
        {
            rotateLeft(g);
        }
    }

    // Recursive insertion helper method
    void insert(Node *Prev, int newNode)
    {
        if (newNode < Prev->value && Prev->left == nil)
        {
            Prev->left = new Node(newNode);
            Prev->left->left = Prev->left->right = nil;
            Prev->left->parent = Prev;
            insertCase1(Prev->left);
        }
        else if (newNode > Prev->value && Prev->right == nil)
        {
            Prev->right = new Node(newNode);
            Prev->right->left = Prev->right->right = nil;
            Prev->right->parent = Prev;
            insertCase1(Prev->right);
        }
        else if (newNode < Prev->value && !(Prev->left == nil))
        {
            insert(Prev->left, newNode);
        }
        else if (newNode > Prev->value && !(Prev->right == nil))
        {
            insert(Prev->right, newNode);
        }
    }

    // Helper methods for deletion method
    // Case 1: Node is root
    void deleteCase1(Node *node)
    {
        if (!node->parent)
        {
            if (node->left != nil)
            {
                root = node->left;
            }
            else
            {
                root = node->right;
            }
        }
        else
        {
            deleteCase2(node);
        }
    }

    // Case 2: Sibling is red
    void deleteCase2(Node *node)
    {
        Node *s = sibling(node);

        if (s->color == RED)
        {
            node->parent->color = RED;
            s->color = BLACK;
            if (node == node->parent->left)
            {
                rotateLeft(node->parent);
            }
            else
            {
                rotateRight(node->parent);
            }
        }
        deleteCase3(node);
    }

    // Case 3: Parent, sibling, and sibling's children are black
    void deleteCase3(Node *node)
    {
        Node *s = sibling(node);

        if (node->parent->color == BLACK && s->color == BLACK &&
            (s->left == nil || s->left->color == BLACK) && (s->right == nil || s->right->color == BLACK))
        {
            s->color = RED;
            deleteCase1(node);
        }
        else
        {
            deleteCase4(node);
        }
    }

    // Case 4: Parent is red, sibling and sibling's children are black
    void deleteCase4(Node *node)
    {
        Node *s = sibling(node);

        if (node->parent->color == RED && s->color == BLACK &&
            (s->left == nil || s->left->color == BLACK) && (s->right == nil || s->right->color == BLACK))
        {
            s->color = RED;
            node->parent->color = BLACK;
        }
        else
        {
            deleteCase5(node);
        }
    }

    // Case 5: Sibling is black with one red child, rotate and recolor to transform to case 6
    void deleteCase5(Node *node)
    {
        Node *s = sibling(node);

        if (s->color == BLACK)
        {
            if (node == node->parent->left &&
                (s->left != nil && s->left->color == RED) && (s->right == nil || s->right->color == BLACK))
            {
                s->color = RED;
                s->left->color = BLACK;
                rotateRight(s);
            }
            else if (node == node->parent->right &&
                (s->right != nil && s->right->color == RED) && (s->left == nil || s->left->color == BLACK))
            {
                s->color = RED;
                s->right->color = BLACK;
                rotateLeft(s);
            }
        }
        deleteCase6(node);
    }

    // Case 6: Sibling is black with red child
    void deleteCase6(Node *node)
    {
        Node *s = sibling(node);
        s->color = node->parent->color;
        node->parent->color = BLACK;

        if (node == node->parent->left)
        {
            s->right->color = BLACK;
            rotateLeft(node->parent);
        }
        else
        {
            s->left->color = BLACK;
            rotateRight(node->parent);
        }
    }

    // Replace node with its single child in the tree
    void replace(Node *node)
    {
        Node *ch;
        if (node->left != nil)
        {
            ch = node->left;
            ch->parent = node->parent;
            if (node->parent)
            {
                if (node == node->parent->left)
                {
                    node->parent->left = ch;
                }
                else
                {
                    node->parent->right = ch;
                }
            }
        }
        else
        {
            ch = node->right;
            ch->parent = node->parent;
            if (node->parent)
            {
                if (node == node->parent->left)
                {
                    node->parent->left = ch;
                }
                else
                {
                    node->parent->right = ch;
                }
            }
        }
    }

    // Helper method for finding the node
    Node* findNode(Node *node, int value)
    {
        if (node == nil || value == node->value)
        {
            return node;
        }
        if (value < node->value)
        {
            return findNode(node->left, value);
        }
        return findNode(node->right, value);
    }

    void symmetricBypass(Node *node)
    {
        if (node != nil)
        {
            symmetricBypass(node->left);

            std::string color = node->color == RED ? "R" : "B";
            std::cout << node->value << color << " ";

            symmetricBypass(node->right);
        }
    }

    void printLeaves(Node *node) {
        if (node == nil) return;

        if (node->left == nil && node->right == nil) {
            std::cout << node->value << " ";
        } else {
            printLeaves(node->left);
            printLeaves(node->right);
        }
    }


public:
    RBTree() {
        nil = new Node(0);
        nil->color = BLACK;
        nil->left = nil->right = nil->parent = nullptr;
        root = nil;
    }

    void insert(int node)
    {
        if (root == nil)
        {
            root = new Node(node);
            root->color = BLACK;
            root->left = root->right = nil;
            root->parent = nil;
        } else {
            insert(root, node);
        }
    }

    // Find node with given value
    Node* findNode(int value)
    {
        Node *node = findNode(root, value);
        return node;
    }

    void deleteNode(Node* node) {
        if (node->left != nil && node->right != nil)
        {
            Node *buf;
            if (node->value <= root->value)
            {
                buf = node->left;
                while (buf->right != nil)
                {
                    buf = buf->right;
                }
            }
            else
            {
                buf = node->right;
                while (buf->left != nil)
                {
                    buf = buf->left;
                }
            }

            node->value = buf->value;
            deleteNode(buf);
            return;
        }
        else if (node->left != nil || node->right != nil)
        {
            Node *ch = nullptr;
            if (node->left != nil && node->right == nil)
            {
                ch = node->left;
            }
            else if (node->left == nil && node->right != nil)
            {
                ch = node->right;
            }

            replace(node);

            if (node->color == BLACK)
            {
                if (ch->color == RED)
                {
                    ch->color = BLACK;
                }
                else
                {
                    deleteCase1(node);
                }
            }
            if (!ch) return;
        }
        else
        {
            if (node->color == BLACK)
            {
                deleteCase1(node);
            }
            if (node == node->parent->left)
            {
                node->parent->left = nil;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = nil;
            }
        }

        delete node;
    }

    void symmetricBypass() {
        symmetricBypass(root);
        std::cout << std::endl;
    }

    void printLeaves() {
        printLeaves(root);
        std::cout << std::endl;
    }
};

int main()
{
    std::string input;
    std::cout << "Enter nodes of the tree separated by space:" << std::endl;
    getline(std::cin, input);
    std::stringstream ss(input);

    RBTree tree;

    int temp;
    while (ss >> temp)
    {
        tree.insert(temp);
    }

    std::cout << "\nTree:" << std::endl;
    tree.symmetricBypass();

    int nodeToDelete;
    std::cout << "\nEnter node to delete:" << std::endl;
    std::cin >> nodeToDelete;
    auto node = tree.findNode(nodeToDelete);
    tree.deleteNode(node);

    std::cout << "\nTree after deleting the element:" << std::endl;
    tree.symmetricBypass();

    std::cout << "\nLeaves:" << std::endl;
    tree.printLeaves();

    return 0;
}

