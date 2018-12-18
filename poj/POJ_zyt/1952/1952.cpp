#include<iostream>
#include<algorithm>
using namespace std;
int n,p[5010],ans,num[5010];
struct day
{
	int id;
	int l;
};
day dp[5010];
bool cmp(const day &d1,const day &d2)
{
	return d1.l<d2.l;
}
int main(void)
{
	cin>>n;
	for(int i=0;i<n;i++)cin>>p[i];
	dp[0].l=1;
	dp[0].id=0;
	num[0]=1;
	for(int i=1;i<n;i++)
	{
		dp[i].id=i;
		dp[i].l=1;
		num[i]=1;
		for(int k=i-1;k>=0;k--)
			if(p[k]>p[i])
				if(dp[i].l<dp[k].l+1)dp[i].l=dp[k].l+1,num[i]=num[k];
				else {if(dp[i].l==dp[k].l+1)num[i]+=num[k];}
			else if(p[k]==p[i])
			{
				if(dp[i].l==1)num[i]=0;
				break;
			}
	}
	sort(dp,dp+n,cmp);
	cout<<dp[n-1].l<<" ";
	for(int i=n-1;i>=0;i--)
		if(dp[i].l==dp[n-1].l)ans+=num[dp[i].id];
	cout<<ans;
	return 0;
}
