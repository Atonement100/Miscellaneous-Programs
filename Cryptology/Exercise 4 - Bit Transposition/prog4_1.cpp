// Author: Timothy Russell-Wagner
// CIS4362 Exercise 4, Program 4-1
// Rough project specification:
/*
	> Reads stdin in binary (ascii)
	> Run as ./prog4_1 (-e|-d) (-b<n>) -k<filename>
	
	> Read n bytes at a time, reorder them according to permuation given in file
		> Output block of bytes in the mutated order
		> Input file must be a multiple of n bytes 
			> Else output error message to stderr
			> Final block should not be output (if bad input)
		> Key file is 8n bytes long 
			> One byte per position
			> Encodes 8n bit positions, one byte per position
			> Must be unique values in range of [0, 8n-1]

	> [-e] Encryption
		> Permutation is specified by position of key byte
			> i.e. OutputBlock[Keyfile[i]] = InputBlock[i];
			> OutputBlock is broken up by bits, i.e. each Keyfile[i] will be in the range [0,64) by default.
			> For each block with size specified by -b<n>, the most significant bit is n-1, and the least significant is n-n. 

	> [-d] Decryption
		> Invert permutation before applying encryption method

	> Important error checks:
		> Missing key file
		> Invalid permutation of bytes
		> Invalid input file length (not multiple of n bytes)
		> Report to stderr, return with non-zero exit code.
*/

#include "prog4_1.h"


int main(int argc, char * argv[])
{
	if (ProcessArgs(argc, argv) != 0) return -1;
	std::ifstream KeyFile;
	KeyFile.open(FilenameToOpen.c_str());
	if (!KeyFile.is_open()) {
		std::cerr << "Error opening file with filename " << FilenameToOpen << ". Exiting." << std::endl;
		return -1;
	}

	std::vector<int> Key(BlockSizeInBits);
	if (ProcessKeyFile(KeyFile, Key) != 0) return -1;
	if (!ShouldEncrypt) InvertKey(Key);

	if (ProcessInput(Key) != 0) return -1;

	return 0;
}

int ProcessInput(std::vector<int> &Key) {
	char Input;
	std::string InString = "";
	while (std::cin.get(Input)) {
		InString += Input;
		while (InString.length() >= BlockSize) {
			std::string OutBlock = Encrypt(InString.substr(0, BlockSize), Key);
			std::cout << OutBlock;
			InString.erase(0, BlockSize);
		}
	}

	if (InString.length() != 0) {
		std::cerr << "Input is not padded to a multiple of n bytes. Number of bytes discarded: " << InString.length() << std::endl;
		return -1;
	}

	return 0;
}

int InvertKey(std::vector<int>& Key) {
	std::vector<int> TempKey(Key.size());
	for (unsigned int Index = 0; Index < Key.size(); Index++) {
		TempKey[Key[Index]] = Index;
	}
	Key = TempKey;
	return 0;
}

int ProcessKeyFile(std::ifstream& KeyFile, std::vector<int> &Key) {
	std::string InputStr = "";
	char Input;
	while (KeyFile.get(Input)) { InputStr += Input; }

	if (InputStr.length() != BlockSizeInBits) {
		std::cerr << "Keyfile is not the correct size - should be equal to the given block size." <<  std::endl;
		return -1;
	}

	if (CheckBinaryString(InputStr, Key) != 0) return -1;

	return 0;
	
}

int CheckBinaryString(std::string InputStr, std::vector<int> &Key) {
	std::vector<bool> NumUsed(InputStr.length());
	for (unsigned int Index = 0; Index < NumUsed.size(); Index++) { NumUsed[Index] = false; }

	for (unsigned int Index = 0; Index < InputStr.length(); Index++) {
		int DecChar = (int)InputStr[Index];
		if (DecChar < 0) DecChar += 256;
		
		if ((unsigned int)DecChar > InputStr.length() - 1) { //Safe to cast to unsigned int because inputstr can only have values in range [-128,128), and we add 256 to any negative values
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

int ProcessArgs(int argc, char* argv[]) {
	if (argc > 4) {
		std::cerr << "Invalid number of arguments passed. Usage is (-e|-d) (-b<n>) -k<filename>." << std::endl;
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

std::string Encrypt(std::string InputString, std::vector<int>& Key)
{
	std::string NewString = "";
	std::vector<unsigned char> Output(BlockSize);
	for (unsigned int Index = 0; Index < InputString.length(); Index++) {
		for (unsigned short BitIndex = 0; BitIndex < 8; BitIndex++) { 			// < 8 since a byte is 8 bits...
			if((InputString[Index] >> (7-BitIndex)) & 1){								// MSB is char[7], LSB is char[0], so we subtract from 7 to get index within char
				Output[Key[Index*8+BitIndex]/BlockSize] += pow(2,7-Key[Index*8+BitIndex]%8);		// Find which byte the key wants the bit we are processing to go, then add 2^x to that byte
																										// where x is the significance within the byte.
			}
		}
	}

	for (unsigned int Index = 0; Index < Output.size(); Index++){
		NewString += (Output[Index]);
	}
	return NewString;
}

int CheckArg(std::string InArg, int ArgNum, int ArgCount) {
	switch (ArgNum) {
	case 1:
		if (InArg == EncryptIn) {
			ShouldEncrypt = true;
			return 0;
		}
		else if (InArg == DecryptIn) {
			ShouldEncrypt = false;
			return 0;
		}
		//Defaults to encrypt, fallthrough if not passed
	case 2:
		if (InArg.substr(0, 2) == BlockArg) {
			BlockSize = atoi((InArg.substr(2)).c_str());
			if (BlockSize < 1) {
				std::cerr << "Invalid pad length. Must be greater than zero." << std::endl;
				return -1;
			}
			BlockSizeInBits = BlockSize * 8;
			return 0;
		}
		//Defaults to blocksize 8, fallthrough if not passed
	case 3:
		if (InArg.substr(0, 2) == FileIn) {
			FilenameToOpen = InArg.substr(2); //Validity of this filename is checked when we open it
			return 0;
		}
	default:
		std::cerr << "Either an invalid parameter or an invalid number of parameters has been passed." << std::endl;
		return -1;
	}
}
