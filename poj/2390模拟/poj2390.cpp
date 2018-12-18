#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
double r,m;
int y,ans;

int main()
{
	scanf("%lf%lf%d",&r,&m,&y);
	r=r/100;
	for(int i=1;i<=y;i++) 
	  m=(1+r)*m;
	printf("%d",(int)m);
	return 0;
}