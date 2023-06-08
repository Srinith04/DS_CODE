#include <iostream>

#include <cstdlib>

#include <stdlib.h>

#include <string>

using namespace std;

struct r_b_node
{
    char color;

    struct r_b_node *left;

    int age;

    struct r_b_node *right;

    struct r_b_node *parent;
};

typedef struct r_b_node *Node;

class RedBlackTrees
{
public:
    Node root;

public:
    RedBlackTrees()
    {
        this->root = NULL;
    }

    bool left_right_child(Node parent)
    {
        Node grandparent = parent->parent;

        if (grandparent->left == parent)
            return 0;
        else
            return 1;
    }

    Node rightrotate(Node grandparent)
    {
        Node parent = grandparent->left;
      
        grandparent->left = parent->right;

        if(parent->right != NULL)    parent->right->parent = grandparent;

        if(grandparent->parent != NULL) 
        {
            parent->parent = grandparent->parent;

            if (left_right_child(grandparent) == 0)
            {
                grandparent->parent->left = parent;
            }
            else
            {
                grandparent->parent->right = parent;
            }
        }
        else
        {
            this->root = parent;

            this->root->parent = NULL;
        }

        parent->right = grandparent;

        grandparent->parent = parent;

        parent->color = 'b';

        grandparent->color = 'r';
        
        this->root->color = 'b';

        return parent;
    }

    Node leftrotate(Node grandparent)
    {
        Node parent = grandparent->right;

        grandparent->right = parent->left;

        if(parent->left != NULL) parent->left->parent = grandparent;

        if(grandparent->parent != NULL)
        {
            parent->parent = grandparent->parent;

            if (left_right_child(grandparent) == 0)
            {
                grandparent->parent->left = parent;
            }
            else
            {
                grandparent->parent->right = parent;
            }
        }
        else
        {  
            this->root = parent;

            this->root->parent = NULL;
        }

        parent->left = grandparent;

        grandparent->parent = parent;

        parent->color = 'b';

        grandparent->color = 'r';

        this->root->color = 'b';

        return parent;
    }

    Node func1(Node newone)
    {
        bool k1 = 0, k2 = 0;

        Node parent = newone->parent;

        Node grandparent = parent->parent;

        if(grandparent == NULL) return this->root;

        Node uncle ;

        if(left_right_child(parent) == 0) uncle = grandparent->right;
        else uncle = grandparent->left;

        if (parent->color == 'r') // X'S PARENT IS NOT BLACK
        {
            if (uncle != NULL && uncle->color == 'r')
            {
                grandparent->left->color = 'b';

                grandparent->right->color = 'b';

                grandparent->color = 'r';

                this->root->color = 'b';

                return grandparent;
            }
            else
            {
                k1 = left_right_child(newone);

                k2 = left_right_child(parent);

                if (k1 == 0)
                {
                    if (k2 == 0) // case 1
                    {
                        return rightrotate(grandparent);
                    }
                    else // case 4
                    {
                        rightrotate(parent);
                        
                        return leftrotate(grandparent);
                    }
                }
                else
                {
                    if (k2 == 0) // case 2
                    {
                        leftrotate(parent);

                        return rightrotate(grandparent);
                    }   
                    else // case 3
                    {
                        return leftrotate(grandparent);
                    }
                }
                
                this->root->color = 'b';
            }
        }
        return this->root;
    }

    void Insert()
    {
        int t = 0;

        Node newone = new struct r_b_node;

        cout << "Enter the Age : ";

        int age;

        cin >> age;

        newone->age = age;

        newone->color = 'r';

        newone->left = NULL;

        newone->right = NULL;

        Node temp, parent;

        temp = this->root;

        parent = NULL;

        while (temp != NULL)
        {
            if (temp->age > newone->age)
            {
                t = 1;
                parent = temp;
                temp = temp->left;
            }
            else
            {
                t = 2;
                parent = temp;
                temp = temp->right;
            }
        }

        newone->parent = parent;

        if (t == 0)
        {
            this->root = newone;

            newone->color = 'b'; // Step 2
        }
        if (t == 1)
        {
            parent->left = newone;

            while (newone != this->root)
            {
                newone = func1(newone);
            }
        }
        if (t == 2)
        {
            parent->right = newone;

            while (newone != this->root)
            {
                newone = func1(newone);
            }
        }
    }

    bool SearchByAge()
    {
        int Age;

        cout << "Enter the Age : ";

        cin >> Age;

        Node curr = this->root;

        Node curr_before = NULL;

        while (curr != NULL)
        {
            if (curr->age == Age)
            {
                cout << endl;

                cout << "----------------------------------------------------" << endl;

                cout << "Element is present" << endl;

                cout << "----------------------------------------------------" << endl;

                cout << endl;

                return 1;
            }
            if (curr->age < Age)
            {
                curr_before = curr;
                curr = curr->right;
            }
            else
            {
                curr_before = curr;
                curr = curr->left;
            }
        }

        return 0;
    }

    void PrintTree()
    {
        Node temp = this->root;

        Node temp_right = NULL;

        Node temp_left = NULL;

        if (temp != NULL)
        {
            temp_right = temp->right;

            temp_left = temp->left;

            RedBlackTrees tree_left;

            tree_left.root = temp_left;

            tree_left.PrintTree();

            cout << temp->age << ' ';

            RedBlackTrees tree_right;

            tree_right.root = temp_right;

            tree_right.PrintTree();
        }
    }

    void free_memory()
    {
        Node temp = this->root;

        Node temp_right = NULL;

        Node temp_left = NULL;

        if (temp != NULL)
        {
            temp_right = temp->right;

            temp_left = temp->left;

            delete temp;

            RedBlackTrees tree_right;

            tree_right.root = temp_right;

            RedBlackTrees tree_left;

            tree_left.root = temp_left;

            tree_left.free_memory();

            tree_right.free_memory();
        }
    }

    int intro_page()
    {
        cout << endl;

        cout << endl;

        cout << "The elements present in the Red Black Tree are : " << endl;

        cout << endl;

        this->PrintTree();

        cout << endl;

        cout << endl;

        cout << "----------------------------------------------------" << endl;

        cout << "What would you like to do ?" << endl;

        cout << "1. Insert an element into the Tree" << endl;

        cout << "2. Search an element from the Tree by age" << endl;

        cout << "3. Exit" << endl;

        cout << "----------------------------------------------------" << endl;

        cout << endl;

        int opt;

        cin >> opt;

        fflush(stdin);

        return opt;
    }
};

int main()
{
    RedBlackTrees tree;

    int opt;

    while ((opt = tree.intro_page()))
    {
        switch (opt)
        {
        case 1:
            tree.Insert();

            cout << endl;

            cout << "----------------------------------------------------" << endl;

            cout << "Element added !" << endl;

            cout << "----------------------------------------------------" << endl;

            cout << endl;

            break;

        case 2:
            if (tree.SearchByAge() == 0)
            {
                cout << endl;

                cout << "----------------------------------------------------" << endl;

                cout << "Element is not present" << endl;

                cout << "----------------------------------------------------" << endl;

                cout << endl;
            }

            break;

        case 3:
        {
            tree.free_memory();
        }
        break;

        default:
            break;
        }
        if (opt == 3)
            break;
    }
}