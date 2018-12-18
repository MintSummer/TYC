#include<cstdio>
#include<algorithm>
using namespace std;
struct edge
{
	int a;
	int b;
	int v;
}e[10010];
int n,cnt,p[110],ans;
int f(int x)
{
	return p[x]==x?x:p[x]=f(p[x]);
}
bool cmp(const edge a,const edge b)
{
	return a.v<b.v;
}
int main(void)
{
	while(scanf("%d",&n)==1)
	{
		ans=cnt=0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				int a;
				scanf("%d",&a);
				e[cnt++]={i,j,a};
			}
			p[i]=i;
		}
		sort(e,e+cnt,cmp);
		for(int i=0;i<cnt;i++)
		{
			int u=e[i].a,v=e[i].b,w=e[i].v;
			int x=f(u),y=f(v);
			if(x!=y)
			{
				ans+=w;
				p[x]=y;
			}
		}
		printf("%d\n",ans);
	}
}
