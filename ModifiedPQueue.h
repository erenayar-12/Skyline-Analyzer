#ifndef MODIFIEDPQUEUE_H
#define MODIFIEDPQUEUE_H
#include <vector>
using namespace std;


struct Node {
    int x;
    int y;
    bool side;     // 0/false -> left, 1/true ->right
    int index;     // order of input

    Node(int x, int y, bool side, int index) {  this->x = x; this->y = y; this->side = side; this->index = index; };
    Node() : x(0), y(0), side(false), index(0) {};
};

struct HeapNode {
    int y;
    int index;

    HeapNode(int _y, int _index) : y(_y), index(_index) {};
    HeapNode() : y(0), index(-1) {};
};

class ModifiedPQueue {
    public:

    explicit ModifiedPQueue(int max_elements);
    ~ModifiedPQueue();
    void insert(int value, int index);
    void remove(int label);
    int getMax();
    bool isEmpty();

    private:

    vector<HeapNode> heap;      // stores ongoing building infos.
    vector<int> location;       // i th entry stores the i th input's heap address
    void percolateUp(HeapNode node_in_heap);
    void percolateDown(HeapNode node_in_heap);

};

#endif
