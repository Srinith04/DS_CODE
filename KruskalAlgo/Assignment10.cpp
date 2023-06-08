#include <iostream>

#include <cstdlib>

#include <string>

using namespace std;


struct input
{
    int V1;

    int V2;

    int edge_length;
};

typedef struct input Input;

bool max (Input *arr, int a)
{
    if(arr[2*a].edge_length > arr[2*a+1].edge_length) return 0;
    else return 1;
}

class  Graph
{
    public :

    int V;

    int E;

    int* parent;

    int* rank;

    Input* arr;

    public :

    Graph()
    {
        cout << "Enter the number of vertices and edges in the graph : "<< endl;

        cin >> this->V;

        cin >> this->E;

        cout << endl;

        cout << endl;

        this->arr = (Input*)calloc(E+1,sizeof(Input));

        this->parent = (int*)calloc(V,sizeof(int));

        this->rank = (int*)calloc(V,sizeof(int));

        for(int i=0;i<V;i++)
        {
            this->parent[i] = i;

            this->rank[i] = 0;
        }

        cout << "Give the input of edges in format /* V1 V2 Edge_length /* :"<< endl;

        for(int i=1;i<=E;i++)
        {
            cin >> arr[i].V1;

            cin >> arr[i].V2;

            cin >> arr[i].edge_length;
        }

        for( int i=(int)(this->E/2) ; i>0 ; i--)
        {
            this->heapify(i,this->E);
        }

        this->Deleting_n_times();
    }



    void min_span_tree()
    {
        int V1;

        int V2;

        int P1;

        int P2;

        int edges = 0;

        int min_weight = 0;

        cout << "The edges in the minimum spanning tree are :" << endl;

        for(int i = 1 ;i <= E; i++)
        {
            V1 = this->arr[i].V1;

            V2 = this->arr[i].V2;

            while(this->parent[V1] != V1 || this->parent[V2] != V2)
            {
                V1 = this->parent[V1];

                V2 = this->parent[V2];
            }

            if(V1 != V2)
            {
                if(this->rank[V1] > this->rank[V2])
                {
                    this->parent[V2] = V1;

                    this->rank[V1]++;
                }
                else
                {
                    this->parent[V1] = V2;

                    this->rank[V2]++;
                }

                edges++;
                
                cout << this->arr[i].V1 << ' ' << this->arr[i].V2 << ' ' << this->arr[i].edge_length << endl;

                min_weight = min_weight + arr[i].edge_length;
            }

            if(edges == this->V-1)
            {
                i = E+1;
            }
        }

        cout << endl;

        cout << endl;

        cout << "The sum of all weight in MST is : " << min_weight << endl;
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
                if(arr[a].edge_length < arr[2*a].edge_length)
                {
                    temp = arr[a].edge_length;

                    arr[a].edge_length = arr[2*a].edge_length;

                    arr[2*a].edge_length = temp;

                    temp = arr[a].V1;

                    arr[a].V1 = arr[2*a].V1;

                    arr[2*a].V1 = temp;

                    temp = arr[a].V2;

                    arr[a].V2 = arr[2*a].V2;

                    arr[2*a].V2 = temp;
                }
            }
            else
            {
                bool maximum = max(arr,a);

                if(arr[a].edge_length < arr[2*a + maximum].edge_length)
                {
                    temp = arr[2*a + maximum].edge_length;

                    arr[2*a + maximum].edge_length = arr[a].edge_length;

                    arr[a].edge_length = temp;

                    temp = arr[2*a + maximum].V1;

                    arr[2*a + maximum].V1 = arr[a].V1;

                    arr[a].V1 = temp;

                    temp = arr[2*a + maximum].V2;

                    arr[2*a + maximum].V2 = arr[a].V2;

                    arr[a].V2 = temp;

                    a =  2*a + maximum ;

                    heapify(a,num_ele);
                }
            }
            return ;
        }
    }

    void Deleting_n_times ()
    {
        int num_ele = this->E;

        int temp ;

        while(num_ele != 0)
        {
            if(num_ele == 1) {num_ele-- ; return ;}

            if (num_ele != 1)
            {
                temp  = this->arr[1].edge_length;

                this->arr[1].edge_length = this->arr[num_ele].edge_length;

                this->arr[num_ele].edge_length = temp;

                temp  = this->arr[1].V1;

                this->arr[1].V1 = this->arr[num_ele].V1;

                this->arr[num_ele].V1 = temp;

                temp  = this->arr[1].V2;

                this->arr[1].V2 = this->arr[num_ele].V2;

                this->arr[num_ele].V2 = temp;

                num_ele -- ;

                int a = 1;

                heapify(a,num_ele);
            }
        }
        return ;
    }

    void free_memory()
    {
        free(this->parent);

        free(this->rank);

        free(this->arr);
    }


};


int main()
{
    Graph G;

    G.min_span_tree();

    G.free_memory();
}