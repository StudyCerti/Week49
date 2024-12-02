#include <iostream>
#include <vector>
#include <string>
int gSampleCount;
int gWorkCount;
char input;
int inputA, inputB, inputC;
std::vector<std::pair<int, int>> gNode; // first = parent, second = weight 

void add(int a, int b, int w);
std::string question(int a, int b);

int main()
{
	std::string result ="";
	while (true)
	{
		gNode.clear();
		std::cin >> gSampleCount >> gWorkCount;
		if (gSampleCount == 0 || gWorkCount == 0) break;

		gNode.push_back({ 0, 0 });
		for (int i = 0; i < gSampleCount; i++)
		{
			gNode.push_back({i+1, 0});
		}

		for (int i = 0; i < gWorkCount; i++)
		{
			std::cin >> input;
			if (input == '?')
			{
				std::cin >> inputA >> inputB;
				result = question(inputA, inputB);
				std::cout << result << "\n";
			}
			else if (input == '!')
			{
				std::cin >> inputA >> inputB >> inputC;
				add(inputA, inputB, inputC);
			}
		}
	}

	return 0;
}


void add(int a, int b, int w)
{
	// b = a + w
	gNode.at(a).first = b;
	gNode.at(a).second = w;
}

std::pair<int, int> find(int value)
{
	std::pair<int, int> retval;

	retval.first = gNode.at(value).first;
	retval.second = gNode.at(value).second;

	while (true)
	{
		if (retval.second == 0) break;
		retval.first = gNode.at(retval.first).first;
		retval.second = retval.second + gNode.at(retval.first).second;
	}
	return retval;
}

std::string question(int a, int b)
{
	// return b - a
	std::pair<int, int> A, B;

	A = find(a);
	B = find(b);

	if (A.first == B.first)
	{
		return  std::to_string(B.second - A.second);
	}
	else
	{
		return "UNKNOWN";
	}
}

