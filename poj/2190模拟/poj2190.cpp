#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<string>
using namespace std;
string st;
int ans=-1,sum=0,m;

int main()
{
	cin>>st;
	for(int i=0;i<=9;i++)
	  {
	  	if(st[i]<='9'&&st[i]>='0') 
		  sum+=(st[i]-'0')*(10-i);	  	
	  	if(st[i]=='X') 
		  sum+=10*(10-i);
	  	if(st[i]=='?') 
		  m=10-i;
	  }
	for(int i=0;i<=9;i++)
	  if((sum+i*m)%11==0) 
	    {
	    	printf("%d",i);
	    	return 0;
	    }
	if(m==1&&(sum+10)%11==0) 
	  {
	  	printf("X");//当此时为10时，应当输出的为X
	  	return 0;
	  }
	printf("%d",-1);
	return 0;
}