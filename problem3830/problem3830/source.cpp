#include <iostream>
#include <cstring>

#define NUM 100010

using namespace std;
typedef long long ll;
int n, m;
int par[NUM];
ll psum[NUM];

int find(int start) {
    if (start == par[start])
        return start;

    int root = find(par[start]);
    psum[start] += psum[par[start]];

    return par[start] = root;
}

void sum_uni(int x, int y, ll d) {
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

    for (int i = 1; i < NUM; i++) {
        par[i] = i;
    }
}

void init() {
    while (true) {
        reset();
        cin >> n >> m;
        
        if (n == 0 && m == 0) break;
        for (int i = 0; i < m; i++) {
            char c;            
            cin >> c;

            if (c == '!') {
                int s, e, d;

                cin >> s >> e >> d;
                
                sum_uni(s, e, d);
            }
            else {
                int s, e;
                cin >> s >> e;                
                if (print_uni(s, e)) {
                    cout << psum[e] - psum[s] << "\n";
                }
                else
                {
                    cout << "UNKNOWN\n";
                }
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0); //!!! 반드시 해야함
    cin.tie(0); cout.tie(0); ///!!! 반드시 해야함

    init();
    return 0;
}
