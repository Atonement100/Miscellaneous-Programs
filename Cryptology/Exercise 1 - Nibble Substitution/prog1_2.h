#ifndef Guard
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#endif // Guard

bool Encrypt = true;
bool KeyIsBinary = true;
const std::string EncryptIn = "-e";
const std::string DecryptIn = "-d";
const std::string HexKey = "-x";
const std::string BinKey = "-b";
const std::string FileIn = "-k";
const std::string ERROR_STRING = "NON_HEX_CHAR";
std::string FilenameToOpen;

int InvertKey(std::vector<int> &Key);
int ProcessArgs(int argc, char* argv[]);
int CheckArg(std::string InArg, int ArgNum);
int ProcessInput(std::vector<int>& Key);
int ProcessBinaryKeyFile(std::ifstream& KeyFile, std::vector<int> &Key);
int CheckBinaryString(std::string InputStr, std::vector<int>& Key);
int ProcessHexKeyFile(std::ifstream& KeyFile, std::vector<int> &Key);
int CheckBinaryNibble(int Nibble, std::vector<int> &Key, int KeyIndex);
int Conv_HexToBinary(char ToConvert);