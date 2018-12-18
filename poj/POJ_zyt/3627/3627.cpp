#include<iostream>
#include<algorithm> 
#include<functional>
using namespace std;
int n,b,ans,h[20010];
int main(void)
{
	cin>>n>>b;
	for(int i=0;i<n;i++)
		cin>>h[i];
	sort(h,h+n,greater<int>());
	for(int sum=0;sum<b;sum+=h[ans++]);
	cout<<ans;
	return 0;
} 
