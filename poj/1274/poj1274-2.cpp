  #include<cstdio>  
    #include<cstring>  
    #include<algorithm>  
    #include<iostream>  
      
    using namespace std;  
      
    const int M = 1000 + 5;  
    int n, m;  
    int link[M];  
    bool MAP[M][M];  
    bool cover[M];  
    int ans;  
      
    void init()  
    {  
        int num;  
        int y;  
        memset(MAP, false, sizeof(MAP));  
        for(int i=1; i<=n; i++)  
        {  
            scanf("%d", &num);  
            while( num-- )  
            {  
                scanf("%d", &y);  
                MAP[i][y]=true;  
            }  
        }  
      
    }  
      
    bool dfs(int x)  
    {  
        for(int y=1; y<=m; y++)  
        {  
            if(MAP[x][y] && !cover[y])  
            {  
                cover[y]=true;  
                if(link[y]==-1 || dfs(link[y]))  
                {  
                    link[y]=x;  
                    return true;  
                }  
            }  
        }  
        return false;  
    }  
      
    int main()  
    {  
        while(scanf("%d%d", &n, &m)!=EOF)  
        {  
            ans=0;  
            init();  
      
            memset(link, -1, sizeof(link));  
            for(int i=1; i<=n; i++)  
            {  
                memset(cover, false, sizeof(cover));  
                if( dfs(i) )  
                    ans++;  
            }  
            printf("%d\n", ans);  
        }  
      
        return 0;  
    }  