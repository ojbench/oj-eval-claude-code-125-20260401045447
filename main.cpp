#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Fast I/O
namespace FastIO {
    const int BUF_SIZE = 1 << 20;
    char buf[BUF_SIZE], *p1 = buf, *p2 = buf;

    inline char gc() {
        if (p1 == p2) {
            p2 = (p1 = buf) + fread(buf, 1, BUF_SIZE, stdin);
            if (p1 == p2) return EOF;
        }
        return *p1++;
    }

    inline int readInt() {
        int x = 0;
        char c = gc();
        while (c < '0' || c > '9') c = gc();
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            c = gc();
        }
        return x;
    }
}

using FastIO::readInt;

// Global arrays for Union-Find
vector<int> parent;
vector<int> rankArr;

inline int find(int x) {
    int root = x;
    while (parent[root] != root) {
        root = parent[root];
    }
    // Path compression
    while (parent[x] != root) {
        int next = parent[x];
        parent[x] = root;
        x = next;
    }
    return root;
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
    int t = readInt();

    while (t--) {
        int n = readInt();

        vector<int> ci(n), cj(n), e(n);
        unordered_map<int, int> idMap;
        int idCount = 0;

        // Read all constraints and assign compressed IDs
        for (int k = 0; k < n; k++) {
            int i = readInt();
            int j = readInt();
            int eq = readInt();

            if (idMap.find(i) == idMap.end()) {
                idMap[i] = idCount++;
            }
            if (idMap.find(j) == idMap.end()) {
                idMap[j] = idCount++;
            }

            ci[k] = idMap[i];
            cj[k] = idMap[j];
            e[k] = eq;
        }

        parent.resize(idCount);
        rankArr.assign(idCount, 0);
        for (int i = 0; i < idCount; i++) {
            parent[i] = i;
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
