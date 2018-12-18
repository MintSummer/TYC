#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
int n,a[MAXN],b[MAXN],dp[MAXN],vis[MAXN];//用dp[i]表示取到a[i]时的最优解，二维存不下 
vector<int> pos[MAXN<<1];//乘2->详见第52行 
/*
简单的dp方程为： dp[i][j]表示取到a[i]、b[j]时的最优解 
1、当a[i]==b[j]时，dp[i][j]=min(dp[i-1][j],dp[i][j-1])+1
2、当a[i]!=b[j]时，dp[i][j]=dp[i-t+1][j-t+1]+t;
此时t为离i、j最近的一对相同的值，且在a、b取值位置相差abs(i-j)的
因为i、j需要减掉同一个数，既要保证值相等，又要保证 i原-i现==j原-j现==t
可以先预处理出来和a[i]相同的数的编号，因为编号必然单调，故在dp时二分查找
总结算法为 ：dp+二分(据说还要+贪心，贪心得出的dp方程) 
*/ 

inline int read()
{
	int x=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}

inline int find(int sub,int x) 
{
	int lt=0,rt=pos[sub].size()-1,mid,ans=-1;//sub即为i、j之差 
	while(lt<=rt)
	{
		mid=(lt+rt)>>1;
		if(pos[sub][mid]<=x) ans=mid,lt=mid+1;
		//当pos[sub][mid]<=x(即i)时, 则此时的pos[sub][mid]是合法的 
		else rt=mid-1;
	}
	return ~ans?pos[sub][ans]:0;
}

int dfs(int i,int j)
{
	if(!i||!j) return i+j;//有一边已经写完了 
	if(a[i]==b[j]) 
		return dp[i]?dp[i]:dp[i]=min(dfs(i-1,j),dfs(i,j-1))+1;
	int t=find(i-j+n,i);
	return t?dfs(t,j-i+t)+i-t:max(i,j);
	//当t==0时，即表示此时在i、j前没有符合条件的一对了，可以直接贪心，双手一起写 
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read(),vis[b[i]]=i;
	for(int i=1;i<=n;i++)
	{
		int tmp=i-vis[a[i]]+n;//加上n就不用abs了，去掉差绝对值重复情况
		pos[tmp].push_back(i);
		//pos中记录的是i、j之差为(i-j)的那一对的中j的值 
	}	 
	printf("%d",dfs(n,n));
	return 0;
} 
