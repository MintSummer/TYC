//根据那个A不掉的Matrix_tree推出来的式子
//dp[i]=(dp[i-1]*3-dp[i-2]+2)
//这道题的重点居然是高精度……难以置信……
#include<bits/stdc++.h>
using namespace std;
int n;
struct node
{
    int a[110],len;
}dp[110];

inline node mul(node x)
{
    for(int i=1;i<=x.len;i++) x.a[i]*=3;
    for(int i=1;i<=x.len;i++)
    {
	x.a[i+1]+=x.a[i]/10;
	x.a[i]%=10;
    }
    if(x.a[x.len+1]!=0) x.len++;
    return x;
}

inline node sub(node x,node y)
{
    x.a[1]+=2;//在这里+2了
    int k=1;
    while(x.a[k]>=10)
	x.a[k+1]++,x.a[k]%=10,k++;
    for(int i=1;i<=x.len;i++)
    {
	x.a[i]-=y.a[i];
	if(x.a[i]<0) x.a[i]+=10,x.a[i+1]--;
    }
    while(x.a[x.len]==0) x.len--;
    return x;
}

int main()
{
    scanf("%d",&n);
    dp[1].a[1]=1,dp[1].len=1;
    dp[2].a[1]=5,dp[2].len=1;
    
    for(int i=3;i<=n;i++)
	dp[i]=sub(mul(dp[i-1]),dp[i-2]);
    for(int i=dp[n].len;i>=1;i--)
	printf("%d",dp[n].a[i]);
    return 0;
}
