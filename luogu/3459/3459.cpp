#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace Tree
{
    const int N=1000010;
    int sum[N];
    #define ls root<<1
    #define rs root<<1|1

    void build(int root,int l,int r)
    {
        if(l==r) {sum[root]=(l!=1);return;}
        int mid=(l+r)>>1;
        build(ls,l,mid),build(rs,mid+1,r);
        sum[root]=sum[ls]+sum[rs];
    }

    void change(int root,int l,int r,int x)
    {
        if(l==r) {sum[root]=0;return;}
        int mid=(l+r)>>1;
        if(x<=mid) change(ls,l,mid,x);
        else change(rs,mid+1,r,x);
        sum[root]=sum[ls]+sum[rs];
    }

    int query(int root,int l,int r,int s,int e)
    {
        if(e<l||s>r) return 0;
        if(s<=l&&r<=e) return sum[root];
        int mid=(l+r)>>1;
        return query(ls,l,mid,s,e)+query(rs,mid+1,r,s,e);
    }
}

namespace TYC
{
    const int N=250010;
    int n,m,cnt,tim,Head[N],fa[N],top[N],son[N],dfn[N],size[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next;
    }E[N<<1];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    void dfs(int u)
    {
        int hs=0;
        size[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]) continue;
            fa[v]=u;
            dfs(v);
            if(size[v]>size[hs]) hs=v;
            size[u]+=size[v];
        }
        son[u]=hs;
    }

    void dfs(int u,int ance)
    {
        top[u]=ance;
        dfn[u]=++tim;
        if(son[u]) dfs(son[u],ance);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]||v==son[u]) continue;
            dfs(v,v);
        }
	}

    void work()
    {
        n=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        dfs(1);
        dfs(1,1);
        Tree::build(1,1,n);
        m=read()+n-1;
        char ch;
        while(m--)
        {
            do {ch=getchar();} while(ch!='A'&&ch!='W');
            if(ch=='A') Tree::change(1,1,n,dfn[max(read(),read())]);
            else
            {
                int ans=0;
                for(int x=read();x;x=fa[top[x]])
                    ans+=Tree::query(1,1,n,dfn[top[x]],dfn[x]);
                printf("%d\n",ans);
            }
        }
    }    
} 

int main()
{
    TYC::work();
    return 0;
}
