#include<iostream>
#include<algorithm>
using namespace std;
int n,a[10010];
int main(void)
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	sort(a,a+n);
	cout<<a[n/2];
	return 0;
}
