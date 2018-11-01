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
#define DEBUG 1
#ifdef DEBUG
	#define D(x...) printf(x)
#else
	#define D(x...)
#endif
using namespace std;

/*
Shortest possible solution is by going from (2,1) and (2,2) to (1000,1)
and (1000,2) twice in a row, a total of 1998 days, which is correct
in the same way. First sweep catches the thief if he started with
even X coordinate, and second sweep catches the thief if he started with
odd X coordinate.
*/

int N, X1, X2;
const int Y1 = 1, Y2 = 2;


int main (int argc, char const *argv[]) {
	#ifdef NOT_DMOJ
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif // NOT_DMOJ
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	N = 1998;
	cout << N << "\n";
	X1 = X2 = 2;
	cout << X1 << " " << Y1 << " " << X2 << " " << Y2 << "\n";
	while (X1 ^ 1000 && X2 ^ 1000) {
		X1++;
		X2++;
		cout << X1 << " " << Y1 << " " << X2 << " " << Y2 << "\n";
	}
	X1 = X2 = 2;
	cout << X1 << " " << Y1 << " " << X2 << " " << Y2 << "\n";
	while (X1 ^ 1000 && X2 ^ 1000) {
		X1++;
		X2++;
		cout << X1 << " " << Y1 << " " << X2 << " " << Y2 << "\n";
	}
	return 0;
}

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */