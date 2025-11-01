#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

template<typename T, typename MergeFunc>
class SegmentTree {
    int size;
    std::vector<T> *tree;
    MergeFunc merge;
    int originalSize;
    T emptySlotValue;

public:
    SegmentTree(int n, std::vector<T> data, T emptySlotValue, MergeFunc merge) {
        this->originalSize = n;
        this->emptySlotValue = emptySlotValue;
        int logSize = static_cast<int>(log2(n));
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
        if (this->size > 1)
            this->tree->at(0) = this->merge(this->tree->at(1), this->tree->at(2));
    }

    ~SegmentTree() {
        delete this->tree;
    }

    static int parent(int index) {
        return (index - 1) / 2;
    }
    static int leftChild(int index) {
        return 2 * index + 1;
    }
    static int rightChild(int index) {
        return 2 * index + 2;
    }
    T getElement(int index) {
        return this->tree->at(index + this->size / 2);
    }
    void print() {
        for (int i = 0; i < this->originalSize * 2; ++i)
            std::cout << this->tree->at(i) << " ";
        std::cout << std::endl;
    }

    void update(int index, T value) {
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
        T result = this->emptySlotValue;
        while (left < right) {
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

        return left == right ? this->merge(result, this->tree->at(left)) : result;
    }
};

using namespace std;

unsigned long long getMin(unsigned long long a, unsigned long long b) {
    return a < b ? a : b;
}

pair<int, int> getMinWithEqual(pair<int, int> a, pair<int, int> b) {
    pair<int, int> res;
    if(a.first == b.first)
        return
}


int main() {
    #ifdef LOCAL
        freopen("input", "r", stdin);
        freopen("output", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    vector<unsigned long long> arr(n, 0);
    for(int i = 0; i < n; ++i)
        cin >> arr[i];
    SegmentTree<unsigned long long, unsigned long long(*)(unsigned long long, unsigned long long)> segment_tree(n, arr, INT_MAX, getMin);
    for(int i = 0; i < m; ++i) {
        unsigned long long a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            segment_tree.update(b, c);
            continue;
        }
        cout << segment_tree.query(b, c - 1) << " " << segment_tree.getEquals() << endl;
    }

    return 0;
}
