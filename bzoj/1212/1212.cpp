#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e6+10;
int n,m,cnt,q[MAXN],mxlen=0;
bool dp[MAXN];
//用dp[i]表示从0到i能否被完全匹配
//根据题意写出一个方程想要dp[j]=1当且仅当存在{k || dp[k]==1 && 存在i使得T[k+1,j]==word[i])}
char a[MAXN];

struct Trie
{
    int son[211][26],end[211];
    int now,tmp,len,x;
    
    void insert(char ch[])
    {
        len=strlen(ch),now=0;
	mxlen=max(mxlen,len);
        for(int i=0;i<len;i++)
        {
            tmp=ch[i]-'a';
            if(!son[now][tmp]) son[now][tmp]=++cnt;
            now=son[now][tmp];
        }
        end[now]=1;
    }
    
    int search(int s,int e)
    {     
	int now=0;
        for(int i=s;i<=e;i++)
        {
	    tmp=a[i]-'a';
            if(!son[now][tmp]) return 0;
            now=son[now][tmp];
        }
        return end[now];
    }
}trie;

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) 
        scanf("%s",a),trie.insert(a);
    for(int i=1;i<=m;i++) 
    {
	scanf("%s",a);
	memset(dp,false,sizeof(dp));
	int len=strlen(a),ans=0;
	for(int j=0;j<len;j++)
	    for(int k=max(j-mxlen,-1);k<=j;k++)
		if((k==-1||dp[k])&&trie.search(k+1,j))
		{
		    dp[j]=1,ans=j+1;//到第j位均可匹配，长度为j+1
		    break;
		}
	printf("%d\n",ans);
    }
    return 0;
} 


