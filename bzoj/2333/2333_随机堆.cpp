// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int N=300010;

namespace ZPS
{
    int fa[N],val[N],tag[N],ls[N],rs[N];
    
    inline int rand()
    {
        static int seed=23333333;
        seed^=seed<<13;
        seed^=seed>>17;
        seed^=seed<<5;
        return seed;
    }

    inline void pushdown(int root)
    {
        int t=tag[root];
        val[ls[root]]+=t,val[rs[root]]+=t;
        tag[ls[root]]+=t,tag[rs[root]]+=t;
        tag[root]=0;
    }

    int merge(int x,int y)
    {
        if(!x||!y) return x+y;
        if(val[x]<val[y]) swap(x,y);
        pushdown(x);
        int &p=(rand()&1)?ls[x]:rs[x];
        p=merge(p,y);
        fa[p]=x;
        return x;
    }

    void del(int x)
    {
        pushdown(x);
        int f=fa[x];
        fa[ls[x]]=fa[rs[x]]=0;
        int tmp=merge(ls[x],rs[x]);
        if(f) 
        {
            if(x==ls[f]) ls[f]=tmp;
            else rs[f]=tmp;
        }
        fa[tmp]=f;
    }
}

namespace TYC
{
    using namespace ZPS;
    int n,m,tag_all,a[N];
//	multiset<int> s;
    priority_queue<int> q, qr;
    
    namespace IO
    {
        struct input_t
        {
            static const int BUF_SIZ = 10000000;
            char Buf[BUF_SIZ], *p;
            input_t(FILE *f) : p(Buf) { fread(Buf, sizeof(char), BUF_SIZ, f); }
            char getchar() { return *p++; }
            int read()
            {
                int x=0,f=0;char ch=getchar();
                while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
                while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
                return f?-x:x;
            }
            char read_alpha()
            {
                char ch;
                while (!isalpha(ch = getchar())) { }
                return ch;
            }
        };
        
        struct output_t
        {
            static const int BUF_SIZ = 3000000;
            FILE *f;
            char Buf[BUF_SIZ], *p;
            output_t(FILE *a_f) : f(a_f), p(Buf) { }
            ~output_t() { fwrite(Buf, sizeof(char), p - Buf, f); }
            void putchar(char ch) { *p++ = ch; }
            void write(int x)
            {
                static char St[20];
                char *top = St;
                if (x < 0)
                {
                    putchar('-');
                    x = -x;
                }
                do
                    *top++ = char(x % 10 + '0');
                while (x /= 10);
                while (top > St)
                    putchar(*--top);
            }
        };
    }

#ifdef ONLINE_JUDGE
    IO::input_t input(stdin);
    IO::output_t output(stdout);
#else
    IO::input_t input(fopen("2333.in", "r"));
    IO::output_t output(fopen("2333.out", "w"));
#endif


    inline int find(int x)
    {
        while(fa[x]) x=fa[x];
        return x;
    }

    void work()
    {
        n=input.read();
        for(int i=1;i<=n;i++) 
            val[i]=input.read(),q.push(val[i]);
        m=input.read();	
        char ch[5];
        int x,y,fx,fy,w,root,sum,tmp;
        while(m--)
        {
            switch(input.read_alpha())
            {
                case 'U': 
                    x=input.read(),y=input.read();
                    fx=find(x),fy=find(y);
                    if(fx!=fy)
                    {
                        qr.push(val[fx]);
                        qr.push(val[fy]);
                        q.push(val[merge(fx,fy)]);
                    }
                    break;
                case 'A':
                {
                    switch(input.read())
                    {
                        case 1:
                            x=input.read(),w=input.read();
                            root=find(x);
                            qr.push(val[root]);
                            sum=val[x],tmp=x;;
                            while(fa[tmp]) tmp=fa[tmp],sum+=tag[tmp];
                            del(x);
                            val[x]=sum+w;
                            if(x==root) root=find(ls[x]?ls[x]:rs[x]);
                            fa[x]=ls[x]=rs[x]=tag[x]=0;
                            q.push(val[merge(root,x)]);
                            break;
                        case 2: 
                            x=input.read(),w=input.read();
                            root=find(x);
                            qr.push(val[root]);
                            val[root]+=w,tag[root]+=w;
                            q.push(val[root]);
                            break;
                        case 3: 
                            tag_all+=input.read();
                            break;
                    }
                    break;
                }
                case 'F':
                {
                    switch(input.read())
                    {
                        case 1: 
                            x=input.read();
                            sum=val[x];
                            while(fa[x]) x=fa[x],sum+=tag[x];
                            output.write(sum+tag_all);
                            break;
                        case 2:
                            x=input.read(),root=find(x);
                            output.write(val[root]+tag_all);
                            break;
                        case 3:
                            while(!qr.empty()&&qr.top()==q.top()) q.pop(),qr.pop();
                            output.write(q.top()+tag_all);
                            break;
                    }
                    output.putchar('\n');
                    break;
                }
            }
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
