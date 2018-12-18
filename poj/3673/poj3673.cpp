#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int A,B,ans=0;
int a[20],b[20];

int main()
{
	cin>>A>>B;
	int la=0,lb=0;
	while(A)
	  {
	  	la++;
	  	a[la]=A%10;
	  	A/=10;
	  }
	while(B)
	  {
	  	lb++;
	  	b[lb]=B%10;
	  	B/=10;
	  }
	for(int i=1;i<=la;i++)
	  for(int j=1;j<=lb;j++)
	    {
	    	ans+=a[i]*b[j];
	    }
	cout<<ans;
	return 0;
}