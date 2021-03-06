#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define ll long long
#define ull unsigned long long
#define MAXN 1000010
#define MOD 1000000007
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
// #define NOT_DMOJ 0
#ifdef DEBUG
	#define D(x...) printf(x)
#else
	#define D(x...)
#endif
using namespace std;

inline int GCD (int a, int b) { return b == 0 ? a : GCD(b, a % b); }
inline int LCM (int a, int b) { return a * b / GCD(a, b); }
inline ll PowMod (ll a, ll b, ll mod) { ll val = 1; while (b) { if (b & 1) val = (val * a) % mod; a = (a * a) % mod; b >>= 1; } return val; }

int N, M, src, dest;
int a[MAXN], b[MAXN], dist[MAXN], par[MAXN];
vector<pii> ind[MAXN];
vector<pii> path;

int main (int argc, char const *argv[]) {
	#ifdef NOT_DMOJ
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif // NOT_DMOJ
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for (int i=1; i<=M; i++) {
		cin >> a[i] >> b[i];
		if (i == 1) src = a[i];
		if (i == M) dest = b[i];
	}
	memset(dist, INF, sizeof(dist));
	dist[src] = 0;
	for (int i=1; i<=M; i++) {
		if (dist[b[i]] > dist[a[i]] + 1) {
			dist[b[i]] = dist[a[i]] + 1;
			ind[b[i]].pb(mp(a[i], ind[a[i]].size() - 1));
		}
	}
	cout << dist[dest] << "\n";
	pii node = pii(dest, ind[dest].size() - 1);
	while (node.f ^ src) {
		path.pb(mp(ind[node.f][node.s].f, node.f));
		node = ind[node.f][node.s];
	}
	reverse(path.begin(), path.end());
	for (auto i : path) cout << i.f << " " << i.s << "\n";
	return 0;
}

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */