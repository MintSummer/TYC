#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
using namespace std;

namespace TYC
{
	const int N=90;
	const double eps = 1e-8;
	int n, Left[N], Right[N], arr[N << 1], real[N << 1];
	double f[2][N][N], ans[N][N];
	map<int, int> id;
	
	inline int read()
	{
		int x = 0, f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		return f ? -x : x;
	}
	
	void work()
	{
		ios::sync_with_stdio(false);
		cin.tie(0);
		n = read();
		int tot = 0;
		for (int i = 1; i <= n; i++)
		{
			Left[i] = read(), Right[i] = read();
			arr[++tot] = Left[i];
			arr[++tot] = Right[i];
		}
		sort(arr + 1, arr + 1 + tot);
		int num = 0;
		arr[0] = -1;
		for (int i = 1; i <= tot;i++)
			if (arr[i] != arr[i - 1])
				id[arr[i]] = ++num, real[num] = arr[i];
		for (int i = 1; i <= n; i++)
			Left[i] = id[Left[i]], Right[i] = id[Right[i]];

		for (int i = 1; i <= n; i++)
		{
			for (int score = Left[i]; score < Right[i]; score++)
			{
				double p = (double)(real[score + 1] - real[score]) / (real[Right[i]] - real[Left[i]]);
			    // �� i ���˷����� score ~ score + 1 �ĸ���
				int now = 0;
				for (int j = 0; j <= 1; j++)
					for(int less = 0; less <= n; less++)
						for (int more = 0; more <= n; more++)
							f[j][less][more] = 0;
				f[0][0][0] = 1.0;
				// �� f[j][less][more] ��ʾǰ j ���ˣ������ȱ� i ��ǰ�ķ��������䣩С���� less �ˣ������ more �˵ĸ���
				// �����������飨��ʵֻ��Ϊ������Ͱѵ� i �й�����

				for (int j = 1; j <= n; j++) // �� j �ȵ�ǰ�� i �ķ��������䣩Ҫ��
				{
					if (i == j) continue;
					now ^= 1;
					
					if (score < Left[j])
					{
						for (int less = 0; less < j; less++)
							for (int more = 0; more < j - less; more++)
								if (f[now ^ 1][less][more] >= eps)
								{
									f[now][less][more + 1] += f[now ^ 1][less][more];
									f[now ^ 1][less][more] = 0.0;
								}
					}
					else if (score >= Right[j]) // �� j �ȵ�ǰ�� i �ķ��������䣩ҪС
					{
						for (int less = 0; less < j; less++)
							for (int more = 0; more < j - less; more++)
								if (f[now ^ 1][less][more] >= eps)
								{
									f[now][less + 1][more] += f[now ^ 1][less][more];
									f[now ^ 1][less][more] = 0.0;
								}
					}
					else
					{
						int L = real[Left[j]], R = real[Right[j]];
						double p_less = (double)(real[score] - L) / (R - L);
						double p_equal = (double)(real[score + 1] - real[score]) / (R - L);
						double p_more = (double)(R - real[score + 1]) / (R - L);
						for (int less = 0; less < j; less++)
							for (int more = 0; more < j - less; more++)
								if (f[now ^ 1][less][more] >= eps)
								{
									double tmp = f[now ^ 1][less][more];
									f[now][less + 1][more] += tmp * p_less;
									f[now][less][more] += tmp * p_equal;
									f[now][less][more + 1] += tmp * p_more;
									f[now ^ 1][less][more] = 0.0;
								}
					}
				}
				
				for (int less = 0; less < n; less++)
					for (int more = 0; more < n - less; more++)
						if (f[now][less][more] >= eps)
						{
							int equal = n - less - more;
							double p_equal = 1.0 / equal;
							for (int j = 1; j <= equal; j++)
								ans[i][less + j] += p * f[now][less][more] * p_equal;
						}
			}
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++) 
				printf("%.9f ", ans[i][j]);
			putchar('\n');
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
