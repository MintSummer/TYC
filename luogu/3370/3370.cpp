#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int n;
char s[10010];
ull base=131,a[10010];

ull hash(char ch[])
{
    int len=strlen(ch);
    ull ans=0;
    for(int i=0;i<len;i++)
	ans=ans*base+(ull)ch[i];
    return ans&0x7fffffff;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
	scanf("%s",s);
	a[i]=hash(s);
    }
    sort(a+1,a+1+n);
    int tot=0;
    for(int i=2;i<=n+1;i++)
	if(a[i]!=a[i-1]) tot++;
    printf("%d\n",tot);
    return 0;
}
