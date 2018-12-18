#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
	const int N=300010;
	int n,a[N];
	
	void work()
	{
		cin>>n;
		for(int i=0;i<n;i++) cin>>a[i];
		int i=0,j=1,k=0;
		while(i<n&&j<n&&k<n)
		{
			int t=a[(i+k)%n]-a[(j+k)%n];
			if(!t) k++;
			else
			{
				if(t>0) i+=k+1;
				else j+=k+1;
				if(i==j) j++;
				k=0;
			}
		}
		int start=i<j?i:j;
		for(int i=0;i<n;i++)
			cout<<a[(start+i)%n]<<" ";
	}
}

int main()
{
	TYC::work();
	return 0;
}
