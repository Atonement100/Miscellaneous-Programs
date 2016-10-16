#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() { //Question is asking something different from what the test cases expect...
			 //Asks for ReceivedBy, wants LikedBy.
	int EndDay, ReceivedBy = 5, LikedBy = floor(ReceivedBy / 2);
	std::cin >> EndDay;
	for (unsigned int Day = 1; Day < EndDay; Day++) {
		ReceivedBy = floor(ReceivedBy / 2) * 3;
		LikedBy += ReceivedBy / 3;
	}
	std::cout << LikedBy;
	return 0;
}
