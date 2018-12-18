#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000000+10;
char a[MAXN],b[MAXN];
int fail[MAXN];

void get_fail(char ch[])
{
    fail[0]=fail[1]=0;
    int len=strlen(ch);
    for(int i=1;i<len;i++)
    {
		int tmp=fail[i];
		while(tmp&&ch[i]!=ch[tmp])
			tmp=fail[tmp];
		fail[i+1]=(ch[i]==ch[tmp])?tmp+1:0;
    }
}

void ask(char find[],char ch[])
{   
    int tmp=0;
    int l1=strlen(find),l2=strlen(ch);
    for(int i=0;i<l1;i++)
    {
		while(tmp&&find[i]!=ch[tmp])
			tmp=fail[tmp];
		if(find[i]==ch[tmp]) tmp++;
		if(tmp==l2)
			printf("%d\n",i-l2+2);
    }
}

int main()
{
    scanf("%s%s",a,b);
    get_fail(b);
    ask(a,b);
    int len=strlen(b);
    for(int i=1;i<=len;i++)
		printf("%d ",fail[i]);
    return 0;
}
