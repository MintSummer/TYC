#include <bits/stdc++.h>

using namespace std;

namespace jumpmelon
{
	typedef long long big;
	typedef long double ld;

	const int MAXN = 30000, MAXL = (1 << 16) + 3, MAXC = 5;
	const ld PI = acos(-1.0L);
	int p, Fac[MAXN + 1], InvFac[MAXN + 1], Inv[MAXN + 1];
	int pcnt, Pr[MAXC], Ind[MAXC];
	int ans, F[MAXL], G[MAXL], Gm[MAXL], H[MAXL];

	struct comp
	{
		ld r, i;
		comp() { }
		comp(ld a_r, ld a_i = 0) : r(a_r), i(a_i) { }
		comp operator /(ld v) const { return comp(r / v, i / v); }
		comp &operator /=(ld v) { return *this = *this / v; }
	};

	inline comp operator +(const comp &a, const comp &b) { return comp(a.r + b.r, a.i + b.i); }
	inline comp operator -(const comp &a, const comp &b) { return comp(a.r - b.r, a.i - b.i); }
	inline comp operator *(const comp &a, const comp &b)
	{ return comp(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
	inline comp &operator *=(comp &a, const comp &b) { return a = a * b; }

	int qpow(int x, int n)
	{
		int s = 1;
		while (n)
		{
			if (n & 1)
				s = int((big)s * x % p);
			x = int((big)x * x % p);
			n >>= 1;
		}
		return s;
	}

	int inv(int x) { return x == 1 ? 1 : int(big(p - p / x) * inv(p % x) % p); }

	void FFT(int f, comp *X, int n)
	{
		static int prev, Rev[MAXL];
		if (prev != n)
		{
			prev = n;
			for (int i = 1; i < n; i++)
				Rev[i] = (Rev[i >> 1] >> 1) | ((i & 1) * (n >> 1));
		}
		for (int i = 0; i < n; i++)
			if (i < Rev[i])
				swap(X[i], X[Rev[i]]);
		for (int i = 1; i < n; i <<= 1)
		{
			comp wn(cos(PI / i), f * sin(PI / i));
			for (int j = 0; j < n; j += i << 1)
			{
				comp w = 1;
				for (int k = 0; k < i; k++, w *= wn)
				{
					comp x0 = X[j + k], x1 = w * X[i + j + k];
					X[j + k] = x0 + x1;
					X[i + j + k] = x0 - x1;
				}
			}
		}
		if (f == -1)
			for (int i = 0; i < n; i++)
				X[i] /= n;
	}

	void get(comp *A1, comp *A0, const int *A, int n, int t)
	{
		static comp T[MAXL];
		for (int i = 0; i < n; i++)
			T[i] = comp(A[i] >> 15, A[i] & 32767);
		for (int i = n; i < t; i++)
			T[i] = 0;
		FFT(1, T, t);
		for (int i = 0; i < t; i++)
		{
			int j = (t - i) & (t - 1);
			A1[i] = comp((T[i].r + T[j].r) / 2, (T[i].i - T[j].i) / 2);
			A0[i] = comp((T[i].i + T[j].i) / 2, (T[j].r - T[i].r) / 2);
		}
	}

	void mul(int *R, const int *A, const int *B, int n, int m)
	{
		static comp A1[MAXL], A0[MAXL], B1[MAXL], B0[MAXL], R1[MAXL], R0[MAXL];
		int t = 1;
		while (t < n + m - 1)
			t <<= 1;
		get(A1, A0, A, n, t);
		if (A != B)
		{
			get(B1, B0, B, m, t);
			for (int i = 0; i < t; i++)
			{
				R1[i] = A1[i] * B1[i] + A0[i] * B0[i] * comp(0, 1);
				R0[i] = A0[i] * B1[i] + A1[i] * B0[i];
			}
		}
		else
			for (int i = 0; i < t; i++)
			{
				R1[i] = A1[i] * A1[i] + A0[i] * A0[i] * comp(0, 1);
				R0[i] = A0[i] * A1[i] + A1[i] * A0[i];
			}
		FFT(-1, R1, t);
		FFT(-1, R0, t);
		for (int i = 0; i < n + m - 1; i++)
			R[i] = int((((big(R1[i].r + 0.5) % p) << 30) +
						((big(R0[i].r + 0.5) % p) << 15) + big(R1[i].i + 0.5)) % p);
	}

	void inv(int *R, const int *A, int n)
	{
		if (n == 1)
			R[0] = inv(A[0]);
		else
		{
			static int T[MAXL];
			int nn = (n + 1) >> 1;
			inv(R, A, nn);
			mul(T, A, R, n, nn);
			mul(T + nn, T + nn, R, n - nn, n - nn);
			for (int i = (n + 1) >> 1; i < n; i++)
				R[i] = (p - T[i]) % p;
		}
	}

	void ln(int *R, const int *A, int n)
	{
		static int T1[MAXL], T2[MAXL];
		for (int i = 1; i < n; i++)
			T1[i - 1] = int((big)A[i] * i % p);
		inv(T2, A, n - 1);
		mul(T1, T1, T2, n - 1, n - 1);
		R[0] = 0;
		for (int i = 1; i < n; i++)
			R[i] = int((big)T1[i - 1] * Inv[i] % p);
	}

	void exp(int *R, const int *A, int n)
	{
		if (n == 1)
			R[0] = 1;
		else
		{
			static int T[MAXL];
			int nn = (n + 1) >> 1;
			exp(R, A, nn);
			for (int i = nn; i < n; i++)
				R[i] = 0;
			ln(T, R, n);
			for (int i = 0; i < n; i++)
				T[i] = (T[i] + p - A[i]) % p;
			mul(T + nn, T + nn, R, n - nn, n - nn);
			for (int i = nn; i < n; i++)
				R[i] = (p - T[i]) % p;
		}
	}

	void DFS(int cur, int m, int phi, int n)
	{
		if (cur >= pcnt)
		{
			for (int i = 0; i * m <= n; i++)
				Gm[i] = G[i * m];
			exp(H, Gm, n / m + 1);
			ans = int((ans + (big)H[n / m] * phi) % p);
		}
		else
		{
			DFS(cur + 1, m, phi, n);
			for (int i = 1; i <= Ind[cur]; i++)
			{
				m *= Pr[cur];
				phi *= i != 1 ? Pr[cur] : Pr[cur] - 1;
				DFS(cur + 1, m, phi, n);
			}
		}
	}

	void work()
	{
		int tot_kase;
		scanf("%d", &tot_kase);
		for (int kase = 1; kase <= tot_kase; kase++)
		{
			int n;
			scanf("%d%d", &n, &p);
			Fac[0] = 1;
			for (int i = 1; i <= n; i++)
				Fac[i] = int((big)Fac[i - 1] * i % p);
			InvFac[n] = inv(Fac[n]);
			for (int i = n; i >= 1; i--)
				InvFac[i - 1] = int((big)InvFac[i] * i % p);
			Inv[1] = 1;
			for (int i = 2; i <= n; i++)
				Inv[i] = int(big(p - p / i) * Inv[p % i] % p);
			for (int i = 0; i <= n; i++)
				F[i] = int((big)qpow(2, (i * (i - 1)) >> 1) * InvFac[i] % p);
			ln(G, F, n + 1);
			pcnt = 0;
			for (int i = 2, t = n; t != 1; i++)
			{
				if (i * i > t)
					i = t;
				if (!(t % i))
				{
					Pr[pcnt] = i;
					Ind[pcnt] = 0;
					while (!(t % i))
					{
						t /= i;
						Ind[pcnt]++;
					}
					pcnt++;
				}
			}
			ans = 0;
			DFS(0, 1, 1, n);
			printf("Case #%d: %d\n", kase, int((big)ans * Fac[n] % p));
		}
	}
}

int main()
{
	jumpmelon::work();
	return 0;
}
