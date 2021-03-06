#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define ll long long
#define MAXN 110
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
#define println cout << "\n";
#ifdef DEBUG
	#define D(x...) printf(x)
#else
	#define D(x...)
#endif
using namespace std;

int N, A, B, val = -1, minn = INF, ans;
vi check;
int P[MAXN];

int main (int argc, char const *argv[]) {
	#ifdef NOT_DMOJ
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif // NOT_DMOJ
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for (int i=0, x; i<N; i++) {
		cin >> x;
		P[i] = x;
		for (int j=0; j<=i; j++) {
			int ind = (x + P[j]) >> 1;
			if (ind & 1) check.pb(ind);
			else {
				check.pb(ind - 1);
				check.pb(ind + 1);
			}
		}
	}
	cin >> A >> B;
	A += A & 1 ? 0 : 1;
	B += B & 1 ? 0 : -1;
	check.pb(A);
	check.pb(B);
	for (auto i : check) {
		if (i < A || i > B) continue;
		minn = INF;
		for (int j=0; j<N; j++) {
			if (abs(P[j] - i) < minn) minn = abs(P[j] - i);
		}
		if (minn > val) {
			val = minn;
			ans = i;
		}
	}
	cout << ans << "\n";
	return 0;
}

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */