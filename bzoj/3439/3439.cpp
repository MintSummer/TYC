//将字符串倒着插入Trie树中,节点的kpm串即为其子树代表的串,主席树查询第k小
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N=100010,L=300010,inf=0x3f3f3f3f;
string s;

namespace Trie
{
    int now,cnt,num,son[L][26],root[L],sum,st[N],end[N],val[N];
    vector<int> belong[L];

    void insert(int id)
    {
		int len=s.size();now=0;
		sum+=len;
		for(int i=len-1;i>=0;i--)
		{
			int tmp=s[i]-'a';
			if(!son[now][tmp]) son[now][tmp]=++cnt;
			now=son[now][tmp];
		}
		belong[now].push_back(id);
    }

    void dfs(int u)
    {
		if(belong[u].size())
		{
		    for(int i=0;i<belong[u].size();i++)
			st[belong[u][i]]=num;//此时st记的num实际上是空的,val[num]没有值
		    for(int i=0;i<belong[u].size();i++)
			val[++num]=belong[u][i];
		}
		for(int i=0;i<26;i++)
			if(son[u][i]) dfs(son[u][i]);
		if(belong[u].size()) 
		    for(int i=0;i<belong[u].size();i++) end[belong[u][i]]=num;
    }
}

namespace Tree
{
    int cnt,ls[N*20],rs[N*20],val[N*20];

    void insert(int &root,int last,int l,int r,int v)
    {
		root=++cnt;
		val[root]=val[last]+1;
		ls[root]=ls[last],rs[root]=rs[last];
		if(l==r) return;
		int mid=(l+r)>>1;
		if(v<=mid) insert(ls[root],ls[last],l,mid,v);
		else insert(rs[root],rs[last],mid+1,r,v);
    }

    int query(int x,int y,int l,int r,int k)
    {
		if(l==r) return l;//直接返回l,lr本身即为权值
		int mid=(l+r)>>1,tmp=val[ls[y]]-val[ls[x]];
		if(k<=tmp) return query(ls[x],ls[y],l,mid,k);
		else return query(rs[x],rs[y],mid+1,r,k-tmp);
    }
}

namespace TYC
{
    int n,root[N];

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>s;
			Trie::insert(i);
		}
		Trie::dfs(0);
		for(int i=1;i<=n;i++)
			Tree::insert(root[i],root[i-1],1,n,Trie::val[i]);
		int k;
		for(int i=1;i<=n;i++)
		{   
			cin>>k;
			int x=Trie::st[i],y=Trie::end[i];//这里的x不要减1,这是已经不算起点的区间了
			if(y-x<k) puts("-1");
			else printf("%d\n",Tree::query(root[x],root[y],1,n,k));
		}
	}
}

int main()
{
    TYC::work();
    return 0;
}
