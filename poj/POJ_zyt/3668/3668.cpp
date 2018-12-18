#include<iostream>
#include<set>
using namespace std;
set<double>s;
int x[300],y[300];
int zero;
int n;
int main(void)
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>x[i]>>y[i];
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
		{
			if(x[i]==x[j])
				zero=1;
			else
				s.insert((y[i]-y[j])/(double)(x[i]-x[j]));
		}
	cout<<s.size()+zero;
	return 0;
}
