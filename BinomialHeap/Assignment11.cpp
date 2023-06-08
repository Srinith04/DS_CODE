#include <iostream>

#include <cstdlib>

#include <string>

using namespace std;

struct b_heap_node
{
    int Age;

    int degree;

    struct b_heap_node* left_most;

    struct b_heap_node* right_sibling;
};

typedef struct b_heap_node* Node;

Node Heap_union(Node,Node);

Node create_b_node()
{
    Node newone = new struct b_heap_node;

    newone->degree = 0;

    newone->left_most = NULL;

    newone->right_sibling = NULL;

    return newone;
}

class B_heap
{
    public:

    Node head;

    public:

    B_heap()
    {
        this->head = NULL;
    }

    bool Insert()
    {
        int t = -1;

        cout << "Enter the age of the faculty : ";

        int Age;

        cin >> Age;

        fflush(stdin);

        Node newone = create_b_node();

        newone->Age = Age;

        this->head = Heap_union(newone , this->head);

        return 1;
    }

    void PrintB_heap(Node head)
    {
        while(head != NULL)
        {
            cout << head->Age << ' ';

            PrintB_heap(head->left_most);

            head = head->right_sibling;
        }
    }

    Node reverse_linked_list(Node head)
    {
        Node curr , curr_before , curr_before_before;

        curr = head;

        curr_before = NULL;

        curr_before_before = NULL;

        while(curr != NULL)
        {
            if(curr == head)
            {
                curr_before_before = NULL;

                curr_before = curr;

                curr = curr->right_sibling;

                curr_before->right_sibling = NULL;
            }
            else
            {
                curr_before_before = curr_before;

                curr_before = curr;

                curr = curr->right_sibling;

                curr_before->right_sibling = curr_before_before;
            }
        }

        return curr_before;
    }

    bool Delete_min()
    {
        Node temp ;

        Node min_pointer = this->head;

        temp = this->head;

        int min_age;

        if(temp != NULL) min_age = temp->Age;

        while(temp != NULL)
        {
            if(min_age > temp->Age)
            {
                min_pointer = temp;

                min_age = temp->Age;
            }
            temp = temp->right_sibling;
        }

        temp = this->head;

        Node temp_before = NULL;

        while(temp != NULL)
        {
            if(temp == min_pointer)
            {
                if(temp_before == NULL)
                {
                    this->head = temp->right_sibling;

                    temp_before = temp->left_most;

                    temp->left_most = NULL;

                    delete temp;

                    this->head = Heap_union(reverse_linked_list(temp_before) , this->head);

                    return 1;
                }
                else
                {
                    temp_before->right_sibling = temp->right_sibling;

                    temp_before = temp->left_most;

                    temp->left_most = NULL;

                    delete temp;

                    this->head = Heap_union(reverse_linked_list(temp_before) , this->head);

                    return 1;
                }
            }
            else
            {
                temp_before = temp;

                temp = temp->right_sibling;
            }
        }

        return 0;
    }

    int intro_page ()
    {
        cout << endl;

        cout << endl;

        cout << "The elements present in the Binomial heap are : " <<endl;

        cout << endl;

        this->PrintB_heap(this->head);

        cout << endl;

        cout << endl;

        cout << "----------------------------------------------------" << endl;


        cout << "What would you like to do ?" << endl;

        cout << "1. Insert an element into the Heap" << endl;

        cout << "2. Delete min element from the Heap" << endl;

        cout << "3. Exit" << endl;

        cout << "----------------------------------------------------" << endl;

        cout << endl;

        int opt;

        cin >> opt;

        fflush(stdin);

        return opt;
    }

    void free_memory(Node head)
    {
        Node child , sibling ;

        while(head != NULL)
        {
            child = head->left_most;

            sibling = head->right_sibling;

            delete head;

            free_memory(child);

            head = sibling;
        }
    }
};

Node Heap_union(Node H1 ,Node H2)
{
    Node head1 = H1;

    Node head2 = H2;

    Node newone = create_b_node();

    Node newhead = newone;

    newhead->Age = -1;

    while(head1 != NULL && head2 != NULL)
    {
        if(head1->degree < head2->degree)
        {
            newhead->right_sibling = head1;

            head1 = head1->right_sibling;
        }
        else
        {
            newhead->right_sibling = head2;

            head2 = head2->right_sibling;
        }

        newhead = newhead->right_sibling;
    }

    while (head1 != NULL)
    {
        newhead->right_sibling = head1;

        head1 = head1->right_sibling;

        newhead = newhead->right_sibling;
    }

    while (head2 != NULL)
    {
        newhead->right_sibling = head2;

        head2 = head2->right_sibling;

        newhead = newhead->right_sibling;
    }

    Node H3;

    H3 = newone->right_sibling;

    if(H3 == NULL)  
    {
        delete newone;
        
        return NULL;
    }

    Node curr_before  = NULL;

    Node curr = newone->right_sibling;

    Node curr_next = curr->right_sibling;

    while(curr_next != NULL)
    {
        if((curr->degree != curr_next->degree) || (curr_next->right_sibling != NULL && curr_next->right_sibling->degree == curr->degree) )
        {
            curr_before = curr;

            curr = curr_next;

            curr_next = curr_next->right_sibling;
        }
        else
        {
            if(curr->Age <= curr_next->Age)
            {
                curr->right_sibling = curr_next->right_sibling;

                curr_next->right_sibling = curr->left_most;

                curr->left_most = curr_next;

                curr->degree++;

                curr_next = curr->right_sibling;
            }
            else
            {
                if(curr_before == NULL)
                {
                    H3 = curr_next;
                }
                else
                {
                    curr_before->right_sibling = curr_next;
                }

                curr->right_sibling = curr_next->left_most;

                curr_next->left_most = curr;

                curr_next->degree++;

                curr = curr_next;

                curr_next = curr->right_sibling;
            }
        }
    }

    delete newone ;
    
    return H3;
}

int main()
{
    B_heap heap;
          
    int opt;

    while((opt = heap.intro_page()))
    {
        switch (opt)
        {
            case 1:
                bool t;

                t = heap.Insert();

                system("clear");
                
                if(t == 1)
                {
                    cout << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << "Element Added !" << endl;

                    cout << "----------------------------------------------------" << endl;

                    cout << endl;
                     
                }
                
                break;

            case 2:               
                bool f ;

                f = heap.Delete_min();
        
                system("clear");

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
                {
                   heap.free_memory(heap.head);
                }
                break;

            default:
                break;
        }
        if(opt ==3 ) break;
    }
}