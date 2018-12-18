#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=5e5+10,inf=2147483647;

namespace Treap
{
    int cnt;

    struct node
    {
		int ls,rs,val,size,key;
    }tree[N*50];
    //中序遍历val从小到大,根据key排大根堆

    void update(int root)
    {
		tree[root].size=tree[tree[root].ls].size+tree[tree[root].rs].size+1;
    }

    int merge(int a,int b)
    {
		if(!a||!b) return a+b;
		if(tree[a].key>tree[b].key)
		{
			int root=++cnt;
			tree[root]=tree[a];
			tree[root].rs=merge(tree[root].rs,b);
			update(root);
			return root;
		}
		else 
		{
			int root=++cnt;
			tree[root]=tree[b];
			tree[root].ls=merge(a,tree[root].ls);
			update(root);
			return root;
		}
    }

    void split(int root,int val,int &l,int &r)//分离,左边区间值均<=val,右边值均>val
    {
		if(!root) l=0,r=0;
		else
		{
			if(tree[root].val<=val)//root和其左子树均在左树中
			{
				l=++cnt;
				tree[l]=tree[root];
				split(tree[l].rs,val,tree[l].rs,r);//讨论root的右子树
				update(l);
			}
			else
			{
				r=++cnt;
				tree[r]=tree[root];
				split(tree[r].ls,val,l,tree[r].ls);
				update(r);
			}
		}
    }

    void newnode(int &root,int val)
    {
		root=++cnt;
		tree[root].val=val;
		tree[root].size=1;
		tree[root].key=rand();
    }

    void insert(int &root,int val)
    {
		int l=0,r=0,now=0;
		split(root,val,l,r);//根据val的值分成两棵树
		newnode(now,val);//根据当前val建一棵新树
		root=merge(merge(l,now),r);//将这三棵树合并成一棵
    }

    void Delete(int &root,int val)
    {
		int l=0,r=0,now=0;
		split(root,val,l,r);//分成1~val和val+1~r两棵
		split(l,val-1,l,now);//分成1~val-1和val两棵
		//now的这棵树全部权值为val
		now=merge(tree[now].ls,tree[now].rs);//删除树now的根,即将now的左右两子树合并即可
		root=merge(merge(l,now),r);
    }

    int get_rank(int root,int val)//查找在root这棵树中值val的排名
    {
		int l=0,r=0;
		split(root,val-1,l,r);//分成1~val-1和val~r两棵
		int ans=tree[l].size+1;//1~val-1这棵树的size+1就刚好是值val
		root=merge(l,r);//还原
		return ans;
    }

    int get_kth(int root,int k)//找到root这棵树中排名为k的数的值
    {
		while(1)
		{
			int lsize=tree[tree[root].ls].size;
			if(k<=lsize) root=tree[root].ls;
			else if(k==lsize+1) return tree[root].val;
			else k-=lsize+1,root=tree[root].rs;
		}
    }

    int get_pre(int &root,int val)//前驱
    {
		int l=0,r=0,ans;
		split(root,val-1,l,r);//1~val-1和val~r
		if(!l) ans=-inf;//不存在
		int k=tree[l].size;//要查找1~val-1这棵树上最大的一个数(即第size个)
		ans=get_kth(l,k);
		root=merge(l,r);//还原
		return ans;
    }

    int get_next(int &root,int val)//后继,同于前驱
    {
		int l=0,r=0,ans;
		split(root,val,l,r);
		if(!r) ans=inf;
		ans=get_kth(r,1);
		root=merge(l,r);
		return ans;
    }
}

namespace TYC
{
    int root[N];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void work()
    {
		int n=read();
		for(int i=1;i<=n;i++)
		{
			int Edition=read(),opt=read(),x=read();
			root[i]=root[Edition];
			switch(opt)
			{
				case 1: Treap::insert(root[i],x);break;
				case 2: Treap::Delete(root[i],x);break;
				case 3: printf("%d\n",Treap::get_rank(root[i],x));break;
				case 4: printf("%d\n",Treap::get_kth(root[i],x));break;
				case 5: printf("%d\n",Treap::get_pre(root[i],x));break;
				case 6: printf("%d\n",Treap::get_next(root[i],x));break;
			}
		}
    }
}

int main()
{
    //freopen("3835.in","r",stdin);
    TYC::work();
    return 0;
}
