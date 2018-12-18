#include<bits/stdc++.h>
using namespace std;
int n,dp[1010];

int dfs(int x)
{
    if(dp[x]) return dp[x];
    dp[x]=1;
    for(int i=1;i<=x/2;i++)
        dp[x]+=dfs(i);
    return dp[x];
}

int main()
{
    scanf("%d",&n);
    dp[1]=1;
    printf("%d",dfs(n));
    return 0;
} 
