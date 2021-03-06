//TYC
//spfa过不去……dijkstra会T
#include<bits/stdc++.h>
using namespace std;
#define inf 1000000000000000000ll  
#define pa pair<long long,int>  
const int MAXN=200000+10;
int n,cnt=0,Head[MAXN],vis[MAXN];
long long dis[MAXN];
struct edge
{
	int to,next,w;
}E[MAXN*10];

struct point
{
	int x,y,id;
}node[MAXN];

bool cmpx(point a,point b)
{
	return a.x<b.x;
}

bool cmpy(point a,point b)
{
	return a.y<b.y;
}

void add(int u,int v,int w)
{
	cnt++;
	E[cnt].to=v;
	E[cnt].next=Head[u];
	E[cnt].w=w;
	Head[u]=cnt;
}

priority_queue<pa,vector<pa>,greater<pa> > q;  
void dijkstra()  
{  
    memset(vis,0,sizeof(vis));  
    for (int i=1;i<=n;i++) dis[i]=inf;  
    dis[1]=0;  
    q.push(make_pair(0,1));  
    while (!q.empty())  
    {  
        int x=q.top().second;q.pop();  
        if (vis[x]) continue;
		vis[x]=1;  
        for (int p=Head[x];p;p=E[p].next)  
        {
			int v=E[p].to;
			if (dis[v]>dis[x]+E[p].w)  
            {  
            	dis[v]=dis[x]+E[p].w;  
            	q.push(make_pair(dis[v],v));  
            }
		}  
    }  
}  

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&node[i].x,&node[i].y),node[i].id=i;
	
	sort(node+1,node+1+n,cmpx);
	for(int i=1;i<n;i++)
	{
		add(node[i].id,node[i+1].id,node[i+1].x-node[i].x);
		add(node[i+1].id,node[i].id,node[i+1].x-node[i].x);
	}
	
	sort(node+1,node+1+n,cmpy);
	for(int i=1;i<n;i++)
	{
		add(node[i].id,node[i+1].id,node[i+1].y-node[i].y);
		add(node[i+1].id,node[i].id,node[i+1].y-node[i].y);
	}

	spfa();
	printf("%lld",dis[n]);
	return 0;
}
