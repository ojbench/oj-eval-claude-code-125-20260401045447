#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class UnionFind {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;

public:
    void init(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
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
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    void clear() {
        parent.clear();
        rank.clear();
    }
};

struct Constraint {
    int i, j, e;
};

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        vector<Constraint> constraints(n);
        vector<Constraint> equalities, inequalities;

        UnionFind uf;

        // Read all constraints
        for (int k = 0; k < n; k++) {
            scanf("%d %d %d", &constraints[k].i, &constraints[k].j, &constraints[k].e);
            uf.init(constraints[k].i);
            uf.init(constraints[k].j);

            if (constraints[k].e == 1) {
                equalities.push_back(constraints[k]);
            } else {
                inequalities.push_back(constraints[k]);
            }
        }

        // Process all equality constraints first
        for (const auto& c : equalities) {
            uf.unite(c.i, c.j);
        }

        // Check inequality constraints
        bool satisfied = true;
        for (const auto& c : inequalities) {
            if (uf.find(c.i) == uf.find(c.j)) {
                satisfied = false;
                break;
            }
        }

        printf("%s\n", satisfied ? "YES" : "NO");

        uf.clear();
    }

    return 0;
}
