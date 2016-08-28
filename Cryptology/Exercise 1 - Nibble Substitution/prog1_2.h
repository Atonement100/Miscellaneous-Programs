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


int ProcessArgs(int argc, char* argv[]);
int CheckArg(std::string InArg, int ArgNum);
int VerifyFilename(std::string Filename);
int ProcessBinaryKeyFile(std::ifstream& KeyFile, std::vector<std::string> &Key);
int CheckBinaryString(std::string InputStr, std::vector<std::string>& Key);
int ProcessHexKeyFile(std::ifstream& KeyFile, std::vector<std::string> &Key);
int CheckBinaryNibble(std::string Nibble, std::vector<std::string> &Key, int KeyIndex);
std::string Conv_HexToBinary(char ToConvert);