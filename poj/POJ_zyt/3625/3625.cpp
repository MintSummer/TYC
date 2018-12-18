#include<cstdio>
#include<algorithm>
#include<cmath>
struct edge
{
	int a;
	int b;
	double v;
}e[1000010];
using namespace std;
int p[1010],cnt=0,n,m;
double ans=0;
struct point
{
	int x;
	int y;
}a[1010]; 
int f(int x)
{
	return p[x]==x?x:p[x]=f(p[x]);
}
double dis(int x,int y)
{
	return sqrt(pow((double)a[x].x-a[y].x,2.0)+
				pow((double)a[x].y-a[y].y,2.0));
}
bool cmp(edge a,edge b)
{
	return a.v<b.v;
}
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].x,&a[i].y),p[i]=i;
		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
            if(i!=j)
			e[cnt].v=dis(e[cnt].a=i,e[cnt].b=j),cnt++;
	for(int i=0;i<m;i++,cnt++)
		scanf("%d%d",&e[cnt].a,&e[cnt].b),e[cnt].v=0;
	sort(e,e+cnt,cmp);
	int done=1;
	for(int i=0;done<n&&i<cnt;i++)
	{
		int x=f(e[i].a),y=f(e[i].b);
		if(x==y)continue;
		else ans+=e[i].v,done++,p[x]=y;
    }
    printf("%.2f",ans);
    return 0;
}
