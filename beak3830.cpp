#include<iostream>
#include<cstring>
#define MAX 100001
using namespace std;

int parent[MAX];
int weight[MAX];

void init()
{
	memset(parent, -1, sizeof(parent));
	memset(weight, 0, sizeof(weight));
}

int find(int a)
{
	if (parent[a] == -1) return a;

	int parentA = find(parent[a]);
	weight[a] += weight[parent[a]];
	
	return parent[a] = parentA;
}

void merge(int a, int b, int w)
{
	int parentA = find(a);
	int parentB = find(b);

	if (parentA == parentB) return;

	weight[parentB] = weight[a] + w - weight[b];
	parent[parentB] = parentA;

}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M, s, e, w;
	char c;

	while (1)
	{
		init();
		cin >> N >> M;
		if (N == 0 && M == 0) break;

		for (int i = 0; i < M; i++)
		{
			cin >> c;

			if (c == '!')
			{
				cin >> s >> e >> w;
				merge(s, e, w);
			}
			else if (c == '?')
			{
				cin >> s >> e;
				if (find(s) == find(e))
				{
					cout << weight[e] - weight[s] << "\n";
				}
				else
				{
					cout << "UNKNOWN\n";
				}
			}
		}
	}
	
	return 0;
}