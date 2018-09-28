#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define ll long long
#define ull unsigned long long
#define MAXN 2010
#define INF 0x3f3f3f3f
#define MOD 998244353
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

int N;
ll arr[MAXN], DP[MAXN];
vector<ll> ans;

int main (int argc, char const *argv[]) {
    #ifdef NOT_DMOJ
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // NOT_DMOJ
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    for (int i=0; i<N; i++) {
        cin >> arr[i];
        arr[i] = (((arr[i] + MOD) % MOD) + MOD) % MOD;
    }
    for (int i=0; i<=N; i++) DP[i] = 1LL;
    for (int i=0; i<N; i++) {
        for (int j=0; j<=N - i - 1; j++) {
            DP[j] = (((DP[j + 1] + MOD) % MOD * (arr[j] + MOD) % MOD) + MOD) % MOD;
        }
        for (int j=N - i - 2; j>=0; j--) {
            DP[j] = (((DP[j] + MOD) % MOD + (DP[j + 1] + MOD) % MOD) + MOD) % MOD;
        }
        ans.pb((DP[0] + MOD) % MOD);
    }
    for (auto i : ans) cout << i << " ";
    cout << "\n";
    return 0;
}

/* 
 * Look for:
 * the exact constraints (multiple sets are too slow for n=10^6 :( ) 
 * special cases (n=1?)
 * overflow (ll vs int?)
 * array bounds
 */