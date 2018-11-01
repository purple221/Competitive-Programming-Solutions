#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define ll long long
#define ull unsigned long long
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
#ifdef DEBUG
	#define D(x...) printf(x)
#else
	#define D(x...)
#endif
using namespace std;

/*
Now we know from maxima-minima concept that,
if an integer need to break in two parts, then to
maximize their product those part should be equal.
Using this concept lets break n into (n/x) x’s then
their product will be x^(n/x), now if we take derivative of
this product and make that equal to 0 for maxima, we will
get to know that value of x should be e (base of the
natural logarithm) for maximum product. As we know that
2 < e < 3, so we should break every integer into 2 or 3
only for maximum product.
*/

int N;
ll ans;

inline ll PowMod (ll a, ll b) {
	ll val = 1;
	while (b) {
		if (b & 1) val = (val * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return val;
}

ll Solve () {
	if (N == 2) return 1LL;
	if (N == 3) return 2LL;
	ll maxx;
	if (N % 3 == 0) maxx = PowMod(3, N / 3);
	else if (N % 3 == 1) maxx = 4 * PowMod(3, (N / 3) - 1);
	else maxx = 2 * PowMod(3, N / 3);
	return maxx;
}

int main (int argc, char const *argv[]) {
	#ifdef NOT_DMOJ
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif // NOT_DMOJ
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	cout << Solve() << "\n";
	return 0;
}

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */