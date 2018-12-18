#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const double pi=3.1415926535897932384626;
    const int N=1<<21|5;

    struct cmplex
    {
        double re,im;
        cmplex(double _re=0.0,double _im=0.0):re(_re),im(_im){}
        cmplex operator + (const cmplex &t) const {return cmplex(re+t.re,im+t.im);}
        cmplex operator - (const cmplex &t) const {return cmplex(re-t.re,im-t.im);}
        cmplex operator * (const cmplex &t) const {return cmplex(re*t.re-im*t.im,re*t.im+im*t.re);}
    };
    cmplex inv(const cmplex &x) 
    {
        double D=x.re*x.re+x.im*x.im;
        return cmplex(x.re/D,-x.im/D);
    }
    cmplex operator / (const cmplex &l,const cmplex &r) {return l*inv(r);}

    void get_unit_root(cmplex w[],int n)
    {
        for(int i=0;i<n;i++)
            w[i]=cmplex(cos(pi*2*i/n),sin(pi*2*i/n));
    }

    void get_inv(int a[],int n)
    {
        for(int i=0;i<n;i++) 
            a[i]=(a[i>>1]>>1)|((n>>1)*(i&1));
    }

    void FFT(cmplex a[],int n,int type=0)
    {
        static cmplex w[N];
        static int rev[N];
        get_unit_root(w,n);
        get_inv(rev,n);
        cmplex x,y;
        for(int i=0;i<n;i++)
            if(i<rev[i]) swap(a[i],a[rev[i]]);
        if(type) reverse(w+1,w+n);
        for(int i=1;i<n;i<<=1)
            for(int j=0,d=n/(i<<1);j<n;j+=(i<<1))
                for(int k=j,l=0;k<j+i;k++,l+=d)
                {
                    x=a[k+i]*w[l];
                    y=a[k];
                    a[k]=y+x;
                    a[k+i]=y-x;
                }
        if(type) 
            for(int i=0;i<n;i++) a[i]=a[i]/n;
    }

    int n,m,Len=1,a[N],b[N];
    cmplex ta[N],tb[N];
    void work()
    {
        ios::sync_with_stdio(false);
        cin>>n>>m;
        while(Len<=(n+m)) Len<<=1;
        for(int i=0;i<=n;i++) cin>>a[i];
        for(int i=0;i<=m;i++) cin>>b[i];
        for(int i=0;i<=n;i++) ta[i]=a[i];
        for(int i=0;i<=m;i++) tb[i]=b[i];
        FFT(ta,Len),FFT(tb,Len);
        for(int i=0;i<Len;i++) ta[i]=ta[i]*tb[i];
        FFT(ta,Len,1);
        for(int i=0;i<=n+m;i++) cout<<(int)(ta[i].re+0.5)<<" ";
        cout<<endl;
    }
}

int main()
{
    TYC::work();
    return 0;
}