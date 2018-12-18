#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,c,ans;
struct coin
{
	int v;
	int b;
};
coin a[30];
bool cmp(coin a,coin b)
{
	return a.v<b.v;
}
int main(void)
{
	scanf("%d%d",&n,&c);
	for(int i=0;i<n;i++)
	{
		int v,b;
		scanf("%d%d",&v,&b);
		a[i]={v,b};
	}
	sort(a,a+n,cmp);
	int tmp,first=0;
	for(tmp=n-1;tmp>=0;tmp--)
	{
		if(a[tmp].v<c)break;
		else ans+=a[tmp].b,a[tmp].b=0;
	}
	while(1)
	{
		int need[30];
		memset(need,0,sizeof(need));
		int sum=0;
		for(int i=tmp;i>=first;i--)
		{
			int x=min((c-sum)/a[i].v,a[i].b);
			sum+=x*a[i].v;
			need[i]+=x;
		}
		for(int i=first;i<=tmp&&sum<c;i++)
		{
			int x=min((int)ceil((c-sum)/(double)a[i].v),a[i].b-need[i]);
			sum+=x*a[i].v;
			need[i]+=x;
		}
		if(sum>=c)
		{
			ans++;
			for(int i=tmp;i>=first;i--)
			{
				a[i].b-=need[i];
				if(i==tmp&&a[i].b==0)tmp--;
			}
			while(a[first].b==0&&first<=tmp)first++;
		}
		else break;
	}
	printf("%d",ans);
	return 0;
}
