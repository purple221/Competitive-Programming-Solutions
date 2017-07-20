#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar_unlocked())<'0'); for(x-='0'; '0'<=(_=getchar_unlocked()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define MAXN 500010
#define INF 0x3f3f3f3f
#define max(a, b) ((a) > (b)) ? (a) : (b)
#define ll long long
#define ull unsigned long long 
using namespace std;

const int MOD = 1000000007;

struct Books { 
public:
  int s, l, w;
} textbook[MAXN];

struct Node { 
public:
  int l, r, val, lazy; 
} Seg[MAXN << 3]; 

void Push_Up (int idx) {
  Seg[idx].val = max(Seg[idx << 1].val, Seg[idx << 1 | 1].val);
}

void Push_Down(int idx) {
  if (Seg[idx].lazy && Seg[idx].l ^ Seg[idx].r) {
    Seg[idx << 1].val = max(Seg[idx].val, Seg[idx << 1].val);
    Seg[idx << 1].lazy = 1;
    Seg[idx << 1 | 1].val = max(Seg[idx].val, Seg[idx << 1 | 1].val);
    Seg[idx << 1 | 1].lazy = 1;
    Seg[idx].lazy = 0;
  }
}

void Build(int idx, int l, int r) {
    Seg[idx].l = l; 
    Seg[idx].r = r;
    if (l == r) { 
      Seg[idx].val = 0; 
      Seg[idx].lazy = 0;
      return; 
    }
    int mid = (l + r) >> 1;
    Build(idx << 1, l, mid);
    Build(idx << 1 | 1, mid + 1, r);
}

void Update(int idx, int l, int r, int val) {
    Push_Down(idx);
    if (l > Seg[idx].r || r < Seg[idx].l) return;
    if (l <= Seg[idx].l && r >= Seg[idx].r){
        Seg[idx].val = val; 
        Seg[idx].lazy = 1;
        return;
    }
    int mid = (Seg[idx].l + Seg[idx].r) >> 1;
    if (r <= mid) Update(idx << 1, l, r, val);
    else if (l > mid) Update(idx << 1 | 1, l, r, val);
    else {
        Update(idx << 1, l, mid, val);
        Update(idx << 1 | 1, mid + 1, r, val);
    }
    Push_Up(idx);
}

int Query(int idx, int l, int r) {
    Push_Down(idx);
    if (l > Seg[idx].r || r < Seg[idx].l) return INF;
    if (l <= Seg[idx].l && r >= Seg[idx].r) return Seg[idx].val;
    int mid = (Seg[idx].l + Seg[idx].r) >> 1;
    if (r <= mid) return Query(idx << 1, l, r);
    else if (l > mid) return Query(idx << 1 | 1, l, r);
    else return max(Query(idx << 1, l, mid), Query(idx << 1 | 1, mid + 1, r));
  }

/*  
struct Segtree {
private:
  vector<Node> Seg;

public:
  Segtree(int N) : Seg(N << 3) { }

void Push_Up (int idx) {
  Seg[idx].val = max(Seg[idx << 1].val, Seg[idx << 1 | 1].val);
}

void Push_Down(int idx) {
  if (Seg[idx].lazy && Seg[idx].l ^ Seg[idx].r) {
    Seg[idx << 1].val = max(Seg[idx].val, Seg[idx << 1].val);
    Seg[idx << 1].lazy = 1;
    Seg[idx << 1 | 1].val = max(Seg[idx].val, Seg[idx << 1 | 1].val);
    Seg[idx << 1 | 1].lazy = 1;
    Seg[idx].lazy = 0;
  }
}

void Build(int idx, int l, int r) {
    Seg[idx].l = l; 
    Seg[idx].r = r;
    if (l == r) { 
      Seg[idx].val = 0; 
      Seg[idx].lazy = 0;
      return; 
    }
    int mid = (l + r) >> 1;
    Build(idx << 1, l, mid);
    Build(idx << 1 | 1, mid + 1, r);
}

void Update(int idx, int l, int r, int val) {
    Push_Down(idx);
    if (l > Seg[idx].r || r < Seg[idx].l) return;
    if (l <= Seg[idx].l && r >= Seg[idx].r){
        Seg[idx].val = val; 
        Seg[idx].lazy = 1;
        return;
    }
    int mid = (Seg[idx].l + Seg[idx].r) >> 1;
    if (r <= mid) Update(idx << 1, l, r, val);
    else if (l > mid) Update(idx << 1 | 1, l, r, val);
    else {
        Update(idx << 1, l, mid, val);
        Update(idx << 1 | 1, mid + 1, r, val);
    }
    Push_Up(idx);
}

int Query(int idx, int l, int r) {
    Push_Down(idx);
    if (l > Seg[idx].r || r < Seg[idx].l) return INF;
    if (l <= Seg[idx].l && r >= Seg[idx].r) return Seg[idx].val;
    int mid = (Seg[idx].l + Seg[idx].r) >> 1;
    if (r <= mid) return Query(idx << 1, l, r);
    else if (l > mid) return Query(idx << 1 | 1, l, r);
    else return max(Query(idx << 1, l, mid), Query(idx << 1 | 1, mid + 1, r));
  }
};
*/

int N, size; 
set<int> coor; 
unordered_map<int, int> arr; 
vector<int> v; 
ull ans;
//Segtree Seg(MAXN);

int main() {
    scan(N);
    for(int i=1; i<=N; i++) {
      scan(textbook[i].s); scan(textbook[i].l); scan(textbook[i].w);
        ans = (ans - 1ull * textbook[i].l * textbook[i].w % MOD + MOD) % MOD; 
        textbook[i].l += textbook[i].s;
        coor.insert(textbook[i].s); 
        coor.insert(textbook[i].l);
    }
    for(int i : coor) {
        arr[i] = size++; 
        v.push_back(i);
    }
    Build(1, 1, size);
    //Seg.Build(1, 1, size);
    for(int i=1; i<=N; i++){
        int l = arr[textbook[i].s] + 1;
        int r = arr[textbook[i].l];
        Update(1, l, r, textbook[i].w + Query(1, l, r));//Seg.Query(1, l, r));
        //Seg.Update(1, l, r, textbook[i].w + Seg.Query(1, l, r));
    }
    for(int i=1; i<=size - 1; i++) ans = (ans + (1ull * (v[i] - v[i - 1]) * Query(1, i, i)) % MOD) % MOD;//Seg.Query(1, i, i)) % MOD) % MOD;
    printf("%llu\n", ans % MOD);
}
