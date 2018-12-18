#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
int n,m,cnt=0,Head[MAXN],out[MAXN];
int vis[MAXN],dp[MAXN],in[MAXN];

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

int dfs(int u)
{
    vis[u]=1;
    int v;
    for(int i=Head[u];i;i=E[i].next)
    {
        v=E[i].to;
        if(vis[v]) {dp[u]+=dp[v];continue;}
        dp[u]+=dfs(v);
    }
    return dp[u];
}

int main()
{
	scanf("%d%d",&n,&m);
    int a,b;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        add(a,b);
        out[a]++,in[b]++;
    }
    for(int i=1;i<=n;i++)
        if(out[i]==0&&in[i]>0) dp[i]=1;
    int ans=0;
    for(int i=1;i<=n;i++)
        if(in[i]==0&&out[i]>0) ans+=dfs(i);
    printf("%d",ans);
    return 0;
}
