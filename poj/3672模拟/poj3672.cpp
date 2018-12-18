#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
int m,t,u,f,d;
int s[100010];

int main()
{
	scanf("%d%d%d%d%d",&m,&t,&u,&f,&d);
	char ch;
	int sum=0,ans=0;
	for(int i=1;i<=t;i++)
	  {
	  	cin>>ch;
	  	if(ch=='u') s[i]=u+d;//上坡去，下坡回
	  	if(ch=='f') s[i]=f+f;
	  	if(ch=='d') s[i]=d+u;
		sum+=s[i];
	  	if(sum>m) break;
	  	else ans++;
	  }
	printf("%d",ans);
	return 0;
}

