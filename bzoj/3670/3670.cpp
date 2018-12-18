//讲解https://blog.csdn.net/qpswwww/article/details/44937169
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1000000+10;
const int p=1000000007; 
char ch[MAXN];
int T,len,fail[MAXN],num[MAXN];

void get_num()
{
    fail[0]=-1,fail[1]=0;
    num[0]=0,num[1]=1;
    int tmp=0;
    for(int i=1;i<len;i++)
    {
    	while(tmp>=0&&ch[i]!=ch[tmp])
    	    tmp=fail[tmp];
    	fail[i+1]=++tmp;
    	num[i+1]=num[tmp]+1;
    }
}

void get_ans()
{
    ll ans=1LL;
    int tmp=0;
    for(int i=0;i<len;i++)
    {
    	while(tmp>=0&&ch[i]!=ch[tmp]) 
    	    tmp=fail[tmp];
    	tmp++;
    	while((tmp<<1)>(i+1))
    	    tmp=fail[tmp];
    	ans=(ll)ans*(num[tmp]+1)%p;
    }
    printf("%lld\n",ans);
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
    scanf("%s",ch);
    len=strlen(ch);
    get_num();
    get_ans();
    }
    return 0;
}
