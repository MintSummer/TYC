#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int MAXN=51000100;
    typedef long long ll;
    char s[MAXN<<1],a[MAXN];
    int ans,n,p[MAXN];

    void manacher()
    {
		int maxright=0,mid=0;
		for(int i=1;i<n;i++)
		{
			if(i<maxright) 
				p[i]=min(p[(mid<<1)-i],maxright-i);
			else p[i]=1;
			while(1<=i-p[i]&&i+p[i]<=n&&s[i-p[i]]==s[i+p[i]]) p[i]++;
			if(i+p[i]>maxright) 
				maxright=i+p[i],mid=i;
		}
    }

    void work()
    {
		scanf("%s",a);
		s[0]='#',s[1]='#';
		int len=strlen(a);
		for(int i=0;i<len;i++)
			s[i*2+2]=a[i],s[i*2+3]='#';
		n=len*2+2;
		s[n]='#';
		manacher();
		for(int i=0;i<=n;i++) ans=max(ans,p[i]);
		printf("%d",ans-1);
    }
}

int main()
{
    TYC::work();
    return 0;
}
