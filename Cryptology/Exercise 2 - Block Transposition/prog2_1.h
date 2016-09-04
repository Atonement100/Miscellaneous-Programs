#ifndef Guard
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#endif // Guard

const std::string PadArg = "-p";
const std::string UnpadArg = "-u";
const std::string BlockArg = "-b";

bool PadInput = false;
int PadLength = 0;

int ProcessArgs(int argc, char* argv[]);
int CheckArg(std::string InArg, int ArgNum);
int ProcessInput();