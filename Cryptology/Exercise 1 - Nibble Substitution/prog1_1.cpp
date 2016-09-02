// Author: Timothy Russell-Wagner
// CIS4362 Exercise 1, Program 1-1
// Rough project specification:
/*
	> Read in binary or hex
	> Output in binary or hex
	> When reading hex
		> Ignore whitespace
		> Non-hex values are errors
	> When writing hex
		> High nibble -> lower nibble -> space
		> 16 bytes (32 chars) per line
	> Bin to Bin is identity
	> Hex to Hex is identity
*/
#include "prog1_1.h"

int main(int argc, char* argv[])
{
	ProcessArgs(argc, argv);
	ProcessInput();

    return 0;
}

void ProcessInput() {
	if (InputIsBinary) {
		if (OutputIsBinary) {
			ProcessIdentity(); //Binary to Binary
		}
		else {
			if (ProcessBinaryToHex() != 0) {
				std::cerr << "WARNING: Error(s) found in the binary input. Non-binary input has been omitted from the output." << std::endl;
			}
		}
	}
	else {
		if (OutputIsBinary) {
			if (ProcessHexToBinary() != 0) {
				std::cerr << "WARNING: Error(s) found in the ASCII-coded hexadecimal input. Non-hex input has been omitted from the output." << std::endl;
			}
		}
		else {
			ProcessIdentity(); //Hex to Hex
		}
	}
}

void ProcessIdentity() {
	std::string InputStr;
	char Input;
	if (InputIsBinary) {
		while (std::cin.get(Input)) {
			std::cout << Input;
		}
	}
	else {
		while (std::cin.get(Input)) {
			if (Conv_HexToBinary(Input) != -1) {
				std::cout << Input;
			}
			else {
				std::cerr << "Potentially invalid input in hex string (or spaces are being culled)";
			}
		}
	}
	std::cout << std::endl;
}

void VerifyBinaryInput(std::string In) {
	for (int Index = 0; Index < In.length(); Index++) {
		if (In[Index] == '0' || In[Index] == '1') {
			std::cout << In[Index];
		}
		else {
			std::cerr << "Invalid input in binary string";
		}
	}
}

void VerifyHexInput(std::string In) {
	for (int Index = 0; Index < In.length(); Index++) {
		if (Conv_HexToBinary(In[Index]) != -1) {
			std::cout << In[Index];
		}
		else {
			std::cerr << "Invalid input in hex string";
		}
	}
}

int Conv_BinaryToHex(char ToConvert) {
	
	int Value = (int)(ToConvert);
	if (Value < 16) std::cout << "0";
	std::cout << std::hex << (int)ToConvert;
	return 0;
}

int ProcessBinaryToHex(){
	char Input;
	int BytesInLine = 0;

	std::string InputStr = "";
	std::string Output = "";
	std::string TempStr;
	bool ReturnWithWarning = false;
	int NibblesInLine = 0;
	while (std::cin.get(Input)) {
		if (NibblesInLine < 15) {
			Conv_BinaryToHex(Input);
			std::cout << " ";
			NibblesInLine++;
		}
		else {
			Conv_BinaryToHex(Input);
			std::cout << std::endl;
			NibblesInLine = 0;
		}
	}
	std::cout << std::endl;
	if (ReturnWithWarning) return -1;
	return 0;
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

int ProcessHexToBinary() {
	std::string InputStr;
	std::string Output;
	bool ReturnWithWarning = false;
	while (std::cin >> std::skipws >> InputStr) {
		std::string TempStr;
		int Value = 0;
		for (int Index = 0; Index < InputStr.length(); Index++) {
			int TempValue = Conv_HexToBinary(InputStr[Index]);
			if (TempValue == -1) {
				std::cerr << "Invalid hex input" << std::endl;
				return -1;
			}

			if (Index % 2 == 0) {
				Value += TempValue*16;
			}
			else {
				Value += TempValue;
				std::cout << (char)Value;
				Value = 0;
			}
		}
		
	}
	std::cout << std::endl;
	if (ReturnWithWarning) return -1;
	return 0;
}

void ProcessArgs(int argc, char * argv[])
{
	if (argc == 1) {
		std::cerr << "No arguments passed. Assuming binary input and ASCII coded hex output." << std::endl << "Valid arguments are " << BinIn << ", " << BinOut << ", " << HexIn << ", " << HexOut << std::endl;
	}
	else if (argc == 2) {
		std::string ArgOne = std::string(argv[1]);
		CheckArg(ArgOne);
	}
	else {
		std::string* Arguments = new std::string[argc - 1];
		for (int Args = 1; Args < argc; Args++) {
			Arguments[Args - 1] = std::string(argv[Args]);
			CheckArg(Arguments[Args - 1]);
		}
	}
}

void CheckArg(std::string InArg) {
	if (InArg == BinIn) {
		InputIsBinary = true;
	}
	else if (InArg == BinOut) {
		OutputIsBinary = true;
	}
	else if (InArg == HexIn) {
		InputIsBinary = false;
	}
	else if (InArg == HexOut) {
		OutputIsBinary = false;
	}
	else {
		std::cerr << "Invalid argument passed, ignoring. Valid arguments are " << BinIn << ", " << BinOut << ", " << HexIn << ", " << HexOut << std::endl;
	}
}

void PrintIOTypes() {
	std::cerr << "Input Type: " << (InputIsBinary ? "Binary" : "Hex") << std::endl << "Output Type: " << (OutputIsBinary ? "Binary" : "Hex") << std::endl;
}