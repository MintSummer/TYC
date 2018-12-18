#include<bits/stdc++.h>
using namespace std;
const int MAXN=10000*30+10;
int n,q[MAXN];

struct AC
{
    int son[MAXN][26],fail[MAXN],end[MAXN],len[MAXN],fa[MAXN];
    int now,tmp,length,cnt;

    void init(int f)
    {
	cnt=0;
	for(int i=0;i<26;i++) son[0][i]=0;
	fail[0]=end[0]=fa[0]=len[0]=0;
    }

    int newnode(int k)
    {
	cnt++;
	for(int i=0;i<26;i++) son[cnt][i]=0;
	fail[cnt]=end[cnt]=0;
	len[cnt]=len[k]+1;
	fa[cnt]=k;
	return cnt;
    }

    void insert(char ch[])
    {
	len=strlen(ch),now=0;
	for(int i=0;i<len;i++)
	{
	    tmp=ch[i]-'a';
	    if(!son[now][tmp]) son[now][tmp]=newnode(now);
	    now=son[now][tmp];
	}
	end[now]=1;
    }

    void get_fail()
    {
	int h=0,t=0;
	for(int i=0;i<26;i++)
	    if(son[0][i]) q[++t]=son[0][i];
	while(h<t)
	{
	    now=q[++h];
	    int f=fail[now];
	    for(int i=0;i<26;i++)
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
}ac;

int main()
{
    char ch[35];
    while(scanf("%d",&n)&&n)
    {
	ac.init();
	for(int i=1;i<=n;i++)
	    scanf("%s",ch),ac.insert(ch);
	ac.get_fail();
    }
}
