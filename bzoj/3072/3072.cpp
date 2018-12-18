#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
int n,a[MAXN],b[MAXN],dp[MAXN],vis[MAXN];//��dp[i]��ʾȡ��a[i]ʱ�����Ž⣬��ά�治�� 
vector<int> pos[MAXN<<1];//��2->�����52�� 
/*
�򵥵�dp����Ϊ�� dp[i][j]��ʾȡ��a[i]��b[j]ʱ�����Ž� 
1����a[i]==b[j]ʱ��dp[i][j]=min(dp[i-1][j],dp[i][j-1])+1
2����a[i]!=b[j]ʱ��dp[i][j]=dp[i-t+1][j-t+1]+t;
��ʱtΪ��i��j�����һ����ͬ��ֵ������a��bȡֵλ�����abs(i-j)��
��Ϊi��j��Ҫ����ͬһ��������Ҫ��ֵ֤��ȣ���Ҫ��֤ iԭ-i��==jԭ-j��==t
������Ԥ���������a[i]��ͬ�����ı�ţ���Ϊ��ű�Ȼ����������dpʱ���ֲ���
�ܽ��㷨Ϊ ��dp+����(��˵��Ҫ+̰�ģ�̰�ĵó���dp����) 
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
	int lt=0,rt=pos[sub].size()-1,mid,ans=-1;//sub��Ϊi��j֮�� 
	while(lt<=rt)
	{
		mid=(lt+rt)>>1;
		if(pos[sub][mid]<=x) ans=mid,lt=mid+1;
		//��pos[sub][mid]<=x(��i)ʱ, ���ʱ��pos[sub][mid]�ǺϷ��� 
		else rt=mid-1;
	}
	return ~ans?pos[sub][ans]:0;
}

int dfs(int i,int j)
{
	if(!i||!j) return i+j;//��һ���Ѿ�д���� 
	if(a[i]==b[j]) 
		return dp[i]?dp[i]:dp[i]=min(dfs(i-1,j),dfs(i,j-1))+1;
	int t=find(i-j+n,i);
	return t?dfs(t,j-i+t)+i-t:max(i,j);
	//��t==0ʱ������ʾ��ʱ��i��jǰû�з���������һ���ˣ�����ֱ��̰�ģ�˫��һ��д 
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read(),vis[b[i]]=i;
	for(int i=1;i<=n;i++)
	{
		int tmp=i-vis[a[i]]+n;//����n�Ͳ���abs�ˣ�ȥ�������ֵ�ظ����
		pos[tmp].push_back(i);
		//pos�м�¼����i��j֮��Ϊ(i-j)����һ�Ե���j��ֵ 
	}	 
	printf("%d",dfs(n,n));
	return 0;
} 
