#include<iostream>  
#include<cstdio>  
using namespace std;  
#define INF -999999999  
#define N 200005  
#define pos 100000  
#define max(a,b) (a)>(b)?(a):(b)  
int dp[N];  
int minn,maxn;  
int main()  
{  
   int n,i,j,s,t,ans;  
   while(scanf("%d",&n)!=EOF)  
   {  
       for(i=0;i<N;i++) dp[i]=INF;  
       dp[pos]=0;  
       minn=maxn=pos;  
      for(i=0;i<n;i++)  
      {  
         scanf("%d%d",&s,&t);  
         if(s>0)  
         {  
            for(j=maxn;j>=minn;j--)  
                dp[j+s]=max(dp[j+s],dp[j]+t);  
            maxn=maxn+s;  
         }  
          else  
          {  
              for(j=minn;j<=maxn;j++)  
                  dp[j+s]=max(dp[j+s],dp[j]+t);  
             minn=minn+s;  
          }  
      }  
      ans=0;  
       for(i=pos;i<=maxn;i++)  
         if(dp[i]>=0) ans=max(ans,i-pos+dp[i]);  
         printf("%d\n",ans);  
   }  
   return 0;  
}  