#include <iostream>

#include <cstdlib>

#include <stdlib.h>

using namespace std;

struct tree_node 
{
    struct tree_node* left;

    string Name;

    string Department;

    string Gender;

    int Age;

    bool left_child;

    bool right_child;
    
    struct tree_node* right;
};

typedef struct tree_node* Node;

class Trees_trans
{
    public:

    Node root;

    public:

    Trees_trans()
    {
        this->root = NULL;
    }

    void Insert ()
    {
        int t = 0;

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

        newone->left_child = 0;

        newone->right_child = 0;

        Node temp = this->root ;

        Node temp_before = NULL ;

        while(temp != NULL)
        {
            if(temp->Name.compare(newone->Name) > 0)
            {
                t=1;
                temp_before = temp;
                temp = temp->left;
                if(temp_before->left_child == 0)
                {
                    temp = NULL;
                }
            }
            else
            {
                t=2;
                temp_before = temp;
                temp = temp->right;
                if(temp_before->right_child == 0)
                {
                    temp = NULL;
                }
            }
        }

        if(t==0)
        {
            this->root = newone;

            newone->left = NULL;

            newone->right = NULL;
        }
        if(t==1)
        {
            newone->left = temp_before->left;

            newone->right = temp_before;

            temp_before->left = newone;

            temp_before->left_child = 1;
            
        }
        if(t==2)
        {
            newone->left = temp_before;

            newone->right = temp_before->right;

            temp_before->right = newone;

            temp_before->right_child = 1;
        }

        return ;
    }

    void TressTraversal ()
    {
        Node curr = this->root;

        bool t = 0;

        if(curr != NULL)
        {
            while(curr->left_child == 1)
            {
                curr = curr->left;
            }

            while(curr != NULL)
            {
                cout << curr->Name << " | ";
                cout << curr->Age << " | ";
                cout << curr->Gender << " | ";
                cout << curr->Department << endl;
                
                if(curr->right_child == 1)
                {
                    curr = curr->right;

                    while(curr->left_child == 1)
                    {
                        curr = curr->left;
                    }
                }
                else
                {
                    curr = curr->right;
                }
            }            
        }
        return;

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
                if(curr->right_child == 1)
                {
                    curr = curr->right;
                }
                else
                {
                    curr = NULL;
                }
            }
            else
            {
                curr_before = curr;
                if(curr->left_child == 1)
                {
                    curr = curr->left;
                }
                else
                {
                    curr = NULL;
                }
            }
        }
        return 0 ;
    }

    bool DeleteByName ()
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
                    if(curr->left_child == 0)
                    {
                        curr = NULL;
                    }
                    else
                    {
                        curr = curr->left;
                    }
                }
                else
                {
                    t = 1;
                    curr_before = curr;
                    if(curr->right_child == 0)
                    {
                        curr = NULL;
                    }
                    else
                    {
                        curr = curr->right;
                    }
                }

                if(curr == NULL) break;
            }
        }

        if(curr != NULL)
        {
            Node temp = curr->left;

            if(curr->left_child == 0)
            {
                temp = NULL;
            }

            Node temp_before = NULL;

            // Have to locate the highest value in the tree with node temp;

            if(temp == NULL)
            {
                if( t==0 )
                {
                    if(curr_before != NULL)
                    {
                        if(curr->right_child == 0)
                        {
                            curr_before->left_child = 0;

                            curr_before->left = curr->left;
                        }
                        else
                        {
                            Node another_temp = curr->right;

                            while(another_temp->left_child != 0)
                            {
                                another_temp = another_temp->left;
                            }

                            another_temp->left = curr->left;

                            curr_before->left = curr->right;
                        }
                    }
                    else
                    {
                        if(curr->right_child == 0)
                        {
                            this->root = curr->left;
                        }
                        else
                        {
                            Node another_temp2 = curr->right;

                            while(another_temp2->left_child != 0)
                            {
                                another_temp2 = another_temp2->left;
                            }

                            another_temp2->left = curr->left;

                            this->root = curr->right;
                        }
                    }
                    delete curr;

                    return 1;
                }
                else
                {
                    if(curr_before != NULL)
                    {
                        if(curr->right_child == 0)
                        {
                            curr_before->right_child = 0;

                            curr_before->right = curr->right;
                        }
                        else
                        {
                            Node another_temp3 = curr->right;

                            while(another_temp3->left_child != 0)
                            {
                                another_temp3 = another_temp3->left;
                            }

                            another_temp3->left = curr->left;

                            curr_before->right = curr->right;
                        }
                    }
                    else
                    {
                        if(curr->right_child == 0)
                        {
                            this->root = curr->left;
                        }
                        else
                        {
                            Node another_temp4 = curr->right;

                            while(another_temp4->left_child != 0)
                            {
                                another_temp4 = another_temp4->left;
                            }

                            another_temp4->left = curr->left;

                            this->root = curr->right;
                        }
                    }

                    delete curr;

                    return 1;
                }
            }
            else
            {
                while(temp->right_child != 0)
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
                    if(temp->left_child == 0)
                    {
                        temp_before->right_child = 0;

                        temp_before->right = temp->right;
                    }
                    else
                    {
                        Node another_temp6 = temp->left;

                        while(another_temp6->right_child != 0)
                        {
                            another_temp6 = another_temp6->right;
                        }

                        another_temp6->right = temp->right;

                        temp_before->right = temp->left;
                    }
                }
                else
                {
                    if(temp->left_child == 0)
                    {
                        curr->left_child = 0;

                        curr->left = temp->left;
                    }
                    else
                    {
                        Node another_temp5 = temp->left;

                        while(another_temp5->right_child != 0)
                        {
                            another_temp5 = another_temp5->right;
                        }

                        another_temp5->right = temp->right;

                        curr->left = temp->left;
                    }
                   
                }
                delete temp;

                return 1;
            }
        }
        return 0;
    
    }
    
    void free_memory()
    {
        Node curr = this->root;

        Node curr_right = NULL;

        Node curr_left = NULL;

        if(curr != NULL)
        {
            if(curr->right_child == 1)
            {
                curr_right = curr->right;
            }

            if(curr->left_child == 1)
            {
                curr_left = curr->left;
            }

            free(curr);

            Trees_trans tree_right;

            tree_right.root = curr_right;

            Trees_trans tree_left;

            tree_left.root = curr_left;

            tree_left.free_memory();

            tree_right.free_memory();
                        
        }
    }

    int intro_page ()
    {
        cout << endl;

        cout << endl;

        cout << "The elements present in the Tree are : " <<endl;

        cout << endl;

        this->TressTraversal();

        cout << endl;

        cout << endl;

        cout << "----------------------------------------------------" << endl;


        cout << "What would you like to do ?" << endl;

        cout << "1. Insert an element into the Tree" << endl;

        cout << "2. Delete an element from the Tree by name" << endl;

        cout << "3. Search an element from the Tree by name" << endl;

        cout << "4. Inorder Tree Traversal" << endl;

        cout << "5. Exit" << endl;

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
    Trees_trans tree;

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
                cout << endl;

                cout << "----------------------------------------------------" << endl;
                
                tree.TressTraversal();   

                cout << "----------------------------------------------------" << endl;

                cout << endl;

                break;

            case 5:
                {
                   tree.free_memory();
                }
                break;

            default:
                break;
        }
        if(opt ==5 ) break;
    }
}

