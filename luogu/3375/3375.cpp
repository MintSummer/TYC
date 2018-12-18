#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
char a[MAXN],b[MAXN];
int next[MAXN],la,lb;

void get_next()
{
    int k=0;
    next[1]=0;
    for(int i=2;i<=lb;i++)
    {
	while(k&&b[i]!=b[k+1]) k=next[k];
	if(b[k+1]==b[i]) k++;
	next[i]=k;
    }
}

void kmp()
{
    for(int i=1,j=0;i<=la;i++)
    {
	while(j&&b[j+1]!=a[i]) j=next[j];
	if(b[j+1]==a[i]) j++;
	if(j==lb) {printf("%d\n",i-lb+1);}
    }
}

int main()
{
    scanf("%s%s",a+1,b+1);
    la=strlen(a+1),lb=strlen(b+1);
    get_next();
    kmp();
    for(int i=1;i<=lb;i++) printf("%d ",next[i]);
    return 0;
}
