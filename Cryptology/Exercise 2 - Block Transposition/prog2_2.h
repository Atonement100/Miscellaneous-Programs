#ifndef Guard
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#endif // Guard

const std::string EncryptIn = "-e";
const std::string DecryptIn = "-d";
const std::string BlockArg = "-b";
const std::string FileIn = "-k";

bool ShouldEncrypt = false;
int BlockSize = 8;
std::string FilenameToOpen;

int InvertKey(std::vector<int> &Key);
int ProcessArgs(int argc, char* argv[]);
int CheckArg(std::string InArg, int ArgNum, int ArgCount);
int ProcessInput(std::vector<int> &Key);
int ProcessKeyFile(std::ifstream& KeyFile, std::vector<int> &Key);
int CheckBinaryString(std::string Input, std::vector<int> &Key);