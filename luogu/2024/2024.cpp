#include<bits/stdc++.h>
using namespace std;
int n,m,fa[50010],num[50010];
//对于这三种种类，同类可以用0表示，其他两种分别用1表示该结点被父节点吃，2表示该节点吃父节点


int find(int a)
{
	if(a!=fa[a])
	{
		int f=fa[a];
		fa[a]=find(fa[a]);
		num[a]=(num[a]+num[f])%3;
	}
	return fa[a];
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i,num[i]=0;
	int opt,x,y,ans=0,fx,fy;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&opt,&x,&y);
		if(x>n||y>n) ans++;
		else if(opt==2&&x==y) ans++;
		else 
		{
			fx=find(x),fy=find(y);
			if(fx==fy) {if(num[y]!=(num[x]+(opt-1))%3) ans++;}
			else 
			{
				fa[fy]=fx;
				num[fy]=(3+num[x]-num[y]+(opt-1))%3;
			}
		}
	}
	printf("%d",ans);
	return 0;
}
