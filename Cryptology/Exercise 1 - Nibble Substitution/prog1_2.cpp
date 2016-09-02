// Author: Timothy Russell-Wagner
// CIS4362 Exercise 1, Program 1-2
// Rough project specification:
/*
	> Binary input, binary output
		> Divide bytes into nibbles
			> For each byte (upper->lower) substitute according to key file
			> Recombine into byte, output byte
	> Key file is 16 nibbles long
		> Can be bin / hex
		> Upper 0 Lower 0 Upper 1 Lower 1 etc
		> Each nibble must be unique

	> Encryption
		> 0000 replaced with whatever is in position 0
		> 0001 replaced with whatever is in position 1
		> . . .
		> 1111 replaced with whatever is in position 15

	> Decryption
		> Invert key first, then apply encryption method

	> Report errors to stderr, exit with non-zero code
		> Missing key file
		> Invalid permutation 


*/

#include "prog1_2.h"

int main(int argc, char * argv[])
{
	if (ProcessArgs(argc, argv) != 0) return -1;
	std::ifstream KeyFile;
	KeyFile.open(FilenameToOpen.c_str());
	if (!KeyFile.is_open()) {
		std::cerr << "Error opening file with filename " << FilenameToOpen << ". Exiting." << std::endl;
		return -1;
	}

	std::vector<int> Key(16);
	for (int Index = 0; Index < Key.size(); Index++) Key[Index] = -1;
	if (KeyIsBinary) {
		if (ProcessBinaryKeyFile(KeyFile, Key) != 0) return -1;
	}
	else {
		if (ProcessHexKeyFile(KeyFile, Key) != 0) return -1;
	}

	if (!Encrypt) { //i.e. Decrypting
		InvertKey(Key);
	}

	if (ProcessInput(Key) != 0) return -1;
	std::cerr << std::endl;
    return 0;
}

int ProcessInput(std::vector<int> &Key) {
	char Input;
	while (std::cin.get(Input)) {
		int DecChar = (int)Input;
		if (DecChar < 0) DecChar += 256;
		int HighNibble = (DecChar > 15) ? (DecChar - DecChar % 16)/16 : 0;
		int LowNibble = DecChar % 16;
		std::cout << (char)(Key[HighNibble] * 16 + Key[LowNibble]);
	}
	return 0;
}

int ProcessBinaryKeyFile(std::ifstream& KeyFile, std::vector<int> &Key)
{
	std::string InputStr = "";
	std::string TempStr;
	char Input;
	while (KeyFile.get(Input)) { InputStr += Input; }
	
	if (InputStr.length() != 8) {
		std::cerr << "Either a malformed binary key file has been passed, or the -x flag should have been used (i.e. for a hex key file)." << std::endl;
		return -1;
	}

	if (CheckBinaryString(InputStr, Key) != 0) return -1;
	return 0;
}

int CheckBinaryString(std::string InputStr, std::vector<int> &Key) {
	for (int Index = 0; Index < InputStr.length(); Index ++) {
		int DecChar = (int)InputStr[Index];
		if (DecChar < 0) DecChar += 256;
		int HighNibble = (DecChar > 15) ? (DecChar - DecChar % 16)/16 : 0;
		int LowNibble = DecChar % 16;

		if (CheckBinaryNibble(HighNibble, Key, Index*2) != 0) return -1;
		if (CheckBinaryNibble(LowNibble, Key, Index*2 + 1) != 0) return -1;
	}
}

int ProcessHexKeyFile(std::ifstream& KeyFile, std::vector<int> &Key)
{
	std::string InputStr = "";
	std::string TempStr;
	while (KeyFile >> std::skipws >> TempStr) {
		InputStr.append(TempStr);
	}

	if (InputStr.length() != 16) {
		std::cerr << "Either a malformed hex key file has been passed, or the -b flag should have been used (i.e. for a binary key file)." << std::endl;
		return -1;
	}

	for (int Index = 0; Index < InputStr.length(); Index++) {
		int Nibble = Conv_HexToBinary(InputStr[Index]);
		if (Nibble == -1) {
			std::cerr << "Malformed hex key (non-hex character)." << std::endl;
			return -1;
		}
		if (CheckBinaryNibble(Nibble, Key, Index) != 0) return -1;
	}

	return 0;
}

int CheckBinaryNibble(int Nibble, std::vector<int> &Key, int KeyIndex)
{
	if (std::find(Key.begin(), Key.end(), Nibble) == Key.end()) {
		Key[KeyIndex] = Nibble;
	}
	else{
		std::cerr << "Malformed binary key (key is not a permutation)." << std::endl;
		return -1;
	}
	return 0;
}

int InvertKey(std::vector<int>& Key)
{
	std::vector<int> TempKey(Key.size());
	for (int Index = 0; Index < Key.size(); Index++) {
		TempKey[Key[Index]] = Index;
	}
	Key = TempKey;
	return 0;
}

int ProcessArgs(int argc, char * argv[])
{
	if (argc != 4) {
		std::cerr << "Incorrect number of arguments passed. Usage is [-e|-d] [-k<filename>] [-x|-b]." << std::endl;
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
	if (ArgNum == 1) {
		if (InArg == EncryptIn) {
			Encrypt = true;
		}
		else if (InArg == DecryptIn) {
			Encrypt = false;
		}
		else {
			std::cerr << "First parameter invalid. Should be [-e|-d]." << std::endl;
			return -1;
		}
		return 0;
	}
	else if (ArgNum == 2) {
		if (InArg.substr(0, 2) == FileIn) {
			FilenameToOpen = InArg.substr(2);
		}
		else {
			std::cerr << "Second parameter invalid. Should be -k<filename>." << std::endl;
			return -1;
		}
		return 0;
	}
	else if (ArgNum == 3) {
		if (InArg == HexKey) {
			KeyIsBinary = false;
		}
		else if (InArg == BinKey) {
			KeyIsBinary = true;
		}
		else {
			std::cerr << "Third parameter invalid. Should be [-x|-b]." << std::endl;
			return -1;
		}
		return 0;
	}
}

int Conv_HexToBinary(char ToConvert)
{
	switch (ToConvert) {
	case '0': return 0; break;
	case '1': return 1; break;
	case '2': return 2; break;
	case '3': return 3; break;
	case '4': return 4; break;
	case '5': return 5; break;
	case '6': return 6; break;
	case '7': return 7; break;
	case '8': return 8; break;
	case '9': return 9; break;
	case 'a':
	case 'A': return 10; break;
	case 'b':
	case 'B': return 11; break;
	case 'c':
	case 'C': return 12; break;
	case 'd':
	case 'D': return 13; break;
	case 'e':
	case 'E': return 14; break;
	case 'f':
	case 'F': return 15; break;
	default: return -1; break;
	}
}

