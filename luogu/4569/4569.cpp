#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long double ld;
	const int N=5*15+10;

	int n,len,alphabet;

	struct Matrix
	{
		ld m[N][N];
		Matrix() {memset(m,0,sizeof(m));}

		Matrix operator *(const Matrix &x)
		{
			Matrix ans;
			for(int i=0;i<=n;i++)
				for(int k=0;k<=n;k++)
					for(int j=0;j<=n;j++)
						ans.m[i][j]+=m[i][k]*x.m[k][j];
			return ans;
		}

		Matrix operator ^(int tim)
		{
			Matrix ans;
			for(int i=0;i<=n;i++) ans.m[i][i]=1;
			for(;tim;tim>>=1,*this=(*this)*(*this))
				if(tim&1) ans=ans*(*this);
			return ans;
		}
	}M;

	namespace AC
	{
		int cnt,son[N][26],end[N],fail[N];

		void insert(char *ch)
		{
			int len=strlen(ch),now=0;
			for(int i=0;i<len;i++)
			{
				int c=ch[i]-'a';
				if(!son[now][c]) son[now][c]=++cnt;
				now=son[now][c];
			}
			end[now]=1;
		}

		void get_fail()
		{
			static queue<int> q;
			for(int i=0;i<alphabet;i++)
				if(son[0][i]) q.push(son[0][i]);
			while(!q.empty())
			{
				int now=q.front();q.pop();
				end[now]|=end[fail[now]];
				for(int i=0;i<alphabet;i++)
					if(son[now][i])
					{
						int x=son[now][i];
						fail[x]=son[fail[now]][i];
						q.push(x);
					}
					else son[now][i]=son[fail[now]][i];
			}
		}

		void build()
		{
			n=cnt+1;
			ld t=(ld)1.0/alphabet;
			static queue<int> q;
			static int vis[N];
			vis[0]=1,q.push(0);
			while(!q.empty())
			{
				int now=q.front();q.pop();
				for(int i=0;i<alphabet;i++)
				{
					int x=son[now][i];
					if(end[x]) M.m[now][n]+=t,M.m[now][0]+=t;
					else M.m[now][x]+=t;
					if(!vis[x]) vis[x]=1,q.push(x);
				}
			}
			M.m[n][n]=1.0;
		}
	}


	void work()
	{
		scanf("%d%d%d",&n,&len,&alphabet);
		static char ch[20];
		for(int i=1;i<=n;i++)
		{
			scanf("%s",ch);
			AC::insert(ch);
		}
		AC::get_fail();
		AC::build();
		printf("%.10f",(double)(M^len).m[0][n]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
