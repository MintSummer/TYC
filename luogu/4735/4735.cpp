#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
const int N=300010*2;
int bin[30];

namespace Tree
{
    int cnt,son[N*25][2],val[N*25];

    void insert(int &root,int last,int x)
    {
    	root=++cnt;
    	int tmp=root;
    	for(int i=23;i>=0;i--)
    	{
    		son[root][0]=son[last][0],son[root][1]=son[last][1];
    		val[root]=val[last]+1;
    		int t=(x&bin[i]);
    		t>>=i;
    		son[root][t]=++cnt;
    		last=son[last][t];
    		root=son[root][t];
		}
		val[root]=val[last]+1;
		root=tmp;
	}
	
    int query(int l,int r,int x)
    {
    	int tmp=0;
    	for(int i=23;i>=0;i--)
    	{
    		int t=(x&bin[i]);
    		t>>=i;
    		if(val[son[r][t^1]]>val[son[l][t^1]])
    			tmp+=bin[i],r=son[r][t^1],l=son[l][t^1];
    		else r=son[r][t],l=son[l][t];
		}
		return tmp;
    }
}

namespace TYC
{
	int n,m,root[N*2],xorsum[N*2];

	inline int read()
	{
	    int x=0,f=0;char ch=getchar();
	    while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	    return f?-x:x;
	}

	void work()
	{
	    n=read(),m=read();
	    int l,r,x;
	    bin[0]=1;
	    for(int i=1;i<24;i++) bin[i]=bin[i-1]<<1;
	    n++;
	    xorsum[1]=xorsum[0]^0;
		Tree::insert(root[1],root[0],xorsum[1]);
	    for(int i=2;i<=n;i++)
	    {
	    	x=read();
	    	xorsum[i]=xorsum[i-1]^x;
			Tree::insert(root[i],root[i-1],xorsum[i]);
	    }
	    while(m--)
	    {
			char ch[10];
			scanf("%s",ch);
			if(ch[0]=='A')
			{
				x=read();
				n++;
		    	xorsum[n]=xorsum[n-1]^x;
				Tree::insert(root[n],root[n-1],xorsum[n]);
			}
			else
			{
			    l=read(),r=read(),x=read();
			    printf("%d\n",Tree::query(root[l-1],root[r],x^xorsum[n]));
			}
	    }
    }
}

int main()
{
    TYC::work();
    return 0;
}
