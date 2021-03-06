// Author: Timothy Russell-Wagner
// CIS4362 Exercise 3, Program 3-1
// Rough project specification:
/*
	> Reads stdin in binary (ascii)
	> Counts the number of each char present in the input
	> Outputs the number of each value seen

	> Default: one char per line with char in ascii-coded hex, followed by a space, then the frequency count
	> If -n is passed, the char and the space are omitted (i.e. just frequencies)
	> If -c is passed, the space is replaced with a comma (i.e. char,frequency)
	> If -L<N> is passed, where N is an integer in the range [1,256]
		> N values/pairs are printed per line
			> 2 hex chars per char (XX) and a constant number of characters per frequency or percent value
			> Followed by semicolon and space after each frequency
		> Example with -L1 flag
		00 105;
		01   3;
		02  17;
		> Example with -c -L3 flag
		00,105; 01,  3; 02, 17;
	> If -p is passed, the percent (normalized frequency) is given with 1 decimal resolution instead of frequency
	> If -s is passed, the output is sorted from most frequent character to least frequent character.

	> Run as ./prog3_1 (-n|-c) (-L<N>) (-p) (-s) <in >out
*/

#include "prog3_1.h"

int main(int argc, char * argv[])
{
	if (ProcessArgs(argc, argv) != 0) return -1;
	if (ProcessInput() != 0) return -1;
	if (ProduceOutput() != 0) return -1;

	return 0;
}

int ProduceOutput() {
	int TotalChars = 0, MaxCount = 0, MaxLength = 0;
	bool CharHasLargeShare = false;
	char Delimiter = ' ';
	
	std::vector<int> IndexArray(256);
	for (int Index = 0; Index < IndexArray.size(); Index++) {
		IndexArray[Index] = Index;
	}
	
	AnalyzeInput(TotalChars, MaxCount, MaxLength);

	if (ShouldReplaceSpaces) Delimiter = ',';

	if (ShouldPrintFrequencies) { 
		std::cout.precision(1); 
		if (100*((float)MaxCount / (float)TotalChars) >= 10.0f) CharHasLargeShare = true;
	}

	if (ShouldSortOutput) {
		SortArrays(charCountTracker, IndexArray);
	}

	for (int Index = 0; Index < charCountTracker.size(); Index++) {
		if (!ShouldOmitSpaces) {
			std::cout << Conv_CharToHex(IndexArray[Index]) << Delimiter; //no else statement, simple omission if should omit. This is redundant if array is not sorted.
		}

		if (!ShouldPrintFrequencies) {
			//Print a certain number of spaces then value of count tracker
			int NumSpacesToPrint = 0, Temp = charCountTracker[Index];
			while (Temp /= 10) {
				NumSpacesToPrint++;
			}
			NumSpacesToPrint = MaxLength - NumSpacesToPrint;
			std::cout << std::string(NumSpacesToPrint,' ') << charCountTracker[Index] << "; ";
		}
		else {
			//Print 1 space if <10% then value of count tracker.
			float Percent = ((float)charCountTracker[Index] / (float)TotalChars)*100;
			if (CharHasLargeShare && Percent < 10.0f) std::cout << " ";
			std::cout << std::fixed << Percent << "; ";
		}
		if ((Index + 1) % ValuesPerLine == 0) { std::cout << std::endl; }
	}

	return 0;
}

int AnalyzeInput(int &CharCount, int &MaxCount, int &MaxLength) {
	CharCount = 0;
	MaxCount = 0;
	MaxLength = 0;
	for (int Index = 0; Index < charCountTracker.size(); Index++) {
		int Temp = charCountTracker[Index];
		CharCount += Temp;
		if (Temp > MaxCount) MaxCount = Temp;
	}
	
	int MaxCtCopy = MaxCount;
	while (MaxCtCopy /= 10) {
		MaxLength++;
	}
}

//Takes int, but assumes int8. Not hard to extend to larger int with loop though
std::string Conv_CharToHex(int ToConvert) {
	short Input = ToConvert;
	if (Input < 0) Input += 256;
	int Low = Input % 16;
	int High = (Input > 15) ? (Input - Low) / 16 : 0;

	std::string ToReturn = "";
	if (High < 10) ToReturn += (char)(High + '0');
	else ToReturn += (char)(High - 10 + 'a');

	if (Low < 10) ToReturn += (char)(Low + '0');
	else ToReturn += (char)(Low - 10 + 'a');
	
	return ToReturn;
}

int SortArrays(std::vector<int>& CountTracker, std::vector<int>& IndexArray){
	for (int MainIndex = 0; MainIndex < CountTracker.size(); MainIndex++) {
		int CtValue = CountTracker[MainIndex], 
			CtIndex = IndexArray[MainIndex], 
			SwapIndex = MainIndex - 1;
		while (SwapIndex >= 0 && CountTracker[SwapIndex] < CtValue) {
			CountTracker[SwapIndex + 1] = CountTracker[SwapIndex];
			IndexArray[SwapIndex + 1] = IndexArray[SwapIndex];
			SwapIndex--;
		}
		CountTracker[SwapIndex + 1] = CtValue;
		IndexArray[SwapIndex + 1] = CtIndex;
	}

	return 0;
}

int ProcessInput() {
	std::fill(charCountTracker.begin(), charCountTracker.end(), 0);
	char InputChar;
	while (std::cin.get(InputChar)) {
		int Index = ((InputChar < 0) ? (256 + (int)InputChar) : (int)InputChar);
		charCountTracker[Index]++;
	}
	return 0;
}

int ProcessArgs(int argc, char* argv[]) {
	if (argc > 5) {
		std::cerr << "Too many arguments passed. Usage is (-n|-c) (-L<N>) (-p) (-s)." << std::endl;
		return -1;
	}
	else {
		std::string* Arguments = new std::string[argc - 1];
		for (int Args = 1; Args < argc; Args++) {
			Arguments[Args - 1] = std::string(argv[Args]);
			if (CheckArg(Arguments[Args - 1], Args) == 0) continue;
			else {
				return -1;
			}
		}
	}

	return 0;
}

int CheckArg(std::string InArg, int ArgNum) {
	//The idea of this is to allow all inputs to be optional, so fallthrough is allowed if an argument is not found at its intended position. If it is found nowhere, then we will fall through to the default case
	//where we will recognize that it's not a good input, or it was put in the wrong place. This does require flags to come no later than expected, but they may come earlier. 

	//This could be made more rigorous to check if arguments that should come after a given argument have been called. For example, -s -p will work as long as there are 3 or less arguments, but -s -p is in the wrong order.
	//Checking if -s has been called (i.e. ShouldSortOutput == true) 
	switch (ArgNum) {
	case 1:
		if (InArg == OmitSpacesArg) {
			ShouldOmitSpaces = true;
			break;
		}
		else if (InArg == ReplaceSpacesArg){
			ShouldReplaceSpaces = true;
			break;
		}
		//If neither of those, then it's probably been omitted or is not a valid argument, drop down.
	case 2:
		if (InArg.substr(0,2) == MultiLineArg) {
			ValuesPerLine = atoi((InArg.substr(2)).c_str());
			if (ValuesPerLine < 1 || ValuesPerLine > 256) {
				std::cerr << "Invalid number of characters per line. Must be in the range [1,256]." << std::endl;
				return -1;
			}
			else {
				break;
			}
		}
		//If not this arg, it's probably been omitted or is not a valid argument, drop down.
	case 3:
		if (InArg == FrequencyArg) {
			ShouldPrintFrequencies = true;
			break;
		}
		//Fall through if arg not yet found
	case 4:
		if (InArg == SortArg) {
			ShouldSortOutput = true;
			break;
		}
	default:
		std::cerr << "An invalid number of parameters, an invalid parameter, or an out of order parameter has been passed.\nUsage should follow (-n|-c) (-L<N>) (-p) (-s)" << std::endl;
		return -1;
	}

	return 0;
}