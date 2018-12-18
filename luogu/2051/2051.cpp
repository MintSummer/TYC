#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p=9999973;
int n,m,cnt;
ll dp[110][110][110];
//因为每行每列最多有2个棋子
//dp[i][j][k]表示放了前i行，有j列是有1个棋子，有k列有两个棋子

ll C(int x,int k)//取两个位置的时候用上组合数C(x,2)
{
    return x*(x-1)/2;
}

int main()
{
    scanf("%d%d",&n,&m);
    dp[0][0][0]=1;
    for(int i=0;i<n;i++)//每多加一行，就可以最多加2个棋子
		for(int j=0;j<=m;j++)//有一个棋子
			for(int k=0;j+k<=m;k++)//有两个棋子
				if(dp[i][j][k])
				{
					//不放棋子
					dp[i+1][j][k]=(dp[i+1][j][k]+dp[i][j][k])%p;
					//只放一个棋子
					if(m-j-k>=1) 
						dp[i+1][j+1][k]=(dp[i+1][j+1][k]+dp[i][j][k]*(m-j-k)%p)%p;//在没有棋子的地方放一个
					if(j>=1)
						dp[i+1][j-1][k+1]=(dp[i+1][j-1][k+1]+dp[i][j][k]*j%p)%p;//在原本就有一个棋子的地方放一个
					//放两个棋子
					if(m-j-k>=2)
						dp[i+1][j+2][k]=(dp[i+1][j+2][k]+dp[i][j][k]*C(m-j-k,2)%p)%p;//在没有棋子的地方放两个
					if(j>=2)
						dp[i+1][j-2][k+2]=(dp[i+1][j-2][k+2]+dp[i][j][k]*C(j,2)%p)%p;//在原本就有一个棋子的地方放两个
					if(m-j-k>=1&&j>=1)
						dp[i+1][j][k+1]=(dp[i+1][j][k+1]+dp[i][j][k]*(m-j-k)%p*j%p)%p;
				}
    ll ans=0;
    for(int i=0;i<=m;i++)//枚举有一个棋子的列
		for(int j=0;j<=m;j++)//枚举有两个棋子的列
			ans=(ans+dp[n][i][j])%p;
    printf("%lld",ans);
    return 0;
}
