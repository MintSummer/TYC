#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10;
int n,m,f[MAXN][20];

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

inline void init()
{
    int k=(int)ceil(log2(n));
    for(int j=1;j<=k;j++)
	for(int i=1;i+(1<<j)-1<=n;i++)
	    f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}

inline int ask(int lt,int rt)
{
    int p=log2(rt-lt+1);
    return max(f[lt][p],f[rt-(1<<p)+1][p]);
}

int main()
{
   n=read(),m=read();
   for(int i=1;i<=n;i++) f[i][0]=read();
   init();
   while(m--)
   {
       int lt=read(),rt=read();
       printf("%d\n",ask(lt,rt));
   }
   return 0;
}
