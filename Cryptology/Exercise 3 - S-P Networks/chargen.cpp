#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
int main(int argc, char* argv[]){
int toGen = 8;

if (argc == 2){
toGen = atoi(argv[1]);
}

for (int i = 0; i < toGen; i++){
std::cout << char(i);
}

}