#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(int x)
	{
		if(x<0) putchar('-'),x=-x;
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar('\n');
	}

	namespace Splay
	{
		struct node
		{
			int size,tag,val,num;
			node *fa,*son[2];
			node(){}
			node(int v,node *f):val(v),fa(f)
			{
				size=num=1,tag=0;
				son[0]=son[1]=NULL;
			}
		}*head,*space;
		#define ls root->son[0]
		#define rs root->son[1]

		inline void update(node *root)
		{
			root->size=root->num;
			if(ls) root->size+=ls->size;
			if(rs) root->size+=rs->size;
		}

		inline void pushdown(node *root)
		{
			int t=root->tag;
			if(!t) return;
			if(ls) ls->tag+=t,ls->val+=t;
			if(rs) rs->tag+=t,rs->val+=t;
			root->tag=0;
		}

		inline int dir(node *root)
		{
			return root->fa->son[0]!=root;
		}

		inline void rotate(node *root)
		{
			int d=dir(root);
			node *f=root->fa;
			if(f->fa) f->fa->son[dir(f)]=root;
			else head=root;
			root->fa=f->fa;
			f->son[d]=root->son[d^1];
			if(root->son[d^1]) root->son[d^1]->fa=f;
			f->fa=root;
			root->son[d^1]=f;
			update(f);
			update(root);
		}

		inline void splay(node *root,node *goal=NULL)
		{
			for(node *f=root->fa;f!=goal;rotate(root),f=root->fa)
				if(f->fa!=goal)
					rotate(dir(f)^dir(root)?root:f);
		}

		inline void insert(int val)
		{
			if(!head) head=new node(val,NULL);
			else
			{	
				node *root=head;
				while(true)
				{
					pushdown(root);
					if(root->val>val)
					{
						if(ls) root=root->son[0];
						else 
						{
							root->son[0]=new node(val,root);
							splay(root->son[0]);
							return;
						}
					}
					else if(root->val<val)
					{
						if(rs) root=root->son[1];
						else 
						{
							root->son[1]=new node(val,root);
							splay(root->son[1]);
							return;
						}
					}
					else 
					{
						root->size++;
						root->num++;
						splay(root);
						return;
					}
				}
			}
		}

		inline node *findkth(int k)
		{
			node *root=head;
			if(!head||k>head->size) return space;
			while(1)
			{
				pushdown(root);
				if(rs&&rs->size>=k) root=rs;
				else
				{
					if(rs) k-=rs->size;
					if(k<=root->num) return root;
					else k-=root->num,root=ls;
				}
			}	
		}

		inline node *nxt(node *root)
		{
			splay(root);
			if(!head->son[1]) return NULL;
			node *tmp=head->son[1];
			while(tmp->son[0]) tmp=tmp->son[0];
			return tmp;
		}

		inline int check(int mn)
		{
			node *ans=NULL,*root=head;
			if(!head) return 0;
			while(1)
			{
				if(!root) break;
				pushdown(root);
				if(root->val<mn) ans=root,root=rs;
				else root=ls;
			}
			if(!ans||ans->val>=mn) return 0;
			while((root=nxt(ans))&&root->val<mn) ans=root;
			splay(ans);
			int num=ans->size-(ans->son[1]?ans->son[1]->size:0);
			head=ans->son[1];
			if(head) head->fa=NULL;
			return num;
		}
	}

	void work()
	{
		int n=read(),mn=read();
		Splay::space=new Splay::node(-1,NULL);
		char ch;
		int k,tot=0;
		while(n--)
		{
			do ch=getchar(); while(!isalpha(ch));
			switch(ch)
			{
				case 'I': 
					k=read();
					if(k>=mn) Splay::insert(k);
					break;
				case 'F':
					k=read();
					write(Splay::findkth(k)->val);
					break;
				default:
					k=read()*(ch=='S'?-1:1);
					if(!Splay::head) continue;
					Splay::head->val+=k;
					Splay::head->tag+=k;
					if(ch=='S') tot+=Splay::check(mn);
			}
		}
		write(tot);
	}
}

int main()
{
	TYC::work();
	return 0;
}
