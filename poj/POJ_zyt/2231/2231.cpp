#include<iostream>
#include<algorithm>
long long n,sum[10010],a[10010],ans;

using namespace std;
int main(void)
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	sort(a,a+n);
	sum[0]=0;
	for(int i=1;i<n;i++)
		sum[i]=sum[i-1]+i*(a[i]-a[i-1]);
	for(int i=0;i<n;i++)
		ans+=sum[i];
	cout<<ans*2;
	return 0;
} 
