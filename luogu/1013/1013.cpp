#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    int n,to[30];
    bool finish[12][12];
    string form[12][12];

    bool search()
    {
        int a,b;
        for(int i=2;i<=n;i++)
            for(int j=2;j<=n;j++)
                if(!finish[i][j])
                    if(~to[a=form[i][1][0]-'A']&&~to[b=form[j][1][0]-'A'])
                    {
                        int t=form[i][j][0]-'A';
                        int x=to[a]+to[b];
                        if(x>=n-1) 
                        {
                            x-=n-1;
                            if(form[i][j].size()<2) return false;
                            t=form[i][j][1]-'A';
                        }
                        if(~to[t])
                        {
                            if(to[t]!=x) return false;
                            else continue;
                        }
                        to[t]=x;
                        finish[i][j]=true;
                        return true;
                    }
    }

    bool check()
    {
        for(int i=2;i<=n;i++)
            for(int j=2;j<=n;j++)
            {
                int a=form[i][1][0]-'A',b=form[j][1][0]-'A';
                int x=to[a]+to[b],t=form[i][j][0]-'A';
                if(x>=n-1)
                {
                    if(form[i][j].size()<2) return false;
                    if(to[form[i][j][0]-'A']!=1) return false;
                    x-=n-1;
                    t=form[i][j][1]-'A';
                }
                if(to[t]!=x) return false;
            }
        return true;
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        memset(to,-1,sizeof(to));
        cin>>n;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                cin>>form[i][j];
                if(form[i][j].size()==2) 
                    to[form[i][j][0]-'A']=1;
            }
        for(int i=2;i<=n;i++)
        {
            int flag_zero=1;
            for(int j=2;j<=n;j++)
                if(form[i][j].size()==2||form[j][1][0]!=form[i][j][0])
                    {flag_zero=0;break;}
            if(flag_zero) 
            {
                to[form[i][1][0]-'A']=0;
                for(int j=2;j<=n;j++)
                    finish[i][j]=true;
                break;
            }
        }
        for(int now=2;now<n-1;now++) 
            if(!search()) {cout<<"ERROR!\n";return;}
        if(!check()) cout<<"ERROR!\n";			
        else
        {
        	for(int i=2;i<=n;i++)
            {
                char t=form[i][1][0];
            	cout<<t<<"="<<to[t-'A']<<" ";
            }
        	cout<<"\n"<<n-1<<"\n";
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
