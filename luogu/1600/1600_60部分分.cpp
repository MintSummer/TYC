#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace TYC
{
    const int N=3e5+10;
    int n,m,cnt,dfstim,Head[N],tim[N],s[N],t[N],dep[N],fa[N],top[N],dfn[N],son[N],size[N];

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
        dep[u]=dep[fa[u]]+1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]) continue;
            fa[v]=u;
            dfs(v);
            size[u]+=size[v];
            if(size[v]>size[hs]) hs=v;
        }
        son[u]=hs;
    }

    void dfs(int u,int ance)
    {
        top[u]=ance;
        dfn[u]=++dfstim;
        if(son[u]) dfs(son[u],ance);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]||v==son[u]) continue;
            dfs(v,v);
        }
    }

    namespace Subtask_Small //25pts
    {
        const int M=1010;
        int num[M][M];

        int LCA(int u,int v)
        {
            while(top[u]!=top[v])
            {
                if(dep[top[u]]<dep[top[v]]) swap(u,v);
                u=fa[top[u]];
            }
            return dep[u]<dep[v]?u:v;
        }

        void work()
        {
            dfs(1);
            dfs(1,1);
            for(int i=1;i<=m;i++)
            {
                int u=s[i],v=t[i],lca=LCA(u,v);
                int len=dep[u]+dep[v]-dep[lca]-dep[fa[lca]]-1;
                while(u!=lca) 
                {
                    num[u][dep[s[i]]-dep[u]]++;
                   u=fa[u];
                }
                num[lca][dep[s[i]]-dep[lca]]++;
                while(v!=lca)
                {
                    num[v][len-(dep[t[i]]-dep[v])]++;
                    v=fa[v];
                }
            }
            for(int i=1;i<=n;i++)
                printf("%d ",num[i][tim[i]]);
        }
    }

    namespace Subtask_S1 //20pts
    {
        namespace Segment_Tree
        {
            struct node
            {
                int sum,tag;
            }tree[N<<2];
            #define ls tree[root<<1]
            #define rs tree[root<<1|1]

            void pushdown(int root,int l,int r)
            {
                int mid=(l+r)>>1,tag=tree[root].tag;
                if(!tag) return;
                ls.sum+=(mid-l+1)*tag,ls.tag+=tag;
                rs.sum+=(r-mid)*tag,rs.tag+=tag;
                tree[root].tag=0;
            }

            void insert(int root,int l,int r,int s,int e)
            {
                if(s<=l&&r<=e) 
                {
                    tree[root].sum+=r-l+1;
                    tree[root].tag++;
                    return;
                }
                pushdown(root,l,r);
                int mid=(l+r)>>1;
                if(s<=mid) insert(root<<1,l,mid,s,e);
                if(e>mid) insert(root<<1|1,mid+1,r,s,e);
                tree[root].sum=ls.sum+rs.sum;
            }

            int query(int root,int l,int r,int x)
            {
                if(l==x&&x==r) return tree[root].sum;
                pushdown(root,l,r);
                int mid=(l+r)>>1;
                if(x<=mid) return query(root<<1,l,mid,x);
                else return query(root<<1|1,mid+1,r,x);
            }
        }

        void work()
        {
            dep[0]=-1;
            dfs(1);
            dfs(1,1);
            for(int i=1;i<=m;i++)
            {
                int x=t[i];
                while(top[x]!=1) 
                {
                    Segment_Tree::insert(1,1,n,dfn[top[x]],dfn[x]);
                    x=fa[top[x]];
                }
                Segment_Tree::insert(1,1,n,dfn[1],dfn[x]);
            }
            for(int i=1;i<=n;i++)
                if(dep[i]!=tim[i]) printf("0 ");
                else printf("%d ",Segment_Tree::query(1,1,n,dfn[i]));
        }
    }

    namespace Subtask_Link //15pts
    {
        int ans[N],num[N];

        struct interval
        {
            int s,t;
        }a[N];

        struct node
        {
            int pos,tag,id;
        }x[N<<1];

        bool cmp1(const node &p,const node &q)
        {
            return p.pos==q.pos?p.tag>q.tag:p.pos<q.pos;
        }

        bool cmp2(const node &p,const node &q)
        {
            return p.pos==q.pos?p.tag>q.tag:p.pos>q.pos;
        }

        void work()
        {
            int L=0,R=m;
            for(int i=1;i<=m;i++)
                if(s[i]<t[i]) a[++L]=(interval){s[i],t[i]};
                else a[R--]=(interval){s[i],t[i]};
            int tot=0;
            for(int i=1;i<=m;i++)
            {
                x[++tot]=(node){a[i].s,1,i};
                x[++tot]=(node){a[i].t,-1,i};
            }   
            L<<=1;
            sort(x+1,x+1+L,cmp1);
            sort(x+L+1,x+tot+1,cmp2);

            int now=1;
            for(int i=1;i<=n;i++)
            {
                while(x[now].pos==i&&x[now].tag==1&&now<=L) 
                    num[x[now].pos]++,now++;
                ans[i]+=num[i-tim[i]];
                while(x[now].pos==i&&now<=L)
                    num[a[x[now].id].s]--,now++;
            }
            if(now!=L+1) now=L+1;
            for(int i=n;i;i--)
            {
                while(x[now].pos==i&&x[now].tag==1&&now<=tot) 
                    num[x[now].pos]++,now++;
                ans[i]+=num[i+tim[i]];
                while(x[now].pos==i&&now<=tot)
                    num[a[x[now].id].s]--,now++;
            }
            for(int i=1;i<=n;i++) printf("%d ",ans[i]);
        }
    }

    void work()
    {
        n=read(),m=read();
        int flag_s1=1,flag_link=1;
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
            if(v!=u+1) flag_link=0;
        }
        for(int i=1;i<=n;i++) tim[i]=read();
        for(int i=1;i<=m;i++)
        {   
            s[i]=read(),t[i]=read();
            if(s[i]!=1) flag_s1=0;
        }
        if(n<=1000) Subtask_Small::work();
        else if(flag_s1) Subtask_S1::work();
        else if(flag_link) Subtask_Link::work();
    }
}

int main()
{
    TYC::work();
    return 0;
}