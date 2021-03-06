#include <bits/stdc++.h>
#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define ll long long
#define MAXN 100010
#define MAXM 200010
#define INF 0x3f3f3f3f
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) < (b) ? (b) : (a)
#define vi vector<int>
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define f first
#define s second
#define msll map<string, ll>
#define psll pair<string, ll>
using namespace std;

struct Edge {
	int a, b, c;
};

int N, M, X, Y, A, B, C, Q, F, L;
int *earliest, *late;
vector<pii> adj[MAXN];
Edge edges[MAXM];
bool vis[MAXN], isnode, ischannel, flag1, flag2, flag3;
int dist1[MAXN], dist2[MAXN];
priority_queue<pii, vector<pii>, greater<pii>> pq;

void SPFA (int src, int dist[MAXN]) {
	memset(vis, 0, sizeof(vis));
	pq.push(mp(0, src));
	dist[src] = 0;
	vis[src] = 1;
	while (!pq.empty()) {
		pii curr = pq.top();
		pq.pop();
		vis[curr.s] = 0;
		for (pii &next : adj[curr.s]) {
		    int nextcost = dist[curr.s] + next.s;
		    if (nextcost >= dist[next.f]) continue;\
		    dist[next.f] = nextcost;
		    if (!vis[next.f]) {
		        vis[next.f] = 1;
		        pq.push(mp(dist[next.f], next.f));
		    }
		}
	}
}

void Check_Cases (int node1, int node2) {
	flag1 = ((dist1[node1] < dist2[node1] && dist1[node2] < dist2[node2]) || (dist2[node1] < dist1[node1] && dist2[node2] < dist1[node2]) || (dist1[node2] < dist2[node2] && dist1[node1] < dist2[node1]) || (dist2[node2] < dist1[node2] && dist2[node1] < dist1[node1]));
	flag2 = ((dist1[node1] < dist2[node1] && dist1[node2] == dist2[node2]) || (dist2[node1] < dist1[node1] && dist2[node2] == dist1[node2]) || (dist1[node2] < dist2[node2] && dist1[node1] == dist2[node1]) || (dist2[node2] < dist1[node2] && dist2[node1] == dist1[node1]));
	flag3 = ((dist1[node1] < dist2[node1] && dist1[node2] > dist2[node2]) || (dist2[node1] < dist1[node1] && dist2[node2] > dist1[node2]));
}

void Get_Earliest (int node1, int node2) {
	if (dist1[node1] < dist2[node1]) {
		earliest = dist1;
		late = dist2;
	}
	else {
		earliest = dist2;
		late = dist1;
	}
}

int main () {
    scan(N); scan(M); scan(X); scan(Y);
	for (int i=1; i<=M; i++) {
	    scan(A); scan(B); scan(C);
		adj[A].pb(mp(B, C));
		adj[B].pb(mp(A, C));
		edges[i] = (Edge) {A, B, C};
	}
	memset(dist1, INF, sizeof(dist1));
	memset(dist2, INF, sizeof(dist2));
	SPFA(X, dist1);
	SPFA(Y, dist2);
	scan(Q);
	for (int i=0; i<Q; i++) {
		scan(F); scan(L);
		if (F == 1) {
			if (dist1[L] == dist2[L]) printf("%d\n", dist1[L]);
			else printf("%d\n", -1);
		}
		else {
			int node1 = edges[L].a;
			int node2 = edges[L].b;
			int cost = edges[L].c;
			Check_Cases(node1, node2);
			if (flag1) printf("%d\n", -1);
			else if (flag2) {
				if (dist1[node1] == dist2[node1]) swap(node1, node2);
				Get_Earliest(node1, node2);
				if (earliest[node2] == earliest[node1] + cost) printf("%d\n", -1);
				else printf("%d\n", earliest[node2]);
			}
			else if (flag3) {
				Get_Earliest(node1, node2);
				printf("%f\n", ((earliest[node1] + late[node2] + cost) / 2.0));
			}
			else printf("%d\n", min(dist1[node1], dist1[node2]));
		}
	}
	return 0;
}