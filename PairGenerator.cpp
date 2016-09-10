/*
By: Timothy Russell-Wagner
Quick program hashed together to take a vector of some length, assign random bool values to each index
and then remove any pairs (i,j) where i is divisible by 2 and j = i + 1 that do not have equal values.
This was used to help analyze a problem with the following specification.

Chip A says | Chip B says  | Conclusion
B is good   | A is good    | both are good, or both are bad
B is good   | A is bad     | at least one is bad
B is bad    | A is good    | at least one is bad
B is bad    | A is bad     | at least one is bad

Consider the problem of finding a single good chip from among n chips, assuming
that more than n/2 of the chips are good. Show that floor(n/2) pairwise
tests are sufficient to reduce the problem to one of nearly half the size.

I used this to generate a small sample of pairs that should follow the specification, and then used
those pairs to test solutions. The solution that I've written for this is as follows.

For each pair in p, if the chips do not identify each other as good, then at least one is bad, 
so that pair should be discarded. For the remaining pairs in p, take the first chip of each pair and 
apply this method to pairs formed in the new group p. 

This will recursively eliminate all pairs that do not identify each other as good. 
When the number of items in the subset p after verifying that they identify each other 
as good is 1 or 2 (i.e. both identify as good, or the group is thrown away and 
the leftover chip that was not in a group), then those chips are good, since there are 
more good chips than bad chips. 

Note that this program only generates and eliminates the first level of chips. It does not carry out
the completed algorithm, though it would not be hard to implement from here.
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

int main() {
	srand(time(0));
	vector<bool> isGood(50);
	int bothGood = 0, bothBad = 0;
	
	if (isGood.size() % 2 != 0) {isGood.push_back(false);} //rest of code assumes length is even
	
	for (int i = 0; i < isGood.size(); i++){
		isGood[i] = ((rand() % 100) < 60);
	}
	
	for (int i = 0; i < isGood.size();){
		if(isGood[i] == isGood[i+1]){
			i += 2;
			isGood[i]? bothGood++:bothBad++;
		}else{
			isGood.erase(isGood.begin()+i, isGood.begin()+i+2);
		}	
	}
	
	for (int i = 0; i < isGood.size(); i += 2){
		cout << isGood[i] << " " << isGood[i+1] << endl;
	}
	cout << "Good pairs: " << bothGood << endl << "Bad pairs: " << bothBad;
	return 0;
}