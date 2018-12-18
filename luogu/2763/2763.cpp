#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int inf=0x3f3f3f3f,MAXN=1050;
    int K,N,S,T,cnt=1,Head[MAXN],dep[MAXN],sit[MAXN];

    struct edge
    {
        int to,next,w;
    }E[510*510*2];

    void add(int u,int v,int w)
    {
        cnt++;
        E[cnt].to=v;
        E[cnt].next=Head[u];
        E[cnt].w=w;
        Head[u]=cnt;
    }

    void insert(int u,int v,int w)
    {
        add(u,v,w),add(v,u,0);
    }

    bool bfs()
    {
        memset(dep,-1,sizeof(dep));
        queue<int> q;
        q.push(S);
        dep[S]=0;
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
        return dep[T]!=-1;
    }

    int dfs(int u,int mn)
    {
        if(u==T) return mn;
        int v,w,used=0;
        for(int i=Head[u];i;i=E[i].next)
        {
            v=E[i].to;
            if(E[i].w>0&&dep[v]==dep[u]+1)
            {
                w=dfs(v,min(mn-used,E[i].w));
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
        while(bfs()) ans+=dfs(S,inf);
        return ans;
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin>>K>>N;
        S=0,T=N+K+1;
        int p,x,sum=0;
        for(int i=1;i<=K;i++)
        {
            cin>>x;
            sum+=x;
            insert(S,i,x);
        }
        for(int i=1;i<=N;i++)
        {
            cin>>p;
        insert(i+K,T,1);
        for(int j=1;j<=p;j++)	
            cin>>x,insert(x,i+K,1);
        }
        if(Dinic()!=sum) cout<<"0";
        else 
        {
            cout<<"1"<<endl;
            for(int u=1;u<=K;u++)
            {
                cout<<u<<"：";
                int tot=0;
                for(int i=Head[u];i;i=E[i].next)
                {
                    int v=E[i].to;
                    if(v>K&&v<=N+K&&E[i].w==0) sit[++tot]=v-K;
                }
                for(int i=tot;i;i--) cout<<sit[i]<<" ";
                cout<<endl;
            }
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
