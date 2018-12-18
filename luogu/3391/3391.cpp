#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
int n,m;

int read()
{
	int x=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}

struct node
{
	int val,tag,size;
	node *fa,*son[2];
}*head;

inline void update(node *root)
{
	root->size=1;
	for(int i=0;i<2;i++)
		if(root->son[i]) root->size+=root->son[i]->size;
}

inline void pushdown(node *root)
{
	if(root==NULL) return;
	if(!root->tag) return;
	for(int i=0;i<2;i++)
		if(root->son[i])
		{
			node *nxt=root->son[i];
			swap(nxt->son[0],nxt->son[1]);
			nxt->tag^=root->tag;
		}
	root->tag=0;
}

inline int getdir(node *root)
{
	return root==root->fa->son[1];
}

inline void rotate(node *root)
{
	node *f=root->fa,*ff=f->fa;
	int d=getdir(root);
	if(ff) ff->son[getdir(f)]=root;
	else head=root;
	root->fa=ff;
	
	f->son[d]=root->son[d^1];
	if(root->son[d^1]) root->son[d^1]->fa=f;
	
	root->son[d^1]=f;
	f->fa=root;
	
	update(f);
	update(root);
}

inline void splay(node *root,node *to)
{
	while(root&&root->fa!=to)
	{
		node *f=root->fa,*ff=f->fa;
		if(ff==to) rotate(root);
		else if(getdir(f)^getdir(root)) 
			rotate(root),rotate(root);
		else rotate(f),rotate(root);
	}
}

inline node *create(int x,node *f)
{
	node *p=new node;
	p->val=x;
	p->tag=0,p->size=1;
	p->fa=f;
	p->son[0]=p->son[1]=NULL;
	return p;
}

inline node *findkth(int k)
{
	node *root=head;
	k++;
	while(1)
	{
		pushdown(root);
		node *lt=root->son[0],*rt=root->son[1];
		if(lt)
		{
			if(lt->size+1<k) k-=lt->size+1,root=rt;
			else if(lt->size>=k) root=lt;
			else return root;
		}
		else if(k==1) return root;
		else k--,root=rt;
	}
}

inline void insert(int x,int pos)
{
	if(head==NULL)
	{
		head=create(x,NULL);
		head->son[0]=create(-inf,head);
		head->son[1]=create(-inf,head);
		update(head);
		return;
	}
	node *pre=findkth(pos-1),*nxt=findkth(pos);
	splay(pre,NULL),splay(nxt,pre);
	pre->son[1]=create(x,pre);
	pre->son[1]->son[1]=nxt;
	nxt->fa=pre->son[1];
	update(pre->son[1]);
	update(pre);
}

inline void reverse(int lt,int rt)
{
	node *pre=findkth(lt-1),*nxt=findkth(rt+1);
	splay(pre,NULL),splay(nxt,pre);
	node *root=nxt->son[0];
	root->tag^=1;
	swap(root->son[0],root->son[1]);
}

int main()
{
	n=read(),m=read();
	int lt,rt;
	for(int i=1;i<=n;i++) insert(i,i);
	for(int i=1;i<=m;i++) lt=read(),rt=read(),reverse(lt,rt);
	for(int i=1;i<=n;i++) printf("%d ",findkth(i)->val);
	return 0;
} 
