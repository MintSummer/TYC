//����dp[i][j]��ʾ��i�˵�ʱ�򵽵�j¥��ķ������� 
//ת�Ʒ���dp[i][j] += dp[i-1][k] (k = 1,��.,n) 
//�Ե�ǰ��O(n^3)�����Ż������Է��ִ�һ��λ���ܵ���λ��Ϊһ������
//����ǰ׺�ͺͲ�֣���j�ܵ�������Ϊl~r���͸�dp[i+1][l]+dp[i][j],dp[i+1][r+1]-dp[i][j]
//����ǰ׺�ͼ��� 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace TYC
{
	const int p=1e9+7,N=5010;
	int dp[N][N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	void add(int now,int l,int r,int val)
	{
		dp[now][l]=(dp[now][l]+val)%p;
		dp[now][r]=(dp[now][r]-val+p)%p;//����ע�ⲻҪ���ɸ��� 
	}
	
	void work()
	{
		int n=read(),a=read(),b=read(),k=read();
		dp[0][a]=1;//��� 
		for(int i=0;i<k;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(j==b) continue;
				int tmp=abs(j-b)-1;
				int l=max(j-tmp,1),r=min(j+tmp,n);
				add(i+1,l,j,dp[i][j]);
				add(i+1,j+1,r+1,dp[i][j]);//j���ܵ�j 
				//����ǰ��ֵ����ʱ���Ҳ��õ�i+1����Ӱ���i��Ĵ𰸣�Ȼ������¸��ǵ�i+1�� 
			}
			int sum=0;
			for(int j=1;j<=n;j++)
			{
				sum=(sum+dp[i+1][j])%p;
				dp[i+1][j]=sum;//���³�ǰ׺�͵�ʵ��ֵ 
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			ans=(ans+dp[k][i])%p;
		printf("%d",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
