#include<bits/stdc++.h>
using namespace std;
const int MAXN=10010;
int n,m,f[MAXN],ans;
struct yanshu
{
	int tim,x,y;
}a[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	int t,x,y;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&t,&x,&y);
		a[i].tim=t,a[i].x=x,a[i].y=y;
		f[i]=1;
		for(int j=i-1;j>=1;j--)
			if(abs(x-a[j].x)+abs(y-a[j].y)<=t-a[j].tim) f[i]=max(f[i],f[j]+1);
		ans=max(ans,f[i]);
	}
	printf("%d",ans);
	return 0;
}
