#include <iostream>

#include <cstdlib>

#include <string>


using namespace std;


struct b_tree_node
{
    struct b_tree_node** pointers;

    int *Age;

    struct b_tree_node* parent;
    
    int num_ele;
};

typedef struct b_tree_node* Node;

class B_Trees
{
    public :
     
    Node root;

    public :

    B_Trees()
    {
        this->root = NULL;
    }

    int function(Node temp, int k)
    {
        if(k < temp->Age[0]) return 0;

        int i = 1;

        for(i = 1;i<temp->num_ele;i++)
        {
            if(k < temp->Age[i])
            {
                return i ;
            }
        }

        return i;
    }

    Node create_new_node()
    {
        Node newone = new struct b_tree_node;

        newone->Age = (int*)calloc(5,sizeof(int));

        newone->pointers = (Node*)calloc(6,sizeof(Node));

        newone->parent = (Node)calloc(1,sizeof(struct b_tree_node));

        newone->parent = NULL;

        for(int i=0;i<6;i++)
        {
            newone->pointers[i] = NULL;
        }

        return newone;
    }

    void Insert()
    {
        int t = -1;

        cout << "Enter the age of the faculty : ";

        int k;

        cin >> k;

        fflush(stdin);
        
        Node temp , temp_before;

        temp = this->root;

        while(temp != NULL)
        {
            t = function(temp,k);

            temp_before = temp;

            temp = temp->pointers[t];
        }

        if(t == -1)
        {
            Node newone = create_new_node();

            this->root = newone;

            newone->Age[0] = k;

            newone->num_ele = 1;
        }
        else
        {
            for(int i =temp_before->num_ele; i>t ;i--)
            {
                temp_before->Age[i] = temp_before->Age[i-1];
            }

            temp_before->Age[t] = k;

            temp_before->num_ele++;

            while(temp_before->num_ele == 5)
            {
                if(temp_before == this->root)
                {
                    Node newroot = create_new_node();

                    Node sibling = create_new_node();

                    for(int i = 3;i<5;i++)
                    {
                        sibling->Age[i-3] = temp_before->Age[i];

                        sibling->pointers[i-3] = temp_before->pointers[i];
                    }

                    sibling->pointers[2] = temp_before->pointers[5];

                    for(int i = 3;i<6;i++)
                    {
                        sibling->pointers[i] = NULL;

                        temp_before->pointers[i] = NULL;
                    }

                    newroot->Age[0] = temp_before->Age[2];

                    newroot->num_ele = 1;

                    sibling->num_ele = 2;

                    temp_before->num_ele = 2;

                    newroot->parent = NULL;

                    temp_before->parent = newroot;

                    sibling->parent = newroot;

                    newroot->pointers[0] = temp_before;

                    newroot->pointers[1] = sibling;

                    this->root = newroot;

                    if(sibling->pointers[0] != NULL)
                    {
                        for(int i=0 ; i<3;i++)
                        {
                            sibling->pointers[i]->parent = sibling;
                        }
                    }
                }
                else
                {
                    Node sibling = create_new_node();

                    sibling->parent = temp_before->parent;

                    if(sibling->pointers[0] != NULL)
                    {
                        for(int i=0 ; i<3;i++)
                        {
                            sibling->pointers[i]->parent = sibling;
                        }
                    }

                    sibling->num_ele = 2;

                    temp_before->num_ele = 2;

                    for(int i = 3;i<5;i++)
                    {
                        sibling->Age[i-3] = temp_before->Age[i];
                    }

                    int p = function(temp_before->parent,temp_before->Age[2]);

                    for(int i = temp_before->parent->num_ele ; i > p ; i --)
                    {
                        temp_before->parent->Age[i] = temp_before->parent->Age[i-1];

                        temp_before->parent->pointers[i+1] = temp_before->parent->pointers[i];
                    }

                    temp_before->parent->num_ele++;

                    temp_before->parent->Age[p] = temp_before->Age[2];

                    temp_before->parent->pointers[p+1] = sibling;
                }

                temp_before = temp_before->parent;
            }
        }
    }

    bool SearchByAge()
    {
        int Age , o ;

        cout << "Enter the Age : ";

        cin >> Age;

        Node curr = this->root;

        while (curr != NULL)
        {
            o = function(curr,Age);

            if (curr->Age[o-1] == Age)
            {
                cout << endl;

                cout << "----------------------------------------------------" << endl;

                cout << "Element is present" << endl;

                cout << "----------------------------------------------------" << endl;

                cout << endl;

                return 1;
            }

            curr = curr->pointers[o];
        }

        return 0;
    }

    bool DeleteByAge()
    {
        int Age,o;

        cout << "Enter the age : " ;

        cin >> Age ;

        Node curr = this->root;

        while (curr != NULL)
        {
            o = function(curr,Age);

            if (curr->Age[o-1] == Age)
            {
                if(curr->pointers[o] != NULL)
                {   // Non - Leaf case
                    while(curr->pointers[o] != NULL)
                    {
                        curr->Age[o-1] = curr->pointers[o]->Age[0];

                        curr = curr->pointers[o];

                        o = 1;
                    }

                    for(int l = 1 ; l < curr->num_ele ; l++)
                    {
                        curr->Age[l-1] = curr->Age[l];
                    }
                    curr->num_ele -- ;

                }
                else
                {   // Leaf case
                    for(int l = o ; l < curr->num_ele ; l++)
                    {
                        curr->Age[l-1] = curr->Age[l];
                    }
                    curr->num_ele -- ;
                }

                while(curr != this->root)
                {
                    if(curr->num_ele < 2)
                    {
                        Node sibling ;

                        o = function(curr->parent,curr->Age[0]);

                        if( o >= 1)
                        {
                            if( o == curr->parent->num_ele )
                            {
                                sibling = curr->parent->pointers[o-1];   
                                
                                if(sibling->num_ele == 2)
                                {   // Left one has less children
                                    sibling->Age[2] = curr->parent->Age[o-1];

                                    for(int k = 3 ; k < 4 ; k++)
                                    {
                                        sibling->Age[k] = curr->Age[k-3];
                                    }

                                    for(int i = 3;i<5;i++)
                                    {
                                        sibling->pointers[i] = curr->pointers[i-3];
                                        if(curr->pointers[i-3] != NULL)
                                        {
                                            curr->pointers[i-3]->parent = sibling;
                                        }
                                    }
                                    
                                    for(int j = o; j < curr->parent->num_ele ; j++)
                                    {
                                        curr->parent->Age[j-1] = curr->parent->Age[j];
                                        curr->parent->pointers[j] = curr->parent->pointers[j+1]; 
                                    }

                                    curr->parent->pointers[curr->parent->num_ele] = NULL;
                                    
                                    curr->parent->num_ele--;

                                    sibling->num_ele = 4;

                                    Node temp = curr;

                                    free(temp);

                                    curr = sibling->parent;

                                    if(curr == this->root && curr->num_ele == 0)
                                    {
                                        this->root = curr->pointers[0];

                                        free(curr);

                                        return 1;
                                    }
                                }
                                else
                                {   // case 2 (left)
                                    for(int q = curr->num_ele; q > 0 ; q--)
                                    {
                                        curr->Age[q] = curr->Age[q-1];

                                        curr->pointers[q+1] = curr->pointers[q]; 
                                    }

                                    curr->Age[0] = curr->parent->Age[o - 1];

                                    curr->pointers[0] = sibling->pointers[sibling->num_ele];

                                    if(curr->pointers[0]!= NULL)
                                    {
                                        curr->pointers[0]->parent = curr;
                                    }

                                    sibling->pointers[sibling->num_ele] = NULL;

                                    curr->parent->Age[o - 1] = sibling->Age[sibling->num_ele - 1];

                                    sibling->num_ele -- ;

                                    curr->num_ele ++ ;
                                }
                            }
                            else
                            {
                                if(curr->parent->pointers[o-1]->num_ele != 2)
                                {   // Case 2
                                    sibling = curr->parent->pointers[o-1];

                                    for(int q = curr->num_ele; q > 0 ; q--)
                                    {
                                        curr->Age[q] = curr->Age[q-1];
                                    }

                                    curr->Age[0] = curr->parent->Age[o-1];

                                    curr->pointers[0] = sibling->pointers[sibling->num_ele];

                                    if(curr->pointers[0]!= NULL)
                                    {
                                        curr->pointers[0]->parent = curr;
                                    }

                                    sibling->pointers[sibling->num_ele] = NULL;

                                    curr->parent->Age[o - 1] = sibling->Age[sibling->num_ele - 1];

                                    sibling->num_ele -- ;

                                    curr->num_ele ++ ;
                                }
                                else
                                {
                                    if(curr->parent->pointers[o+1]->num_ele == 2)
                                    {   // Less one has less children
                                        sibling = curr->parent->pointers[o-1];   
                                        
                                        sibling->Age[2] = curr->parent->Age[o-1];

                                        for(int k = 3 ; k < 4 ; k++)
                                        {
                                            sibling->Age[k] = curr->Age[k-3];
                                        }

                                        for(int i = 3;i<5;i++)
                                        {
                                            sibling->pointers[i] = curr->pointers[i-3];
                                            if(curr->pointers[i-3] != NULL)
                                            {
                                                curr->pointers[i-3]->parent = sibling;
                                            }
                                        }
                                        
                                        for(int j = o; j < curr->parent->num_ele ; j++)
                                        {
                                            curr->parent->Age[j-1] = curr->parent->Age[j];
                                            curr->parent->pointers[j] = curr->parent->pointers[j+1]; 
                                        }

                                        curr->parent->pointers[curr->parent->num_ele] = NULL;
                                        
                                        curr->parent->num_ele--;

                                        sibling->num_ele = 4;

                                        Node temp = curr;

                                        free(temp);

                                        curr = sibling->parent;

                                        if(curr == this->root && curr->num_ele == 0)
                                        {
                                            this->root = curr->pointers[0];

                                            free(curr);

                                            return 1;
                                        }
                                    }
                                    else
                                    {
                                        sibling = curr->parent->pointers[o+1];

                                        curr->Age[curr->num_ele] = curr->parent->Age[o];

                                        curr->pointers[curr->num_ele+1] = sibling->pointers[0];

                                        if(sibling->pointers[0] != NULL)
                                        {
                                            curr->pointers[curr->num_ele+1]->parent = curr;
                                        }

                                        curr->parent->Age[o] = sibling->Age[0];

                                        for(int q = 1; q < sibling->num_ele ; q++)
                                        {
                                            sibling->Age[q-1] = sibling->Age[q];

                                            sibling->pointers[q] = sibling->pointers[q+1];
                                        }

                                        sibling->pointers[sibling->num_ele] = NULL;

                                        sibling->num_ele -- ;

                                        curr->num_ele ++ ;
                                    }
                                }
                            }
                        }
                        else
                        {
                            sibling = curr->parent->pointers[o+1];

                            if(sibling->num_ele == 2)
                            {   // Right one has less children

                                curr->Age[1] = curr->parent->Age[o];

                                for(int k = 2 ; k < 4 ; k++)
                                {
                                    curr->Age[k] = sibling->Age[k-2];
                                }

                                for(int i= 2;i < 5;i++)
                                {
                                    curr->pointers[i] = sibling->pointers[i-2];
                                    if(sibling->pointers[i-2] != NULL)
                                    {
                                        sibling->pointers[i-2]->parent =  curr;
                                    }

                                }

                                for(int j = o; j < curr->parent->num_ele - 1 ; j++)
                                {
                                    curr->parent->Age[j] = curr->parent->Age[j+1];
                                    curr->parent->pointers[j+1] = curr->parent->pointers[j+2]; 
                                }

                                curr->parent->pointers[curr->parent->num_ele] = NULL;

                                curr->parent->num_ele--;

                                curr->num_ele = 4;

                                curr = curr->parent;

                                free(sibling);

                                if(curr == this->root && curr->num_ele == 0)
                                {
                                    this->root = curr->pointers[0];

                                    free(curr);

                                    return 1;
                                }
                            }
                            else
                            {   // case 2

                                 curr->Age[curr->num_ele] = curr->parent->Age[o];

                                curr->pointers[curr->num_ele+1] = sibling->pointers[0];

                                if(sibling->pointers[0] != NULL)
                                {
                                    curr->pointers[curr->num_ele+1]->parent = curr;
                                }

                                curr->parent->Age[o] = sibling->Age[0];

                                for(int q = 1; q < sibling->num_ele ; q++)
                                {
                                    sibling->Age[q-1] = sibling->Age[q];

                                    sibling->pointers[q] = sibling->pointers[q+1];
                                }

                                sibling->pointers[sibling->num_ele] = NULL;

                                sibling->num_ele -- ;
    
                                curr->num_ele ++ ;
                            }
                        }
                    }
                    else
                    {
                        curr = this->root;
                    }
                }
                
                if(curr == this->root && curr->num_ele == 0)
                {
                    this->root = curr->pointers[0];

                    free(curr);
                }
                return 1;
            }

            curr = curr->pointers[o];
        }

        return 0;
    
    }

    void PrintTree()
    {
        Node curr = this->root;

        if(curr!= NULL)
        {
            // for(int i=0;i<curr->num_ele;i++)
            // {
            //     B_Trees newtree;

            //     newtree.root = curr->pointers[i];

            //     newtree.PrintTree();

            //     cout << curr->Age[i] << ' ';
            // }


            // B_Trees newtree;

            // newtree.root = curr->pointers[curr->num_ele];

            // newtree.PrintTree();

            for(int i = 0;i<curr->num_ele;i++)
            {
                cout << curr->Age[i] << ' ';
            }

            cout << endl;

            for(int i=0;i<=curr->num_ele;i++)
            {
                Node curr2 = curr->pointers[i];

                if(curr2 != NULL)
                {
                    for(int i = 0;i<curr2->num_ele;i++)
                    {
                        cout << curr2->Age[i] << ' ';
                    }

                    cout << "      " ;
                }
            }

            cout << endl;

            for(int i=0;i<=curr->num_ele;i++)
            {
                Node curr2 = curr->pointers[i];

                if(curr2 != NULL)
                {
                    for(int j=0;j<=curr2->num_ele;j++)
                    {
                        Node curr3 = curr2->pointers[j];

                        if(curr3 != NULL)
                        {
                            for(int k = 0;k<curr3->num_ele;k++)
                            {
                                cout << curr3->Age[k] << ' ';
                            }

                            cout << "      " ;
                        }
                    }
                }
            }
            
        }
        cout << endl;
       
    }

    void free_memory()
    {
        Node curr = this->root;

        if(curr!= NULL)
        {
            for(int i=0;i<curr->num_ele;i++)
            {
                B_Trees newtree;

                newtree.root = curr->pointers[i];

                newtree.free_memory();
            }

            B_Trees newtree;

            newtree.root = curr->pointers[curr->num_ele];

            newtree.free_memory();

            free(curr->Age);

            free(curr->parent);

            for(int i=0;i<=curr->num_ele;i++)
            {
                free(curr->pointers[i]);
            }

            free(curr);
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
    B_Trees tree;

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

                end = tree.DeleteByAge();
                
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

                    cout << "Element is not present in Binomial tree !" << endl;

                    cout << "----------------------------------------------------" << endl;

                     cout << endl;
                    
                }
                
                break;

            case 3:
                if(tree.SearchByAge() == 0)
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