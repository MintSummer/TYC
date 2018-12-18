#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;

namespace TYC
{
    const int MAXN=110010;
    char a[MAXN],s[MAXN<<1];
    int n,len,ans,p[MAXN<<1];

    void manacher()
    {
		int maxright=0,mid=0;
		for(int i=1;i<n;i++)
		{
			if(i<maxright)
				p[i]=min(p[(mid<<1)-i],maxright-i);
			else p[i]=1;
			while(1<=i-p[i]&&i+p[i]<=n&&s[i-p[i]]==s[i+p[i]])
				p[i]++;
			if(i+p[i]>maxright) 
				maxright=i+p[i],mid=i;
		}
    }

    void work()
    {
		while(~scanf("%s",a))
		{
			memset(p,0,sizeof(p));
			len=strlen(a);
			s[0]=s[1]='#';
			for(int i=0;i<len;i++)
				s[i*2+2]=a[i],s[i*2+3]='#';
			n=len*2+2;
			s[n]='#';
			manacher();
			ans=0;
			for(int i=1;i<n;i++) ans=max(ans,p[i]);
			printf("%d\n",ans-1);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
