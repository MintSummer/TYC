//分析详见http://blog.csdn.net/hqddm1253679098/article/details/78829766
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5010;
int n,m,cnt,Head[MAXN],f1[MAXN],f2[MAXN];

struct node
{
	int num,val;
	bool operator < (const node &b) const
	{
		return val>b.val;
	}
};

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

void dijkstra()
{
	priority_queue<node> q;
	f1[1]=0;
	q.push((node){1,0});
	int u,v,dis;
	while(!q.empty())
	{
		u=q.top().num,dis=q.top().val;
		q.pop();
		if(dis>f2[u]) continue;
		for(int i=Head[u];i;i=E[i].next)
		{
			v=E[i].to;
			bool flag=false;

			if(f1[v]>f1[u]+E[i].w) 
				f1[v]=f1[u]+E[i].w,flag=true;

			if(f1[v]<f1[u]+E[i].w&&f2[v]>f1[u]+E[i].w)
				f2[v]=f1[u]+E[i].w,flag=true;

			if(f2[v]>f2[u]+E[i].w)
				f2[v]=f2[u]+E[i].w,flag=true;

			if(flag) q.push((node){v,f1[v]});
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
	dijkstra();
	printf("%d",f2[n]);
	return 0;
}
