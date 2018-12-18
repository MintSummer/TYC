#include<bits/stdc++.h>
using namespace std;
const int MAXN=500010;
int T,n,cnt,q[MAXN*10];
char a[1000010],b[1000010];

struct AC
{
    int son[MAXN][26],fail[MAXN],end[MAXN],vis[MAXN];
    int len,now,tmp,x,root;

    int clear()
    {
	for(int i=0;i<=26;i++) son[cnt][i]=0;
	fail[cnt]=0,end[cnt]=0;
	vis[cnt]=0;
	return cnt++;
    }

    void init()
    {
	cnt=0;
	root=clear();
    }

    void insert(char ch[])
    {
	len=strlen(ch),now=root;
	for(int i=0;i<len;i++)
	{
	    tmp=ch[i]-'a';
	    if(!son[now][tmp]) son[now][tmp]=clear();
	    now=son[now][tmp];
	}
	end[now]++;
    }

    void get_fail()
    {
	int h=0,t=0;
	q[++t]=root;
    	while(h<t)
	{
	    now=q[++h];
	    for(int i=0;i<26;i++)
		if(son[now][i])
		{
		    if(now==root) fail[son[now][i]]=root;
		    else fail[son[now][i]]=son[fail[now]][i];
		    q[++t]=son[now][i];
		}
		else 
		{
		    if(now==root) son[now][i]=root;
		    else son[now][i]=son[fail[now]][i];
		}
    	}
    }

    int search(char ch[])
    {
	int ans=0;
	len=strlen(ch),now=0;
	for(int i=0;i<len;i++)
	{
	    now=son[now][ch[i]-'a'];
	    for(int j=now;j!=root&&!vis[j];j=fail[j])
		ans+=end[j],vis[j]=1;
	}
	return ans;
    }
}ac;

int main()
{
    scanf("%d",&T);
    while(T--)
    {
	ac.init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	    scanf("%s",a),ac.insert(a);
	ac.get_fail();
	scanf("%s",b);
	printf("%d\n",ac.search(b));
    }
}
