#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

namespace TYC
{
    const int MAXN=50010,p=52453;//网上找的质数,>50000就可以保证不冲突了
    int h[MAXN];

    inline int read()
    {
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    bool find(int x)
    {
		int tmp=x%p;
		int i=0;
		while(i<=p&&h[(i+tmp)%p]!=0&&h[(i+tmp)%p]!=x) i++;//找一个不冲突的位置
		if(!h[(i+tmp)%p])//x未出现过
		{
			h[(i+tmp)%p]=x;//x加进哈希表中
			return false;
		}
		return true;
    }

    void work()
    {
		int T=read();
		while(T--)
		{
			int n=read();
			memset(h,0,sizeof(h));
			while(n--)
			{
			    int x=read();
			    if(!find(x)) printf("%d ",x);
			}
			puts("");
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
