#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=20010,inf=0x3f3f3f3f;
    int n,num,cnt,Head[N],c[N],s[N],w[N],dis[N],L[N],R[N],dp[N];

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
    }E[N];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    namespace Tree
    {
        struct node
        {
            int mn,tag;
        }tree[N<<2];
        #define ls root<<1
        #define rs root<<1|1

        inline void update(int root)
        {
            tree[root].mn=min(tree[ls].mn,tree[rs].mn);
        }

        inline void pushdown(int root)
        {
            int tag=tree[root].tag;
            if(!tag) return;
            tree[ls].tag+=tag;
			tree[ls].mn+=tag;
            tree[rs].tag+=tag;
			tree[rs].mn+=tag;
            tree[root].tag=0;
        }

        void build(int root,int l,int r)
        {
            tree[root].tag=0;
            if(l==r) {tree[root].mn=dp[l];return;}
            int mid=(l+r)>>1;
            build(ls,l,mid),build(rs,mid+1,r);
            update(root);
        }

        void change(int root,int l,int r,int s,int e,int val)
        {
            if(s<=l&&r<=e) 
            {
                tree[root].mn+=val;
				tree[root].tag+=val;
                return;
            }
            pushdown(root);
            int mid=(l+r)>>1;
            if(s<=mid) change(ls,l,mid,s,e,val);
            if(e>mid) change(rs,mid+1,r,s,e,val);
            update(root);
        }

        int query(int root,int l,int r,int s,int e)
        {
            if(s<=l&&r<=e) return tree[root].mn;
            pushdown(root);
            int mid=(l+r)>>1,ans=inf;
            if(s<=mid) ans=min(ans,query(ls,l,mid,s,e));
            if(e>mid) ans=min(ans,query(rs,mid+1,r,s,e));
            return ans;
        }
    }

	void work()
	{
        n=read(),num=read();
        for(int i=2;i<=n;i++) dis[i]=read();
        for(int i=1;i<=n;i++) c[i]=read();
        for(int i=1;i<=n;i++) s[i]=read();
        for(int i=1;i<=n;i++) w[i]=read();
        n++,dis[n]=w[n]=inf;
        for(int i=1;i<=n;i++)
        {
            L[i]=lower_bound(dis+1,dis+1+n,dis[i]-s[i])-dis;
            R[i]=upper_bound(dis+1,dis+1+n,dis[i]+s[i])-dis-1;
            add(R[i],i);
        }
        int res=0;
        for(int j=1;j<=n;j++)
        {
            dp[j]=res+c[j];
            for(int k=Head[j];k;k=E[k].next)
                res+=w[E[k].to];
        }
        int ans=dp[n];
        for(int i=1;i<=num;i++)
        {
            Tree::build(1,1,n);
            for(int j=1;j<=n;j++)
            {
                if(j>i) dp[j]=Tree::query(1,1,n,i-1,j-1);
                else dp[j]=0;
                dp[j]+=c[j];
                for(int k=Head[j];k;k=E[k].next)
                {
                    int t=E[k].to;
                    if(L[t]>1) Tree::change(1,1,n,1,L[t]-1,w[t]);
                }
            }
            ans=min(ans,dp[n]);
        }
        printf("%d",ans);
	}
}

int main()
{
	freopen("rand.in","r",stdin);
	TYC::work();
	return 0;
}
