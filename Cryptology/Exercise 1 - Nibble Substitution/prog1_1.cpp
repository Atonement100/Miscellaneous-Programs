// prog1_1.cpp : Defines the entry point for the console application.
//
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
				std::cout << "WARNING: Error(s) found in the binary input. Non-binary input has been omitted from the output." << std::endl;
			}
		}
	}
	else {
		if (OutputIsBinary) {
			if (ProcessHexToBinary() != 0) {
				std::cout << "WARNING: Error(s) found in the ASCII-coded hexadecimal input. Non-hex input has been omitted from the output." << std::endl;
			}
		}
		else {
			ProcessIdentity(); //Hex to Hex
		}
	}
}

void ProcessIdentity() {
	std::string InputStr;
	while (std::cin >> std::skipws >> InputStr) {
		std::cin.ignore();
		std::cout << InputStr;
	}
	std::cout << std::endl;
}

char Conv_BinaryToHex(std::string ToConvert) {
	
	int Value = 0;
	for (int Index = ToConvert.length() - 1; Index >= 0; Index--) {
		if (ToConvert[Index] == '0') {
			continue;
		}
		else if (ToConvert[Index] == '1'){
			Value += pow((float)2, (int)(ToConvert.length() - 1 - Index));
		}
		else {
			return 'Z';
		}
	}

	if (Value >= 0 && Value <= 9) {
		return (char)(48 + Value); 
	}
	else if (Value >= 10 && Value <= 16) {
		return (char)(65 + Value - 10);
	}
	else {
		return 'Z';
	}
}

int ProcessBinaryToHex(){
	std::string InputStr = "";
	std::string Output = "";
	std::string TempStr;
	bool ReturnWithWarning = false;
	int NibblesInLine = 0;
	while (std::cin >> std::skipws >> TempStr) {
		InputStr.append(TempStr);
	}

	for (int Index = 0; Index < InputStr.length(); Index += 4) {
		char Nibble = Conv_BinaryToHex(InputStr.substr(Index, 4));

		if (Nibble == 'Z') ReturnWithWarning = true;

		if (NibblesInLine % 2 == 0) {
			Output.append(1, (char)(Nibble));
			NibblesInLine++;
		}
		else {
			Output.append(1, (char)(Nibble));
			Output.append(" ");
			NibblesInLine++;
		}

		if (NibblesInLine == 32) {
			std::cout << Output << std::endl;
			Output.clear();
			NibblesInLine = 0;
		}
	}

	std::cout << Output << std::endl;
	if (ReturnWithWarning) return -1;
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

int ProcessHexToBinary() {
	std::string InputStr;
	std::string Output;
	bool ReturnWithWarning = false;
	while (std::cin >> std::skipws >> InputStr) {
		Output.clear();
		std::cin.ignore();
		std::string TempStr;
		for (int Index = 0; Index < InputStr.length(); Index++) {
			TempStr = Conv_HexToBinary(InputStr[Index]);
			if (TempStr == ERROR_STRING) { ReturnWithWarning = true; continue; }
			Output.append(TempStr);
		}
		std::cout << Output;
	}
	std::cout << std::endl;
	if (ReturnWithWarning) return -1;
	return 0;
}

void ProcessArgs(int argc, char * argv[])
{
	if (argc == 1) {
		//std::cout << "No arguments passed. Assuming binary input and ASCII coded hex output." << std::endl << "Valid arguments are " << BinIn << ", " << BinOut << ", " << HexIn << ", " << HexOut << std::endl;
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
		std::cout << "Invalid argument passed, ignoring. Valid arguments are " << BinIn << ", " << BinOut << ", " << HexIn << ", " << HexOut << std::endl;
	}
}

void PrintIOTypes() {
	std::cout << "Input Type: " << (InputIsBinary ? "Binary" : "Hex") << std::endl << "Output Type: " << (OutputIsBinary ? "Binary" : "Hex") << std::endl;
}