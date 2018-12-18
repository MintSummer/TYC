#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;

struct Query 
{
	int x, y, id, typ, num; 
	bool operator < (const Query &a) const
	{
		return id < a.id; 
	}
} q[200005], t[200005];

int x1, y1, x2, y2, tot, w, S, x, y, z, op,b[2000005];

void add(int x, int y) 
{
	for (; x <= w; x += x & -x) b[x] += y; 
}

void clear(int x) 
{
	for (; x <= w; x += x & -x) b[x] = 0; 
}

int query(int x) 
{
	int ans = 0; 
	for(; x; x -= x & -x) ans += b[x]; 
	return ans; 
}

void CDQ(int l, int r) 
{
    if (l == r) return;
    int mid = l + r >> 1;
    CDQ(l, mid); CDQ(mid + 1, r);
    int p1 = l, p2 = mid + 1, p3 = l;
    while (p1 <= mid && p2 <= r)
    {
        if (q[p1].x <= q[p2].x) 
        {
            if (!q[p1].typ) add(q[p1].y, q[p1].num);
            t[p3++] = q[p1++];
        } 
        else 
        {
            if (q[p2].typ) q[p2].num += query(q[p2].y);
            t[p3++] = q[p2++];
        }
    }
    while (p1 <= mid) 
    {
        if (!q[p1].typ) add(q[p1].y, q[p1].num);
        t[p3++] = q[p1++];
    }
    while (p2 <= r) 
    {
        if (q[p2].typ) q[p2].num += query(q[p2].y);
        t[p3++] = q[p2++];
    }
    for (int i = l; i <= mid; i++) 
    	if (!q[i].typ)  clear(q[i].y);
    for (int i = l; i <= r; i++) q[i] = t[i];
}
signed main() 
{
    scanf("%lld%lld", &S, &w);
    while (scanf("%lld", &op), op ^ 3) 
    {
        if (op == 1) 
        {
            scanf("%lld%lld%lld", &x, &y, &z); ++tot;
            q[tot] = (Query) {x, y, tot, 0, z};
        } 
        else 
        {
            scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
            ++tot, q[tot] = (Query) {x2, y2, tot, 1, 0};
            ++tot, q[tot] = (Query) {x1 - 1, y2, tot, 1, 0};
            ++tot, q[tot] = (Query) {x2, y1 - 1, tot, 1, 0};
            ++tot, q[tot] = (Query) {x1 - 1, y1 - 1, tot, 1, 0};
        }
    }
    CDQ(1, tot);
    sort(q + 1, q + tot + 1);
    for (int i = 1; i <= tot; i++) 
        if (q[i].typ) 
        {
            printf("%lld\n", q[i].num - q[i + 1].num - q[i + 2].num + q[i + 3].num);
            i += 3;
        }
    return 0;
}
