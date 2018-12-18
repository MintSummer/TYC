#include<cstring>
#include<cstdio>
using namespace std;
int n,m,dp[20][10000],st[10000],k;
int map[20];
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		int a;
		scanf("%d",&a);
		if(a==0)map[i]+=1<<(j-1);
	}
	for(int i=0;i<(1<<m);i++)
		if(!(i&(i<<1)))
			st[k++]=i;
	for(int i=0;i<k;i++)
		if((map[1]&st[i])==0)dp[1][i]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j<k;j++)
		{
			if((map[i]&st[j])==0)
			{
				for(int f=0;f<k;f++)
					if(!(map[i-1]&st[f])&&!(st[j]&st[f]))
						dp[i][j]+=dp[i-1][f];
			}
		}
	}
	int ans=0;
	for(int i=0;i<k;i++)
		ans+=dp[n][i],ans%=100000000;
	printf("%d",ans);
	return 0;
}
