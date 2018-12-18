#include<iostream>
#include<cmath>
using namespace std;
int s,t,r,n,k;
int main(void)
{
	cin>>n>>k;
	for(int i=0;i<k;i++)
	{
		cin>>s>>t>>r;
		int done=0,time=0;
		while(1)
		{
			if((done+s*t)>=n)
			{
				cout<<ceil((double)(n-done)/s+time)<<endl;
				break;
			}
			done+=s*t;
			time+=t+r;
		}
	}
	return 0;
}
