#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
const int N=50010,inf=0x3f3f3f3f;
int bin[35];

namespace Trie
{
    int cnt,son[N*35][2],val[N*35];

    void insert(int &root,int last,int v)
    {
		root=++cnt;
		int tmp=root;
		for(int i=30;i>=0;i--)
		{
			int t=(v&bin[i]);t>>=i;
			son[root][!t]=son[last][!t];
			val[root]=val[last]+1;
			son[root][t]=++cnt;
			root=son[root][t];
			last=son[last][t];
		}
		val[root]=val[last]+1;
		root=tmp;
    }

    int query(int x,int y,int v)
    {
		int ans=0;
		for(int i=30;i>=0;i--)
		{
			int t=(v&bin[i]);t>>=i;
			if(val[son[y][!t]]>val[son[x][!t]])
				ans+=bin[i],x=son[x][!t],y=son[y][!t];
			else x=son[x][t],y=son[y][t];
		}
		return ans;
    }
}

namespace TYC
{
    int n,root[N];
    set<int> s;
    set<int>::iterator L,R;

    struct node
    {
		int val,pos;
		bool operator < (const node &x) const
		{
			return val>x.val;
		}//按权值降序排序.从大到小加入,用set找到当前数x后继的后继的位置r,和前驱的前驱的位置l.
    }a[N];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void work()
    {
		n=read();
		bin[0]=1;
		for(int i=1;i<=30;i++) bin[i]=bin[i-1]<<1;
		for(int i=1;i<=n;i++)
		{
			a[i].val=read(),a[i].pos=i;
			Trie::insert(root[i],root[i-1],a[i].val);
		}
		sort(a+1,a+1+n);
		s.insert(-2),s.insert(-1),s.insert(inf),s.insert(inf+1);
		s.insert(a[1].pos);
		int ans=0;
		for(int i=2;i<=n;i++)
		{
			L=R=s.lower_bound(a[i].pos);
			L--,L--,R++;
			int l=*L+1,r=*R-1;
			//满足x是次小值的区间只有 前驱的前驱+1到后继 或者 前驱到后继的后继-1
			//所以,可以对x产生影响的区间为 前驱的前驱+1到后继的后继-1
			l=max(l,1),r=min(r,n);
			if(l!=r) ans=max(ans,Trie::query(root[l-1],root[r],a[i].val));
			s.insert(a[i].pos);
		}
		printf("%d",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
