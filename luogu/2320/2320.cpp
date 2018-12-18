#include<bits/stdc++.h>
using namespace std;

bool cmp(int x,int y)
{
	return x<y;
}

int main()
{
	long long n,cnt=0,a[1000010];
	cin>>n;
	while(n>0)
	{
		if(n%2==0) a[++cnt]=n/2;
		else a[++cnt]=(n+1)/2;
		n/=2;
	}
	sort(a+1,a+cnt+1,cmp);
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
		cout<<a[i]<<' ';
	return 0;
}
