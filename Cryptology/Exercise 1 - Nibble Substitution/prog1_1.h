#ifndef Guard
#include <iostream>
#include <cstdio>
#include <math.h>
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

int Conv_BinaryToHex(char ToConvert);
int Conv_HexToBinary(char ToConvert);

void ProcessIdentity();
void VerifyBinaryInput(std::string In);
void VerifyHexInput(std::string In);
//void ProcessBinaryToBinary(); //@DEPRECATED: Replaced with ProcessIdentity
int ProcessBinaryToHex();
int ProcessHexToBinary();
//void ProcessHexToHex(); //@DEPRECATED: Replaced with ProcessIdentity


void CheckArg(std::string InArg);
void PrintIOTypes();