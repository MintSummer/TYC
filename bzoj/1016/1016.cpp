/*
不同的最小生成树方案，每种权值的边的数量是确定的，每种权值的边的作用是确定的
排序以后先做一遍最小生成树，得出每种权值的边使用的数量x
然后对于每一种权值的边搜索，得出每一种权值的边选择方案
*/
#include<bits/stdc++.h>
using namespace std;
const int P=31011;
int n,m,cnt,tot,Head[110],fa[110],ans=1,sum;

struct Edge
{
    int u,v,w;
    bool operator < (const Edge &p) const
    {
	return w<p.w;
    }
}e[1010];

struct node
{
    int lt,rt,tim;
}a[1010];

inline int find(int x)
{
    return fa[x]==x?x:find(fa[x]);
}

void dfs(int id,int now,int num)
{
    if(now==a[id].rt+1)
    {
	if(num==a[id].tim) sum++;
	return;
    }

    int fu=find(e[now].u),fv=find(e[now].v);
    if(fu!=fv)
    {
	fa[fu]=fv;
	dfs(id,now+1,num+1);
	fa[fu]=fu,fa[fv]=fv;
    }

    dfs(id,now+1,num);
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++)
	scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    
    sort(e+1,e+1+m);
    int fu,fv;
    for(int i=1;i<=m;i++)
    {
	if(e[i].w!=e[i-1].w) a[cnt].rt=i-1,a[++cnt].lt=i;
	fu=find(e[i].u),fv=find(e[i].v);
	if(fu!=fv) 
	{
	    fa[fu]=fv;
	    a[cnt].tim++;
	    tot++;
	}
    }
    a[cnt].rt=m;
    if(tot!=n-1) {printf("0");return 0;}

    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=cnt;i++)
    {
	sum=0;
	dfs(i,a[i].lt,0);
	ans=(ans*sum)%P;
	for(int j=a[i].lt;j<=a[i].rt;j++)
	{
	    fu=find(e[j].u),fv=find(e[j].v);
	    if(fu!=fv) fa[fu]=fv;
	}
    }
    printf("%d",ans);
    return 0;
}
