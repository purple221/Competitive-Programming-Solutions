#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define ll long long
#define ull unsigned long long
#define MAXN 100010
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
#define allof(x) x.begin(), x.end()
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

// https://atcoder.jp/contests/dp/tasks/dp_g

int N, M, ans;
int x[MAXN], y[MAXN], DP[MAXN];
vi adj[MAXN];

inline int Solve (int node) {
	int &res = DP[node];
	if (~res) return res;
	int maxx = 0;
	for (auto i : adj[node]) {
		maxx = max(maxx, Solve(i) + 1);
	}
	return res = maxx;
}

int main (int argc, char const *argv[]) {
	#ifdef NOT_DMOJ
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif // NOT_DMOJ
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	memset(DP, -1, sizeof(DP));
	for (int i=0; i<M; i++) {
		cin >> x[i] >> y[i];
		adj[x[i]].pb(y[i]);
	}
	for (int i=1; i<=N; i++) {
		ans = max(ans, Solve(i));
	}
	cout << ans << "\n";
	return 0;
}

/*
5 8
5 3
2 3
2 4
5 2
5 1
1 4
4 3
1 3
Ans: 3
*/

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */