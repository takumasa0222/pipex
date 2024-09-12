#!/bin/bash

echo -e  "\e[34mtest case 1: if first command cannot refer to infile what will be happend\e[0m"
./test/temp cat | grep $c > ./test/outfile_1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 2: if second command option doesn't exist what will be happend\e[0m"
ls -l | grep c$ > ./test/outfile_1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 3: if first command doesn't have permission to read what will be happend\e[0m"
 < ./test/no_permission ls -l | wc -l > ./test/outfile
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 4: if second command doesn't have permission to write what will be happend\e[0m"
 < ./test/infile_1 ls -l | wc -l > ./test/no_permission
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 5: if first command cannot refer anything what will be happend\e[0m"
 < ls -l | wc -l > ./test/outfile_1
echo -e "\e[31merr number is\e[0m" $?

# Because this case return invalid syntax skip the case.
# error message "bash: syntax error near unexpected token `newline'" and errno is 2
# echo -e  "\e[34mtest case 6: if second command cannot refer anything what will be happend\e[0m"
#  < ./test/infile_1 ls -l | wc -l >
# echo -e "\e[31merr number is\e[0m" $?

# it seemingly "nothing" is passed to the second command and second command should works without problem.
echo -e  "\e[34mtest case 6: if first command cannot be found what will be happend\e[0m"
 < ./test/infile_1 | cat > ./test/outfile_2
echo -e "\e[31merr number is\e[0m" $?

# it seemingly just creating outfile after executing first command and no error ruturn.
echo -e  "\e[34mtest case 7: if second command cannot be found what will be happend\e[0m" 
 < ./test/infile_1 ls -l |  > ./test/outfile_1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 8: if you can't access both file what will happend\e[0m"
touch test/infile_no_perm
touch test/outfile_no_perm
chmod 000 test/infile_no_perm
chmod 000 test/outfile_no_perm
 < ./test/infile_no_perm cat | wc -l > ./test/outfile_no_perm
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 9: if you can't access read file and doesn't exit outfile what will happend\e[0m"
touch test/infile_no_perm
chmod 000 test/infile_no_perm
rm -f test/non_exit_out
 < ./test/infile_no_perm cat | wc -l > ./test/non_exit_out
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 10: if you don't pass any command what will happend\e[0m"
touch test/infile
chmod 755 test/infile
 < ./test/infile | > ./test/outfile
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 11: if there is no permmision and no valid command what will happend\e[0m"
touch test/infile_no_perm
touch test/out_no_perm
chmod 000 test/infile_no_perm
chmod 000 test/out_no_perm
< test/infile_no_perm a | s > test/out_no_perm
echo -e "\e[31merr number is\e[0m" $?