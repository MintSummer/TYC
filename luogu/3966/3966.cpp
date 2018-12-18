#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000005;
char a[MAXN],b[MAXN+200];
int n,cnt,tim[210],all,same[210];
queue<int> q;

struct AC
{
    int son[MAXN][26],fail[MAXN],end[MAXN],start[MAXN];
    int tmp,now,len,x;

    void insert(char ch[],int num)
    {
	now=0,len=strlen(ch);

	for(int i=0;i<len;i++)
	    b[all+i]=ch[i];
	all+=len;
	b[all++]='#';

	for(int i=0;i<len;i++)
	{
	    tmp=ch[i]-'a';
	    if(!son[now][tmp]) son[now][tmp]=++cnt;
	    now=son[now][tmp];
	}
    	if(!end[now]) end[now]=num;
	same[num]=end[now];
	//same[num]记录和num的末尾字母一样的单词，显然该单词一定是编号最小的
    }

    void get_fail()
    {
	for(int i=0;i<26;i++)
	    if(son[0][i]) q.push(son[0][i]);
	while(!q.empty())
	{
	    now=q.front();
	    q.pop();
	    for(int i=0;i<26;i++)
	    {
		x=son[now][i];
		if(x)
		{
		    fail[x]=son[fail[now]][i];
		    start[x]=end[fail[x]]?fail[x]:start[fail[x]];
    		    q.push(x);
		}
		else son[now][i]=son[fail[now]][i];
	    }
	}
    }

    void search()
    {
	now=0;
	for(int i=0;i<all;i++)
	{
	    if(b[i]=='#') {now=0;continue;}
	    now=son[now][b[i]-'a'];
	    if(end[now]) tim[end[now]]++;
	    for(int j=start[now];j;j=start[j]) tim[end[j]]++;
	}
    }
}ac;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
	scanf("%s",a),ac.insert(a,i);
    ac.get_fail();
    ac.search();
    for(int i=1;i<=n;i++)
	printf("%d\n",tim[same[i]]);
    return 0;
}
