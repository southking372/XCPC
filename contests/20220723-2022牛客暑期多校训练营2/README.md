# 总结

这场比赛只过了两个题：G 和 J。G 是个简单构造题，J 是个基础数学题（竟然卡精度，最开始就用double 过不去）。





# 题解

TO BE COMPLETED



## D

### yh

这道题就是一个简单图论：将图边权取对，给所有边权重同时减去一个值，使得所有环都是负环，问这个值的最小值。

spfa 思路可以求出一个图 “是否存在负环”，而要让所有环都是负环，则可以考虑 “是否存在正环”，于是将所有边取相反数。

二分答案就解决了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lll __int128
using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch>'9') { if (ch == '-')f = -1;ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0';ch = getchar(); }
    return x * f;
}

const ll MAX = 3e3;

int n, m;
vector<int> target[MAX];
double len[MAX][MAX];

bool in_queue[MAX];
double min_dis[MAX];
int path_len[MAX];

bool exist_neg(double offset) {
    queue<int> q;
    for (int i = 1;i <= n;i++) {
        q.push(i);
        in_queue[i] = true;
        min_dis[i] = 0;
        path_len[i] = 0;
    }
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        in_queue[node] = false;
        // found a negtive circle
        if (path_len[node] >= n) return true;
        for (int dst : target[node]) {
            double w = len[node][dst] + offset;
            if (min_dis[node] + w < min_dis[dst]) {
                path_len[dst] = path_len[node] + 1;
                min_dis[dst] = min_dis[node] + w;
                // re-queue to update distance from dst
                if (!in_queue[dst]) {
                    q.push(dst);
                    in_queue[dst] = true;
                }
            }
        }
    }
    return false;
}

bool check(double value) {
    return !exist_neg(value);
}

int main() {
    n = read(), m = read();
    for (int i = 0;i <= n;i++) {
        for (int j = 0;j <= n;j++) {
            len[i][j] = 1e100;
        }
    }
    for (int i = 0;i < m;i++) {
        int a = read(), b = read(), c = read(), d = read();
        double val = -log(c / (double)a);
        target[b].push_back(d);
        len[b][d] = min(val, len[b][d]);
    }
    double l = -1e3, r = 0;
    while (r - l > 1e-7) {
        double m = (l + r) / 2;
        if (check(-m)) l = m;
        else r = m;
    }
    printf("%.10lf", exp(l));
}

/*

4 5
1 1 2 2
1 2 4 3
1 3 2 4
1 4 1 1
1 2 3 1

0.4082482905

*/
```



## G

### yh

G 是个构造题。考虑分组，组内递增，组间递减，最小值为根号。**至于为什么，参见 Solution。**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lll __int128
using namespace std;

const ll MAX = 5e5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int m = 1;
        for (;m * (ll)m < (ll)n;m++);
        for (int group = (n + m - 1) / m;group >= 0;group--) {
            int val;
            for (int i = 0;i < m && (val = i + group * m) < n;i++)
                printf("%d ", val + 1);
        }
        printf("\n");
    }
}
```



## J

### yh

这是个最小二乘解线性回归。公式贴在这：

![image-20220724194847656](README.assets/image-20220724194847656.png)

这个题就离谱，tnnd，卡精度，后面用 `__int128` 才过。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lll __int128
using namespace std;

inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-')f = -1;ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0';ch = getchar(); }
    return x * f;
}

const ll MAX = 5e5;
ll x[MAX], y[MAX];


int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    ll t = read();
    while (t--) {
        ll n = read();
        lll cross_sum = 0;
        lll x_sum = 0;
        lll y_sum = 0;
        lll x2_sum = 0;
        for (int i = 0;i < n;i++) {
            x[i] = i;
            y[i] = read();
            cross_sum += x[i] * (lll)y[i];
            x_sum += x[i];
            y_sum += y[i];
            x2_sum += x[i] * (lll)x[i];
        }
        double b = (n * (double)cross_sum - x_sum * (double)y_sum)
            / (n * (double)x2_sum - x_sum * (double)x_sum);
        double a = y_sum / (double)n - b * x_sum / (double)n;
        double ans = 0;
        for (int i = 0;i < n;i++) {
            double y_predict = b * i + a;
            ans += (y_predict - y[i]) * (y_predict - y[i]);
        }
        printf("%.9lf\n", ans);
    }
}
```



## K

### yh

#### 最长公共子序列（LCS）

> 摘自 OI-WIKI

![image-20220724194829382](README.assets/image-20220724194829382.png)

#### 回到题目

令 `dp[x][y][z]` 表示 a 的前 y 位是 b 的前 x 位的子序列，且 b 的前 x 位中左括号数比右括号数多 z 的总情况数。因为构造的 b 是一个符合要求的括号序列，故中间过程 z 一定是一个非负整数（栈）。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lll __int128
using namespace std;

const ll MOD = 1e9 + 7;

void append(ll& dst, ll src) {
    dst %= MOD;
    dst += src;
    dst %= MOD;
}

char a[300];
ll dp[300][300][300] = { 0 };
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d%s", &n, &m, a);
        for (int x = 0;x <= m + 1;x++) for (int y = 0;y <= m + 1;y++) for (int z = 0;z <= m + 1;z++) dp[x][y][z] = 0;
        dp[0][0][0] = 1;
        for (int x = 0;x < m;x++) {
            for (int y = 0;y <= x && y < n;y++) {
                for (int z = 0;z <= x;z++) {
                    if (a[y] == '(') {
                        append(dp[x + 1][y + 1][z + 1], dp[x][y][z]); // b[x] == '('
                        if (z > 0) append(dp[x + 1][y][z - 1], dp[x][y][z]); // b[x] == ')'
                    }
                    else {
                        append(dp[x + 1][y][z + 1], dp[x][y][z]); // b[x] == '('
                        if (z > 0) append(dp[x + 1][y + 1][z - 1], dp[x][y][z]); // b[x] == ')'
                    }
                }
            }
            // for y == n:
            for (int z = 0;z <= x;z++) {
                append(dp[x + 1][n][z + 1], dp[x][n][z]); // b[x] == '('
                if (z > 0) append(dp[x + 1][n][z - 1], dp[x][n][z]); // b[x] == ')'
            }
        }
        printf("%lld\n", (dp[m][n][0] % MOD + MOD) % MOD);
    }
}
```

计算 dp 可以采取两种方案：

- 拉式：通过已经算出的 dp 值计算当前的 dp；
- 推式：当前的 dp 值已经算出，于是计算它对未来 dp 值的贡献。

本题采用后者更方便。

