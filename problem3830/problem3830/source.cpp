#include <iostream>
#include <cstring>
#define NUM 100010

using namespace std;
typedef long long ll;
int n, m;
ll par[NUM], psum[NUM];

int find(int start) {
    if (start == par[start]) 
        return start;

    int root = find(par[start]);
    psum[start] += psum[par[start]];
    
    return par[start] = root;
}

void sum_uni(int x, int y, int d) {
    int xx = find(x), yy = find(y);
    if (xx == yy) return;
    psum[yy] = psum[x] - psum[y] + d;
    par[yy] = par[xx];
    return;
}

bool print_uni(int x, int y) {
    int xx = find(x), yy = find(y);
    if (xx != yy) return false;
    return true;
}

void reset() {
    memset(psum, 0, sizeof(psum));

    for (int i = 0; i <= 100000; i++) {
        par[i] = i;
    }
}

void init() {
    while (true) {
        reset();
        scanf("%d %d", &n, &m);

        if (n == 0 && m == 0) break;
        for (int i = 0; i < m; i++) {
            char c;
            cin >> c;
            if (c == '!') {
                int s, e, d;
                scanf("%d %d %d", &s, &e, &d);
                sum_uni(s, e, d);
            }
            else {
                int s, e;
                scanf("%d %d", &s, &e);
                if (print_uni(s, e)) {
                    printf("%lld\n", psum[e] - psum[s]);
                }
                else
                {
                    printf("UNKNOWN\n");
                }
            }
        }
    }
}


int main() {
    init();
    return 0;
}
