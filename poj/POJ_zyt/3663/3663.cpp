#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[20010],n,s,ans;
int main(void)
{
	cin>>n>>s;
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	sort(a,a+n);
	for(int i=0;i<n;i++)
	{
		if(a[i]>=s)break;
		for(int j=i+1;j<n;j++)
			if(a[i]+a[j]<=s)ans++;
			else break;
	}
	cout<<ans;
	return 0;
}
