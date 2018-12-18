//tyc
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int sum[210];

int main()
{
    memset(sum,0,sizeof(sum));
    int s1,s2,s3,s,ans=0;
    scanf("%d%d%d",&s1,&s2,&s3);
    for(int i=1;i<=s1;i++)
      for(int j=1;j<=s2;j++)
        for(int k=1;k<=s3;k++)
	{
	    s=i+j+k;
	    sum[s]++;
	    if(sum[s]>sum[ans]||(sum[s]==sum[ans]&&ans>s)) ans=s;
	}
    printf("%d",ans);
    return 0;
}
