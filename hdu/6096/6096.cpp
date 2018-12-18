#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=500010;

	inline void write(int x)
	{
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

	namespace AC
	{
		const int M=1e6+10;
		int cnt,son[M][27],val[M],fail[M],dep[M];

		inline void init()
		{
			for(int i=0;i<=cnt;i++)
				memset(son[i],0,sizeof(son[i]));
			memset(val,0,sizeof(int[cnt+1]));
			memset(fail,0,sizeof(int[cnt+1]));
			memset(dep,0,sizeof(int[cnt+1]));
			cnt=0;
		}

		inline int insert(string &str)
		{
			int len=str.size(),now=0;
			for(int i=0;i<len;i++)
			{
				int c=str[i]-'a';
				if(!son[now][c]) 
					son[now][c]=++cnt,dep[cnt]=dep[now]+1;
				now=son[now][c];
			}
			return now;
		}
	
		inline void get_fail()
		{
			static queue<int> q;
			for(int i=0;i<27;i++)
				if(son[0][i]) q.push(son[0][i]);
			while(!q.empty())
			{
				int now=q.front();q.pop();
				for(int i=0;i<27;i++)
				{
					int x=son[now][i];
					if(!x) son[now][i]=son[fail[now]][i];
					else 
					{
						fail[x]=son[fail[now]][i];
						q.push(x);
					}
				}
			}
		}

		inline void search(string &str,int tmp)
		{
			int len=str.size(),now=0;
			for(int i=0;i<len;i++)
			{
				now=son[now][str[i]-'a'];
				while(now&&dep[now]-1>tmp) now=fail[now];
				val[now]++;
			}
		}

		inline void solve()
		{
			static int deg[N],q[N];
			for(int i=0;i<=cnt;i++) deg[fail[i]]++;
			int h=1,t=0;
			for(int i=0;i<=cnt;i++)
				if(!deg[i]) q[++t]=i;
			while(h<=t)
			{
				int u=q[h++],f=fail[u];
				val[f]+=val[u];
				if(!(--deg[f])) q[++t]=f;
			}
		}
	}

	void work()
	{
		ios::sync_with_stdio(false);
		cin.tie(0);
		int T,n,m;
		static int pos[N];
		static string str[N],pre,suf;
		cin>>T;
		while(T--)
		{
			AC::init();
			cin>>n>>m;
			for(int i=1;i<=n;i++) cin>>str[i];
			for(int i=1;i<=m;i++) 
			{
				cin>>pre>>suf;
				string s=suf;
				s+='z'+1;
				s+=pre;
				pos[i]=AC::insert(s);
			}
			AC::get_fail();
			for(int i=1;i<=n;i++)
			{
				int len=str[i].size();
				string s=str[i];
				s+='z'+1;
				s+=str[i];
				AC::search(s,len);
			}
			AC::solve();
			for(int i=1;i<=m;i++)
				write(AC::val[pos[i]]);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
