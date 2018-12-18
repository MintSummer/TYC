#include<bits/stdc++.h>
using namespace std;
int T,ans,REAL;
int h,t,tim,bianliang[150],add[150];
char panduan[30];
char ch,name,from[15],to[15];
bool vis[50];

void read()
{
	ans=0;
	cin>>tim>>panduan;
	if(panduan[2]=='1') return;
	ans=panduan[4]-'0';
	for(int i=5;i<=6;i++)
		if(panduan[i]==')') return;
		else ans=ans*10+panduan[i]-'0';
}

int getans(char st[15])
{
	int ANS=st[0]-'0';
	for(int i=1;i<=15;i++)
		if(st[i]=='\0') return ANS;
		else ANS=ANS*10+st[i]-'0';
	return ANS;
}

int main()
{
	freopen("3952.in","r",stdin);
	freopen("3952.out","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		bool flag=false;
		int jinbuqu=-1,ci=0;
		memset(vis,0,sizeof(vis));
		memset(add,0,sizeof(add));
		t=0,REAL=0;
		read();
		if(tim%2) flag=1;
		for(int i=1;i<=tim;i++)
		{
			cin>>ch;
			if(ch=='F')
			{
				t++;
				cin>>name>>from>>to;
				int NAME=name-'a';
				if(vis[NAME]) flag=true;
				vis[NAME]=1;
				bianliang[t]=NAME;
				if(jinbuqu!=-1) continue;
				if(from[0]!='n'&&to[0]=='n') ci++,add[t]=1;
				else if((from[0]=='n'&&to[0]!='n')||getans(from)>getans(to)) jinbuqu=t;
				REAL=max(REAL,ci);
			}
			else 
			{
				if(jinbuqu==t) jinbuqu=-1;
				if(add[t]) ci--,add[t]=0;
				int NAME=bianliang[t--];
				vis[NAME]=0;
			}
		}
		if(t!=0) flag=true;
		if(flag) {printf("ERR\n");continue;}
		if(ans==REAL) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

