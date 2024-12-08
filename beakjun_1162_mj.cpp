#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <limits>

#define CITY_MAX 10000
#define NEWROAD_MAX 20 
#define LLONG_MAX_     9223372036854775807

using namespace std;
int gCityNum, gRoadNum, gNewRoadNum;
vector<pair<int, int>> gMap[CITY_MAX + 1]; //city, time
priority_queue <pair<long long, pair<int, int>>> pq; //time, city, newroad_count
long long gTimemap[CITY_MAX + 1][NEWROAD_MAX + 1];

long long GetMinimunTime(int NewRoadNum);

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//freopen("input.txt", "r", stdin); // debug
	cin >> gCityNum >> gRoadNum >> gNewRoadNum;
	int scity, ecity, time;
	for (int i = 0; i < gRoadNum; i++)
	{
		cin >> scity >> ecity >> time;
		gMap[scity].push_back({ ecity, time });
		gMap[ecity].push_back({ scity, time });//양방향이니까
	}
	cout << GetMinimunTime(gNewRoadNum);
	return 0;
}

long long GetMinimunTime(int NewRoadNum)
{
	long long retval, curtime;
	int curcity, curNRCount;
	for (int i = 0; i < CITY_MAX + 1; i++)
	{
		for (int j = 0; j < NEWROAD_MAX + 1; j++)
		{
			gTimemap[i][j] = LLONG_MAX_;
		}
	}
	pq.push({ 0, {1, 0} });
	while (!pq.empty())
	{
		curtime = -pq.top().first;
		curcity = pq.top().second.first;
		curNRCount = pq.top().second.second;
		pq.pop();

		if ((curtime > gTimemap[curcity][curNRCount]))
			continue;

		for (int i = 0; i < (int)gMap[curcity].size(); i++)
		{
			int nextcity = gMap[curcity][i].first;
			int nexttime = gMap[curcity][i].second;

			if (curNRCount < NewRoadNum) // 포장: time = 0
			{
				if (gTimemap[nextcity][curNRCount + 1] > curtime)
				{
					gTimemap[nextcity][curNRCount + 1] = curtime;
					pq.push({ -gTimemap[nextcity][curNRCount + 1], {nextcity, curNRCount + 1} });
				}
			}

			if (gTimemap[nextcity][curNRCount] > (curtime + nexttime)) //포장 못 함
			{
				gTimemap[nextcity][curNRCount] = curtime + nexttime;
				pq.push({ -gTimemap[nextcity][curNRCount], {nextcity, curNRCount} });
			}
		}
	}

	retval = gTimemap[gCityNum][0];
	for (int i = 0; i < NewRoadNum + 1; i++)
	{
		if (retval > gTimemap[gCityNum][i])
		{
			retval = gTimemap[gCityNum][i];
		}
	}
	return retval;
}

