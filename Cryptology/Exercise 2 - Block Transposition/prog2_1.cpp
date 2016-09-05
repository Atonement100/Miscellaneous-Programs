// Author: Timothy Russell-Wagner
// CIS4362 Exercise 2, Program 2-1
// Rough project specification:
/*
	> Reads stdin in binary (ascii)
	> Run as ./prog2_1 [-p|-u] (-b<n>)
		> -p pad
			> Outputs input data in binary (ascii) padded to multiple of n bytes
			> Each padding byte is equal to value of n
		> -u unpad
			> Removes all padding bytes, outputs unpadded data in binary (ascii)
			> If padding is incorrect, outputs error message to stderr
			> May produce partial output if padding is incorrect
				> i.e. last block may or may not be output
		> -b<n> block <length>
			> n is block length in bytes
			> default n = 8
			> Padding is between 1 and n bytes (to reach multiple of n)
*/

#include "prog2_1.h"

int main(int argc, char * argv[])
{
	if (ProcessArgs(argc, argv) != 0) return -1;

	if (ProcessInput() != 0) return -1;

	return 0;
}

int ProcessInput() {
	if (ShouldPadInput) {
		if (PadInput() != 0) return -1;
	}
	else {
		if (UnpadInput() != 0) return -1;
	}
	return 0;
}

int PadInput() {
	char Input;
	std::string InputStr;
	while (std::cin.get(Input)) {
		InputStr += Input;
		while (InputStr.length() >= PadLength) {
			std::cout << InputStr.substr(0, PadLength);
			InputStr.erase(0, PadLength);
		}
	}

	//Check for leftover inputstr after all input is processed
	if (InputStr.length() > 0) {
		int RemainingLength = PadLength - InputStr.length();
		std::cout << InputStr << std::string(RemainingLength, (char)PadLength);
	}
	else {
		std::cout << std::string(PadLength, (char)PadLength);
	}

}

int UnpadInput() {
	char Input;
	std::string InputStr;
	while (std::cin.get(Input)) {
		InputStr += Input;
		while (InputStr.length() > PadLength) {
			std::cout << InputStr.substr(0, PadLength);
			InputStr.erase(0, PadLength);
		}
	}

	if (InputStr.length() == PadLength) {

		//Minimum required padding is 1 byte at end of input. While there may be multiple padding bytes, there needs to only be one to assume padded input
		if (InputStr[InputStr.length()-1] == (char)PadLength) {
			std::cout << InputStr.substr(0, InputStr.find_last_not_of((char)PadLength) + 1);
		}
		else {
			std::cerr << "Input is invalid for this padding size" << std::endl;
			return -1;
		}
	}
	else {
		std::cerr << "Invalid unpad input. File was not a multiple of n bytes given. Did you mean to pad input?" << std::endl;
		return -1;
	}
	return 0;
}

int ProcessArgs(int argc, char* argv[]) {
	if (argc < 2 || argc > 3) {
		std::cerr << "Invalid number of argument passed. Usage is [-p|-u] (-b<n>)." << std::endl;
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
	switch (ArgNum) {
	case 1:
		if (InArg == PadArg) {
			ShouldPadInput = true;
		}
		else if (InArg == UnpadArg) {
			ShouldPadInput = false;
		}
		else {
			std::cerr << "First parameter invalid. Should be [-p|-u]." << std::endl;
			return -1;
		}
		return 0;
	case 2:
		if (InArg.substr(0, 2) == BlockArg) {
			PadLength = atoi((InArg.substr(2)).c_str());
			if (PadLength < 1) {
				std::cerr << "Invalid pad length. Must be greater than zero." << std::endl;
				return -1;
			}
		}
		else {
			std::cerr << "Second parameter invalid. Should be -b<n>." << std::endl;
			return -1;
		}
		return 0;
	default:
		std::cerr << "Invalid number of parameters" << std::endl;
		return -1;
	}
}