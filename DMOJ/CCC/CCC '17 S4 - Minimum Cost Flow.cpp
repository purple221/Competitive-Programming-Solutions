#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define ll long long
#define ull unsigned long long
#define MAXN 100010
#define INF 0x3f3f3f3f
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) < (b) ? (b) : (a)
#define vi vector<int>
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define f first
#define s second
#define mii map<int, int>
#define umii unordered_map<int, int>
#ifdef DEBUG
    #define D(x...) printf(x)
#else
    #define D(x...)
#endif
using namespace std;

struct Edge {
    int a, b, c;
    bool oldedge;

    inline bool operator < (const Edge &e) const {
        if (c == e.c) return oldedge > e.oldedge;
        return c < e.c;
    }
};

int N, M, D, A, B, C, maxcost, days, cnt;
vector<Edge> edges;

struct Disjoint {
private:
    int N;
    vi lead, rank;

public:
    Disjoint (int N) : N(N), lead(N + 1), rank(N + 1) { }

    inline void make_Set () {
        for (int i=0; i<N; i++) {
            lead[i] = i;
            rank[i] = 0;
        }
    }

    inline int Find (int x) {
        while (lead[x] ^ x) {
            lead[x] = lead[lead[x]];
            x = lead[x];
        }
        return x;
    }

    inline bool Merge (int x, int y) {
        return Find(x) ^ Find(y);
    }

    inline void Union (int x, int y) {
        int a = Find(x), b = Find(y);
        if (Merge(x, y)) {
            if (rank[a] > rank[b]) {
                lead[b] = a;
                rank[a] += rank[b];
            }
            else {
                lead[a] = b;
                rank[b] += rank[a];
            }
        }
    }
};

Disjoint ds(MAXN);

int main (int argc, char const *argv[]) {
    #ifdef NOT_DMOJ
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // NOT_DMOJ
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> M >> D;
    for (int i=1; i<=M; i++) {
        cin >> A >> B >> C;
        if (i <= N - 1) edges.pb((Edge) {A, B, C, 1});
        else edges.pb((Edge) {A, B, C, 0});
    }
    sort(edges.begin(), edges.end());
    ds.make_Set();
    for (size_t i=0; i<edges.size(); i++) {
        Edge &next = edges[i];
        if (ds.Merge(next.a, next.b)) {
            maxcost = next.c;
            if (!next.oldedge) days++;
            ds.Union(next.a, next.b);
        }
    }
    ds.make_Set();
    for (size_t i=0; i<edges.size(); i++) {
        Edge &next = edges[i];
        if (ds.Merge(next.a, next.b)) {
            if (next.c < maxcost || (next.c == maxcost && next.oldedge)) ds.Union(next.a, next.b);
            else if (next.c <= D && next.oldedge) {
                cout << days - 1 << "\n";
                return 0;
            }
        }
    }
    cout << days << "\n";
    return 0;
}

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */