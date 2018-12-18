#include<bits/stdc++.h>
using namespace std;
 
namespace TYC
{
    const int N=15010;
 
    int n,k,rot,Size,MX,Head[N],dist[N],top[N],son[N],dep[N],size[N],vis[N],mxsize[N],id[N*2],pre[N],fa[N];
 
    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }
 
    struct edge
    {
        int to,next,w;
    }E[N<<1];
 
    inline void add(int u,int v,int w)
    {
        static int cnt=0;
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }
 
    void dfs(int u)
    {
        int hs=0;
        size[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==pre[u]) continue;
            dep[v]=dep[u]+1;
            dist[v]=dist[u]+E[i].w;
            pre[v]=u;
            dfs(v);
            size[u]+=size[v];
            if(size[v]>size[hs]) hs=v;
        }
        son[u]=hs;
    }
 
    void dfs(int u,int ance)
    {
        top[u]=ance;
        if(son[u]) dfs(son[u],ance);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==pre[u]||v==son[u]) continue;
            dfs(v,v);
        }
    }
 
    inline int LCA(int u,int v)
    {
        while(top[u]!=top[v])
        {
            if(dep[top[u]]<dep[top[v]]) swap(u,v);
            u=pre[top[u]];
        }
        return dep[u]<dep[v]?u:v;
    }
 
    inline int distance(int u,int v)
    {
        return dist[u]+dist[v]-dist[LCA(u,v)]*2;
    }
 
    namespace Tree
    {
        const int M=15000*80+5;
        int cnt;
        struct node
        {
            int ls,rs,sum;
        }tree[M];
        #define ls tree[root].ls
        #define rs tree[root].rs
 
        void insert(int &root,int l,int r,int pos)
        {
            if(!root) root=++cnt;
            tree[root].sum++;           
            if(l==r) return;
            int mid=(l+r)>>1;
            if(pos<=mid) insert(ls,l,mid,pos);
            else insert(rs,mid+1,r,pos);
        }
 
        int query(int root,int l,int r,int s,int e)
        {
            if(!root) return 0;
            if(s<=l&&r<=e) return tree[root].sum;
            int mid=(l+r)>>1,ans=0;
            if(s<=mid) ans+=query(ls,l,mid,s,e);
            if(e>mid) ans+=query(rs,mid+1,r,s,e);
            return ans;
        }
    }
 
    void get_root(int u,int f)
    {
        size[u]=1,mxsize[u]=0;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f||vis[v]) continue;
            get_root(v,u);
            size[u]+=size[v];
            mxsize[u]=max(mxsize[u],size[v]);
        }
        mxsize[u]=max(mxsize[u],Size-size[u]);
        if(mxsize[u]<mxsize[rot]) rot=u;
    }
 
    void run(int root,int type,int u,int f,int dis)
    {
        Tree::insert(id[root+type*n],0,MX,dis);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f||vis[v]) continue;
            run(root,type,v,u,dis+E[i].w);
        }
    }
 
    void solve(int u)
    {
        vis[u]=1;
        run(u,0,u,0,0);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(vis[v]) continue;
            rot=0,Size=size[v];
            get_root(v,0);
            fa[rot]=u;
            run(rot,1,v,u,E[i].w);
            solve(rot);
        }
    }
 
    void init()
    {
        dfs(1);
        dfs(1,1);
        Size=n,mxsize[0]=n+5;
        get_root(1,0);
        solve(rot);
    }
 
    int query(int x,int mid)
    {
        int tot=Tree::query(id[x],0,MX,0,mid);
        for(int i=x;fa[i];i=fa[i])
        {
            int dis=distance(x,fa[i]);
            if(dis>mid) break;
            tot+=Tree::query(id[fa[i]],0,MX,0,mid-dis);
            tot-=Tree::query(id[i+n],0,MX,0,mid-dis);
        }
        return tot;
    }
 
    void work()
    {
        n=read(),k=read()+1;
        MX=n*10;
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read(),w=read();
            add(u,v,w),add(v,u,w);
        }
        init();
        for(int i=1;i<=n;i++)
        {
            int l=0,r=n*10,mid,ans;
            while(l<=r)
            {
                mid=(l+r)>>1;
                if(query(i,mid)>=k)ans=mid,r=mid-1;
                else l=mid+1;
            }
            printf("%d\n",ans);
        }
    }
}
 
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
    TYC::work();
    return 0;
}
