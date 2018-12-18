#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
typedef long long ll;
int cnt,num,Head[MAXN],a[MAXN];
int son[MAXN],dfn[MAXN],fa[MAXN],dep[MAXN],top[MAXN],w[MAXN],size[MAXN];

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

struct edge
{
    int to,next;
}E[MAXN*2];

void add(int u,int v)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    Head[u]=cnt;
}

void dfs1(int u)
{
    int hs=0;
    dep[u]=dep[fa[u]]+1;
    size[u]=1;
    for(int i=Head[u];i;i=E[i].next)
    {
		int v=E[i].to;
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs1(v);
		size[u]+=size[v];
		if(size[v]>size[hs]) hs=v;
    }
    son[u]=hs;
}

void dfs2(int u,int ance)
{
    dfn[u]=++num;
    top[u]=ance;
    w[num]=a[u];
    if(son[u]) dfs2(son[u],ance);
    for(int i=Head[u];i;i=E[i].next)
    {
		int v=E[i].to;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
    }
}

struct node
{
    int l,r,sum,tag;
}tree[MAXN*4];

void build(int root,int lt,int rt)
{
    tree[root].l=lt,tree[root].r=rt;
    if(lt==rt) {tree[root].sum=w[lt];return;}
    int mid=(lt+rt)>>1;
    build(root*2,lt,mid),build(root*2+1,mid+1,rt);
    tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

void pushdown(int root)
{
    int lt=tree[root].l,rt=tree[root].r,mid=(lt+rt)>>1;
    int tag=tree[root].tag;
    tree[root].tag=0;
    node &ls=tree[root*2],&rs=tree[root*2+1];
    ls.sum+=tag*(mid-lt+1),rs.sum+=tag*(rt-mid);
    ls.tag+=tag,rs.tag+=tag;
}

void add(int root,int s,int e,int val)
{
    int lt=tree[root].l,rt=tree[root].r;
    if(s<=lt&&rt<=e)
    {
		tree[root].sum+=val*(rt-lt+1);
		tree[root].tag+=val;
		return;
    }
    pushdown(root);
    int mid=(lt+rt)>>1;
    if(e<=mid) add(root*2,s,e,val);
    else if(s>mid) add(root*2+1,s,e,val);
    else add(root*2,s,mid,val),add(root*2+1,mid+1,e,val);
    tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

ll ask(int root,int s,int e)
{
    int lt=tree[root].l,rt=tree[root].r;
    if(s<=lt&&rt<=e) return tree[root].sum;
    pushdown(root);
    int mid=(lt+rt)>>1;
    if(e<=mid) return ask(root*2,s,e);
    else if(s>mid) return ask(root*2+1,s,e);
    return ask(root*2,s,mid)+ask(root*2+1,mid+1,e);
}

int main()
{
    int n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++)
    {
		int u=read(),v=read();
		add(u,v),add(v,u);
    }
    dfs1(1);
    dfs2(1,1);
    build(1,1,n);
    int opt,x;
    while(m--)
    {
		opt=read(),x=read();
		if(opt==1) add(1,dfn[x],dfn[x],read());
		else if(opt==2) add(1,dfn[x],dfn[x]+size[x]-1,read());
		else
		{
			int ans=0;
			int y=1;
			while(top[x]!=top[y])
			{
				if(dep[top[x]]<dep[top[y]]) swap(x,y);
				ans+=ask(1,dfn[top[x]],dfn[x]);
				x=fa[top[x]];
			}
			if(dep[x]>dep[y]) swap(x,y);
			ans+=ask(1,dfn[x],dfn[y]);
			printf("%d\n",ans);
		}
    }
    return 0;
}
