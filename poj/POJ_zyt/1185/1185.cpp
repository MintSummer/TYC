#include<cstdio>
#include<algorithm>
#include<iostream>
#include<string>
using namespace std;
int map[110],n,m,st[100],k,dp[110][100][100],num[100];
bool judge1(int x)
{
	return !((x&(x<<1))||(x&(x<<2)));
}
bool judge2(int i,int j)
{
	return !(map[i]&st[j]);
}
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int j=0;j<m;j++)
		{
			char c=s[j];
			if(c=='H')map[i]+=1<<j;
		}
	}
	for(int i=0;i<(1<<m);i++)
		if(judge1(i))
		{
			st[k]=i;
			int a=i;
			while(a>0)
			{
				if(a%2!=0)num[k]++;
				a/=2;
			}
			k++;
		}
	for(int i=0;i<k;i++)
		if(judge2(1,i))
			dp[1][i][0]=num[i];
	if(n>1)
		for(int j=0;j<k;j++)
		{
			if(judge2(2,j))
			{
				for(int f=0;f<k;f++)
						if(judge2(1,f)&&!(st[j]&st[f]))
							dp[2][j][f]=max(dp[2][j][f],dp[1][f][0]+num[j]);
			}
		}
	for(int i=3;i<=n;i++)
	{
		for(int j=0;j<k;j++)
		{
			if(judge2(i,j))
			{
				for(int f=0;f<k;f++)
					if(judge2(i-1,f)&&!(st[j]&st[f]))
						for(int g=0;g<k;g++)
							if(judge2(i-2,g)&&!(st[j]&st[g])&&!(st[f]&st[g]))
								dp[i][j][f]=max(dp[i][j][f],dp[i-1][f][g]+num[j]);
			}
		}
	} 
	int ans=0;
	for(int i=0;i<k;i++)
		for(int j=0;j<k;j++)
			ans=max(dp[n][i][j],ans);
	printf("%d",ans);
	return 0;
}
