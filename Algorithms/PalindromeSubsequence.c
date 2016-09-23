/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Author: Timothy Russell-Wagner										 * 
 * Solution to longest palindromic subsequence problem in O(n^2) time	 * 
 * Written to prove viability of solution for Analysis of Algorithms	 * 
 * CLRS Problem 15-2													 * 
 * 																		 * 
 * After development of this solution, it turned out that there is		 * 
 * actually an existing O(n) time solution. . .							 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> //So I don't have to write a function int max(a,b) :-)

#define PRINT_FULL_ARRAY true 

int main(int argc, char* argv[]){
	std::cout << "Please input string to be checked for its longest palindromic subsequence:" << std::endl;
	std::string Input;
	getline(std::cin, Input);
	
	std::vector< std::vector<int> > Cost;
	Cost.resize(Input.length()+1, std::vector<int>(Input.length()+1, 0));

	for (unsigned int FwdIndex = 1; FwdIndex < Input.length()+1; FwdIndex++){
		int x = FwdIndex; //Redefined as x to be analogue to y
		for (unsigned int RevIndex = Input.length(); RevIndex > 0; RevIndex--){
			int y = Input.length() - RevIndex + 1; //Redefined to be much more readable
			if (Input[FwdIndex-1] == Input[RevIndex-1]) {
				Cost[y][x] = Cost[y-1][x-1]+1;		//Arrays were initially referred to by x,y
			}										//y,x makes the array much more human-readable, however
			else{
				Cost[y][x] = std::max(Cost[y-1][x], Cost[y][x-1]);
			}
		}		
	}		
		
	if(PRINT_FULL_ARRAY){
		unsigned int DisplayShift = 4;
		unsigned int DisplayLength = Input.length() + DisplayShift;
		for (unsigned int Index = 0; Index < DisplayLength; Index++){
			if(Index < DisplayShift) std::cout << " ";
			else std::cout << Input[Index - DisplayShift] << " ";

			if (Index == DisplayLength-1) std::cout << std::endl;
		}	
	
		for (unsigned int IndexX = 0; IndexX < Cost.size(); IndexX++){
			for (unsigned int IndexY = 0; IndexY < Cost[IndexX].size()+1; IndexY++){
				if (IndexY == 0) {
					std::cout << Input[Input.length()-1 - IndexX+1] << " ";
				}
				else{
					std::cout << Cost[IndexX][IndexY-1] << " ";
				}
			}
			std::cout << std::endl;
		}
	}

	//Backtracking for palindrome!
	std::string Palindrome = ""; 
	//Since it's a palindrome, we don't have to construct it in reverse order...
	int x = Cost.size()-1, y = Cost[x].size()-1;
	int CostRemaining = Cost[x][y];
	while (CostRemaining > 0){
		if (Cost[x][y] == Cost[x][y-1]){
			y--;
			continue;
		}
		else if (Cost[x][y] == Cost[x-1][y]){
			x--;
			continue;
		}
		else {
			Palindrome += Input[y-1];
			x--;
			y--;	
			CostRemaining--;
			continue;
		}
	}	

	std::cout << "A longest palindromic subsequence of " << Input << " is " << Palindrome << std::endl;
	return 0;
}
