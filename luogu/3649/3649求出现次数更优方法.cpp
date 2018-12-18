#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=300010;
    char s[MAXN];
    int tot,Head[MAXN];

    struct PAM
    {
		int even,odd,cnt,now,son[MAXN][26],size[MAXN],len[MAXN],fail[MAXN];
		PAM()
		{
			odd=++cnt,even=++cnt;
			fail[odd]=fail[even]=odd;
			len[odd]=-1,len[even]=0;
			now=even;
		}
		void insert(int pos,char c)
		{
			while(s[pos-1-len[now]]!=c) now=fail[now];//否则当pos==0的时候-1会越界
			if(!son[now][c-'a'])
			{
				son[now][c-'a']=++cnt;
				len[cnt]=len[now]+2;
				if(now==odd) fail[cnt]=even;
				else 
				{
					int tmp=fail[now];
					while(s[pos-1-len[tmp]]!=c) tmp=fail[tmp];
					fail[cnt]=son[tmp][c-'a'];
				}
			}
			now=son[now][c-'a'];
			size[now]++;
		}
    }pam;

    void work()
    {
		scanf("%s",s+1);//一定要从1开始
		int len=strlen(s+1);
		for(int i=1;i<=len;i++) 
			pam.insert(i,s[i]);
		for(int i=pam.cnt;i;i--) pam.size[pam.fail[i]]+=pam.size[i];
		ll ans=0;
		for(int i=1;i<=pam.cnt;i++)
			ans=max(ans,(ll)pam.size[i]*pam.len[i]);
		printf("%lld",ans);
	}
}

int main()
{
    TYC::work();
    return 0;
}
