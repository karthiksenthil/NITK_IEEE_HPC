//Huffman Codes

#include<stdio.h>
#include<iostream>
#include<vector>

//One heap for the final tree. each node has data and freq.
using namespace std;

struct node
{
    char data;
    int freq;
    node*left, *right;
};

struct PQ
{
    int size;
    node** arr;
};

struct node* createnode(char data, int freq)
{
    node* temp;
    temp->left=temp->right=NULL;
    temp->data=data;
    temp->freq=freq;
    return temp;
}

struct PQ* createPQ()
{
    PQ* newPQ;
    newPQ->size=0;

    return newPQ;
}

void swap(node** a, node** b)
{
    node* temp = *a;
    *a = *b;
    *b = temp;
}

void minheapify(PQ* newPQ, int i)
{
    int smallest = i;
    int left = 2*i+1;
    int right = 2*i + 2;

    if(left<newPQ->size && newPQ->arr[left]->freq<newPQ->arr[smallest]->freq)
        smallest = left;
    if(right<newPQ->size && newPQ->arr[right]->freq<newPQ->arr[smallest]->freq)
        smallest=right;

    if(smallest!=i)
    {
        swap(&newPQ->arr[smallest], &newPQ->arr[i]);
        minheapify(newPQ, smallest);
    }
}

node* extractmin(PQ* newPQ)
{
    node* temp = newPQ->arr[0];
    newPQ->arr[0] = newPQ->arr[newPQ->size - 1];
    newPQ->size--;
    minheapify(newPQ, 0);
    return temp;
}

void insertnode(PQ* newPQ, node* newnode)
{
    newPQ->size++;
    int i = newPQ->size - 1;

    while(i && newnode->freq < newPQ->arr[(i-1)/2]->freq)
    {
        newPQ->arr[i]=newPQ->arr[(i-1)/2];
        i = (i-1)/2;
    }
    newPQ->arr[i] = newnode;
}

void buildminheap(PQ* newPQ)
{
    int n = newPQ->size-1;

    int i = (n-1)/2;

    while(i>=0)
    {
        minheapify(newPQ, i);
        i--;
    }
}

void printArr(int arr[], int n)
{
    for(int i=0; i<n; i++)
        cout<<arr[i];
    cout<<endl;
}

PQ* createBuildMinHeap(char data[], int freq[], int size)
{
    PQ* newPQ = createPQ();
    for(int i=0; i<size; i++)
        newPQ->arr[i]=createnode(data[i], freq[i]);

    newPQ->size=size;

    buildminheap(newPQ);
    return newPQ;
}

node* buildHT(char data[], int freq[], int size)
{
    node *left, *right, *top;

    PQ *newPQ = createBuildMinHeap(data, freq, size);

    while(newPQ->size>1)
    {
        left = extractmin(newPQ);
        right = extractmin(newPQ);

        top = createnode('$', left->freq + right->freq);
        top -> left = left;
        top->right = right;

        insertnode(newPQ, top);
    }

    return extractmin(newPQ);
}
int isLeaf(struct node* root)
{
    return !(root->left) && !(root->right) ;
}
void printcodes(node* root, int arr[], int top)
{
    if(root->left)
    {
        arr[top]=0;
        printcodes(root->left, arr, top+1);
    }
    if(root->right)
    {
        arr[top]=1;
        printcodes(root->right, arr, top+1);
    }

    if(isLeaf(root))
    {
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}
void Huffman(char data[], int freq[], int size)
{
    node* root = buildHT(data, freq, size);

    int arr[1000];
    int top=0;
    printcodes(root, arr, top);
}
int main()
{
    int n;
    char data[1000];
    int freq[1000];
    cout<<"enter number of characters : ";
    cin>>n;
    cout<<"Enter characters and frequencies\n";
    for(int i=0;i<n; i++)
        cin>>data[i]>>freq[i];

    Huffman(data, freq, n);
    return 0;

}
