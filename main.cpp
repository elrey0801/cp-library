#include <iostream>
#include "lib/SegmentTree.h"

using namespace std;

int summation(int a, int b) {
    return a + b;
}

int main() {
    #ifdef LOCAL
        freopen("input", "r", stdin);
//        freopen("output.txt", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    vector<int> arr(n, 0);
    for(int i = 0; i < n; ++i)
        cin >> arr[i];
    SegmentTree<int, int(*)(int, int)> segment_tree(n, arr, 0, summation);
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            segment_tree.update(b, c);
            continue;
        }
        cout << segment_tree.query(b, c - 1) << endl;
    }

    return 0;
}
