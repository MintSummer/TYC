#include<iostream>
using namespace std;
int n,s,out[30][30];
int main(void)
{
	cin>>n>>s;
	s--;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			if((++s)%10==0)j--;
			else out[j][i]=s%10;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)cout<<"  ";
		for(int j=i;j<n;j++)
			cout<<out[i][j]<<" ";
		cout<<out[i][n]<<endl;
	}
	return 0;
} 
