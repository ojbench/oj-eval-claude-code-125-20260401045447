#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

// Global arrays for Union-Find to avoid repeated allocation
vector<int> parent;
vector<int> rankArr;

inline int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

inline void unite(int x, int y) {
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

        vector<int> ci(n), cj(n), e(n);
        vector<int> ids;
        ids.reserve(2 * n);

        // Read all constraints and collect IDs
        for (int k = 0; k < n; k++) {
            int i, j, eq;
            scanf("%d %d %d", &i, &j, &eq);
            ci[k] = i;
            cj[k] = j;
            e[k] = eq;
            ids.push_back(i);
            ids.push_back(j);
        }

        // Coordinate compression
        sort(ids.begin(), ids.end());
        ids.erase(unique(ids.begin(), ids.end()), ids.end());

        int idCount = ids.size();
        parent.resize(idCount);
        rankArr.assign(idCount, 0);
        for (int i = 0; i < idCount; i++) {
            parent[i] = i;
        }

        // Map constraints to compressed IDs
        for (int k = 0; k < n; k++) {
            ci[k] = lower_bound(ids.begin(), ids.end(), ci[k]) - ids.begin();
            cj[k] = lower_bound(ids.begin(), ids.end(), cj[k]) - ids.begin();
        }

        // Process all equality constraints first
        for (int k = 0; k < n; k++) {
            if (e[k] == 1) {
                unite(ci[k], cj[k]);
            }
        }

        // Check inequality constraints
        bool satisfied = true;
        for (int k = 0; k < n; k++) {
            if (e[k] == 0) {
                if (find(ci[k]) == find(cj[k])) {
                    satisfied = false;
                    break;
                }
            }
        }

        printf("%s\n", satisfied ? "YES" : "NO");
    }

    return 0;
}
