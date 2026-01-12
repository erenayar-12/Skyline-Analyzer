#include <sstream>
#include <fstream>
#include <iostream>
#include "ModifiedPQueue.h"

using namespace std;

//swap func to be used while sorting
inline void swap(Node &a, Node &b) {
    Node temp = a;
    a = b;
    b = temp;
}

//sorting left,center and right
Node median(Node a[], int left, int right) {
    int mid = (left + right) / 2;
    if(a[mid].x < a[left].x) {
        swap(a[mid], a[left]);
    }
    if(a[right].x < a[left].x) {
        swap(a[left], a[right]);
    }
    if(a[right].x < a[mid].x) {
        swap(a[mid], a[right]);
    }
    swap(a[mid], a[right - 1]);
    return a[right - 1];
}

//to be used at the end of quickSort
void insertionSort(Node a[], int left, int right) {
    for(int i = left + 1; i <= right; i++) {
        Node temp = a[i];
        int j;

        for(j = i; j > left && temp.x < a[j-1].x; j--) {
            a[j] = a[j - 1];
        }
        a[j] = temp;
    }
}

//main sorting algorithm
void quicksort(Node a[], int left, int right) {
    if(left + 10 <= right) {
        Node pivot = median(a, left, right);
        int i = left, j = right;
        for(;;) {
            while(a[++i].x < pivot.x){}
            while(pivot.x < a[--j].x){}
            if(i < j) {
                swap(a[i], a[j]);
            }
            else {
                break;
            }
        }
        swap(a[i], a[right - 1]);

        quicksort(a, left, i - 1);
        quicksort(a, i + 1, right);
    }
    else {
        insertionSort(a , left, right);
    }
}

int main() {
    ifstream input;
    input.open("input.txt");
    if(!input.is_open()) {
        return 0;
    }
    string line;
    int building_count = -1;
    int array_index = 0;
    int building_index = 0;
    getline(input, line);
    stringstream ss_count(line);
    ss_count >> building_count;                                            //number of buildings (first line)
    Node* buildingsArray = new Node[building_count*2];
    while(getline(input, line)) {
        stringstream ss(line);
        int xl, y, xr;
        ss >> xl >> y >> xr;
        if(ss.fail()) {
            continue;
        }
        Node leftSide = Node(xl, y, false, building_index);
        Node rightSide = Node(xr, y, true, building_index);
        buildingsArray[array_index] = leftSide;
        buildingsArray[array_index+1] = rightSide;
        array_index += 2;
        building_index++;
    }
    input.close();
    quicksort(buildingsArray, 0, building_count*2 - 1);
    ModifiedPQueue mpq(building_count);
    int max = mpq.getMax();
    if (building_count > 0 && buildingsArray[0].x > 0) {             //printing height at 0 when there is no building at 0
        cout << "0 0" << endl;
    }
    for(int i = 0; i < building_count*2; i++) {
        if(!buildingsArray[i].side) {
            mpq.insert(buildingsArray[i].y , buildingsArray[i].index);
        }
        else {
            mpq.remove(buildingsArray[i].index);
        }
        if (i != building_count*2 - 1 && buildingsArray[i].x == buildingsArray[i+1].x) {
            continue;
        }
        int new_max = mpq.getMax();
        if(new_max != max) {
            cout << buildingsArray[i].x << " " << new_max << endl;
            max = new_max;
        }
    }
}
