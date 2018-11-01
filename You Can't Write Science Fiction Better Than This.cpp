#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define ll long long
#define ull unsigned long long
#define MAXN 1010
#define INF 0x3f3f3f3f
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) < (b) ? (b) : (a)
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define f first
#define s second
#define mii map<int, int>
#define umii unordered_map<int, int>
#define DEBUG 1
#ifdef DEBUG
	#define D(x...) printf(x)
#else
	#define D(x...)
#endif
using namespace std;

int N, M, A, B, V1, V2;
bool vis[MAXN];
int dist[MAXN];
queue<int> q;
vi adj[MAXN];

inline int BFS (int src, int dest) {
	memset(vis, 0, sizeof(vis));
	memset(dist, INF, sizeof(dist));
	dist[src] = 0;
	vis[src] = 1;
	q.push(src);
	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		for (size_t i=0; i<adj[curr].size(); i++) {
			int &next = adj[curr][i];
			if (!vis[next]) {
				vis[next] = 1;
				dist[next] = dist[curr] + 1;
				q.push(next);
			}
		}
	}
	return dist[dest];
}

int main (int argc, char const *argv[]) {
	#ifdef NOT_DMOJ
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif // NOT_DMOJ
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> A >> B;
	for (int i=0; i<M; i++) {
		cin >> V1 >> V2;
		adj[V1].pb(V2);
		adj[V2].pb(V1);
	}
	int ans1 = BFS(1, A), ans2 = BFS(A, B);
	if (!vis[B]) {
		cout << -1 << "\n";
		return 0;
	}
	cout << ans1 + ans2 << "\n";
	return 0;
}

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */