#include <iostream>
#include "lib/SegmentTree.h"


int summation(int a, int b) {
    return a + b;
}

int main() {
    int arr[7] = {50, 30, 20, 15, 10, 8, 16};
    SegmentTree<int, int(*)(int, int)> segment_tree(7, arr, 0, summation);
    segment_tree.print();
    segment_tree.update(2, 25);
    segment_tree.print();
    std::cout << segment_tree.query(0, 6);
    return 0;
}
