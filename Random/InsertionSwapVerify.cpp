//By: Timothy Russell-Wagner
//Quick implementation of insertion sort based on pseudocode
//Intended to simply verify that the number of swaps in insertion sort
//is equal to the number of inversions in the original array

#include <iostream>
#include <vector>
using namespace std;

int main() {
	int swaps = 0;
	
	vector<int> vec(50);
	int size = vec.size();
	for (int i = 0; i < size; i++){
		vec[i] = size-i;
	}
	
	for (int i = 1; i < size; i++){
		int j = i;
		int temp;
		while (j > 0 && vec[j-1] > vec[j]){
			temp = vec[j-1];
			vec[j-1] = vec[j];
			vec[j] = temp;
			j--;
			swaps++;
			
		}
	}
	
	std::cout << "swaps = " << swaps << std::endl << "inversions = " << size * (size - 1) / 2;
	return 0;
}