#include<bits/stdc++.h>
using namespace std;

class LRU
{
    public:

    //storing maximum cache capacity
    int maxCapa;

    class node {
        public :
        int key;
        int value;
        node *next;
        node *prev;

        //node constructor
        node(int k, int val){
            key = k;
            value = val;
        }

    };

    node *head = new node(-1, -1);
    node *tail = new node(-1, -1);
    map<int, node*> mp;

    //constructor to initialise the LRU
    LRU(int cc) {
        maxCapa = cc;
        head->next = tail;
        tail->prev = head;
    }

    //function to add a new node, this node addition is always at the beginning
    //since cache stires the most frequently used values
    void addnode(node *newNode){
        node *temp = head->next;
        newNode->next = head->next;
        newNode->prev = head;
        temp->prev = newNode;
        head->next = newNode;
    }

    //function to delete any node, whose location is found from the map
    void deletenode(node *oldNode){
        node *tempnext = oldNode->next;
        node *tempprev = oldNode->prev;
        tempnext->prev = tempprev;
        tempprev->next = tempnext;

    }

    //fetching from cache
    int cacheGet(int k){
        if(mp.find(k) == mp.end()){
            cout<<"No value for this key!\n";
            return -1;
        }

        else {
            node *temp = mp[k];
            deletenode(temp);
            addnode(temp);
            mp.erase(k);
            mp[k] = head->next;
            cout<<"Value for "<<k<<" is : "<<mp[k]->value<<"\n";
            return mp[k]->value;
        }
    }

    //setting key:value in cache
    void cacheSet(int k, int val){
        cout<<"Setting "<<k<<" : "<<val<<"\n";

        //setting a previosuly stored key:val
        if(mp.find(k) != mp.end()){
            node *same = mp[k];
            mp.erase(k);
            deletenode(same);
        }

        //if cache is full, delete the least used value (stored at the last)
        if(mp.size() == maxCapa){
            mp.erase(tail->prev->key);
            deletenode(tail->prev);
        }

        addnode(new node(k, val));
        mp[k] = head->next;
    }

    void viewCache(){
        node *temp = head;
        while(temp){
            cout<<temp->value<<" ";
            temp = temp->next;
        }
    }

};

int main()
{
    cout<<"testing LRU implementation\n";

    //initialising the cache with maxCache capacity as 3
    LRU *mem = new LRU(3);

    mem->cacheSet(1,10);
    mem->cacheSet(2,20);
    mem->cacheSet(3,30);
    mem->cacheSet(4,40);
    mem->cacheSet(5,50);

    mem->viewCache();

    mem->cacheGet(4);
    mem->cacheGet(2);
    mem->cacheGet(5);
    mem->cacheGet(4);
    mem->cacheGet(4);
    mem->cacheGet(3);

    mem->viewCache();


    return 0;
    
}

// with this cache implementation
//Get and Set is done in O(1) time, in the fastest time possible.
