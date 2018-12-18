#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
typedef long long ll;
int n,m;
ll a[MAXN];

struct node
{
    int l,r,flag;
    ll sum;
}tree[MAXN*4];

void update(int root)
{
    tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
    tree[root].flag=tree[root*2].flag&tree[root*2+1].flag;
}

void build(int root,int lt,int rt)
{
    tree[root].l=lt,tree[root].r=rt;
    if(lt==rt) 
    {
		tree[root].sum=a[lt];
		if(a[lt]<=1) tree[root].flag=1;
		return;
    }
    int mid=(lt+rt)>>1;
    build(root*2,lt,mid),build(root*2+1,mid+1,rt);
    update(root);
}

void change(int root,int s,int e)
{
    int lt=tree[root].l,rt=tree[root].r;
    if(tree[root].flag) return;
    if(lt==rt)
    {
		tree[root].sum=sqrt(tree[root].sum);
		if(tree[root].sum<=1) tree[root].flag=1;
		return;
    }
    int mid=(lt+rt)>>1;
    if(e<=mid) change(root*2,s,e);
    else if(s>mid) change(root*2+1,s,e);
    else change(root*2,s,mid),change(root*2+1,mid+1,e);
    update(root);
}

ll ask(int root,int s,int e)
{
    int lt=tree[root].l,rt=tree[root].r;
    if(s<=lt&&rt<=e) return tree[root].sum;
    int mid=(lt+rt)>>1;
    if(e<=mid) return ask(root*2,s,e);
    else if(s>mid) return ask(root*2+1,s,e);
    else return ask(root*2,s,mid)+ask(root*2+1,mid+1,e);
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    cin>>m;
    int opt,lt,rt;
    while(m--)
    {
		cin>>opt>>lt>>rt;
		if(lt>rt) swap(lt,rt);
		if(opt==0) change(1,lt,rt);
		else printf("%lld\n",ask(1,lt,rt));
    }
    return 0;
}
