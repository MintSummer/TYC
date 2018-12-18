#include<bits/stdc++.h>
using namespace std;
const int MAXN=30010;
int n,cnt;
char ch[MAXN];

struct AC
{
    int son[MAXN][2],fail[MAXN],end[MAXN],q[MAXN],vis[MAXN],ins[MAXN];
    void insert(char ch[])
    {
        int len=strlen(ch),now=0;
        for(int i=0;i<len;i++)
        {
            int tmp=ch[i]-'0';
            if(!son[now][tmp]) son[now][tmp]=++cnt;
            now=son[now][tmp];
        }
        end[now]=1;
    }
    void get_fail()
    {
        int h=0,t=0;
        for(int i=0;i<2;i++)
            if(son[0][i]) q[++t]=son[0][i];
        while(h<t)
        {
            int now=q[++h],f=fail[now];
            if(end[f]) end[now]=1;
            for(int i=0;i<2;i++)
            {
                int x=son[now][i];
                if(x)
                {
                    fail[x]=son[f][i];
                    q[++t]=x;
                }
                else son[now][i]=son[f][i];
            }
        }
    }
    bool dfs(int u)
    {
        ins[u]=1;//vis记录是否访问过，ins记录是否在栈中
        for(int i=0;i<2;i++)
        {
            int v=son[u][i];
	    if(ins[v]) return true;
            if(end[v]||vis[v]) continue;
	    vis[v]=1;
            if(dfs(v)) return true;
        }
        ins[u]=0;
        return false;
    }
}ac;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
	scanf("%s",ch),ac.insert(ch);
    ac.get_fail();
    if(ac.dfs(0)) printf("TAK");
    else printf("NIE");
    return 0;
}