#include<iostream>
using namespace std;
int main(void)
{
	double r,m,y;
	cin>>r>>m>>y;
	while(y--)
		m=m*(1+r/100);
	cout<<(int)m;
	return 0;
} 
