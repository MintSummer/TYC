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
    int val,mx,size;
    int tagadd,tagrev;
    node *fa,*son[2];
}*head;

inline void update(node *root)
{
    root->size=1,root->mx=root->val;
    for(int i=0;i<2;i++)
	if(root->son[i])
	{
	    node *nxt=root->son[i];
	    root->mx=max(root->mx,nxt->mx);
	    root->size+=nxt->size;
	}
}

inline void pushdown(node *root)
{
    if(root==NULL) return;
    if(!root->tagadd&&!root->tagrev) return;
    for(int i=0;i<2;i++)
	if(root->son[i])
	{
	    node *nxt=root->son[i];
	    nxt->tagadd+=root->tagadd;
	    nxt->val+=root->tagadd,nxt->mx+=root->tagadd;
	    if(root->tagrev) swap(nxt->son[0],nxt->son[1]);
	    nxt->tagrev^=root->tagrev;
	}
    root->tagrev=root->tagadd=0;
}

inline int getdir(node *root)
{
    return root==root->fa->son[1];
}

inline void rotate(node *root)
{
    node *f=root->fa,*ff=f->fa;
    int d=getdir(root);
    if(ff!=NULL) ff->son[getdir(f)]=root;
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
    while(root!=NULL&&root->fa!=to)
    {
	node *f=root->fa,*ff=f->fa;
	if(ff==to) rotate(root);
	else if(getdir(root)^getdir(f))
	    rotate(root),rotate(root);
	else rotate(f),rotate(root);
    }
}

inline node *create(int val,node *f)
{
    node *p=new node;
    p->val=p->mx=val;
    p->size=1;
    p->tagadd=p->tagrev=0;
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

inline void insert(int val,int pos)
{
    if(head==NULL)
    {
        head=create(val,NULL);
        head->son[0]=create(-inf,head);
        head->son[1]=create(-inf,head);
        update(head);
        return;
    }
    node *pre=findkth(pos-1),*nxt=findkth(pos);
    splay(pre,NULL),splay(nxt,pre);
    pre->son[1]=create(val,pre);
    nxt->fa=pre->son[1];
    pre->son[1]->son[1]=nxt;
    update(pre->son[1]);
    update(pre);
}

inline node *interval(int lt,int rt)
{
    node *pre=findkth(lt-1),*nxt=findkth(rt+1);
    splay(pre,NULL),splay(nxt,pre);
    return nxt->son[0];
}

inline void add(int lt,int rt,int val)
{
    node *root=interval(lt,rt);
    root->tagadd+=val;
    root->mx+=val,root->val+=val;
}

inline void reverse(int lt,int rt)
{
    node *root=interval(lt,rt);
    root->tagrev^=1;
    swap(root->son[0],root->son[1]);
}

inline int ask(int lt,int rt)
{
    return interval(lt,rt)->mx;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) insert(0,i);
    int opt,x,y,k;
    while(m--)
    {
	opt=read();
	if(opt==1) x=read(),y=read(),k=read(),add(x,y,k);
	else if(opt==2) x=read(),y=read(),reverse(x,y);
	else x=read(),y=read(),printf("%d\n",ask(x,y));
    }
    return 0;
}
