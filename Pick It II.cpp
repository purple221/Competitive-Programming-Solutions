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
Problem Statement: https://www.hackerrank.com/challenges/billboards/problem

Instead of getting max. sum, we do total sum - min. sum
*/

int N, K;
ll sum, ans;
ll DP[MAXN];
deque<int> dq;
int a[MAXN];

inline ll Calc (int x) {
	return DP[x - 1] + a[x];
}

int main (int argc, char const *argv[]) {
	#ifdef NOT_DMOJ
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif // NOT_DMOJ
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K;
	for (int i=1; i<=N; i++) {
		cin >> a[i];
		sum += a[i];
	}
	for (int i=1; i<=K; i++) {
		// if (!dq.empty()) D("%s %d %lld %lld\n", "First:", i, Calc(i), Calc(dq.back()));
		while (!dq.empty() && Calc(i) <= Calc(dq.back())) dq.pop_back();
		dq.pb(i);
	}
	for (int i=K + 1; i<=N; i++) {
		// if (!dq.empty()) D("%s %d %lld %lld\n", "Second:", i, Calc(i), Calc(dq.back()));
		while (!dq.empty() && Calc(i) <= Calc(dq.back())) dq.pop_back();
		dq.pb(i);
		DP[i] = Calc(dq.front()); // Only stores minimum
		if (dq.front() == i - K) dq.pop_front();
	}
	cout << sum - DP[N] << "\n";
	return 0;
}

/*
5 2
1
2
3
4
5
*/

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */