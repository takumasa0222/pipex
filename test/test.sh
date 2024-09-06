#!/bin/bash

echo "test case 1: if first command cannot refer to infile what will be happend"
./test/temp cat | grep $c > ./test/outfile_1
echo "err number is" $?

echo "test case 2: if second command option doesn't exist what will be happend"
ls -l | grep c$ > ./test/outfile_1
echo "err number is" $?

echo "test case 3: if first command doesn't have permission to read what will be happend"
 < ./test/no_permission ls -l | wc -l > ./test/outfile
echo "err number is" $?

echo "test case 4: if second command doesn't have permission to write what will be happend"
 < ./test/infile_1 ls -l | wc -l > ./test/no_permission
echo "err number is" $?

echo "test case 5: if first command cannot refer anything what will be happend"
 < ls -l | wc -l > ./test/outfile_1
echo "err number is" $?

# Because this case return invalid syntax skip the case.
# error message "bash: syntax error near unexpected token `newline'" and errno is 2
# echo "test case 6: if second command cannot refer anything what will be happend"
#  < ./test/infile_1 ls -l | wc -l >
# echo "err number is" $?

# it seemingly "nothing" is passed to the second command and second command should works without problem.
echo "test case 6: if first command cannot be found what will be happend"
 < ./test/infile_1 | cat > ./test/outfile_2
echo "err number is" $?

# it seemingly just creating outfile after executing first command and no error ruturn.
echo "test case 7: if second command cannot be found what will be happend" 
 < ./test/infile_1 ls -l |  > ./test/outfile_1
echo "err number is" $?