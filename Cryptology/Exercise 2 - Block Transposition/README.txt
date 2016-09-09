prog1_1 should be run as ./prog2_1 [-p|-u] (-b<n>) < in > out 
Requires -p or -u to run, -b<n> is optional and defaults to 8 if not provided.
No known bugs.

prog1_2 should be run as ./prog2_2 [-e|-d] (-b<n>) -k<filename> < in > out
Requires -e or -d to run, -b<n> is optional and defaults to 8 if not provided.
Final argument should look like -kKeyInput.txt, for example.
No known bugs.