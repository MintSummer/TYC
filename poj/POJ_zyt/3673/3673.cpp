#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;
int ans,a[20],b[20];
string sa,sb;
int main(void)
{
	cin>>sa>>sb;
	for(int i=0;i<sa.size();i++)
		a[i]=atoi(sa.substr(i,1).c_str());
	for(int i=0;i<sb.size();i++)
		b[i]=atoi(sb.substr(i,1).c_str());
	for(int i=0;i<sa.size();i++)
		for(int j=0;j<sb.size();j++)
			ans+=a[i]*b[j];
	cout<<ans;
	return 0;
}
