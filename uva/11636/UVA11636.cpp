#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
	int n,c=1;
	while(scanf("%d",&n)&&n>0) 
	  printf("Case %d: %d\n",c++,(int)ceil(log2(n)));
	return 0;
}
