#include<cstdio>
#include<algorithm>
using namespace std;
int p[2010],n,m;
struct edge
{
	int a;
	int b;
	int v;
}e[10010];
int find(int x)
{
	return p[x]==x?x:p[x]=find(p[x]);
}
bool cmp(edge x,edge y)
{
	return x.v<y.v;
}
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		e[i]={a,b,c};
	}
	sort(e,e+m,cmp);
	for(int i=1;i<=n;i++)p[i]=i;
	for(int i=0,cnt=0;i<m;i++)
	{
		int u=e[i].a,v=e[i].b,w=e[i].v;
		int x=find(u),y=find(v);
		if(x!=y)cnt++,p[x]=y;
		if(cnt==n-1)
		{
			printf("%d",w);
			return 0;
		}	
	}
}
