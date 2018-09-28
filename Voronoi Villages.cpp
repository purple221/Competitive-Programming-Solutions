#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define ll long long
#define ull unsigned long long
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

int N, V;
vi v;
long double tmp, minn = INF, diff;
vector<long double> vec;

int main (int argc, char const *argv[]) {
	#ifdef NOT_DMOJ
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif // NOT_DMOJ
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	while (N--) {
		cin >> V;
		v.pb(V);
	}
	sort(v.begin(), v.end());
	for (size_t i=0; i<v.size() - 1; i++) {
		tmp = (v[i] + v[i + 1]) / 2.0;
		// cout << tmp << endl;
		diff = 1.0 * abs(v[i] - tmp);
		vec.pb(diff);
	}
	for (size_t i=0; i<vec.size() - 1; i++) {
		long double sum = vec[i] + vec[i + 1];
		if (sum < minn) minn = sum;
	}	
	cout << fixed << setprecision(1) << minn << "\n";
	return 0;
}

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */