#include <iostream>

#include <cstdlib>

#include <string>


using namespace std;

struct tree_node
{
    struct tree_node* left;

    string Name;

    string Department;

    string Gender;

    int Age;
    
    struct tree_node* right;
};

typedef struct tree_node* Node;

class Trees
{
    public :
     
    Node root;

    public :

    Trees()
    {
        this->root = NULL;
    }

    void Insert()
    {
        int t=0;

        Node newone = new struct tree_node;

        cout << "Enter the name of the faculty : ";

        string temporary;

        getline(cin,temporary);

        newone->Name = temporary;

        cout << "Enter the age of the faculty : ";

        int k;

        cin >> k;

        fflush(stdin);

        newone->Age = k;

        cout << "Enter the gender of the faculty : ";

        getline(cin,temporary);

        newone->Gender = temporary;

        cout << "Enter the department of the faculty : ";

        getline(cin,temporary);

        newone->Department = temporary;
        
        Node temp , temp_before;

        temp = this->root;

        while(temp != NULL)
        {
            if(temp->Name.compare(newone->Name) > 0)
            {
                t=1;
                temp_before = temp;
                temp = temp->left;
            }
            else
            {
                t=2;
                temp_before = temp;
                temp = temp->right;
            }
        }

        if(t==0)
        {
            this->root = newone;
        }
        if(t==1)
        {
            temp_before->left = newone;
        }
        if(t==2)
        {
            temp_before->right = newone;
        }

        newone->left = NULL;

        newone->right = NULL;
    }

    bool SearchByName()
    {
        string Name;

        cout << "Enter the name of the faculty : " ;

        getline(cin , Name);

        Node curr = this->root;

        Node curr_before = NULL;

        while(curr != NULL)
        {   
            if(curr->Name.compare(Name) == 0)
            {
                cout << endl;

                cout << "----------------------------------------------------" << endl;

                cout << "The details of the faculty are :" << endl;
                cout << "Name : " << curr->Name << endl;
                cout << "Age : " << curr->Age << endl;
                cout << "Gender : " << curr->Gender << endl;
                cout << "Department : " << curr->Department << endl;

                cout << "----------------------------------------------------" << endl;

                cout << endl;

                return 1;
            }
            if(curr->Name.compare(Name) < 0)
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

    bool DeleteByName()
    {
        string Name;

        cout << "Enter the name of the faculty : " ;

        getline(cin , Name);

        Node curr = this->root;

        Node curr_before = NULL;

        bool t = 0;

        if(curr != NULL)
        {
            while(curr->Name.compare(Name) != 0)
            {
                if(curr->Name.compare(Name) > 0)
                {
                    t = 0;
                    curr_before = curr;
                    curr = curr->left;
                }
                else
                {
                    t = 1;
                    curr_before = curr;
                    curr = curr->right;
                }

                if(curr == NULL) break;
            }
        }

        if(curr != NULL)
        {
            Node temp = curr->left;

            Node temp_before = NULL;

            // Have to locate the highest value in the tree with node temp;

            if(temp == NULL)
            {
                if( t==0)
                {
                    if(curr_before != NULL)
                    {
                        curr_before->left = curr->right;
                    }
                    else
                    {
                        this->root = curr->right;
                    }
                    delete curr;

                    return 1;
                }
                else
                {
                    if(curr_before != NULL)
                    {
                        curr_before->right = curr->right;
                    }
                    else
                    {
                        this->root = curr->right;
                    }

                    delete curr;

                    return 1;
                }
            }
            else
            {
                while(temp->right != NULL)
                {
                    temp_before = temp;
                    temp = temp->right;
                }

                curr->Age = temp->Age;
                curr->Name = temp->Name;
                curr->Department = temp->Department;
                curr->Gender = temp->Gender;

               
                if(temp_before != NULL)
                {
                    temp_before->right = temp->left;
                }
                else
                {
                    curr->left = temp->left;
                }

                delete temp;

                return 1;
            }
        }
        return 0;
    
    }

    void PrintTree()
    {
        Node curr = this->root; 
        
        Node curr_right = NULL;

        Node curr_left = NULL;

        if(curr != NULL)
        {
            curr_right = curr->right;

            curr_left = curr->left; 

            Trees tree_left;

            tree_left.root = curr_left;

            tree_left.PrintTree();

            cout << curr->Name << " | ";
            cout << curr->Age << " | ";
            cout << curr->Gender << " | ";
            cout << curr->Department << endl;

            Trees tree_right;

            tree_right.root = curr_right;

            tree_right.PrintTree();
        }
    }

    void free_memory()
    {
        Node curr = this->root;

        Node curr_right = NULL;

        Node curr_left = NULL;

        if(curr != NULL)
        {
            curr_right = curr->right;

            curr_left = curr->left; 

            free(curr);

            Trees tree_right;

            tree_right.root = curr_right;

            Trees tree_left;

            tree_left.root = curr_left;

            tree_left.free_memory();

            tree_right.free_memory();
                        
        }
    }

    int intro_page()
    {
        cout << endl;

        cout << endl;

        cout << "The elements present in the Tree are : " <<endl;

        cout << endl;

        this->PrintTree();

        cout << endl;

        cout << endl;

        cout << "----------------------------------------------------" << endl;


        cout << "What would you like to do ?" << endl;

        cout << "1. Insert an element into the Tree" << endl;

        cout << "2. Delete an element from the Tree by name" << endl;

        cout << "3. Search an element from the Tree by name" << endl;

        cout << "4. Exit" << endl;

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
    Trees tree;

    int opt;

    while((opt = tree.intro_page()))
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
                bool end;

                end = tree.DeleteByName();
                
                if(end == 1)
                {
                    cout << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << "Element deleted !" << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << endl;
                     
                }
                else
                {
                    cout << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << "Element is not present in Binary tree !" << endl;

                    cout << "----------------------------------------------------" << endl;

                     cout << endl;
                    
                }
                
                break;

            case 3:
                if(tree.SearchByName() == 0)
                {
                    cout << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << "Element is not present" << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << endl;
                }
                
                break;   

            case 4:
                {
                   tree.free_memory();
                }
                break;

            default:
                break;
        }
        if(opt ==4 ) break;
    }

}