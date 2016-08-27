#ifndef Guard
#include <iostream>
#include <cstdio>
#include <string>
#endif // Guard


bool InputIsBinary = true;
bool OutputIsBinary = false;
const std::string BinIn = "-bin";
const std::string BinOut = "-bout";
const std::string HexIn = "-xin";
const std::string HexOut = "-xout";
static const std::string ERROR_STRING = "ERROR";

void ProcessArgs(int argc, char* argv[]);
void ProcessInput();

std::string Conv_HexToBinary(char ToConvert);

void ProcessIdentity();
void ProcessBinaryToBinary();
void ProcessBinaryToHex();
int ProcessHexToBinary();
void ProcessHexToHex();


void CheckArg(std::string InArg);
void PrintIOTypes();