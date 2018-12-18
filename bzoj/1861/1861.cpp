#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int MAXN=80010;
    int n,m,root,cnt;
    int pos[MAXN],size[MAXN],son[MAXN][2],fa[MAXN],id[MAXN];

    int dir(int rot)
    {
		return rot==son[fa[rot]][1];
    }

    void update(int rot)
    {
		size[rot]=size[son[rot][0]]+size[son[rot][1]]+1;
		pos[id[son[rot][0]]]=son[rot][0];
		pos[id[son[rot][1]]]=son[rot][1];
    }

    void rotate(int rot)
    {
		int f=fa[rot],ff=fa[f],d=dir(rot);
		fa[rot]=ff;
		if(f==root) root=rot;
		else son[ff][dir(f)]=rot;
		son[f][d]=son[rot][d^1];
		fa[son[rot][d^1]]=f;
		fa[f]=rot;
		son[rot][d^1]=f;
		update(f),update(rot);
	}

    void splay(int x)
    {
		while(x!=root)
		{
			int f=fa[x];
			if(f!=root)
			rotate(dir(f)^dir(x)?x:f);
			rotate(x);
		}
		pos[id[x]]=x;
    }

    void insert(int x)
    {
		id[++cnt]=x;
		size[cnt]=1;
		pos[x]=cnt;
		son[cnt][0]=son[cnt][1]=0;
		if(cnt>1)
		{
			son[cnt-1][1]=cnt;
			fa[cnt]=cnt-1;
			splay(cnt);
		}
    }

    int find(int k)//找第k项
    {
		int rot=root;
		while(1)
		{
			if(size[son[rot][0]]+1==k) return rot;
			if(size[son[rot][0]]>=k) rot=son[rot][0];
			else k-=size[son[rot][0]]+1,rot=son[rot][1];
		}
    }

    void change(int rot,int d)//d==0放top,d==1放bottom
    {
		splay(rot);
		if(!son[rot][d]) return;
		if(!son[rot][d^1]) son[rot][d^1]=son[rot][d],son[rot][d]=0;
		else
		{
			int tmp=(d?0:2);
			int x=find(size[son[rot][0]]+tmp);//+2为后继,+0为前驱
			fa[son[rot][d]]=x;
			son[x][d]=son[rot][d];
			son[rot][d]=0;
			splay(x);
		}
    }

    void ins(int x,int t)
    {
		if(!t) return;
		int rot=pos[x];
		splay(rot);
		int tmp=(t==1?2:0);
		int y=find(size[son[rot][0]]+tmp);
		swap(pos[x],pos[id[y]]);
		swap(id[y],id[rot]);
    }

    int getans(int rot)
    {
		splay(rot);
		return size[son[rot][0]];
    }

    inline int read()
    {
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }

    void work()
    {
		n=read(),m=read();
		root=1;
		for(int i=1;i<=n;i++)
		{
			int x=read();
			insert(x);
		}
		char ch[10];
		while(m--)
		{
			scanf("%s",ch);
			int x=read();
			switch(ch[0])
			{
				case 'T': change(pos[x],0);break;
				case 'B': change(pos[x],1);break;
				case 'I': ins(x,read());break;
				case 'A': printf("%d\n",getans(pos[x]));break;
				case 'Q': printf("%d\n",id[find(x)]);break;
			}
		}
	}
}

int main()
{
    TYC::work();
    return 0;
}
