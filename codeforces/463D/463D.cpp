#include<bits/stdc++.h>
using namespace std;
int n,k,a[6][1010],pos[6][1010],dp[1010],id[1010];
//pos[i][j]记录在第i个串中j出现的位置
//dp[i]表示以i结尾的最长串

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
	scanf("%d",&a[1][i]);
	pos[1][i]=i;
	id[a[1][i]]=i;//离散化保证搜出的串为升序（好像不用这么写的样子）
    }
    for(int i=2;i<=k;i++)
	for(int j=1;j<=n;j++)
	{
	    scanf("%d",&a[i][j]);
	    pos[i][id[a[i][j]]]=j;
	}
    int ans=0;
    for(int i=1;i<=n;i++)
    {
	for(int j=0;j<i;j++)
	{
	    bool flag=true;
	    for(int d=1;d<=k;d++)
		if(pos[d][i]<=pos[d][j]) 
		    {flag=false;break;}
	    //当所有的j都在i前面时，j就可以接在i后
	    if(flag) dp[i]=max(dp[i],dp[j]+1); 
	}
	ans=max(ans,dp[i]);
    }
    printf("%d",ans);
    return 0;
}
