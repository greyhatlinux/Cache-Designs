#include<bits/stdc++.h>
using namespace std;

class LRU
{
    //size -> current queue size
    //capacity -> max size possisble
    int size, capacity;

    //we use dequeue, because it provides iterator to iterate over the queue;
    deque<char> q;

    public:
    
    LRU(int n) {
        size = 0;
        capacity = n;
    }

    void get(char x){
        bool found = false;
        for(auto it = q.begin(); it != q.end(); it++) {
            //if the value exists, we set found as true
            if(*it == x) found = true;
        }

        //if value is in the cache
        if(found) {
            //no change in size of the cache

            //temp stack to store all values, but k
            stack<char> temp_stack;
            for(auto k : q) {
                if ( k != x) temp_stack.push(k);
            }

            //clearing the entire dequeue
            q.clear();

            //re-filling the cache 
            while(!temp_stack.empty()) {
                q.push_front(temp_stack.top());
                temp_stack.pop();
            }

            //putting the found value at the top
            q.push_front(x);
        }
        
        //if value is not in the cache
        //we remove Least Recently used value from back, and push the new value to front
        else {
            if(size < capacity) q.push_front(x), size++;
            else {
                q.pop_back();
                q.push_front(x);
            }
        }
    }

    void view() {
        cout<<"Cache size : "<<size<<" Cache cc :"<<capacity<<" \n";
        cout<<"Cache contents : \n";
        for(auto it = q.begin(); it != q.end(); it++) {
            cout<<*it<<endl;
        }
    }
    
};

int main()
{
    int n;
    // cin>>n;

    n = 4;

    LRU cache(n);
    cache.get('A');
    cache.get('B');
    cache.get('C');
    cache.get('B');
    cache.get('D');
    cache.get('E');
    cache.get('C');
    cache.get('D');
    cache.get('D');
    cache.get('B');
    
    cache.view();

    return 0;
}
