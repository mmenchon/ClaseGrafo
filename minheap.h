#ifndef MINHEAP_H
#define MINHEAP_H
#include <vector>
#include <assert.h>
#include <iostream>
using namespace std;

template < typename T>
class MinHeap
{
private:
    vector<T> heap;

    int parent(int i) {return (i-1)/2;}
    int left(int i) {return 2*i+1;}
    int right(int i){return 2*i+2;}
    void minHeapify(unsigned int i)
    {
        unsigned int l=left(i);
        unsigned int r=right(i);
        unsigned int smallest = i;
        if (l < heap.size() && heap[l] < heap[i])
            smallest = l;
        if (r < heap.size() && heap[r] < heap[smallest])
            smallest = r;
        if (smallest != i)
        {
            T temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            minHeapify(smallest);
        }
    }

public:
    MinHeap(){};
    T extractMin()
    {
        assert(heap.empty() == false);
        if(heap.size()==1){
            heap.pop_back();
            return heap[0];
        }
        T root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        minHeapify(0);
        return root;
    }
    T getMin(){return heap[0];}
    void insert(const T& value)
    {
        heap.push_back(value);
        unsigned int i=heap.size()-1;
        while( i !=0 && heap[parent(i)] > heap[i])
        {
            T temp = heap[parent(i)];
            heap[parent(i)] = heap[i];
            heap[i] = temp;
            i=parent(i);
        }
        //minHeapify(i);
    }
    bool empty() const{return heap.empty();}
    int size() const{return heap.size();}

};

#endif // MINHEAP_H
