// Author: Timothy Russell-Wagner
// CIS4362 Exercise 2, Program 2-2
// Rough project specification:
/*
	> Reads stdin in binary (ascii)
	> Run as ./prog2_2 [-e|-d] (-b<n>) -k<filename>
	
	> Read n bytes at a time, reorder them according to permuation given in file
		> Output block of bytes in the mutated order
		> Input file must be a multiple of n bytes 
			> Else output error message to stderr
			> Final block should not be output (if bad input)
		> Key file is n bytes long 
			> One byte per position
			> Must be unique values in range of [0, n-1]

	> [-e] Encryption
		> Permutation is specified by position of key byte
			> i.e. OutputBlock[Keyfile[i]] = InputBlock[i];

	> [-d] Decryption
		> Invert permutation before applying encryption method

	> Important error checks:
		> Missing key file
		> Invalid permutation of bytes
		> Invalid input file length (not multiple of n bytes)
		> etc
		> Report to stderr, return with non-zero exit code.
*/

#include "prog2_2.h"


int main(int argc, char * argv[])
{
	if (ProcessArgs(argc, argv) != 0) return -1;
	std::ifstream KeyFile;
	KeyFile.open(FilenameToOpen.c_str());
	if (!KeyFile.is_open()) {
		std::cerr << "Error opening file with filename " << FilenameToOpen << ". Exiting." << std::endl;
		return -1;
	}

	std::vector<int> Key(BlockSize);
	if (ProcessKeyFile(KeyFile, Key) != 0) return -1;


	if (ProcessInput(Key) != 0) return -1;


	std::cout << "Should encrypt: " << ShouldEncrypt << "\nBlock Length: " << BlockSize << "\nFile opened: " << FilenameToOpen << "\nKey is: ";
	for (int i = 0; i < Key.size(); i++) {
		std::cout << Key[i];
	}
	std::cout << "\n";

	return 0;
}

int ProcessInput() {
	
	return 0;
}

int ProcessKeyFile(std::ifstream& KeyFile, std::vector<int> &Key)
{
	std::string InputStr = "";
	char Input;
	while (KeyFile.get(Input)) { InputStr += Input; }

	if (InputStr.length() != BlockSize) {
		std::cerr << "Keyfile is not the correct size - should be equal to the given block size." <<  std::endl;
		return -1;
	}

	if (CheckBinaryString(InputStr, Key) != 0) return -1;

	return 0;
	
}

int CheckBinaryString(std::string InputStr, std::vector<int> &Key) {
	std::vector<bool> NumUsed(InputStr.length());
	for (int Index = 0; Index < NumUsed.size(); Index++) { NumUsed[Index] = false; }

	for (int Index = 0; Index < InputStr.length(); Index++) {
		int DecChar = (int)InputStr[Index];
		if (DecChar < 0) DecChar += 256;
		
		if (DecChar > InputStr.length() - 1) {
			std::cerr << "Invalid byte in given keyfile (larger than block size)" << std::endl;
			return -1;
		}

		if (NumUsed[DecChar] == false) {
			NumUsed[DecChar] = true;
			Key[Index] = DecChar;
		}
		else {
			std::cerr << "Invalid permutation in the given keyfile." << std::endl;
			return -1;
		}
	}
	return 0;
}

int ProcessInput(std::vector<int> &Key) {

	return 0;
}



int ProcessArgs(int argc, char* argv[]) {
	if (argc < 3 || argc > 4) {
		std::cerr << "Invalid number of arguments passed. Usage is [-e|-d] (-b<n>) -k<filename>." << std::endl;
		return -1;
	}
	else {
		std::string* Arguments = new std::string[argc - 1];
		for (int Args = 1; Args < argc; Args++) {
			Arguments[Args - 1] = std::string(argv[Args]);
			if (CheckArg(Arguments[Args - 1], Args, argc) == 0) continue;
			else {
				return -1;
			}
		}
	}

	return 0;
}

int CheckArg(std::string InArg, int ArgNum, int ArgCount) {
	switch (ArgNum) {
	case 1:
		if (InArg == EncryptIn) {
			ShouldEncrypt = true;
		}
		else if (InArg == DecryptIn) {
			ShouldEncrypt = false;
		}
		else {
			std::cerr << "First parameter invalid. Should be [-e|-d]." << std::endl;
			return -1;
		}
		return 0;
	case 2:
		if (ArgCount == 4) {
			if (InArg.substr(0, 2) == BlockArg) {
				BlockSize = atoi((InArg.substr(2)).c_str());
				if (BlockSize < 1) {
					std::cerr << "Invalid pad length. Must be greater than zero." << std::endl;
					return -1;
				}
			}
			else {
				std::cerr << "Second parameter invalid. Should be -b<n>." << std::endl;
				return -1;
			}
		}
		//No return here, if arg count is less than 4, then we want to fallthrough to case 3. i.e. usage would be [-e|-d] -k<filename> in this case
	case 3:
		if (InArg.substr(0, 2) == FileIn) {
			if (InArg.substr(0, 2) == FileIn) {
				FilenameToOpen = InArg.substr(2);
			}
			else {
				std::cerr << "Second parameter invalid. Should be -k<filename>." << std::endl;
				return -1;
			}
			return 0;
		}
		return 0;
	default:
		std::cerr << "Invalid number of parameters" << std::endl;
		return -1;
	}
}