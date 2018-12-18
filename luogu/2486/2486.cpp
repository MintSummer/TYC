#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,m,cnt,num,Head[MAXN],a[MAXN],out[MAXN];
int dep[MAXN],fa[MAXN],son[MAXN],size[MAXN],top[MAXN],dfn[MAXN],w[MAXN];
vector<int> E[MAXN];

void dfs1(int u)
{
    int heavyson=0,v;
    dep[u]=dep[fa[u]]+1;
    size[u]=1;
    for(int i=0;i<E[u].size();i++)
    {
        v=E[u][i];
        if(v==fa[u]) continue;
        fa[v]=u;
        dfs1(v);
        size[u]+=size[v];
        if(size[v]>size[heavyson]) heavyson=v;
    }
    son[u]=heavyson;
}

void dfs2(int u,int ance)
{
    dfn[u]=++num;
    top[u]=ance;
    w[num]=a[u];
    if(son[u]) dfs2(son[u],ance);
    int v;
    for(int i=0;i<E[u].size();i++)
    {
        v=E[u][i];
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}

struct node
{
    int l,r,sum,cl,cr,tag;
    node (int l=0,int r=0,int sum=0,int cl=0,int cr=0,int tag=0) : 
	l(l),r(r),sum(sum),cl(cl),cr(cr),tag(tag) {}
    node operator + (const node &a) const
    {
		node now;
		now.l=min(l,a.l),now.r=max(r,a.r);
		now.cl=cl,now.cr=a.cr;
		now.sum=sum+a.sum-(cr==a.cl);
		return now;
    }
}tree[MAXN*4];

void build(int root,int lt,int rt)
{
    tree[root].l=lt,tree[root].r=rt;
    tree[root].tag=0;
    if(lt==rt) 
    {
		tree[root].sum=1;
		tree[root].cl=tree[root].cr=w[lt];
		return;
    }
    int mid=(lt+rt)>>1;
    build(root*2,lt,mid),build(root*2+1,mid+1,rt);
    tree[root]=tree[root*2]+tree[root*2+1];
}

void pushdown(int root)
{
    int tag=tree[root].tag;
    if(!tag) return;
    node &ls=tree[root*2],&rs=tree[root*2+1];
    ls.cl=ls.cr=rs.cl=rs.cr=tag;
    ls.sum=rs.sum=1;
    ls.tag=rs.tag=tag;
    tree[root].tag=0;
}

void change(int root,int s,int e,int col)
{
    int lt=tree[root].l,rt=tree[root].r;
    if(s<=lt&&rt<=e)
    {
		tree[root].sum=1;
		tree[root].cl=tree[root].cr=col;
		tree[root].tag=col;
		return;
    }
    pushdown(root);
    int mid=(lt+rt)>>1;
    if(e<=mid) change(root*2,s,e,col);
    else if(s>mid) change(root*2+1,s,e,col);
    else change(root*2,s,mid,col),change(root*2+1,mid+1,e,col);
    tree[root]=tree[root*2]+tree[root*2+1];    
}

node ask(int root,int s,int e)
{
    int lt=tree[root].l,rt=tree[root].r;
    if(s<=lt&&rt<=e) return tree[root];
    pushdown(root);
    int mid=(lt+rt)>>1;
    if(e<=mid) return ask(root*2,s,e);
    else if(s>mid) return ask(root*2+1,s,e);
    else return ask(root*2,s,mid)+ask(root*2+1,mid+1,e);
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    int u,v;
    for(int i=1;i<n;i++) 
	cin>>u>>v,E[u].push_back(v),E[v].push_back(u);
    dfs1(1);
    dfs2(1,1);
    build(1,1,n);
    string st;
    int x,y,k;
    while(m--)
    {
		cin>>st>>x>>y;
		if(st[0]=='C') 
		{
			cin>>k;
			while(top[x]!=top[y])
			{
				if(dep[top[x]]<dep[top[y]]) swap(x,y);
				change(1,dfn[top[x]],dfn[x],k);
				x=fa[top[x]];
			}
			if(dep[x]>dep[y]) swap(x,y);
			change(1,dfn[x],dfn[y],k);
		}
		else
		{
			int ans=0,cl=-1,cr=-1;
			node t;
			while(top[x]!=top[y])
			{
				if(dep[top[x]]<dep[top[y]]) swap(x,y),swap(cl,cr);
				t=ask(1,dfn[top[x]],dfn[x]);
				ans+=t.sum-(t.cr==cl);
				cl=t.cl;
				x=fa[top[x]];
			}
			if(dep[x]>dep[y]) swap(x,y),swap(cl,cr);
			t=ask(1,dfn[x],dfn[y]);
			ans+=t.sum-(t.cl==cl)-(t.cr==cr);
			printf("%d\n",ans);
		}
    }
    return 0;
}
