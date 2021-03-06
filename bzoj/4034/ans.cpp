# include <bits/stdc++.h>
using namespace std;

int n, m, val[100010];
const int root = 1;

int head[100010], to[200010], next[200010], tot=0;
int seq[600010], sn=0, in[100010], out[100010];
bool io[600010];

inline void add(int u, int v) {
	++tot;
	next[tot]=head[u];
	head[u]=tot;
	to[tot]=v;
}

inline void dfs(int x, int fa) {
	++sn;
	in[x] = sn; seq[sn] = val[x];
	io[sn] = 1;
	for (int i=head[x]; i; i=next[i]) {
		if(to[i] == fa) continue;
		dfs(to[i], x);
	}
	++sn;
	out[x] = sn; seq[sn] = -val[x];
	io[sn] = 0;
}

typedef long long ll;
int lc[2400010], rc[2400010];
ll w[2400010], lazy[2400010];
int flag[2400010];

inline void pushdown(int x) {
	if(!lazy[x]) return;
	w[x<<1] += lazy[x] * flag[x<<1];
	w[x<<1|1] += lazy[x] * flag[x<<1|1];
	lazy[x<<1] += lazy[x];
	lazy[x<<1|1] += lazy[x];
	lazy[x] = 0;
}

inline void build(int x, int l, int r) {
	lc[x] = l, rc[x] = r; w[x] = lazy[x] = 0;
	if(l == r) {
		w[x] = (ll)seq[l];
		if(io[l]) flag[x] = 1;
		else flag[x] = -1;
		return ;
	}
	int mid = l+r>>1;
	build(x<<1, l, mid);
	build(x<<1|1, mid+1, r);
	w[x] = w[x<<1] + w[x<<1|1];
	flag[x] = flag[x<<1] + flag[x<<1|1];
}

inline void change(int x, int L, int R, ll delta) {
	int l = lc[x], r = rc[x];
	if(L <= l && r <= R) {
		w[x] = w[x] + flag[x] * delta;
		lazy[x] += delta;
		return ;
	}
	pushdown(x);
	int mid = l+r >> 1;
	if(L > mid) change(x<<1|1, L, R, delta);
	else if(R <= mid) change(x<<1, L, R, delta);
	else {
		change(x<<1, L, mid, delta);
		change(x<<1|1, mid+1, R, delta);
	}
	w[x] = w[x<<1] + w[x<<1|1];
}

inline ll query(int x, int L, int R) {
	int l = lc[x], r = rc[x];
	if(L <= l && r <= R) return w[x];
	pushdown(x);
	int mid = l+r >> 1;
	if(L > mid) return query(x<<1|1, L, R);
	else if(R <= mid) return query(x<<1, L, R);
	else return query(x<<1, L, mid) + query(x<<1|1, mid+1, R);
}

int main() {
	freopen("4034.in","r",stdin);
	freopen("ans.out","w",stdout);
	scanf("%d%d", &n, &m);
	for (int i=1; i<=n; ++i) scanf("%d", &val[i]);
	for (int i=1, u, v; i<n; ++i) {
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(root, 0);
	//for (int i=1; i<=sn; ++i) printf("%d ", seq[i]);
	//printf("\n");
	//for (int i=1; i<=n; ++i) printf("%d ", in[i]);
	//printf("\n");
	//for (int i=1; i<=n; ++i) printf("%d ", out[i]);
	//printf("\n");
	build(1, 1, sn);
	for (int i=1; i<=m; ++i) {
		int opt;
		scanf("%d", &opt);
		if(opt == 1) {
			int x, del;
			scanf("%d%d", &x, &del);
			change(1, in[x], in[x], (ll)del);
			change(1, out[x], out[x], (ll)del);
		}
		else if(opt == 2) {
			int x, del;
			scanf("%d%d", &x, &del);
			change(1, in[x], out[x], (ll)del);
		}
		else if(opt == 3) {
			int x;
			scanf("%d", &x);
			printf("%lld\n", query(1, 1, in[x]));
		}
	}
	return 0;
}
