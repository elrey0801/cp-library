//
// Created by Admin on 29/10/2025.
//

#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H
#include <cmath>
#include <iostream>

#endif //SEGMENTTREE_H

#include <vector>
#include <utility>

/*
    Construct a simple Segment Tree given a merge function and the emptySlotValue:
    For example:
    Constructing a min Segment Tree:

    int getMix(int a, int b) {
        return a < b ? a : b;
    }
    SegmentTree<int, int(*)(int, int)> segment_tree(n, arr, INT_MAX, getMix);
*/

template<typename T, typename MergeFunc>
class SegmentTree {
    int size;
    std::vector<T> *tree;
    MergeFunc merge;
    int originalSize;
    T emptySlotValue;

public:
    SegmentTree(int n, T *data, T emptySlotValue, MergeFunc merge) {
        this->originalSize = n;
        this->emptySlotValue = emptySlotValue;
        int logSize = static_cast<int>(std::log2(n));
        if (pow(2, logSize) == n)
            this->size = 2 * n - 1;
        else
            this->size = static_cast<int>(pow(2, logSize + 2)) - 1;

        this->merge = merge;
        this->tree = new std::vector<T>(this->size, emptySlotValue);

        // first segment
        for (int i = 0; i < n; ++i)
            this->tree->at(i + this->size / 2) = data[i];

        // for remaining segments
        int segmentIndex = this->size / 4;
        while (segmentIndex) {
            for (int i = segmentIndex; i <= segmentIndex * 2; ++i) {
                // T leftChild = leftChild(i), rightChild = rightChild(i);
                this->tree->at(i) = this->merge(this->tree->at(leftChild(i)), this->tree->at(rightChild(i)));
            }
            segmentIndex /= 2;
        }
        this->tree->at(0) = this->merge(this->tree->at(1), this->tree->at(2));
    }

    ~SegmentTree() {
        delete this->tree;
    }

    static T parent(int index) {
        return (index - 1) / 2;
    }
    static T leftChild(int index) {
        return 2 * index + 1;
    }
    static T rightChild(int index) {
        return 2 * index + 2;
    }
    void print() {
        for (int i = 0; i < this->originalSize * 2; ++i)
            std::cout << this->tree->at(i) << " ";
        std::cout << std::endl;
    }

    void update(int index, int value) {
        index += this->size / 2;
        this->tree->at(index) = value;

        while (index) {
            int parentIndex = parent(index);
            T newParentValue = this->merge(this->tree->at(leftChild(parentIndex)), this->tree->at(rightChild(parentIndex)));
            if (newParentValue == this->tree->at(parentIndex))
                return;
            this->tree->at(parentIndex) = newParentValue;
            index = parentIndex;
        }
    }
    T query(int from, int to) {
        if (from > to)
            throw std::runtime_error("From cannot be larger than to");
        if(from < 0 || to >= this->originalSize)
            throw std::out_of_range("Out of range query");

        int left = from + this->size / 2;
        int right = to + this->size / 2;
        int result = this->emptySlotValue;
        while (left != right) {
            if (left % 2 == 0) {
                result = this->merge(result, this->tree->at(left));
                left++;
            }
            if (right % 2 == 1) {
                result = this->merge(result, this->tree->at(right));
                right--;
            }
            left = parent(left);
            right = parent(right);
        }

        return this->merge(result, this->tree->at(left));
    }
};