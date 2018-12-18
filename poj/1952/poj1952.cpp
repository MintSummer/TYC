#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    int times[5005];
    int dp[5005];
    int num[5005];
    int n;
    int ans, time;
    while(scanf("%d", &n) != EOF)
    {
        ans = 0;
        time = 0;
        for (int i = 0; i < n; i++)
        {
            cin>>num[i];
            dp[i] = 1;
            times[i] = 1;
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (num[j] > num[i])
                {
                    if (dp[j] + 1 > dp[i])
                    {
                        dp[i] = dp[j] + 1;
                        times[i] = times[j];
                    }
                    else
                    {
                        if (dp[j] + 1 == dp[i])
                        {
                            times[i] += times[j];
                        }
                    }
                }
                else
                {
                    if (num[i] == num[j])
                    {
                        if (dp[i] == 1)
                        {
                            times[i] = 0;
                        }
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, dp[i]);
        }
        for (int i = 0; i < n; i++)
        {
            if (ans == dp[i])
            {
                time += times[i];
            }
        }
        printf("%d %d\n", ans, time);
    }
    return 0;
}