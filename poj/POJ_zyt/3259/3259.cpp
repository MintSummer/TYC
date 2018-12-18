#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
struct
{
	int to;
	int next;
	int v;
}e[5210];
int head[510],num[510],vis[510],dis[510],n,m,w,f,cnt;
void add(int a,int b,int c)
{
	e[cnt].to=b;
	e[cnt].next=head[a];
	e[cnt].v=c;
	head[a]=cnt++;
}
bool spfa()
{
	memset(num,0,sizeof(num));
	memset(vis,0,sizeof(vis));
	dis[1]=0;
	for(int i=2;i<=n;i++)dis[i]=0x3f3f3f3f;
	queue <int>q;
	q.push(1);
	vis[1]=num[1]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i!=-1;i=e[i].next)
		{
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].v)
			{
				dis[v]=dis[u]+e[i].v;
				if(!vis[v])
				{
					if(++num[v]>n)return true;
					q.push(v);
					vis[v]=true;
				}
			}
		}
	}
	return false;
}
int main(void)
{
	cin>>f;
	while(f--)
	{
		memset(e,0,sizeof(e));
		memset(head,-1,sizeof(head));
		cnt=0;
		
		cin>>n>>m>>w;
		for(int i=0;i<m;i++)
		{
			int a,b,c;
			cin>>a>>b>>c;
			add(a,b,c);
			add(b,a,c);
		}
		for(int i=0;i<w;i++)
		{
			int a,b,c;
			cin>>a>>b>>c;
			add(a,b,-c);
		}
		if(spfa())cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}

