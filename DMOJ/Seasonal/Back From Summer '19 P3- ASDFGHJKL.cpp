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
#define umii unordered_map<int, int>w
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

string s, ss;
ll l, k, suml, ans;
map<int, ll> freq;
ll PSA[MAXN][27];
priority_queue<ll> pq;

int main (int argc, char const *argv[]) {
	#ifdef NOT_DMOJ
	freopen("DATA.in", "r", stdin);
	freopen("DATA.out", "w", stdout);
	#endif // NOT_DMOJ
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s >> l >> k;
	if (l + k >= s.size()) {
		cout << 0;
		return 0;
	}
	int start = 0;
	for (size_t i=1; i<=s.size(); i++) PSA[i][s[i - 1] - 'a']++;
	for (size_t i=1; i<=s.size(); i++) {
		for (int j=0; j<26; j++) {
			PSA[i][j] += PSA[i - 1][j];
		}
	}
	for (size_t i=0; i<=s.size() - l; i++) {
		ll sum = 0;
		string ss = s.substr(i, l);
		map<char, bool> flag;
		// cout << ss << endl;
		for (auto j : ss) {
			ll res = PSA[i + l][j - 'a'] - PSA[i][j - 'a'];
			// cout << j << " " << res << " ";
			if (!flag[j]) sum += 1LL * res * res;
			flag[j] = 1;
		}
		// cout << endl;
		if (suml < sum) {
			suml = sum;
			start = i;
		}
	}
	// cout << s.substr(start, l) << " " << suml << endl;
	s.erase(start, l);
	// cout << s << endl;
	for (auto i : s) freq[i - 'a']++;
	for (int i=0; i<26; i++) pq.push(freq[i]);
	while (k--) {
		ll curr = pq.top();
		pq.pop();
		pq.push(curr - 1LL);
	}
	while (!pq.empty()) {
		ll curr = pq.top();
		ans += 1LL * curr * curr;
		pq.pop();
	}
	cout << ans << "\n";
	return 0;
}

/* 
 Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 * number of test cases (T = 10)
 * resetting containers, variables, etc
 */