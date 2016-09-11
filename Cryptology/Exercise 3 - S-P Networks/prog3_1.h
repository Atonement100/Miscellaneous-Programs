#ifndef Guard
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#endif // Guard

std::vector<int> charCountTracker(256);

const std::string OmitSpacesArg = "-n";
const std::string ReplaceSpacesArg = "-c";
const std::string MultiLineArg = "-L";
const std::string FrequencyArg = "-p";
const std::string SortArg = "-s";

bool ShouldOmitSpaces = false;
bool ShouldReplaceSpaces = false;
bool ShouldPrintFrequencies = false;
bool ShouldSortOutput = false;
int ValuesPerLine = 1;

int ProcessArgs(int argc, char* argv[]);
int CheckArg(std::string InArg, int ArgNum);
int ProcessInput();
int ProduceOutput();
int AnalyzeInput(int &CharCount, int &MaxCount, int &MaxLength);
std::string Conv_CharToHex(int ToConvert);

