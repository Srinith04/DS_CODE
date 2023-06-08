#include <iostream>

#include <cstdlib>

#include <stdlib.h>

using namespace std;

class Queue_arr
{
    public :

    int length;

    int elements;

    int first;

    int end;

    int* arr;

    public:

    Queue_arr()
    {
        cout << "Enter the length of the array : " ;
        
        cin >> this->length ;
    }

    void arrdeclare(int* arr)
    {
        this->arr = arr;
    }

    bool insertintoqueue(int value)
    {
        if(elements < length)
        {
            if(end < length-1)
            {
                if(elements == 0)
                {
                    first ++;
                }
                end++;
                this->arr[this->end] = value  ;
                elements++;
                return 1;
            }
            else
            {
                end=0;
                this->arr[this->end] = value;
                elements++;
                return 1;
            }
        }
        else
        {
            cout << "Queue is full can't add value" << endl;
            
            return 0;
        }

        
    }

    void printqueue()
    {
        int i = this->first ;

        for(int j=0;j<elements;j++)
        {
            if(i>=length)
            {
                i = i-length;
            }
            if(i<length)
            {
                cout << this->arr[i] << ' ';
            }
            i++;
        }
    }

    bool deletefromqueue()
    {
        if(elements != 0)
        {
            if(elements != 1)
            {
                first++;
                elements--;
            }
            else
            {
                first = -1;
                end = -1;
                elements--;
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int intro_page()
    {
        cout << endl;

        cout << endl;

        cout << "The elements present in the queue are : ";

        this->printqueue();

        cout << endl;

        cout << endl;

        cout << "----------------------------------------------------" << endl;

        cout << "What would you like to do ?" << endl;

        cout << "1. Insert an element to the Queue" << endl;

        cout << "2. Delete an element from the Queue" << endl;

        cout << "3. Exit" << endl;

        cout << "----------------------------------------------------" << endl;

        cout << endl;


        int opt;

        cin >> opt;

        return opt;
    }

};

int main()
{
    Queue_arr List;

    int arr[List.length];

    List.arrdeclare(arr);

    List.first = -1;

    List.end = -1; 

    List.elements = 0;

    int opt;

    while((opt = List.intro_page()))
    {
        switch (opt)
        {
            case 1:
                
                cout << "Enter the value : ";

                int value;

                cin >> value ;
                value = List.insertintoqueue(value);
                
                if(value == 1)
                {
                    cout << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << "Element added !" << endl;

                    cout << "----------------------------------------------------" << endl;

                     cout << endl;
                }
                
                
                break;

            case 2:
                
                int end;
                end = List.deletefromqueue();
                
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

                    cout << "No elements in queue !" << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << endl;
                    
                }
                
                break;

            case 3:
                break;

            default:
                break;
        }
        if(opt == 3) break;
    }

    
}