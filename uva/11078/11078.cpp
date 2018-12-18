#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int T,N;

int main()
{
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--)
    {
	cin>>N;
	int mx,ans=-0x3f3f3f3f;
	cin>>mx;
	for(int i=2;i<=N;i++)
	{
	    int a;
	    cin>>a;
	    ans=max(ans,mx-a);
	    mx=max(mx,a);
	}
	cout<<ans<<endl;
    }
}
