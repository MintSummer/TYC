#include<bits/stdc++.h>
using namespace std;
int n,m,mx=0;

struct door
{
    int op,x;
}a[100010];

int Get(int d)
{
    for(int i=1;i<=n;i++)
    switch(a[i].op)
    {
        case 1: d&=a[i].x;break;
        case 2: d|=a[i].x;break;
        case 3: d^=a[i].x;break;
    }
    return d;
}

int main()
{
    scanf("%d%d",&n,&m);
    char ch[5];
    for(int i=1;i<=n;i++)
    {
        scanf("%s%d",ch,&a[i].x);
        if(ch[0]=='A') a[i].op=1;
        else if(ch[0]=='O') a[i].op=2;
        else a[i].op=3;
    }
    int ans=0;
    for(int i=30;i>=0;i--)
    {
        //贪心：从最高位开始，争取这一位为i
        if(ans+(1<<i)>m) continue;
        if(Get(ans)<Get(ans+(1<<i)))
            ans+=(1<<i);
    }
    printf("%d",Get(ans));
    return 0;
}
