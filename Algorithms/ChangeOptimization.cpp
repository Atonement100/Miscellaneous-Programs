/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Author: Timothy Russell-Wagner										 * 
 * Solution to change-making problem in O(n*k) time, where n is the 	 * 
 * amount of change to make, and k is the number of denominations 		 *
 * available.															 *
 * Written to prove viability of solution for Analysis of Algorithms	 * 
 * CLRS Problem 16-1													 * 
 * 																		 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> //So I don't have to write a function int min(a,b) :-)

#define PRINT_FULL_ARRAY true 

int main(int argc, char* argv[]){
	if (argc != 2){
		std::cerr << "Invalid number of arguments, should be run as ./change filename.txt" << std::endl; 
		return -1;
	}

	std::ifstream DenomFile;
	DenomFile.open(argv[1]);

	if (!DenomFile.is_open()){
		std::cerr << "Error with opening filename " << argv[1] << ". Exiting." << std::endl;
		return -1;
	}
	std::cout << "Parsing coin denominations from input file . . ." << std::endl;
	std::vector<int> Denominations(0);
	int InDenom;
	
	while(DenomFile >> InDenom){
		Denominations.push_back(InDenom); 
	}


	std::cout << "Please input an integer value to be optimized for the given denominations: " << std::endl;
	int Total;
	std::cin >> Total;	
	
	std::vector< std::vector<int> > Coins;
	Coins.resize(Total+1, std::vector<int>(Denominations.size(), 0));

	for (int Cost = 1; Cost < Total+1; Cost++){
		int x = Cost; //Redefined as x for readability 
		Coins[x][0] = Cost;
		for (unsigned int Denom = 1; Denom < Denominations.size(); Denom++){
			int y = Denom; 
			if (Cost < Denominations[Denom]) {
				Coins[x][y] = Coins[x][y-1];		
			}
			else{
				Coins[x][y] = std::min(Coins[x-Denominations[y]][y] + 1, Coins[x][y-1]);
			}
		}		
	}		

	for (unsigned int i = 0; i < Coins.size(); i++){
		for (unsigned int k = 0; k < Coins[i].size(); k++){
			std::cout << Coins[i][k] << " ";
		}
		std::cout << std::endl;
	}


	std::cout << "Change should be made as follows: " << std::endl;

	int x = Coins.size()-1, y = Coins[x].size()-1;
	int CoinsRemaining = Coins[x][y];
	while (CoinsRemaining > 0){
		if (Coins[x][y] == Coins[x][y-1]){
			y--;
			continue;
		}
		else {
			std::cout << Denominations[y] << std::endl;
			x -= Denominations[y];
			CoinsRemaining--;
			continue;
		}
	}	

	return 0;
}
