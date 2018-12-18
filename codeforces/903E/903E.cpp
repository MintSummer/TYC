#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1010,MX=(1<<16)-1,inf=0x3f3f3f3f;
	int n,cost[6],row[N],bin[20],num[6][6],dp[N][MX+100];
	vector<int> mark[6];
	char str[6][N];
	
	inline int square(int siz,int r)
	{
		int ans=0;
		for(int i=0;i<siz;i++)
			for(int j=1;j<=siz;j++)
				ans|=bin[num[r+i][j]];
		return ans;
	}
	
	void init()
	{
		bin[1]=1;
		for(int i=2;i<=16;i++) bin[i]=bin[i-1]<<1;
		
		int tot=0;
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
				num[j][i]=++tot;
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=4;j++)
				if(str[j][i]=='*') row[i]|=bin[j];
				
		for(int siz=1;siz<=4;siz++)
			for(int i=1;i+siz-1<=4;i++)
					mark[siz].push_back(MX^square(siz,i));
	}
	
	void work()
	{
		scanf("%d",&n);
		for(int i=1;i<=4;i++) scanf("%d",&cost[i]);
		for(int i=1;i<=4;i++) scanf("%s",str[i]+1);
		init();
		int fir=0,tmp=0;
		for(int i=1;i<=min(4,n);i++) fir=fir|(row[i]<<((i-1)*4));
		for(int i=1;i<=12;i++) tmp|=bin[i];
		memset(dp,inf,sizeof(dp));
		dp[1][fir]=0;
		for(int i=1;i<=n;i++)
			for(int s=MX;s>=0;s--)
				if(dp[i][s]!=inf)
				{
					if(!(s&15))
					{
						int d=(s>>4)|(row[i+4]<<12);
						dp[i+1][d]=min(dp[i+1][s],dp[i][s]);
					}
					for(int siz=1;i+siz-1<=n;siz++)
						for(int j=0;j<mark[siz].size();j++)
						{
							int k=mark[siz][j];
							if((s&k)!=s)
								dp[i][s&k]=min(dp[i][s&k],dp[i][s]+cost[siz]);
						}
				}
		printf("%d\n",dp[n][0]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
