#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int t,n,a[50010];
bool cmp(int a,int b)
{
	return abs(a)<abs(b);
}
int main(void)
{
	cin>>t>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1,cmp);
	int sum=0,i=1;
	for(;sum<=t;i++)
		sum+=abs(a[i]-a[i-1]);
	cout<<i-2;
	return 0;
}
