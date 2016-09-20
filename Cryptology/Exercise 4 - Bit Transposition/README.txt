prog4_1 should be run as ./prog4_1 (-e|-d) (-b<n>) -k<filename> < in > out
All parameters are optional.
-e and -d are exclusive and represent encrypt and decrypt respectively. Default is encrypt.
-b<n> can be used with a positive integer n to change the block size. Default is 8.
-k<filename> is required and provides the name of the keyfile. Should be used like -kKeyFile.txt
No known bugs.