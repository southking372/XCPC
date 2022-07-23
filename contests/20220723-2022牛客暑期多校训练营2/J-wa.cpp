#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 8;
int n, t;
struct Node {
    int x, y;
}dian[N];
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch>'9') { if (ch == '-')f = -1;ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0';ch = getchar(); }
    return x * f;
}
int main() {
    t = read();
    while (t--) {
        n = read();
        double f_1 = 0.0000;
        double f_2x = 0.0000;
        double f_2y = 0.0000;
        double m_3 = 0.0000;
        double m_4 = 0.0000;
        double x_av = 0.0000;
        double y_av = 0.0000;
        for (int i = 1;i <= n;i++) {
            dian[i].x = i;
            dian[i].y = read();
            x_av += (double)(dian[i].x);
            y_av += (double)(dian[i].y);
            f_1 += (double)(dian[i].x) * (double)(dian[i].y);
            f_2x += (double)(dian[i].x);
            f_2y += (double)(dian[i].y);
            m_3 += (double)(dian[i].x) * (double)(dian[i].x);
            m_4 += (double)(dian[i].x);
        }
        f_1 = f_1 * (double)(n);
        double f_2 = f_2x * f_2y;
        m_3 = m_3 * (double)(n);
        m_4 = m_4 * m_4;
        double b = (f_1 - f_2) / (m_3 - m_4);
        x_av /= n;
        y_av /= n;
        double a = y_av - b * x_av;
        double ans = 0.0000000000;
        for (int i = 1;i <= n;i++) {
            double y_real = b * (double)(i)+a;
            ans = ans + (dian[i].y - y_real) * (dian[i].y - y_real);
        }
        printf("%.10lf\n", ans);
    }
    return 0;
}
