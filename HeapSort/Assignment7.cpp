#include <iostream>

#include <cstdlib>

using namespace std ;


bool max (int *arr, int a)
{
    if(arr[2*a] > arr[2*a+1]) return 0;
    else return 1;
}

class Heap_Sort
{
    public :

        int N;

        int* arr;

    public :

    Heap_Sort()
    {
        cout << endl;

        cout << "Enter the length of the array to be taken : " << endl;

        cin >> this->N;

        cout << endl;

        fflush(stdin);

        this->arr = (int*)calloc((N+1),(sizeof(int)));  /* arr[0] is not used , stored from arr[1] */

        this->arr[0] = 0 ;
    }

    void Printtree()
    {
        cout << endl;

        cout << "----------------------------------------------------" << endl;

        cout << "The sorted array of ages of faculty is : ";

        int a = 1;

        while(a <= N)
        {
            printf("%d ",arr[a]);

            a++;
        }

        cout << endl;

        cout << "----------------------------------------------------" << endl;
    }

    void heapify(int a,int num_ele)
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
                if(arr[a] < arr[2*a])
                {
                    temp = arr[a];

                    arr[a] = arr[2*a];

                    arr[2*a] = temp;
                }
            }
            else
            {
                bool maximum = max(arr,a);

                if(arr[a] < arr[2*a + maximum])
                {
                    temp = arr[2*a + maximum];

                    arr[2*a + maximum] = arr[a];

                    arr[a] = temp;

                    a =  2*a + maximum ;

                    heapify(a,num_ele);
                }
            }
            return ;
        }
    }

    void Deleting_n_times ()
    {
        int num_ele = N;

        int temp ;

        while(num_ele != 0)
        {
            if(num_ele == 1) {num_ele-- ; return ;}

            if (num_ele != 1)
            {
                temp  = this->arr[1];

                this->arr[1] = this->arr[num_ele];

                this->arr[num_ele] = temp;

                num_ele -- ;

                int a = 1;

                heapify(a,num_ele);
            }
        }
        return ;
    }

    void free_memory()
    {
        free(this->arr);
    }
};


int main()
{
    Heap_Sort heap;

    cout << endl;

    cout << "----------------------------------------------------" << endl;

    cout << "Enter the array of ages of faculty ( RMK : Only the first " << heap.N <<" will be taken ) : ";

    for(int i=1;i<=heap.N;i++)
    {
        cin >> heap.arr[i];
    }

    // Converting random array to a max heap

    for( int i=(int)(heap.N/2) ; i>0 ; i--)
    {
        heap.heapify(i,heap.N);
    }

    heap.Deleting_n_times();

    heap.Printtree();

    heap.free_memory();

}