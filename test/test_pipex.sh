#!/bin/bash
echo ""
echo "file exist test"
echo ""

echo -e  "\e[34mtest case 0: if there is no problem what will be happened\e[0m"
touch test/infile_1
touch test/outfile_1
chmod 664 test/infile_1
chmod 664 test/outfile_1
./pipex ./test/infile_1 "cat" "wc -l" ./test/outfile_1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 1: if first command cannot refer to infile what will be happened\e[0m"
rm -f test/infile_no_exist
touch test/outfile_1
chmod 664 test/outfile_1
./pipex ./test/infile_no_exist "cat" "wc -l" ./test/outfile_1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 2: if second command cannot refer to outfile what will be happened\e[0m"
rm -f test/outfile_no_exist
touch test/infile_1
chmod 664 test/infile_1
./pipex ./test/infile_1 "cat" "wc -l" ./test/outfile_no_exist
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 3: if both commands cannot refer to files what will be happened\e[0m"
rm -f test/outfile_no_exist
rm -f test/infile_no_exist
./pipex ./test/infile_no_exist "cat" "wc -l" ./test/outfile_no_exist
echo -e "\e[31merr number is\e[0m" $?

echo ""
echo "file permission test"
echo ""

echo -e  "\e[34mtest case 4: if infile permission doesn't exist what will be happened\e[0m"
touch test/infile_no_perm
touch test/outfile_perm1
chmod 000 test/infile_no_perm
chmod 644 test/outfile_perm1
./pipex ./test/infile_no_perm "cat" "wc -l" ./test/outfile_perm1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 5: if outfile permission doesn't exist what will be happened\e[0m"
touch test/infile_perm1
touch test/outfile_no_perm
chmod 644 test/infile_perm1
chmod 000 test/outfile_no_perm
./pipex ./test/infile_perm1 "cat" "wc -l" ./test/outfile_no_perm
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 6: if both file permissions don't exist what will be happened\e[0m"
touch test/infile_no_perm
touch test/outfile_no_perm
chmod 000 test/infile_no_perm
chmod 000 test/outfile_no_perm
./pipex ./test/infile_no_perm "cat" "wc -l" ./test/outfile_no_perm
echo -e "\e[31merr number is\e[0m" $?

echo ""
echo "command test"
echo ""

echo -e  "\e[34mtest case 7: if provided 1st command doesn't exist what will be happened\e[0m"
touch test/infile_1
touch test/outfile_1
./pipex ./test/infile_1 "lsl -l" "wc -l" ./test/outfile_1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 8: if provided 2nd command doesn't exist what will be happened\e[0m"
touch test/infile_1
touch test/outfile_1
./pipex ./test/infile_1 "ls -l" "wcl -l" ./test/outfile_1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 9: if both commands don't exist what will be happened\e[0m"
touch test/infile_1
touch test/outfile_1
chmod 644 test/infile_1
chmod 644 test/outfile_1
./pipex ./test/infile_1 "lsl" "wcl" ./test/outfile_1
echo -e "\e[31merr number is\e[0m" $?

 echo ""
 echo "command not found and file no exist test"
 echo ""

 echo -e  "\e[34mtest case 10: if provided 1st command doesn't exist and infile not exist what will be happend\e[0m"
 rm -f test/infile_no_exist
 touch test/outfile_1
 ./pipex ../test/infile_no_exist  "catl" "wc -l" ./test/outfile_1
 echo -e "\e[31merr number is\e[0m" $?

 echo -e  "\e[34mtest case 11: if provided 2nd command doesn't exist and outfile not exist what will be happend\e[0m"
 touch test/infile_1
 rm -f test/outfile_no_exist
 ./pipex ../test/infile_1  "ls" "wcl" ./test/outfile_no_exist
 echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 12: if provided 1st command doesn't exist and outfile not exist what will be happend\e[0m"
touch test/infile_1
rm -f test/outfile_no_exist
 ./pipex ./test/infile_1 "catl" "wc -l" ./test/outfile_no_exist
 echo -e "\e[31merr number is\e[0m" $?

 echo -e  "\e[34mtest case 13: if provided 2nd command doesn't exist and infile not exist what will be happend\e[0m"
 touch test/outfile_1
 rm -f test/infile_no_exist
 ./pipex ./test/infile_no_exist "ls" "wcl" ./test/outfile_1
 echo -e "\e[31merr number is\e[0m" $?

 echo ""
 echo "command option is invalid test"
 echo ""

 echo -e  "\e[34mtest case 14: if provided 1st command option is incorrect what will be happend\e[0m"
 touch test/infile_1
 touch test/outfile_1
 ./pipex ./test/infile_1 "cat -B" "wc -l" ./test/outfile_1
 echo -e "\e[31merr number is\e[0m" $?

 echo -e  "\e[34mtest case 15: if provided 2nd command option is incorrect what will be happend\e[0m"
 touch test/infile_1
 touch test/outfile_1
 ./pipex ./test/infile_1 "cat" "wc -p" ./test/outfile_1
 echo -e "\e[31merr number is\e[0m" $?

 echo -e  "\e[34mtest case 16: if provided both command option are incorrect what will be happend\e[0m"
 touch test/infile_1
 touch test/outfile_1
 ./pipex ./test/infile_1 "cat -B" "wc -p" ./test/outfile_1
 echo -e "\e[31merr number is\e[0m" $?

 echo ""
 echo "command not found and permission deny test"
 echo ""

 echo -e  "\e[34mtest case 17: if infile permission doesn't exist and 1st command is invalid what will be happend\e[0m"
 touch test/infile_no_perm
 touch test/outfile_perm1
 chmod 000 test/infile_no_perm
 chmod 644 test/outfile_perm1
 ./pipex ./test/infile_no_perm  "cate" "wc -l" ./test/outfile_perm1
 echo -e "\e[31merr number is\e[0m" $?
 
 echo -e  "\e[34mtest case 18: if outfile permission doesn't exist and 2nd command is invalid what will be happend\e[0m"
 touch test/infile_perm1
 touch test/outfile_no_perm
 chmod 644 test/infile_perm1
 chmod 000 test/outfile_no_perm
 ./pipex ./test/infile_perm1 "cat" "wcl" ./test/outfile_no_perm
 echo -e "\e[31merr number is\e[0m" $?
 
 echo -e  "\e[34mtest case 19: if both file permission doesn't exist and both command doesn't exist what will be happend\e[0m"
 touch test/infile_no_perm
 touch test/outfile_no_perm
 chmod 000 test/infile_no_perm
 chmod 000 test/outfile_no_perm
 ./pipex ./test/infile_no_perm "catl" "wcl" ./test/outfile_no_perm
 echo -e "\e[31merr number is\e[0m" $?

 echo -e  "\e[34mtest case 20: if outfile permission doesn't exist and 1st command is invalid what will be happend\e[0m"
 touch test/infile_perm1
 touch test/outfile_no_perm
 chmod 644 test/infile_perm1
 chmod 000 test/outfile_no_perm
 ./pipex ./test/infile_perm1  "cate" "wc -l" ./test/outfile_no_perm
 echo -e "\e[31merr number is\e[0m" $?
 
 echo -e  "\e[34mtest case 21: if infile permission doesn't exist and 2nd command is invalid what will be happend\e[0m"
 touch test/infile_no_perm
 touch test/outfile_perm1
 chmod 000 test/infile_no_perm
 chmod 644 test/outfile_perm1
 ./pipex  ./test/infile_no_perm "cat" "wcl" ./test/outfile_perm1
 echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 22: if provided 1st command cannot exec due to permission error what will be happend\e[0m"
touch test/outfile_perm1
chmod 644 test/infile_perm1
chmod 644 test/outfile_perm1
./pipex test/infile_perm1 "/dev/null" "wc -l" ./test/outfile_perm1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 23: if provided 2nd command cannot exec due to permission error what will be happend\e[0m"
touch test/outfile_perm1
# chmod 644 test/infile_perm1
chmod 644 test/outfile_perm1
./pipex test/infile_perm1 "cat" "/dev/null"  ./test/outfile_perm1
echo -e "\e[31merr number is\e[0m" $?


# echo -e  "\e[34mtest case 10: if provided 1st command doesn't exist and infile not exist what will be happened\e[0m"
# rm -f test/infile_no_exist
# touch test/outfile_1
# ./pipex ./test/infile_no_exist "lsl -l" "wc -l" ./test/outfile_1
# echo -e "\e[31merr number is\e[0m" $?

# echo -e  "\e[34mtest case 11: if provided 2nd command doesn't exist and outfile not exist what will be happened\e[0m"
# touch test/infile_1
# rm -f test/outfile_no_exist
# ./pipex ./test/infile_1 "ls -l" "wcl -l" ./test/outfile_no_exist
# echo -e "\e[31merr number is\e[0m" $?

# echo ""
# echo "command option test"
# echo ""

# echo -e  "\e[34mtest case 12: if provided 1st command option is incorrect what will be happened\e[0m"
# touch test/infile_1
# touch test/outfile_1
# ./pipex ./test/infile_1 "cat -B" "wc -l" ./test/outfile_1
# echo -e "\e[31merr number is\e[0m" $?

# echo -e  "\e[34mtest case 13: if provided 2nd command option is incorrect what will be happened\e[0m"
# touch test/infile_1
# touch test/outfile_1
# ./pipex ./test/infile_1 "cat" "wc -p" ./test/outfile_1
# echo -e "\e[31merr number is\e[0m" $?

# echo -e  "\e[34mtest case 14: if both command options are incorrect what will be happened\e[0m"
# touch test/infile_1
# touch test/outfile_1
# ./pipex ./test/infile_1 "cat -B" "wc -p" ./test/outfile_1
# echo -e "\e[31merr number is\e[0m" $?

# echo ""
# echo "command option and no_exist test"
# echo ""

# echo -e  "\e[34mtest case 15: if provided 1st command option is incorrect and infile not exist what will be happened\e[0m"
# rm -f test/infile_no_exist
# touch test/outfile_1
# ./pipex ./test/infile_no_exist "cat -B" "wc -l" ./test/outfile_1
# echo -e "\e[31merr number is\e[0m" $?

# echo -e  "\e[34mtest case 16: if provided 2nd command option is incorrect and outfile not exist what will be happened\e[0m"
# touch test/infile_1
# rm -f test/outfile_no_exist
# ./pipex ./test/infile_1 "ls -l" "wc -p" ./test/outfile_no_exist
# echo -e "\e[31merr number is\e[0m" $?

# echo ""
# echo "command and permission test"
# echo ""

# echo -e  "\e[34mtest case 17: if provided 1st command doesn't exist and infile not exist what will be happened\e[0m"
# touch test/infile_no_perm
# touch test/outfile_perm1
# chmod 000 test/infile_no_perm
# chmod 644 test/outfile_perm1
# ./pipex ./test/infile_no_perm "lsl -l" "wc -l" ./test/outfile_perm1
# echo -e "\e[31merr number is\e[0m" $?

# echo -e  "\e[34mtest case 18: if provided 2nd command doesn't exist and outfile not exist what will be happened\e[0m"
# touch test/infile_perm1
# touch test/outfile_no_perm
# chmod 644 test/infile_perm1
# chmod 000 test/outfile_no_perm
# ./pipex ./test/infile_perm1 "ls -l" "wcl -l" ./test/outfile_no_perm
# echo -e "\e[31merr number is\e[0m" $?
