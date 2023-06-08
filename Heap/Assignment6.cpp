#include <iostream>

#include <cstdlib>

using namespace std ;

bool min (int *arr, int a)
{
    if(arr[2*a] < arr[2*a+1]) return 0;
    else return 1;
}

class Heap 
{
    public :

        int N;

        int num_ele;

        int* arr;

    public :

    Heap()
    {
        cout << endl;

        cout << "Enter the length of the array to be taken : " << endl;

        cin >> this->N;

        cout << endl;

        fflush(stdin);

        this->arr = (int*)calloc((N+1),(sizeof(int)));

        this->arr[0] = 0 ;

        this->num_ele = 0;
    }

    void Printtree()
    {
        int a = 1;

        while(a <= num_ele)
        {
            printf("%d ",arr[a]);

            a++;
        }
    }

    int intro_page ()
    {
        cout << endl;

        cout << endl;

        cout << "The elements present in the Array are : " <<endl;

        cout << endl;

        this->Printtree();

        cout << endl;

        cout << endl;

        cout << "----------------------------------------------------" << endl;


        cout << "What would you like to do ?" << endl;

        cout << "1. Insert an element into the Heap" << endl;

        cout << "2. Delete min element from the Heap" << endl;

        cout << "3. Search min element from the Heap" << endl;

        cout << "4. Exit" << endl;

        cout << "----------------------------------------------------" << endl;

        cout << endl;

        int opt;

        cin >> opt;

        fflush(stdin);

        return opt;
    }

    bool Insert ()
    {
        if(this->num_ele == this->N) return 0;

        this->num_ele++;

        cout << "Enter the age of the faculty : ";

        cin >> this->arr[this->num_ele];

        fflush(stdin);

        int temp,a ;

        if(num_ele != 1)
        {
            if(arr[num_ele] < arr[(int)((num_ele)/2)])
            {
                a = num_ele;

                while(arr[a] < arr[(int)(a/2)])
                {
                    temp = arr[(int)(a/2)];

                    arr[(int)(a/2)] = arr[a];

                    arr[a] = temp;

                    a = (int)(a/2);

                    if(a == 1) break;
                }
            }
        }

        return 1;
    }

    bool SearchMin ()
    {
        if (this->num_ele == 0) return 0;

        cout << "The minimum element in the heap is : ";

        cout << this->arr[1];

        cout << endl;

        return 1;
    }

    void sub_delete_function(int a)
    {
        int temp;

        if(num_ele < 2*a)
        {
            return ;
        }
        else
        {
            if(num_ele == 2*a)
            {
                if(arr[a] > arr[2*a])
                {
                    temp = arr[a];

                    arr[a] = arr[2*a];

                    arr[2*a] = temp;
                }
            }
            else
            {
                bool minimum = min(arr,a);

                if(arr[a] > arr[2*a + minimum])
                {
                    temp = arr[2*a + minimum];

                    arr[2*a + minimum] = arr[a];

                    arr[a] = temp;

                    a =  2*a + minimum ;

                    sub_delete_function(a);
                }
            }
            return ;
        }
    }

    bool DeleteMin ()
    {
        if (num_ele == 0) return 0;

        if(num_ele == 1) {this->num_ele-- ; return 1;}

        if (num_ele != 1)
        {
            int temp ;

            temp  = this->arr[1];

            this->arr[1] = this->arr[num_ele];

            this->arr[num_ele] = temp;

            this->num_ele -- ;

            int a = 1;

            this->sub_delete_function(a);
        }
        return 1;
    }

    void free_memory()
    {
        free(this->arr);
    }
};


int main()
{
    Heap heap;

    int opt;

    while((opt = heap.intro_page()))
    {
        switch (opt)
        {
            case 1:
                bool t;

                t = heap.Insert();
                
                if(t == 1)
                {
                    cout << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << "Element Added !" << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << endl;
                     
                }
                else
                {
                    cout << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << "Heap is full !" << endl;

                    cout << "----------------------------------------------------" << endl;

                     cout << endl;
                    
                }
                
                break;

            case 2:                
                bool f ;

                f = heap.DeleteMin();

                if(f == 0) 
                {
                    cout << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << "No elements in the heap !" << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << endl;
                }
                
                break;

            case 3:
                bool e ;

                e = heap.SearchMin();

                if(e == 0) 
                {
                    cout << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << "No elements in the heap !" << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << endl;
                }
                
                break;   

            case 4:
                {
                   heap.free_memory();
                }
                break;

            default:
                break;
        }
        if(opt ==4 ) break;
    }

}