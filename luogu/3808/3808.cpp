#include<bits/stdc++.h>
using namespace std;
int cnt,q[1000010];

struct node
{
     int fail,end,son[26];
     bool vis;
}AC[1000010];

inline void insert(char st[])
{
    int len=strlen(st);
    int now=0;
    for(int i=0;i<len;i++)
    {
        int tmp=st[i]-'a';
        if(!AC[now].son[tmp]) AC[now].son[tmp]=++cnt;
        now=AC[now].son[tmp];
    }
    AC[now].end++;
}

void get_fail()
{
    int h=0,t=0;
    AC[0].fail=0;
    q[++t]=0;
    while(h<t)
    {
        int now=q[++h];
        for(int i=0;i<26;i++)
            if(AC[now].son[i])
            {
                if(now) AC[AC[now].son[i]].fail=AC[AC[now].fail].son[i];
                q[++t]=AC[now].son[i];
            }
            else AC[now].son[i]=AC[AC[now].fail].son[i];
    }
}

int ask(char st[])
{
    int len=strlen(st);
    int now=0,ans=0;
    for(int i=0;i<len;i++)
    {
        int tmp=st[i]-'a';
        now=AC[now].son[tmp];
        for(int j=now;j&&(!AC[j].vis);j=AC[j].fail)
        {
            ans+=AC[j].end;
            AC[j].vis=true;
        }
    }
    return ans;
}

int main()
{
    int n;
    char st[1000010];
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",st),insert(st);
    get_fail();
    scanf("%s",st);
    printf("%d",ask(st));
    return 0;
}
