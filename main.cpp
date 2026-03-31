#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Constraint {
    int i, j, e;
};

// Global arrays for Union-Find to avoid repeated allocation
vector<int> parent;
vector<int> rankArr;

void init(int size) {
    parent.resize(size);
    rankArr.resize(size);
    for (int i = 0; i < size; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return;

    // Union by rank
    if (rankArr[rootX] < rankArr[rootY]) {
        parent[rootX] = rootY;
    } else if (rankArr[rootX] > rankArr[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rankArr[rootX]++;
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        vector<Constraint> constraints(n);
        vector<int> ids;

        // Read all constraints and collect unique IDs
        for (int k = 0; k < n; k++) {
            scanf("%d %d %d", &constraints[k].i, &constraints[k].j, &constraints[k].e);
            ids.push_back(constraints[k].i);
            ids.push_back(constraints[k].j);
        }

        // Coordinate compression
        sort(ids.begin(), ids.end());
        ids.erase(unique(ids.begin(), ids.end()), ids.end());

        int idCount = ids.size();
        init(idCount);

        // Create mapping from original IDs to compressed IDs
        // Use binary search for mapping
        for (int k = 0; k < n; k++) {
            int ci = lower_bound(ids.begin(), ids.end(), constraints[k].i) - ids.begin();
            int cj = lower_bound(ids.begin(), ids.end(), constraints[k].j) - ids.begin();

            if (constraints[k].e == 1) {
                unite(ci, cj);
            }
        }

        // Check inequality constraints
        bool satisfied = true;
        for (int k = 0; k < n; k++) {
            if (constraints[k].e == 0) {
                int ci = lower_bound(ids.begin(), ids.end(), constraints[k].i) - ids.begin();
                int cj = lower_bound(ids.begin(), ids.end(), constraints[k].j) - ids.begin();

                if (find(ci) == find(cj)) {
                    satisfied = false;
                    break;
                }
            }
        }

        printf("%s\n", satisfied ? "YES" : "NO");
    }

    return 0;
}
