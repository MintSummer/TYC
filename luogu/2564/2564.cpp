#include<bits/stdc++.h>
using namespace std;
int n,k,t,a,num=1,ans=0x3f3f3f3f,cnt=0;
int vis[100];

struct point
{
	int col,x;
}p[1000010];

bool cmp(point a,point b)
{
	return a.x<b.x;
}

int main()
{
	memset(vis,0,sizeof(vis));
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&t);
		while(t--)
		{	
			scanf("%d",&a);
			p[++cnt].col=i;
			p[cnt].x=a;
		}
	}
	sort(p+1,p+cnt+1,cmp);
	for(int l=1,r=0;l<=n;l++)//滑动窗口，l代表左端，r代表右端
	{
		vis[p[l-1].col]--;
		if(vis[p[l-1].col]<=0) num--;
		while(r<=n&&num<k)
		{
			r++;
			if(vis[p[r].col]==0) num++;			
			vis[p[r].col]++;
		}
		if(num==k) ans=min(ans,p[r].x-p[l].x);
	}
	printf("%d",ans);
	return 0;	
}
