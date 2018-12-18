#include<bits/stdc++.h>
using namespace std;
int n,m,num[360],dp[45][45][45][45],g[5];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&num[i]);
    int x;
    for(int i=1;i<=m;i++) scanf("%d",&x),g[x]++;
    dp[0][0][0][0]=num[1];
    for(int a=0;a<=g[1];a++)
	for(int b=0;b<=g[2];b++)
	    for(int c=0;c<=g[3];c++)
		for(int d=0;d<=g[4];d++)
		{
		    int r=a+b*2+c*3+d*4+1;
		    if(a) dp[a][b][c][d]=max(dp[a][b][c][d],dp[a-1][b][c][d]+num[r]);
		    if(b) dp[a][b][c][d]=max(dp[a][b][c][d],dp[a][b-1][c][d]+num[r]);
		    if(c) dp[a][b][c][d]=max(dp[a][b][c][d],dp[a][b][c-1][d]+num[r]);
		    if(d) dp[a][b][c][d]=max(dp[a][b][c][d],dp[a][b][c][d-1]+num[r]);
		}
    printf("%d",dp[g[1]][g[2]][g[3]][g[4]]);
    return 0;
}
