#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef __int128 i128;
typedef unsigned __int128 u128;
// #define fio
#ifdef fio
char buf[1 << 20], *p1, *p2, pbuf[1 << 20], *pp = pbuf;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
#define pc(c) (pp - pbuf == (1 << 20) ? (fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf, *pp++ = (c)) : (*pp++ = (c)))
#else
#define gc getchar
// #define gc getchar_unlocked
#define pc putchar
#endif
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FFOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i > (b); --i)
#define RROF(i, a, b) for (int i = (a); i >= (b); --i)
#define unsync cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define endl '\n'
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define eb emplace_back
#define mkp make_pair
#define mkt make_tuple
#define pii pair<int, int>
#define pll pair<long long, long long>
#define pdd pair<double, double>
#define pld pair<long double, long double>
#define pcc pair<char, char>
#define pss pair<string, string>
#define fi first
#define se second
#define cs const
#define db double
#define ld long double
#define fl float
#define vec vector
#define all(x) (x).begin(), (x).end()
#define local freopen("data.in", "r", stdin)
#define locall freopen("data.in", "r", stdin), freopen("data.out", "w", stdout)
// #define int long long
template <typename T>
void read(T &t)
{
    t = 0;
    bool f = 1;
    char x = gc();
    while (x < '0' || x > '9')
    {
        if (x == '-')
            f = 0;
        x = gc();
    }
    while (x >= '0' && x <= '9')
        t = (t << 1) + (t << 3) + (x ^ '0'), x = gc();
    t = f ? t : -t;
    return;
}
template <typename T>
void write(T t)
{
    bool f = false;
    if (t < 0)
        f = true, pc('-'), t = -t;
    static int sta[40];
    int top = 0;
    do
    {
        sta[top++] = t % 10, t /= 10;
    } while (t);
    while (top)
        pc('0' + sta[--top]);
    return;
}
cs int N = 12;
int n;
u64 ans, a[N];
void permute(int idx)
{
    if (idx == n)
    {
        u64 t = 0;
        for (int i = 0; i < n; ++i)
            t += (u64)(i + 1) ^ a[i];
        ans |= t;
        return;
    }
    for (int i = idx; i < n; ++i)
    {
        u64 tmp = a[idx];
        a[idx] = a[i];
        a[i] = tmp;
        permute(idx + 1);
        tmp = a[idx];
        a[idx] = a[i];
        a[i] = tmp;
    }
}
void sol()
{
    cin >> n;
    FOR(i, 0, n)
    cin >> a[i];
    permute(0);
    cout << ans << endl;
}
signed main()
{
    // local;
    unsync;
    int T = 1;
    // cin >> T;
    while (T--)
    {
        sol();
    }
    return 0;
}
