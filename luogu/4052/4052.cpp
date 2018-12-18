/*
AC自动机+dp
题意是给出一些字符串，求长为m的字符串包含这些的一共有多少个，字符集A-Z
首先运用补集转换，转而求不含这些串的个数，最后用26^M减掉就行
根据输入的字符串建立AC自动机
dp[i][j]表示当前考虑了i位，当前停留在AC自动机的j号节点
每一次可以由dp[i][j]转移到dp[i+1][k]，k是枚举第i+1为后作为j的儿子在AC自动机上的编号
枚举k，就是第i+1为填什么，然后进行下列操作：
首先看看这位能不能填k，判断方法是从j开始向fail[j]跳，看是不是有一个j有一个k儿子，并且k儿子上还有结束标记，只要有一个就证明如果i+1位填k就会让整个字符串出现AC自动机上的字符串，所以不能填k
如果能放，再看看要修改哪个dp数组。
还是从j开始向fail[j]跳，如果j有k这个儿子就直接修改dp[i+1][j的k儿子]就好
每次修改要对修改目标加上dp[i][j]
答案是所有dp[m][x]（x是所有AC自动机上的节点）的和
*/ 
#include<bits/stdc++.h>
using namespace std;
const int p=10007;
const int MAXN=6010;
int n,m,cnt,dp[1010][MAXN];

struct AC
{
	int son[MAXN][26],fail[MAXN],end[MAXN],q[MAXN];
	void insert(char ch[])
	{
		int len=strlen(ch),now=0;
		for(int i=0;i<len;i++)
		{
			int tmp=ch[i]-'A';
			if(!son[now][tmp]) son[now][tmp]=++cnt;
			now=son[now][tmp];
		}
		end[now]=1;
	}
	
	void get_fail()
	{
		int h=0,t=0;
		for(int i=0;i<26;i++) 
			if(son[0][i]) q[++t]=son[0][i];
		while(h<t)
		{
			int now=q[++h],f=fail[now];
			if(end[f]) end[now]=1;
			for(int i=0;i<26;i++) 
				if(son[now][i]) 
				{
					fail[son[now][i]]=son[f][i];
					q[++t]=son[now][i];
				}
				else son[now][i]=son[f][i];
		}
	}
	int DP()
	{
		dp[0][0]=1;
		for(int i=0;i<m;i++)
			for(int j=0;j<=cnt;j++) if(!end[j])
				for(int k=0;k<26;k++) if(!end[son[j][k]])
					dp[i+1][son[j][k]]=(dp[i][j]+dp[i+1][son[j][k]])%p;
		int ans=0;
		for(int i=0;i<=cnt;i++)
			ans=(ans+dp[m][i])%p;
		return ans;
	}
}ac;

int main()
{
	scanf("%d%d",&n,&m);
	char ch[110];
	for(int i=1;i<=n;i++)
		scanf("%s",ch),ac.insert(ch);
	ac.get_fail();
	int ans=1;
	for(int i=1;i<=m;i++) ans=(ans*26)%p;
	printf("%d",(ans-ac.DP()+p)%p);
	return 0;
} 
