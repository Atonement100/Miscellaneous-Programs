// Author: Timothy Russell-Wagner
// CIS4362 Exercise 2, Program 2-1
// Rough project specification:
/*
	> Reads stdin in binary (ascii)
	> Run as ./prog2_1 [-p|-u] (-b<n>)
		> -p pad
			> Outputs input data in binary (ascii) padded to multiple of n bytes
			> Each padding byte is equal to value of n
		> -u unpad
			> Removes all padding bytes, outputs unpadded data in binary (ascii)
			> If padding is incorrect, outputs error message to stderr
			> May produce partial output if padding is incorrect
				> i.e. last block may or may not be output
		> -b<n> block <length>
			> n is block length in bytes
			> default n = 8
			> Padding is between 1 and n bytes (to reach multiple of n)
*/

#include "prog2_1.h"

int main(int argc, char * argv[])
{

}