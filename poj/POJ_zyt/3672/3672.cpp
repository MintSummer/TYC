#include<iostream>
using namespace std;
int main(void)
{
	int m,t,u,f,d,time=0;
	cin>>m>>t>>u>>f>>d;
	for(int i=0;i<t;i++)
	{
		char a;
		int t1;
		cin>>a;
		if(a=='u')t1=time+u+d;
		if(a=='f')t1=time+f+f;
		if(a=='d')t1=time+d+u;
		if(t1>m)
		{
			cout<<i;
			return 0;
		}
		time=t1;
	}
} 
