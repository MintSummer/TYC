#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=2e5+10,M=2e5+10,inf=0x3f3f3f3f;
    int n,s,t,cnt=1,Head[N],dep[N];

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
    }E[M<<4];

    inline void insert(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v],0};
        Head[v]=cnt;
    }

    bool bfs()
    {
        memset(dep,-1,sizeof(dep));
        queue<int> q;
        q.push(s);
        dep[s]=0;
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(E[i].w>0&&dep[v]==-1) 
                    dep[v]=dep[u]+1,q.push(v);
            }
        }
        return dep[t]!=-1;
    }

    int dfs(int u,int mn)
    {
        if(u==t) return mn;
        int w,used=0;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(E[i].w>0&&dep[v]==dep[u]+1)
            {
                w=dfs(v,min(E[i].w,mn-used));
                used+=w;
                E[i].w-=w,E[i^1].w+=w;
                if(used==mn) return used;
            }
        }
        if(!used) dep[u]=-1;
        return used;
    }

    int Dinic()
    {
        int ans=0;
        while(bfs()) 
		{
			int tmp=dfs(s,inf);
			if(tmp>0) ans+=tmp;
		}
        return ans;
    }

    void work()
    {
        int A=read(),B=read(),C=read();
        swap(A,B);
        n=A+B+B+C;
        s=n+1,t=s+1;
        for(int i=1;i<=A;i++) insert(s,i,1);
        for(int i=1;i<=C;i++) insert(A+B+B+i,t,1);
        for(int i=1;i<=B;i++) insert(A+i,A+B+i,1);
        int m=read();
        while(m--)
        {
            int u=read(),v=read();
            insert(v,A+u,1);
        }
        m=read();
        while(m--)
        {
            int u=read(),v=read();
            insert(A+B+u,A+B+B+v,1);
        }
        printf("%d\n",Dinic());
    }
}

int main()
{
    TYC::work();
    return 0;
}
