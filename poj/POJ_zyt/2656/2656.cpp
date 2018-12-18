#include<iostream>
#include<algorithm>
using namespace std;
int main(void)
{
	while(1)
	{
		int n,maxvalue=-1,maxid=0;
		cin>>n;
		if(n==0)return 0;
		for(int i=0;i<n;i++)
		{
			int a,b;
			cin>>a>>b;
			if(maxvalue<a+b)
				maxvalue=a+b,maxid=i;
		}
		if(maxvalue<=8)cout<<0<<endl;
		else cout<<maxid+1<<endl;
	}
	return 0;
} 
