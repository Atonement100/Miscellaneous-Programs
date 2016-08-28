// prog1_2.cpp : Defines the entry point for the console application.
//
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

	std::vector<std::string> Key(16);
	if (KeyIsBinary) {
		if (ProcessBinaryKeyFile(KeyFile, Key) != 0) return -1;
	}
	else {
		if (ProcessHexKeyFile(KeyFile, Key) != 0) return -1;
	}

	if (!Encrypt) { //i.e. Decrypting
		std::reverse(Key.begin(), Key.end());
	}

	if (ProcessInput(Key) != 0) return -1;
	std::cout << std::endl;
    return 0;
}

int ProcessInput(std::vector<std::string> &Key) {
	std::string InputStr;
	std::string WholeStr = "";
	while (std::cin >> std::skipws >> InputStr) {
		WholeStr.append(InputStr);
		while (WholeStr.length() >= 8) {
			if (ApplyKeyToByte(WholeStr.substr(0, 8), Key) != 0) {
				return -1;
			}
			WholeStr.erase(0, 8);
		}
		InputStr.clear();
	}
	return 0;
}

int ApplyKeyToByte(std::string ByteToConvert, std::vector<std::string> Key) {
	while (ByteToConvert.length() >= 4)
	{
		int KeyIndex = Conv_BinaryToDecimal(ByteToConvert.substr(0, 4));
		if (KeyIndex >= 0 && KeyIndex <= 15) {
			std::cout << Key[KeyIndex];
			ByteToConvert.erase(0, 4);
		}
		else {
			std::cerr << "Non binary character in input." << std::endl;
			return -1;
		}
	}
	return 0;
}

int Conv_BinaryToDecimal(std::string NibbleToConvert)
{
	int Value = 0;
	for (int Index = NibbleToConvert.length() - 1; Index >= 0; Index--) {
		if (NibbleToConvert[Index] == '0') {
			continue;
		}
		else if (NibbleToConvert[Index] == '1') {
			Value += pow((float)2, (int)(NibbleToConvert.length() - 1 - Index));
		}
		else {
			return -1;
		}
	}
	return Value;
}



int ProcessBinaryKeyFile(std::ifstream& KeyFile, std::vector<std::string> &Key)
{
	std::string InputStr = "";
	std::string TempStr;
	while (KeyFile >> std::skipws >> TempStr) {
		InputStr.append(TempStr);
	}

	if (InputStr.length() != 64) {
		std::cerr << "Either a malformed binary key file has been passed, or the -x flag should have been used (i.e. for a hex key file)." << std::endl;
		return -1;
	}

	if (CheckBinaryString(InputStr, Key) != 0) {
		return -1;
	}
	/*
	for (int Index = 0; Index < InputStr.length(); Index += 4) {
		if (CheckBinaryNibble(InputStr.substr(Index, 4), Key, Index/4) != 0) return -1;
	}
	*/

	return 0;
}

int CheckBinaryString(std::string InputStr, std::vector<std::string> &Key) {
	for (int Index = 0; Index < InputStr.length(); Index += 4) {
		if (CheckBinaryNibble(InputStr.substr(Index, 4), Key, Index / 4) != 0) return -1;
	}
}

int ProcessHexKeyFile(std::ifstream& KeyFile, std::vector<std::string> &Key)
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

	std::string BinaryStr = "";
	for (int Index = 0; Index < InputStr.length(); Index++) {
		TempStr = Conv_HexToBinary(InputStr[Index]);
		if (TempStr == ERROR_STRING) {
			std::cerr << "Malformed hex key (non-hex character)." << std::endl;
			return -1;
		}
		BinaryStr.append(TempStr);
	}

	if (CheckBinaryString(BinaryStr, Key) != 0) return -1;

	return 0;
}

int CheckBinaryNibble(std::string Nibble, std::vector<std::string> &Key, int KeyIndex)
{
	//std::cout << "processing nibble: " << Nibble << std::endl;
	/*Ensure nibble is binary*/
	for (int NibbleIndex = 0; NibbleIndex < Nibble.length(); NibbleIndex++) {
		if (Nibble[NibbleIndex] == '0' || Nibble[NibbleIndex] == '1') {
			continue;
		}
		else {
			std::cerr << "Malformed binary key (non binary values in key)." << std::endl;
			return -1;
		}
	}

	/*Ensure nibble isn't already in array*/
	if (std::find(Key.begin(), Key.end(), Nibble) == Key.end()) {
		Key[KeyIndex] = Nibble;
	}
	else{
		std::cerr << "Malformed binary key (key is not a permutation)." << std::endl;
		return -1;
	}

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
			//if (VerifyFilename(FilenameToOpen) != 0) {
			//	return -1;
			//}
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

int VerifyFilename(std::string Filename)
{
	int ExtensionStart = Filename.find('.');
	if (ExtensionStart == std::string::npos || Filename.substr(ExtensionStart + 1, 3) != "txt") {
		std::cerr << "Invalid file extension (should be .txt)" << std::endl;
		return -1;
	}
	return 0;
}

std::string Conv_HexToBinary(char ToConvert)
{
	switch (ToConvert) {
	case '0': return "0000"; break;
	case '1': return "0001"; break;
	case '2': return "0010"; break;
	case '3': return "0011"; break;
	case '4': return "0100"; break;
	case '5': return "0101"; break;
	case '6': return "0110"; break;
	case '7': return "0111"; break;
	case '8': return "1000"; break;
	case '9': return "1001"; break;
	case 'a':
	case 'A': return "1010"; break;
	case 'b':
	case 'B': return "1011"; break;
	case 'c':
	case 'C': return "1100"; break;
	case 'd':
	case 'D': return "1101"; break;
	case 'e':
	case 'E': return "1110"; break;
	case 'f':
	case 'F': return "1111"; break;
	default: return ERROR_STRING; break;
	}
}

