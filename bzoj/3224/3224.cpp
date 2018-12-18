#include<bits/stdc++.h>
using namespace std;

struct node
{
    node *lt,*rt,*fa;
    int val,size,cnt;
};
node *head;

inline node *create(node *f,int x)
{
    node *h=new node;
    h->lt=h->rt=NULL;
    h->cnt=h->size=1;
    h->val=x;
    h->fa=f;
    return h;
}

inline void update(node *root)
{
    if(root)
      {
      	root->size=root->cnt;
      	if(root->lt)
      	  root->size+=root->lt->size;
      	if(root->rt)
      	  root->size+=root->rt->size;
      }
}

void left_ro(node *root)
{
    node *f=root->fa,*ff=f->fa;
    root->fa=ff;
    if(ff)
      {
      	if(ff->lt == f) ff->lt=root;
      	else ff->rt=root;
      }
    else head=root;
    
    f->rt = root->lt;
    if(root->lt) root->lt->fa=f;
    
    root->lt=f;
    f->fa=root;
    
    update(f);
    update(root);
}

void right_ro(node *root)
{
    node *f=root->fa,*ff=f->fa;
    root->fa=ff;
    if(ff)
      {
      	if(ff->lt == f) ff->lt=root;
      	else ff->rt=root;
      }
    else head=root;
    
    f->lt = root->rt;
    if(root->rt) root->rt->fa=f;
    
    root->rt=f;
    f->fa=root;
    
    update(f);
    update(root);
}

void splay(node *root)
{
    while(root && root->fa)
      {
      	node *f=root->fa,*ff=f->fa;
        if(ff==NULL)
          if(f->lt==root) right_ro(root);
          else left_ro(root);
        else
          {
          	if(ff->lt == f && f->lt == root)
          	  right_ro(f),right_ro(root);
          	else if(ff->rt == f && f->rt == root)
          	  left_ro(f),left_ro(root);
          	else if(ff->lt == f && f->rt == root)
          	  left_ro(root),right_ro(root);
          	else if(ff->rt == f && f->lt == root)
          	  right_ro(root),left_ro(root);
          }
      }
}

void insert(int x)
{
    if(head==NULL)
      head=create(NULL,x);
    else
      {
      	node *root=head;
      	while(1)
      	  {
      	  	if(x < root->val)
      	  	  if(root->lt) root=root->lt;
      	  	  else 
      	    	{
                  root->lt=create(root,x);
      	    	  splay(root->lt);
      	    	  break;
      	        }
      		else
      	  	  {
      	  		if(x > root->val)
      	  	  	  {
      	  	  		if(root->rt) root=root->rt;
      	  			else 
      	  	  	  	  {
      	  	  			root->rt=create(root,x);
      	  	  			splay(root->rt);
      	  	  			break;
      	  	  	  	  }
      	  	  	  }
      	  		else
      	  	  	  {
      	  	  		root->cnt++;
      	  	  		root->size++;
      	  	  		splay(root);
      	  	  		break;
      	  	  	  }
      	  	  }
      	  }
      }
}

inline node *find(int x)
{
    node *root=head;
    while(1)
      {
      	if(x < root->val)
      	  root=root->lt;
      	else 
      	  {
      	  	if(x > root->val)
      	  	  root=root->rt;
      	  	else return root;
      	  }
      }
}

void del(int x)
{
    node *root=find(x);
    splay(root);
    if(root->cnt>1)
      {
      	root->cnt--;
      	root->size--;
      }
    else if(root->lt==NULL)
      {
      	head=root->rt;
      	head->fa=NULL;
      	delete root;
      }
    else if(root->rt==NULL)
      {
      	head=root->lt;
      	head->fa=NULL;
      	delete root;
      }
    else
      {
      	node *pre=root->lt;
      	while(pre->rt!=NULL) pre=pre->rt;
      	splay(pre);
      	splay(root);
      	pre->rt=root->rt;
      	root->rt->fa=pre;
      	pre->fa=NULL;
      	head=pre;
      	delete root;
      	update(pre);
      }
}

int num(int x)
{
    node *root=find(x);
    splay(root);
    if(root->lt==NULL) return 1;
    return root->lt->size+1;
}

int loca(int x)
{
    node *root=head;
    while(1)
      {
      	if(root->lt && root->lt->size >= x)
          root=root->lt;
         else 
           {
           	 int now=root->cnt;
           	 if(root->lt) now+=root->lt->size;
           	 if(x<=now) return root->val;
           	 else
           	   {
           	   	  x-=now;
           	   	  root=root->rt;
           	   }
           } 
      }
}

int before(int x)
{
    splay(find(x));
    node *root=head,*pre=root->lt;
    while(pre->rt!=NULL) pre=pre->rt;
    return pre->val;
}

int behind(int x)
{
    splay(find(x));
    node *root=head,*beh=root->rt;
    while(beh->lt!=NULL) beh=beh->lt;
    return beh->val;
}

int main()
{
    //freopen("testdata.in","r",stdin);
    //freopen("tyc.out","w",stdout);
    int n;
    scanf("%d",&n);
    int opt,x;
    while(n--)
      {
      	scanf("%d%d",&opt,&x);
      	if(opt==1) {insert(x);continue;}
      	if(opt==2) {del(x);continue;}
      	if(opt==3) {printf("%d\n",num(x));continue;}
      	if(opt==4) {printf("%d\n",loca(x));continue;}
      	if(opt==5) 
          {insert(x);printf("%d\n",before(x));del(x);continue;}
      	insert(x);printf("%d\n",behind(x));del(x);
      }
    return 0;
} 
