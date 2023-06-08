#include <iostream>

#include <cstdlib>

#include <string>

using namespace std;

struct list_node
{
    string Name;

    int Age;

    string Gender;

    string Department;

    struct list_node* next;
};

typedef struct list_node* Node;

class Linkedlist
{
    public:

    Node head;

    public:

    Linkedlist()
    {
        this->head = NULL;
    }

    void PrintLinkedList()
    {
        cout << "Name" << " | ";
        cout << "Age" << " | ";
        cout << "Gender" << " | ";
        cout << "Department" << endl;

        Node curr = this->head;

        if(curr != NULL)
        {
            while(curr->next != NULL)
            {
                cout << curr->Name << " | ";
                cout << curr->Age << " | ";
                cout << curr->Gender << " | ";
                cout << curr->Department << endl;
                
                curr = curr->next;  
            }
            cout << curr->Name << " | ";
            cout << curr->Age << " | ";
            cout << curr->Gender << " | ";
            cout << curr->Department << endl;
        }
    }

    int intro_page()
    {
        cout << endl;

        cout << endl;

        cout << "The elements present in the linked list are " << endl;

        this->PrintLinkedList();

        cout << endl;

        cout << endl;

        cout << "----------------------------------------------------" << endl;


        cout << "What would you like to do ?" << endl;

        cout << "1. Insert an element into the linked list" << endl;

        cout << "2. Delete an element from the linked list by name" << endl;

        cout << "3. Search an element from the linked list by name" << endl;

        cout << "4. Exit" << endl;

        cout << "----------------------------------------------------" << endl;

        cout << endl;


        int opt;

        cin >> opt;

        fflush(stdin);

        return opt;
    }

    void Insert()
    {
        Node newone = new struct list_node;

        cout << "Enter the name of the faculty : ";

        string temp;

        getline(cin,temp);

        newone->Name = temp;

        cout << "Enter the age of the faculty : ";

        int t;

        cin >> t;

        fflush(stdin);

        newone->Age = t;

        cout << "Enter the gender of the faculty : ";

        getline(cin,temp);

        newone->Gender = temp;

        cout << "Enter the department of the faculty : ";

        getline(cin,temp);

        newone->Department = temp;

        newone->next = this->head;

        this->head = newone;

        return;
    }

    bool DeleteByName()
    {
        string Name;

        cout << "Enter the name of the faculty : " ;

        getline(cin , Name);

        Node curr = this->head;

        Node curr2 = NULL;

        bool t = 0;

        if(curr != NULL)
        {
            while(curr ->next != NULL)
            {
                if(Name.compare(curr->Name) != 0)
                {
                    curr2 = curr;

                    curr = curr->next;

                    t = 1;
                }
                else
                {
                    if(t == 0)
                    {
                        this->head = curr->next;

                        delete curr;

                        return 1;
                    }
                    else
                    {
                        curr2->next = curr->next;

                        delete curr;

                        return 1;
                    }
                }
            }
            
            if(Name.compare(curr->Name) == 0)
            {
                if(t == 0)
                {
                    delete curr;

                    this->head = NULL;

                    return 1;
                }
                else
                {
                    curr2->next = NULL;

                    delete curr;

                    return 1;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    bool SearchByName()
    {
        string Name;

        cout << "Enter the name of the faculty : " ;

        getline(cin , Name);

        Node curr  = this->head;

        if(curr != NULL)
        {
            while(curr->next != NULL)
            {
                if (Name.compare(curr->Name) != 0)
                {
                    curr=curr->next;
                }
                else
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
            }
            if(Name.compare(curr->Name) == 0)
            {
                cout << "The details of the faculty are :" << endl;
                cout << "Name : " << curr->Name << endl;
                cout << "Age : " << curr->Age << endl;
                cout << "Gender : " << curr->Gender << endl;
                cout << "Department : " << curr->Department << endl;
                return 1;
            }
        }
        return 0;

    }
};

int main()
{
    Linkedlist List;

    int opt;

    while((opt = List.intro_page()))
    {
        switch (opt)
        {
            case 1:
                List.Insert();
                
                cout << endl;

                // cout << "----------------------------------------------------" << endl;

                // cout << "Element added !" << endl;

                // cout << "----------------------------------------------------" << endl;

                // cout << endl;
                
                break;

            case 2:
                bool end;

                end = List.DeleteByName();
                
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

                    cout << "Element is not present in Linked List !" << endl;

                    cout << "----------------------------------------------------" << endl;

                     cout << endl;
                    
                }
                
                break;

            case 3:
            
                if(List.SearchByName() == 0)
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
                    Node curr = List.head;

                    Node curr2 = NULL;

                    if(curr != NULL)
                    {
                        while(curr->next != NULL)
                        {
                            curr2 = curr;

                            curr = curr->next;

                            delete curr2;
                        }

                        delete curr;
                    }
                }
                break;

            default:
                break;
        }
        if(opt == 4) break;
    }
}
