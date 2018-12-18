/*
AC�Զ���+dp
�����Ǹ���һЩ�ַ�������Ϊm���ַ���������Щ��һ���ж��ٸ����ַ���A-Z
�������ò���ת����ת���󲻺���Щ���ĸ����������26^M��������
����������ַ�������AC�Զ���
dp[i][j]��ʾ��ǰ������iλ����ǰͣ����AC�Զ�����j�Žڵ�
ÿһ�ο�����dp[i][j]ת�Ƶ�dp[i+1][k]��k��ö�ٵ�i+1Ϊ����Ϊj�Ķ�����AC�Զ����ϵı��
ö��k�����ǵ�i+1Ϊ��ʲô��Ȼ��������в�����
���ȿ�����λ�ܲ�����k���жϷ����Ǵ�j��ʼ��fail[j]�������ǲ�����һ��j��һ��k���ӣ�����k�����ϻ��н�����ǣ�ֻҪ��һ����֤�����i+1λ��k�ͻ��������ַ�������AC�Զ����ϵ��ַ��������Բ�����k
����ܷţ��ٿ���Ҫ�޸��ĸ�dp���顣
���Ǵ�j��ʼ��fail[j]�������j��k������Ӿ�ֱ���޸�dp[i+1][j��k����]�ͺ�
ÿ���޸�Ҫ���޸�Ŀ�����dp[i][j]
��������dp[m][x]��x������AC�Զ����ϵĽڵ㣩�ĺ�
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
