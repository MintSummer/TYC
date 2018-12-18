#include<bits/stdc++.h>
using namespace std;
const int MAXN=5010;
int n,m,cnt,Head[MAXN],f1[MAXN],f2[MAXN];
bool vis[MAXN];

struct edge
{
    int to,next,w;
}E[100010*2];

void add(int u,int v,int w)
{
    cnt++;
    E[cnt].to=v;
    E[cnt].next=Head[u];
    E[cnt].w=w;
    Head[u]=cnt;
}

void spfa(int s,int f[])
{
    queue<int> q;
    memset(vis,false,sizeof(vis));
    vis[s]=1;
    q.push(s);
    f[s]=0;
    int u,v;
    while(!q.empty())
    {
        u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=Head[u];i;i=E[i].next)
        {	
            v=E[i].to;
            if(f[v]>f[u]+E[i].w) 
            {
                f[v]=f[u]+E[i].w;
                if(!vis[v]) vis[v]=1,q.push(v);
            }
        }
    }
}

int main()
{
    memset(f1,0x3f3f3f3f,sizeof(f1));
    memset(f2,0x3f3f3f3f,sizeof(f2));
    scanf("%d%d",&n,&m);
    int u,v,w;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w),add(v,u,w);
    }
    spfa(1,f1);
    spfa(n,f2);
    int mn=f1[n],ans=0x3f3f3f3f,len;
    for(int i=1;i<=n;i++)
        for(int j=Head[i];j;j=E[j].next)
        {
            len=f1[i]+f2[E[j].to]+E[j].w;
            if(len>mn&&len<ans) ans=len;
        }
    printf("%d",ans);
    return 0;
}
