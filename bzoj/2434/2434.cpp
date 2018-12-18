#include<bits/stdc++.h>
using namespace std;
const int MAXN=180010;
int m,n,cnt,c,Head[MAXN],pos[MAXN];//pos��¼ÿ�ν�βλ��
int dfn[MAXN],low[MAXN],tim,zyt,C[MAXN],lasty[MAXN];
char ch[MAXN];
/*
��ô�ж�һ����bΪa���ִ��أ���failָ��Ϳ����� 
���a�����нڵ����ͨ��failָ���ߵ�b����ֹ�ڵ㣬��ôb����a�г��ֹ�
��n���ڵ�����ߵ�b����ôb����a�г��ֹ�n��
Ȼ�����ǿ��Ե������룬��failָ�뷴�򣬽���һ��fail��
����b����ͳ���������ж��ٸ�a���Ľڵ㼴��
�����ڵ��dfs���������ģ�Ҳ��ŷ��������
����״�������ά�� 

���ȹ���ac�Զ�����fail��,�ó�dfs�򣬵ó�ÿ��������ʱ��dfn[x]��low[x]
ֻҪ��Trie����������һ�飬�ߵ�һ�����y����1~dfn[y]��+1��
���ѯ��x��y(��y��ͬ������������������ѯdfn[x]��low[x]�ĺ�
��״����ʵ�ּӼ����������
*/ 

int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x;
}

struct question
{
    int x,y,ans,next;
}ques[MAXN];

struct edge
{
    int to,next;
}E[MAXN];

void add(int u,int v)
{
    c++;
    E[c].to=v;
    E[c].next=Head[u];
    Head[u]=c;
}

int lowbit(int x) {return x&(-x);}

void addC(int x,int val)
{
    for(;x<=tim;x+=lowbit(x)) C[x]+=val;
}

int getsum(int x)
{
    int sum=0;
    for(;x;x-=lowbit(x)) sum+=C[x];
    return sum;
}

struct AC
{
    int son[MAXN][26],fail[MAXN],l[MAXN],fa[MAXN],q[MAXN],now,len;  

    AC()
    {
        cnt=1;
        for(int i=0;i<26;i++) son[0][i]=1;
    } 
    
    void insert()
    {
        now=1,len=strlen(ch);
        int duan=0;
        for(int i=0;i<len;i++)
        {
            if(ch[i]=='B') now=fa[now];
            else if(ch[i]=='P') pos[++duan]=now;
            else 
            {
                int tmp=ch[i]-'a';
                if(!son[now][tmp]) 
                    son[now][tmp]=++cnt,fa[cnt]=now;
                now=son[now][tmp];
            }
        }
    }

    void get_fail()
    {
    	int h=0,t=0;
    	fail[1]=0;q[++t]=1;
        while(h<t)
        {
            now=q[++h];
            for(int i=0;i<26;i++)
                if(son[now][i]) 
                {
                	int f=fail[now],x=son[now][i];
                	while(!son[f][i]) f=fail[f];
                    fail[x]=son[f][i];
                	q[++t]=x;
                }
            //Ϊ0����������ǣ����ܻٻ�ԭ��Trie���Ľṹ 
        }
    }
    
    void search()
    {
        int duan=0,now=1;
        addC(dfn[1],1);
        for(int i=0;i<len;i++)
        {
        	if(ch[i]=='P')
        	{
        		duan++;
        		for(int j=lasty[duan];j;j=ques[j].next)
        		{
        			int x=pos[ques[j].x];
        			ques[j].ans=getsum(low[x])-getsum(dfn[x]-1);
                }
            }
            else if(ch[i]=='B') addC(dfn[now],-1),now=fa[now];
            else now=son[now][ch[i]-'a'],addC(dfn[now],1);
        }
    }
}ac;

void dfs(int u)//fail��
{
    dfn[u]=++tim;
    for(int i=Head[u];i;i=E[i].next)
    	dfs(E[i].to);
    low[u]=++tim;
}

int main()
{
    scanf("%s",ch);
    ac.insert();
    ac.get_fail();
    for(int i=1;i<=cnt;i++)
    	add(ac.fail[i],i);
    dfs(0);
    
    m=read();
    int x,y;
    for(int i=1;i<=m;i++)
    {
    	x=read(),y=read();
    	ques[i]=(question){x,y,0,lasty[y]};
        lasty[y]=i;
    }
    
    ac.search();
    for(int i=1;i<=m;i++) printf("%d\n",ques[i].ans);
    return 0;
}
