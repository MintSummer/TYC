#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n;
int s[8010],b[8010],now[8010];
//b表示前面有几头标号更靠前的牛
//s[i]表示第i头牛的标号
//now[i]表示此时标号为i的是队列中的第now[i]头牛

//说实话这道题标解是线段树或树状数组，但我不会
//所幸暴力能解决 
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	  scanf("%d",&b[i]);
	s[1]=1,now[1]=1;
	int pos;
	for(int i=2;i<=n;i++)
	  {
	  	if(b[i]==i-1) 
		  {s[i]=i;now[i]=i;continue;}
	  	pos=b[i]+1;
	  	for(int j=i-1;j>=pos;j--) 
		  s[now[j]]++,now[j+1]=now[j];
	  	now[pos]=i;
	  	s[i]=pos;
	  }
	for(int i=1;i<=n;i++)
	  printf("%d\n",s[i]);
	return 0;
}
