#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long LL;
LL n,k,H[1000010];
LL ans=1e14,pos,change; //ans的初值不能设成0x3f3f3f3f，太小了，会WA六个点

struct node
{
	node *lt,*rt,*fa;
	LL val,size,cnt,sum;
};
node *head;

inline node *create(node *f,LL x)
{
	node *h=new node;
	h->lt=h->rt=NULL;
	h->val=h->sum=x;
	h->size=h->cnt=1;
	h->fa=f;
	return h;
}

inline void update(node *root)
{
	if(root)
	{
		root->size=root->cnt;
		root->sum=root->cnt*root->val;
		if(root->lt)
			root->size+=root->lt->size,
			root->sum+=root->lt->sum;
		if(root->rt)
			root->size+=root->rt->size,
			root->sum+=root->rt->sum;
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

void insert(LL x)
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
			else if(x > root->val)
				if(root->rt) root=root->rt;
				else 
				{
					root->rt=create(root,x);
					splay(root->rt);
					break;
				}
			else 
			{
				root->cnt++;
				root->size++;
				root->sum+=root->val;
				splay(root);
				break;
			}
		}
	}
}

node *find(LL x)
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

void del(LL x)
{
	node *root=find(x);
	splay(root);
	if(root->cnt > 1)
	{
		root->cnt--;
		root->size--;
		root->sum-=root->val;
	}
	else if(root->lt==NULL)
	else if(root->rrt=NULL)
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
		delete root;
		update(pre);
		head=pre;
	}
}

LL getans()
{
	LL x=(k+1)/2;
	node *root=head;
	while(1)
	{
		if(root->lt && x <= root->lt->size)
			root=root->lt;
		else 
		{
			int tmp=root->cnt;
			if(root->lt) tmp+=root->lt->size;
			if(x<=tmp) break;
			else 
			{
				x-=tmp;
				root=root->rt;
			}
		}
	}
	splay(root);
	long long ans=0,tmp=root->val;
	node *lt=root->lt,*rt=root->rt;
	if(lt) ans+=tmp*lt->size-lt->sum;
	if(rt) ans+=rt->sum-tmp*rt->size;
	return ans;
}

int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&H[i]); 
	if(k==1) 
	{
		printf("0\n");
		for(int i=1;i<=n;i++) printf("%lld\n",H[i]);
		return 0;
	}
	for(int i=1;i<k;i++)
		insert(H[i]);
	for(int i=k;i<=n;i++)
	{
		insert(H[i]);
		long long tmp=getans();
		if(tmp<ans)
		{
			ans=tmp;
			change=head->val;
			pos=i-k+1;
		}
		del(H[i-k+1]);
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++)
		if(pos<=i&&i<pos+k) printf("%lld\n",change);
		else printf("%lld\n",H[i]);
	return 0;
}
