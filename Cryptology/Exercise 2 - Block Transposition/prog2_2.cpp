// Author: Timothy Russell-Wagner
// CIS4362 Exercise 2, Program 2-2
// Rough project specification:
/*
	> Reads stdin in binary (ascii)
	> Run as ./prog2_2 [-e|-d] (-b<n>) -k<filename>
	
	> Read n bytes at a time, reorder them according to permuation given in file
		> Output block of bytes in the mutated order
		> Input file must be a multiple of n bytes 
			> Else output error message to stderr
			> Final block should not be output (if bad input)
		> Key file is n bytes long 
			> One byte per position
			> Must be unique values in range of [0, n-1]

	> [-e] Encryption
		> Permutation is specified by position of key byte
			> i.e. OutputBlock[Keyfile[i]] = InputBlock[i];

	> [-d] Decryption
		> Invert permutation before applying encryption method

	> Important error checks:
		> Missing key file
		> Invalid permutation of bytes
		> Invalid input file length (not multiple of n bytes)
		> etc
		> Report to stderr, return with non-zero exit code.
*/

#include "prog2_2.h"

int main(int argc, char * argv[])
{

}