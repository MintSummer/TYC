#include<bits/stdc++.h>
using namespace std;
int n;
string a[30];

bool cmp(string x,string y)
{
	return x+y>y+x;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n,cmp);	
	for(int i=1;i<=n;i++) cout<<a[i];
	return 0;
}
