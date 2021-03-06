#include <bits/stdc++.h>
#define MAXM 130000
#define MAXN 300
#define INF 0x3f3f3f3f
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) < (b) ? (b) : (a)
#define ll long long
#define vi vector<int>
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define f first
#define s second
#define mii map<int, int>
#define umii unordered_map<int, int>
using namespace std;

struct Network {
	struct Edge {
		int dest, cost, next;
		Edge (int dest, int cost, int next) : dest(dest), cost(cost), next(next) { }
	};

	int N, src, sink;
	vector<int> last, dist;
	vector<Edge> e;

	Network (int N, int src, int sink) : N(N), src(src), sink(sink), last(N), dist(N) {
		fill(last.begin(), last.end(), -1);
	}

	void addEdge (int x, int y, int xy, int yx) {
		e.push_back(Edge(y, xy, last[x]));
		last[x] = e.size() - 1;
		e.push_back(Edge(x, yx, last[y]));
		last[y] = e.size() - 1;
	}

	bool getPath () {
		fill(dist.begin(), dist.end(), -1);
		queue<int> q;
		q.push(src);
		dist[src] = 0;
		while (!q.empty()) {
			int curr = q.front();
			q.pop();
			for (int i = last[curr]; i != -1; i = e[i].next) {
				if (e[i].cost > 0 && dist[e[i].dest] == -1) {
					dist[e[i].dest] = dist[curr] + 1;
					q.push(e[i].dest);
				}
			}
		}
		return dist[sink] != -1;
	}

	int dfs (int curr, int flow) {
		if (curr == sink) {
			return flow;
		}
		int ret = 0;
		for (int i = last[curr]; i != -1; i = e[i].next) {
			if (e[i].cost > 0 && dist[e[i].dest] == dist[curr] + 1) {
				int res = dfs(e[i].dest, min(flow, e[i].cost));
				ret += res;
				e[i].cost -= res;
				e[i ^ 1].cost += res;
				flow -= res;
				if (flow == 0) {
					break;
				}
			}
		}
		return ret;
	}

	int getFlow () {
		int res = 0;
		while (getPath()) {
			res += dfs(src, 1 << 30);
		}
		return res;
	}
};

const int radius = 100;

int N, L, W, X, Y, source, sink;
ll ans;
pii centres[MAXN];

inline ll Get_Dist (const pii &a, const pii &b) {
	return (b.f - a.f) * (b.f - a.f) + (b.s - a.s) * (b.s - a.s);
}

int main () {
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> L >> W >> N;
	for (int i=1; i<=N; i++) {
		cin >> X >> Y;
		centres[i] = mp(X, Y);
	}
	source = N << 1 | 1;
	sink = source + 1;
	Network flow(MAXM, source, sink);
	for (int i=1; i<=N; i++) flow.addEdge(i, i + N, 1, 0);
	for (int i=1; i<=N; i++) {
		for (int j=i + 1; j<=N; j++) {
			if (Get_Dist(centres[i], centres[j]) <= (radius * radius) << 2) {
				flow.addEdge(i + N, j, INF, 0);
				flow.addEdge(j + N, i, INF, 0);
			}
		}
	}
	for (int i=1; i<=N; i++) {
		if (centres[i].s <= radius) flow.addEdge(source, i, INF, 0);
		if (W <= centres[i].s + radius) flow.addEdge(i + N, sink, INF, 0);
	}
	cout << flow.getFlow() << "\n";
	return 0;
}