//详细题解:https://blog.csdn.net/ACVector/article/details/77951928
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

namespace PAM
{
    typedef long long ll;
    const int MAXN=200010;
    int last[2];//记左右
    int s[MAXN],cnt,odd,even,now,fail[MAXN],son[MAXN][26],len[MAXN],num[MAXN],lt,rt;
    ll ans=0;
    
    inline int newnode(int l)
    {
		++cnt;
		for(int i=0;i<26;i++) son[cnt][i]=0;
		num[cnt]=fail[cnt]=0;
		len[cnt]=l;
		return cnt;
    }
    
    inline void init(int n)
    {
		memset(s,-1,sizeof(s));		
		ans=cnt=0;
		odd=newnode(-1),even=newnode(0);
		fail[odd]=fail[even]=odd;
		lt=n,rt=n-1;
		now=even;
		last[0]=last[1]=1;
    }

    inline int getfail(int x,int d)
    {
		if(d==0) while(s[lt+len[x]+1]!=s[lt]) x=fail[x];
		else while(s[rt-len[x]-1]!=s[rt]) x=fail[x];
		return x;
    }

    inline int insert(int c,int d)
    {
		if(d==0) s[--lt]=c;
		else s[++rt]=c;
		now=getfail(last[d],d);
		if(!son[now][c])
		{
			son[now][c]=newnode(len[now]+2);
			if(now==odd) fail[cnt]=even;
			else fail[cnt]=son[getfail(fail[now],d)][c];
			num[cnt]=num[fail[cnt]]+1;//神方法%
		}
		now=son[now][c];
		last[d]=now;
		if(len[now]==rt-lt+1) last[d^1]=last[d];//判断当前全部串是否为回文串,左右端点合并节点
		return num[now];
    }
}

namespace TYC
{
    void work()
    {
		using namespace PAM;
		int n,opt;
		char c[10];
		while(~scanf("%d",&n))
		{
			init(n);
			while(n--)
			{
				scanf("%d",&opt);
				switch(opt)
				{
					case 1: scanf("%s",c);ans+=insert(c[0]-'a',1);break;
					case 2: scanf("%s",c);ans+=insert(c[0]-'a',0);break;
					case 3: printf("%d\n",cnt-2);break;
					case 4: printf("%lld\n",ans);break;
				}
			}
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
