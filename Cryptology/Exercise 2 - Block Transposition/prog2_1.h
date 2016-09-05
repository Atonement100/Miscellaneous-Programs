#ifndef Guard
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#endif // Guard

const std::string PadArg = "-p";
const std::string UnpadArg = "-u";
const std::string BlockArg = "-b";

bool ShouldPadInput = false;
int PadLength = 8;

int PadInput();
int UnpadInput();
int ProcessArgs(int argc, char* argv[]);
int CheckArg(std::string InArg, int ArgNum);
int ProcessInput();