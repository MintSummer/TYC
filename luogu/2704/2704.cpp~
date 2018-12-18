#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=(1<<10)+10;
    int n,m,cnt,G[105],ok[MAXN],num[MAXN],dp[105][MAXN][MAXN],mx;
    char ch[15];

    int count(int x)
    {
		int sum=0;
		while(x) sum+=(x&1),x>>=1;
		return sum;
    }

    bool check1(int x,int line)
    {
		return !(x&(x<<1)||x&(x<<2)||x&(x>>1)||x&(x>>2));
    }

    void work()
    {
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",ch);
			for(int j=0;j<m;j++)
			G[i]+=(ch[m-j-1]=='H')*(1<<j);
		}
		for(int i=0;i<(1<<m);i++)
			if(check1(i,1)) 
			{
				ok[i]=1;
				num[i]=count(i);
				dp[1][0][i]=num[i];
				mx=max(mx,i);
			}
		for(int i=0;i<=mx;i++) 
			if(ok[i]&!(i&G[1]))
				for(int j=0;j<=mx;j++) 
					if(ok[j]&&!(i&j)&&!(j&G[2])) 
						dp[2][i][j]=max(dp[2][i][j],dp[1][0][i]+num[j]);
		for(int i=3;i<=n;i++)
			for(int j=0;j<=mx;j++) 
				if(ok[j]&&!(j&G[i]))
					for(int k=0;k<=mx;k++) 
						if(ok[k]&&!(j&k)&&!(k&G[i-1]))
							for(int g=0;g<(1<<m);g++)
								if(ok[g]&&!(j&g)&&!(k&g)&&!(g&(G[i-2])))
									dp[i][k][j]=max(dp[i][k][j],dp[i-1][g][k]+num[j]);
		int ans=0;
		for(int i=0;i<(1<<m);i++) 
			if(ok[i])
				for(int j=0;j<(1<<m);j++) 
					if(ok[j]&&!(i&j))
						ans=max(dp[n][i][j],ans);
		printf("%d",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
