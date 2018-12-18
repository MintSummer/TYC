#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+20; 
const int inf=0x3f3f3f3f;
int cnt,head,a[MAXN],id[MAXN],tag[MAXN],rev[MAXN],mx[MAXN],sum[MAXN],lmx[MAXN],rmx[MAXN];
int size[MAXN],val[MAXN],son[MAXN][2],fa[MAXN];
queue<int> q;

int read()
{
    int x=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

void update(int root)
{
    int lt=son[root][0],rt=son[root][1];
    sum[root]=sum[lt]+sum[rt]+val[root];
    size[root]=size[lt]+size[rt]+1;
    lmx[root]=max(lmx[lt],sum[lt]+val[root]+lmx[rt]);
    rmx[root]=max(rmx[rt],sum[rt]+val[root]+rmx[lt]);
    mx[root]=max(mx[lt],max(mx[rt],rmx[lt]+val[root]+lmx[rt]));
}

void pushdown(int root)
{
    int lt=son[root][0],rt=son[root][1];
    if(tag[root])
    {
		rev[root]=tag[root]=0;
		if(lt) tag[lt]=1,val[lt]=val[root],sum[lt]=val[root]*size[lt];
		if(rt) tag[rt]=1,val[rt]=val[root],sum[rt]=val[root]*size[rt];
		if(val[root]>=0)
		{
		    if(lt) lmx[lt]=rmx[lt]=mx[lt]=sum[lt];
		    if(rt) lmx[rt]=rmx[rt]=mx[rt]=sum[rt];
		}
		else
		{
		    if(lt) lmx[lt]=rmx[lt]=0,mx[lt]=val[root];
		    if(rt) lmx[rt]=rmx[rt]=0,mx[rt]=val[root];
		}
    }
    if(rev[root])
    {
		rev[root]=0;
		rev[lt]^=1,rev[rt]^=1;
		swap(lmx[lt],rmx[lt]);
		swap(lmx[rt],rmx[rt]);
		swap(son[lt][0],son[lt][1]);
		swap(son[rt][0],son[rt][1]);
    }
}

int getdir(int root)
{
    return root==son[fa[root]][1];
}

void rotate(int root,int &to)
{
    int f=fa[root],ff=fa[f],d=getdir(root);
    if(f==to) to=root;
    else son[ff][getdir(f)]=root;
    fa[root]=ff;

    son[f][d]=son[root][d^1];
    if(son[root][d^1]) fa[son[root][d^1]]=f;

    son[root][d^1]=f;
    fa[f]=root;

    update(f);
    update(root);
}

void splay(int root,int &to)
{
    while(root!=to)
    {
		int f=fa[root];
		if(f!=to)
		{
		    if(getdir(f)^getdir(root)) rotate(root,to);
		    else rotate(f,to);
		}
		rotate(root,to);
    }
}

int find(int root,int x)
{
    while(1)
    {
		pushdown(root);
		int lt=son[root][0],rt=son[root][1];
		if(size[lt]+1==x) return root;
		if(size[lt]>=x) root=lt;
		else root=rt,x=x-size[lt]-1;
    }
}

void build(int lt,int rt,int pre)
{
    int mid=(lt+rt)>>1,root=id[mid],f=id[pre];
    if(lt==rt) 
    {
		mx[root]=sum[root]=a[lt];
		tag[root]=rev[root]=0;
	    lmx[root]=rmx[root]=max(a[lt],0);
		size[root]=1;
    }
    if(lt<mid) build(lt,mid-1,mid);
    if(mid<rt) build(mid+1,rt,mid);
    val[root]=a[mid];
    fa[root]=f;
    update(root);
	son[f][mid>=pre]=root;
}

void insert(int pos,int tot)
{
    for(int i=1;i<=tot;i++) a[i]=read();
    for(int i=1;i<=tot;i++)
    {
		if(!q.empty()) id[i]=q.front(),q.pop();
		else id[i]=++cnt;
    }
    build(1,tot,0);
    int root=id[(1+tot)>>1];
    int pre=find(head,pos+1),nxt=find(head,pos+2);
    splay(pre,head),splay(nxt,son[pre][1]);
    fa[root]=nxt,son[nxt][0]=root;
    update(nxt),update(pre);
}

int interval(int pos,int tot)
{
    int pre=find(head,pos),nxt=find(head,pos+tot+1);
    splay(pre,head),splay(nxt,son[pre][1]);
    return son[nxt][0];
}

void recycle(int root)
{
    int &lt=son[root][0],&rt=son[root][1];
    if(lt) recycle(lt);
    if(rt) recycle(rt);
    q.push(root);
    fa[root]=tag[root]=rev[root]=lt=rt=0;
}

void del(int pos,int tot)
{
    int root=interval(pos,tot),f=fa[root];
    recycle(root);
    son[f][0]=0;
    update(f),update(fa[f]);
}

void make_same(int pos,int tot,int v)
{
    int root=interval(pos,tot);
    val[root]=v,tag[root]=1;
    sum[root]=size[root]*v;
    if(v>=0) lmx[root]=rmx[root]=mx[root]=sum[root];
    else lmx[root]=rmx[root]=0,mx[root]=v;
    update(fa[root]),update(fa[fa[root]]);
}

void get_sum(int pos,int tot)
{
    int root=interval(pos,tot);
    printf("%d\n",sum[root]);
}

void reverse(int pos,int tot)
{
    int root=interval(pos,tot);
    if(!tag[root])
    {
		rev[root]^=1;
		swap(son[root][0],son[root][1]);
		swap(lmx[root],rmx[root]);
		update(fa[root]),update(fa[fa[root]]);
    }
}

int main()
{
    int n=read(),m=read();
    mx[0]=a[1]=a[n+2]=-inf;
    for(int i=1;i<=n;i++) a[i+1]=read();
    for(int i=1;i<=n+2;i++) id[i]=i;
    build(1,n+2,0);
    head=(1+n+2)>>1;
    cnt=n+2;
    char ch[10];
    int pos,tot,v;
    while(m--)
    {
		scanf("%s",ch);
		if(ch[0]!='M'||ch[2]!='X') pos=read(),tot=read();
		if(ch[0]=='I') insert(pos,tot);
		else if(ch[0]=='D') del(pos,tot);
		else if(ch[0]=='M'&&ch[2]=='K')
		    v=read(),make_same(pos,tot,v);
		else if(ch[0]=='R') reverse(pos,tot);
		else if(ch[0]=='G') get_sum(pos,tot);
		else printf("%d\n",mx[head]);
    }
    return 0;
}
