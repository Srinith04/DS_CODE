#include <iostream>

#include <cstdlib>

#include <string>

using namespace std;

struct skip_list_node
{
    struct skip_list_node* left;

    string Name;

    string Department;

    string Gender;

    int Age;

    struct skip_list_node* right;

    struct skip_list_node* down;
};

typedef struct skip_list_node* Node;

class Skip_list
{
    public:
    
    Node head ;

    int num_levels;

    public:

    Node create_new_node()
    {
        Node newone = new struct skip_list_node;

        newone->left = NULL;

        newone->right = NULL;

        newone->down = NULL;

        newone->Age = 1;

        return newone;
    }

    Skip_list()
    {
        this->head = create_new_node();

        this->num_levels = 1;
    }

    int toss_function()
    {
        float r = 0.0;

        int times = 0;

        while(r != 1)
        {
            r = (float)rand()/RAND_MAX;

            if(r>0.5)
            {
                r = 1;
            }
            else 
            {
                r = 0;
            }

            times ++;
        }
        
        return times;

    }

    void Insertinto(Node curr ,Node newone)
    {
        Node curr_before = curr;

        curr = curr->right;

        if (curr == NULL)
        {
            curr_before->right = newone;

            newone->left = curr_before;
        }
        else
        {
            while(curr != NULL)
            {
                if(curr->Name.compare(newone->Name) < 0)
                {
                    curr_before = curr;

                    curr = curr->right;
                }
                else
                {
                    Node next = curr_before->right;

                    if(next != NULL) next->left = newone;

                    if(curr_before != NULL) curr_before->right = newone;

                    newone->left = curr_before;

                    newone->right = next;

                    return;
                }
            }
            Node next = curr_before->right;

            if(next != NULL) next->left = newone;

            if(curr_before != NULL) curr_before->right = newone;

            newone->left = curr_before;

            newone->right = next;
        }
    }

    void Insert()
    {
        int num_times = toss_function() + 1;

        Node curr , newone , curr_before = NULL;

        if(num_times > this->num_levels)
        {
            for(int i= this->num_levels ; i < num_times ; i++)
            {
                newone = create_new_node();

                newone->down = this->head;

                this->head = newone;

                newone->Age = i + 1;
            }

            this->num_levels = num_times;

            curr = this->head;
        }
        else
        {
            curr = this->head;

            while(curr->Age != num_times)
            {
                curr = curr->down;
            }
        }

        string Name ;

        cout << "Enter the name of the faculty : ";

        getline(cin,Name);

        int Age;

        cout << "Enter the age of the faculty : ";

        cin >> Age;

        fflush(stdin);

        string Gender ;

        cout << "Enter the gender of the faculty : ";

        getline(cin,Gender);

        string Department;

        cout << "Enter the department of the faculty : ";

        getline(cin,Department);

        newone = create_new_node();

        newone->Age = Age;

        newone->Department = Department;

        newone->Gender = Gender;
        
        newone->Name = Name;

        while(curr != NULL)
        {
            newone = create_new_node();

            newone->Age = Age;

            newone->Department = Department;

            newone->Gender = Gender;
            
            newone->Name = Name;

            if(curr_before != NULL) curr_before->down = newone;

            Insertinto(curr,newone);

            curr = curr->down;

            curr_before = newone;
        }
    }

    bool SearchByName()
    {
        string Name;

        cout << "Enter the name of the faculty : " ;

        getline(cin , Name);

        Node curr = this->head;

        while(curr->right != NULL)
        {
            if(curr->right->Name.compare(Name) == 0)
            {
                cout << endl;

                cout << "----------------------------------------------------" << endl;

                cout << "The details of the faculty are :" << endl;
                cout << "Name : " << curr->right->Name << endl;
                cout << "Age : " << curr->right->Age << endl;
                cout << "Gender : " << curr->right->Gender << endl;
                cout << "Department : " << curr->right->Department << endl;

                cout << "----------------------------------------------------" << endl;

                cout << endl;

                return 1;
            }
            else
            {
                if(curr->right->Name.compare(Name) < 0)
                {
                    curr = curr->right;

                    while(curr->right == NULL)
                    {
                        curr = curr->down;

                        if(curr == NULL) break;
                    }
                }
                else
                {
                    curr = curr->down;
                }
            }

            if(curr == NULL) break;

        }

        return 0;
    }

    void PrintList()
    {
        Node curr = this->head;

        Node temp;

        if(curr == NULL) return;

        while(curr != NULL)
        {
            temp = curr;

            while(temp->right != NULL)
            {
                temp = temp->right;

                cout << temp->Name << ' ';
            }

            curr = curr->down;

            cout << endl;
        }
    }
    
    void free_memory()
    {
        Node curr = this->head;

        Node temp , temp2 , temp3;

        if(curr == NULL) return;

        while(curr != NULL)
        {
            temp = curr;

            while(temp->right != NULL)
            {   
                temp = temp->right;
            }

            while(temp->left != NULL)
            {
                temp2 = temp;

                temp  = temp->left;

                delete temp2;
            }

            temp3 = curr;

            curr = curr->down;

            delete temp3;
        }
    }

    int intro_page()
    {
        cout << endl;

        cout << endl;

        cout << "The elements present in the Tree are : " <<endl;

        cout << endl;

        this->PrintList();

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

    void Deletefrom(Node curr)
    {
        if(curr->left != NULL) curr->left->right = curr->right;

        if(curr->right != NULL) curr->right->left = curr->left;
    }

    bool DeleteByName()
    {
       string Name;

        cout << "Enter the name of the faculty : " ;

        getline(cin , Name);

        Node curr = this->head;

        Node temp;

        while(curr->right != NULL)
        {
            if(curr->right->Name.compare(Name) == 0)
            {
                curr = curr->right;

                while(curr != NULL)
                {
                    temp = curr;

                    Deletefrom(curr);

                    curr = curr->down;

                    delete temp;
                }

                curr = this->head;

                while(curr->right == NULL)
                {
                    if(curr->Age == 1) break;

                    temp = curr;

                    curr = curr->down;

                    delete temp;

                    this->num_levels --;

                    this->head = curr;
                }

                return 1;
            }
            else
            {
                if(curr->right->Name.compare(Name) < 0)
                {
                    curr = curr->right;

                    while(curr->right == NULL)
                    {
                        curr = curr->down;

                        if(curr == NULL) break;
                    }
                }
                else
                {
                    curr = curr->down;
                }
            }
                    if(curr == NULL) break;
        }


        return 0;
    }

};

int main()
{
    Skip_list list;

    int opt;

    while((opt = list.intro_page()))
    {
        switch (opt)
        {
            case 1:
                list.Insert();
                
                cout << endl;

                cout << "----------------------------------------------------" << endl;

                cout << "Element added !" << endl;

                cout << "----------------------------------------------------" << endl;

                cout << endl;
                
                break;

            case 2:                
                bool end;

                end = list.DeleteByName();
                
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

                    cout << "Element is not present in Skip List !" << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << endl;
                    
                }
                
                break;

            case 3:
                if(list.SearchByName() == 0)
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
                   list.free_memory();
                }
                break;

            default:
                break;
        }
        if(opt ==4 ) break;
    }
}