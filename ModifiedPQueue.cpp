#include "ModifiedPQueue.h"

ModifiedPQueue::ModifiedPQueue(int max_elements) {
    heap.reserve(max_elements);
    location.assign(max_elements, -1);   //initializing the vector
};

ModifiedPQueue::~ModifiedPQueue() {};         //default destructor


void ModifiedPQueue::insert(int value, int index) {
    if(location[index] != -1) {               // if already exists
        return;
    }
    HeapNode temp = HeapNode(value, index);
    heap.push_back(temp);
    location[index] = heap.size() - 1;        //last cell in the heap
    percolateUp(temp);
};

void ModifiedPQueue::remove(int index) {
    if(location[index] == -1) {               //if not found
        return;
    }
    int pos = location[index];
    int last = heap.size() - 1;
    HeapNode temp = heap[pos];
    heap[pos] = heap[last];
    heap[last] = temp;
    location[heap[pos].index] = pos;
    location[heap[last].index] = last;
    location[index] = -1;
    heap.pop_back();
    if (pos < heap.size()) {
        percolateUp(heap[pos]);
        percolateDown(heap[pos]);
    }
};

int ModifiedPQueue::getMax() {
    if (heap.empty()) {                       // when there is no building, height is 0
        return 0;
    }
    return heap[0].y;                         // root is the max height
};

bool ModifiedPQueue::isEmpty() {
    return heap.empty();
};

void ModifiedPQueue::percolateDown(HeapNode node_in_heap) {
    int index = location[node_in_heap.index];
    int size = heap.size();
    while (true) {                             // until break, move the node down
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;
        if (left < size && heap[left].y > heap[largest].y) {
            largest = left;
        }
        if (right < size && heap[right].y > heap[largest].y) {
            largest = right;
        }
        if (largest != index) {
            HeapNode temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;
            location[heap[index].index] = index;
            location[heap[largest].index] = largest;
            index = largest;
        }
        else {
            break;
        }
    }
}

void ModifiedPQueue::percolateUp(HeapNode node_in_heap) {
    int pos = location[node_in_heap.index];
    while (pos > 0) {                         //until break or until reaching the root, move the node up
        int parent = (pos - 1) / 2;
        if (heap[pos].y > heap[parent].y) {
            HeapNode temp = heap[pos];
            heap[pos] = heap[parent];
            heap[parent] = temp;
            location[heap[pos].index] = pos;
            location[heap[parent].index] = parent;
            pos = parent;
        }
        else {
            break;
        }
    }
}



