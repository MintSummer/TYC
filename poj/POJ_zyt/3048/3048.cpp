#include<iostream>
using namespace std;
int n,check[20010],p[10000],tot;
void prime(void)
{
	for(int i=2;i<=20000;i++)
	{
		if(!check[i])p[tot++]=i;
		for(int j=0;j<tot;j++)
		{
			if(i*p[j]>20000)break;
			check[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
int main(void)
{
	int ans=0,m,j;
	prime();
	cin>>n;
	cin>>ans;
	for(j=tot-1;j>=0;j--)
		if(ans%p[j]==0)break;
	m=j;
	for(int i=1;i<n;i++)
	{
		int a,j;
		cin>>a;
		for(j=tot-1;j>=0;j--)
			if(a%p[j]==0)break;
		if(j>m)m=j,ans=a;
	}
	cout<<ans;
	return 0;
}
