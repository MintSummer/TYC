#include<bits/stdc++.h>
using namespace std;
const int p=1000000007;
typedef long long ll;
int dp[610][610];
//用dp[n][h]表示有n个节点，深度小于等于h的树的个数
//因为左右子树中只要有一边深度为h-1即可，没必要都是

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

int dfs(int n,int h)
{
    if(!h) return n<=1;
    if(!n) return 1;
    if(~dp[n][h]) return dp[n][h];
    int res=0;
    for(int i=0;i<n;i++)
	res=((ll)dfs(i,h-1)*dfs(n-i-1,h-1)+res)%p;
    return dp[n][h]=res;
}

int main()
{
    int T=read();
    memset(dp,-1,sizeof(dp));
    while(T--)
    {
	int n=read(),h=read();
	if(!h) printf("%d\n",n==1);
	else printf("%d\n",(dfs(n,h)-dfs(n,h-1)+p)%p);
	//由dp的定义可以得出这里要减掉小于等于h-1的个数
    }
    return 0;
}
