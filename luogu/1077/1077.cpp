#include<bits/stdc++.h>
using namespace std;
const int P=1000007;
int n,m,a[110],dp[110][110];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<=n;i++) dp[i][0]=1;
    for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	    for(int k=0;k<=min(a[i],j);k++)
		dp[i][j]=(dp[i][j]+dp[i-1][j-k])%P;
    printf("%d",dp[n][m]);
    return 0;
}
