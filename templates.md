### Best-Practice Binary Search Template
```
low =    high =     ans = impossible ans
while(low <= high) {
	int mid = (low + high)/2;
	if(check(mid)) { ans = mid; high = mid - 1; }
	else low = mid + 1;
}
```

### Djikstra's Algorithm (unfinished)

```
```

### Disjoint Sets (Union-Find) without Union-by-Rank (legacy)
```
int find_parent(int a, vector<int> &parent) {
    if (parent[a] == a) {
        return a;
    }
    parent[a] = find_parent(parent[a], parent);
    return parent[a];
}
void union_(int a, int b, vector<int> &parent) {
    int parent_a = find_parent(a, parent);
    int parent_b = find_parent(b, parent);
    if (parent_a != parent_b) {
        parent[parent_a] = parent_b;
    }
}
void create_set(int a, vector<int> &parent) {
    parent[a] = a;
}
```

### Union-by-Rank with Path Compression

```
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
vector<ll> p;
vector<ll> r;

ll fp(int a) {
    return (p[a] == a) ? a : p[a] = fp(p[a]);
}

void union_(int a, int b) {
    int pa = fp(a);
    int pb = fp(b);
    if (pa != pb) {
        if (r[pa] > r[pb]) p[pb] = pa;
        else if (r[pa] < r[pb]) p[pa] = pb;
        else {
            p[pa] = pb;
            r[pb]++;
        }
    }
}

void create(int a) {
    p[a] = a;
    r[a] = 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    p.assign(PLACEHOLDER_SIZE, PLACEHOLDER_VALUE);
    r.assign(PLACEHOLDER_SIZE, PLACEHOLDER_VALUE);
}
```

### Union-by-Rank with DeUnion
This is very verbose, can be re-written much cleaner like Union-Rank w/ Path Compression is written.

```
// must include <stack> and <tuple>

stack<tuple<int, int, bool>> parent_history; // index, previous, rank_change?
stack<pair<int, int>> rank_history; // index, previous
int find_parent(int a, vector<int> &parent) {
    if (parent[a] == a) {
        return a;
    }
    return find_parent(parent[a], parent);
}
void union_(int a, int b, vector<int> &parent, vector<int> &rank) {
    int parent_a = find_parent(a, parent);
    int parent_b = find_parent(b, parent);
    if (parent_a != parent_b) {
        if (rank[parent_a] > rank[parent_b]) {
            parent_history.push({parent_b, parent[parent_b], false});
            parent[parent_b] = parent_a;
        }
        else {
            if (rank[parent_a] == rank[parent_b]) {
                rank[parent_b] += 1;
                parent_history.push({parent_a, parent[parent_a], true});
                rank_history.push({parent_b, rank[parent_b] - 1});
            }
            else {
                parent_history.push({parent_a, parent[parent_a], false});
            }
            parent[parent_a] = parent_b;
        }
    }
    else {
        parent_history.push({-1, -1, false});
    }
}
void create_set(int a, vector<int> &parent, vector<int> &rank) {
    parent[a] = a;
    rank[a] = 0;
}
void de_union(vector<int> &parent, vector<int> &rank) {
    if (parent_history.empty()) return;
    auto prevparent = parent_history.top();
    parent_history.pop();
    if (get<0>(prevparent) == -1) return;
    parent[get<0>(prevparent)] = get<1>(prevparent);
    if (get<2>(prevparent)) {
        auto prevrank = rank_history.top();
        rank_history.pop();
        rank[prevrank.first] = prevrank.second;
    }
}
```

### Kruskal's Algorithm for MST
Again, very verbose but it is the basic structure of Kruskal's.
```
struct Edge {
    int n1, n2, length;
    bool operator<(const Edge& other) const {
        return length < other.length;
    }
};

int find_parent(int a, vector<int> &parent) {
    if (parent[a] == a) {
        return a;
    }
    parent[a] = find_parent(parent[a], parent);
    return parent[a];
}
void union_(int a, int b, vector<int> &parent) {
    int parent_a = find_parent(a, parent);
    int parent_b = find_parent(b, parent);
    if (parent_a != parent_b) {
        parent[parent_a] = parent_b;
    }
}
void create_set(int a, vector<int> &parent) {
    parent[a] = a;
}

vector<Edge> findMST(vector<Edge> edges, vector<int> &parent, int nodes) { // assuming basic structure, the map is mapping the distance, edge a and b. Make sure parent is initialized.
    vector<Edge> mst;
    for (int i = 0; i <= nodes; i++) {
        create_set(i, parent);
    }
    sort(edges.begin(), edges.end());
    int used_edges = 0;
    for (const Edge &edge : edges) {
        if (find_parent(edge.n1, parent) != find_parent(edge.n2, parent)) {
            union_(edge.n1, edge.n2, parent);
            mst.push_back(edge);
            used_edges++;
        }
        if (used_edges == nodes - 1) {
            return mst;
        }
    }
    return mst;
}
```

### Easy Set-up Template
```
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    return 0;
}
```