#!/bin/bash

echo ""
echo -e  "\e[34mPositive basic test begins\e[0m"
echo ""

echo -e  "\e[34mtest case 0: if there is no problem what will be happened\e[0m"
touch test/tmp/infile_positive_1
touch test/tmp/outfile_positive_0
chmod 664 test/tmp/infile_positive_1
chmod 664 test/tmp/outfile_positive_0
< ./test/tmp/infile_positive_1 cat | wc -l > ./test/tmp/outfile_positive_0
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 1: if there is no outfile what will be happened\e[0m"
touch test/tmp/infile_positive_1
rm -f test/tmp/outfile_positive_1
chmod 664 test/tmp/infile_positive_1
< ./test/tmp/infile_positive_1 cat | wc -l > ./test/tmp/outfile_positive_1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 2: if the first command doesn't need infile what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 664 test/tmp/infile_positive_1
< ./test/tmp/infile_positive_1 sleep 2 | wc -l > ./test/tmp/outfile_positive_2
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 3: if the first command use option what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 664 test/tmp/infile_positive_1
< ./test/tmp/infile_positive_1 cat -e | wc -m > ./test/tmp/outfile_positive_3
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 4: if the first command takes arguments what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 664 test/tmp/infile_positive_1
< ./test/tmp/infile_positive_1 wc Makefile | cat > ./test/tmp/outfile_positive_4
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 5: if the second command takes arguments what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 664 test/tmp/infile_positive_1
< ./test/tmp/infile_positive_1 cat | wc Makefile > ./test/tmp/outfile_positive_5
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 6: if the both command takes no standard input arguments what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 664 test/tmp/infile_positive_1
< ./test/tmp/infile_positive_1 sleep 2 | ls > ./test/tmp/outfile_positive_6
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 7: if the 1st command execute the executable file what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 664 test/tmp/infile_positive_1
< ./test/tmp/infile_positive_1 test/tmp/test_cmd_1 | wc -l > ./test/tmp/outfile_positive_7
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 8: if the 2nd command execute the executable file what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 664 test/tmp/infile_positive_1
< ./test/tmp/infile_positive_1 cat |  test/tmp/test_cmd_2 > ./test/tmp/outfile_positive_8
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 9: if the both command execute the executable file what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 664 test/tmp/infile_positive_1
< ./test/tmp/infile_positive_1 test/tmp/test_cmd_1 |  test/tmp/test_cmd_2 > ./test/tmp/outfile_positive_9
echo -e "\e[31merr number is\e[0m" $?

(
echo -e  "\e[34mtest case 10: if the path doesn't exist but command can be executable using absoluted path what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 644 test/tmp/infile_positive_1
export PATH=""
< test/tmp/infile_positive_1 /bin/cat | /bin/wc -l > ./test/tmp/outfile_positive_10
echo -e "\e[31merr number is\e[0m" $?
)

(
echo -e "\e[34mtest case 11: if the path doesn't exist but command can be executable using absoluted path what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 644 test/tmp/infile_positive_1
export PATH=""
< test/tmp/infile_positive_1 test.out | /bin/wc -m > ./test/tmp/outfile_positive_11
echo -e "\e[31merr number is\e[0m" $?
)

(
echo -e  "\e[34mtest case 12: if the path doesn't exist but command can be executable using absoluted path (part2) what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 644 test/tmp/infile_positive_1
unset $PATH
< test/tmp/infile_positive_1 test/tmp/test_cmd_1 | test.out > ./test/tmp/outfile_positive_12
echo -e "\e[31merr number is\e[0m" $?
)

echo -e  "\e[34mtest case 13: if the path doesn't exist but command can be executable using absoluted path (part2) what will be happened\e[0m"
touch test/tmp/infile_positive_1
chmod 644 test/tmp/infile_positive_1
< test/tmp/infile_positive_1 ./test.out hello world | cat > ./test/tmp/outfile_positive_13
echo -e "\e[31merr number is\e[0m" $?


echo ""
echo -e  "\e[34mError test begins\e[0m"
echo ""

echo ""
echo "file not exist test"
echo ""

echo -e  "\e[34mtest case 0: if there is no problem what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_0
chmod 664 test/tmp/infile_error_1
chmod 664 test/tmp/outfile_error_0
< ./test/tmp/infile_error_1 cat | wc -l > ./test/tmp/outfile_error_0
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 1: if first command cannot refer to infile what will be happend\e[0m"
rm -f test/tmp/infile_no_exist
touch test/tmp/outfile_error_1
chmod 664 test/tmp/outfile_error_1
< ./test/tmp/infile_no_exist cat | wc -l > ./test/tmp/outfile_error_1
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 2: if second command cannot refer to outfile what will be happend\e[0m"
rm -f test/tmp/outfile_error_2
touch test/tmp/infile_error_1
chmod 664 test/tmp/infile_error_1
< ./test/tmp/infile_error_1 cat | wc -l > ./test/tmp/outfile_error_2
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 3: if both command cannot refer to file what will be happend\e[0m"
rm -f test/tmp/outfile_error_3
rm -f test/tmp/infile_no_exist
< ./test/tmp/infile_no_exist cat | wc -l > ./test/tmp/outfile_error_3
echo -e "\e[31merr number is\e[0m" $?

echo ""
echo "file permission test"
echo ""

echo -e  "\e[34mtest case 4: if infile permission doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_4
chmod 000 test/tmp/infile_error_1
chmod 644 test/tmp/outfile_error_4
< ./test/tmp/infile_error_1 cat | wc -l > ./test/tmp/outfile_error_4
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 5: if outfile permission doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_5
chmod 644 test/tmp/infile_error_1
chmod 000 test/tmp/outfile_error_5
< ./test/tmp/infile_error_1 cat | wc -l > ./test/tmp/outfile_error_5
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 6: if both file permission doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_6
chmod 000 test/tmp/infile_error_1
chmod 000 test/tmp/outfile_error_6
< ./test/tmp/infile_error_1 cat | wc -l > ./test/tmp/outfile_error_6
echo -e "\e[31merr number is\e[0m" $?
chmod 644 test/tmp/infile_error_1

echo ""
echo "command not found test"
echo ""

echo -e  "\e[34mtest case 7: if provided 1st command doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_7
< ./test/tmp/infile_error_1 lsl -l | wc -l > ./test/tmp/outfile_error_7
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 8: if provided 2nd command doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_8
< ./test/tmp/infile_error_1 ls -l | wcl -l > ./test/tmp/outfile_error_8
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 9: if provided both command doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_9
< ./test/tmp/infile_error_1 lsl -l | wcl -l > ./test/tmp/outfile_error_9
echo -e "\e[31merr number is\e[0m" $?

echo ""
echo "command not found and file no exist test"
echo ""

echo -e  "\e[34mtest case 10: if provided 1st command doesn't exist and infile not exist what will be happend\e[0m"
rm -f test/tmp/infile_no_exist
touch test/tmp/outfile_error_10
< ./test/tmp/infile_no_exist catl -l | wc -l > ./test/tmp/outfile_error_10
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 11: if provided 2nd command doesn't exist and outfile not exist what will be happend\e[0m"
touch test/tmp/infile_error_1
rm -f test/tmp/outfile_error_11
< ./test/tmp/infile_error_1 ls -l | wcl -l > ./test/tmp/outfile_error_11
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 12: if provided 1st command doesn't exist and outfile not exist what will be happend\e[0m"
touch test/tmp/infile_error_1
rm -f test/tmp/outfile_error_12
< ./test/tmp/infile_error_1 catl | wc -l > ./test/tmp/outfile_error_12
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 13: if provided 2nd command doesn't exist and infile not exist what will be happend\e[0m"
touch test/tmp/outfile_error_13
rm -f test/tmp/infile_no_exist
< ./test/tmp/infile_no_exist ls | wcl > ./test/tmp/outfile_error_13
echo -e "\e[31merr number is\e[0m" $?

echo ""
echo "command option is invalid test"
echo ""

echo -e  "\e[34mtest case 14: if provided 1st command option is incorrect what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_14
< ./test/tmp/infile_error_1 cat -B | wc -l > ./test/tmp/outfile_error_14
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 15: if provided 2nd command option is incorrect what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_15
< ./test/tmp/infile_error_1 cat | wc -p > ./test/tmp/outfile_error_15
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 16: if provided both command option are incorrect what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_16
< ./test/tmp/infile_error_1 cat -B | wc -p > ./test/tmp/outfile_error_16
echo -e "\e[31merr number is\e[0m" $?

echo ""
echo "command not found and permission deny test"
echo ""

echo -e  "\e[34mtest case 17: if infile permission doesn't exist and 1st command is invalid what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_17
chmod 000 test/tmp/infile_error_1
chmod 644 test/tmp/outfile_perm1
< ./test/tmp/infile_error_1  cate | wc -l > ./test/tmp/outfile_error_17
echo -e "\e[31merr number is\e[0m" $?
chmod 644 test/tmp/infile_error_1

echo -e  "\e[34mtest case 18: if outfile permission doesn't exist and 2nd command is invalid what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_18
chmod 644 test/tmp/infile_error_1
chmod 000 test/tmp/outfile_error_18
< ./test/tmp/infile_error_1 cat | wcl > ./test/tmp/outfile_error_18
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 19: if both file permission doesn't exist and both command doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_19
chmod 000 test/tmp/infile_error_1
chmod 000 test/tmp/outfile_error_19
< ./test/tmp/infile_error_1 catl | wcl > ./test/tmp/outfile_error_19
echo -e "\e[31merr number is\e[0m" $?
chmod 644 test/tmp/infile_error_1

echo -e  "\e[34mtest case 20: if outfile permission doesn't exist and 1st command is invalid what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_20
chmod 644 test/tmp/infile_error_1
chmod 000 test/tmp/outfile_error_20
< ./test/tmp/infile_error_1  cate | wc -l > ./test/tmp/outfile_error_20
echo -e "\e[31merr number is\e[0m" $?

echo -e  "\e[34mtest case 21: if infile permission doesn't exist and 2nd command is invalid what will be happend\e[0m"
touch test/tmp/infile_error_1
touch test/tmp/outfile_error_21
chmod 000 test/tmp/infile_error_1
chmod 644 test/tmp/outfile_error_21
< ./test/tmp/infile_error_1 cat | wcl > ./test/tmp/outfile_error_21
echo -e "\e[31merr number is\e[0m" $?
chmod 644 test/tmp/infile_error_1

echo ""
echo "command cannot be executed due to permission"
echo ""

echo -e  "\e[34mtest case 22: if provided 1st command cannot exec due to permission error what will be happend\e[0m"
touch test/tmp/outfile_error_22
touch test/tmp/infile_error_1
chmod 644 test/tmp/infile_error_1
chmod 644 test/tmp/outfile_error_22
< test/tmp/infile_error_1 /dev/null | wc -l > ./test/tmp/outfile_error_22
echo -e "\e[31merr number is\e[0m" $?

echo -e "\e[34mtest case 23: if provided 2nd command cannot exec due to permission error what will be happend\e[0m"
touch test/tmp/outfile_error_23
chmod 644 test/tmp/outfile_error_23
< test/tmp/infile_error_1 /dev/null | /dev/null > ./test/tmp/outfile_error_23
echo -e "\e[31merr number is\e[0m" $?

echo -e "\e[34mtest case 24: if both command cannot exec due to permission error what will be happend\e[0m"
touch test/tmp/outfile_error_24
chmod 644 test/tmp/infile_error_1
chmod 644 test/tmp/outfile_error_24
< test/tmp/infile_error_1 /dev/null | /dev/null > ./test/tmp/outfile_error_24
echo -e "\e[31merr number is\e[0m" $?

echo ""
echo "command cannot be executed due to permission and file not found what will be happened"
echo ""

echo -e "\e[34mtest case 25: if 1st command cannot exec due to permission error and infile doesn't exist what will be happend\e[0m"
touch test/tmp/outfile_error_25
rm -f test/tmp/infile_no_exist
chmod 644 test/tmp/outfile_error_25
< test/tmp/infile_no_exist /dev/null | ls > ./test/tmp/outfile_error_25
echo -e "\e[31merr number is\e[0m" $?

echo -e "\e[34mtest case 26: if 2nd command cannot exec due to permission error and outfile doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
rm -f test/tmp/outfile_error_26
chmod 644 test/tmp/infile_error_1
< test/tmp/infile_error_1 cat | /dev/null > ./test/tmp/outfile_error_26
echo -e "\e[31merr number is\e[0m" $?

echo -e "\e[34mtest case 27: if both command cannot exec due to permission error and infile doesn't exist what will be happend\e[0m"
touch test/tmp/outfile_error_27
rm -f test/tmp/infile_no_exist
chmod 644 test/tmp/outfile_error_27
< test/tmp/infile_no_exist /dev/null | /dev/null > ./test/tmp/outfile_error_27
echo -e "\e[31merr number is\e[0m" $?

echo ""
echo "command cannot be executed due to path is unset"
echo ""

(
echo -e "\e[34mtest case 28: if path doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
chmod 644 test/tmp/infile_error_1
export PATH=""
< test/tmp/infile_error_1 cat | wc -l > ./test/tmp/outfile_error_28
echo -e "\e[31merr number is\e[0m" $?
)

(
echo -e "\e[34mtest case 29: if 2nd cmd path doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
chmod 644 test/tmp/infile_error_1
export PATH=""
< test/tmp/infile_error_1 /bin/cat | /wc -l > ./test/tmp/outfile_error_29
echo -e "\e[31merr number is\e[0m" $?
)

(
echo -e "\e[34mtest case 30: if 1st cmd path doesn't exist what will be happend\e[0m"
touch test/tmp/infile_error_1
chmod 644 test/tmp/infile_error_1
export PATH=""
< test/tmp/infile_error_1 /cat | /bin/wc -l > ./test/tmp/outfile_error_30
echo -e "\e[31merr number is\e[0m" $?
)

echo ""
echo "bonus positive case"
echo ""

echo -e "\e[34mtest case 0: if there are several commands what will be happend\e[0m"
touch test/tmp/infile_positive_1
touch test/tmp/outfile_bonus_positive_0
chmod 664 test/tmp/infile_positive_1
chmod 664 test/tmp/outfile_bonus_positive_0
< test/tmp/infile_positive_1 cat | sort | uniq | awk '{print $1}'| tr '[:lower:]' '[:upper:]' | cat > test/tmp/outfile_bonus_positive_0
echo -e "\e[31merr number is\e[0m" $?

echo -e "\e[34mtest case 1: if there are several commands what will be happend\e[0m"
touch test/tmp/infile_positive_1
touch test/tmp/outfile_bonus_positive_1
chmod 664 test/tmp/infile_positive_1
chmod 664 test/tmp/outfile_bonus_positive_1
< test/tmp/infile_positive_1 cat | sort | tr '[:lower:]' '[:upper:]' | cut -d ' ' -f 1 | rev | sort | wc -l > test/tmp/outfile_bonus_positive_1
echo -e "\e[31merr number is\e[0m" $?

echo ""
echo "bonus error case"
echo ""

# Case 1: コマンドが存在しない場合
echo "Normal infile/outfile, missing intermediate command"
< test/tmp/infile_error_1 cat | nonexistent_command | awk '{print $0}' | wc -l > test/tmp/outfile_bonus_error_case_0
echo -e "\e[31merr number is\e[0m" $?

echo "Normal infile/outfile, missing first command"
< test/tmp/infile_error_1 nonexistent_command | awk '{print $0}' | grep 'test' | wc -l > test/tmp/outfile_bonus_error_case_1
echo -e "\e[31merr number is\e[0m" $?

echo "Normal infile/outfile, missing last command"
< test/tmp/infile_error_1 cat | awk '{print $0}' | grep 'test' | nonexistent_command > test/tmp/outfile_bonus_error_case_2
echo -e "\e[31merr number is\e[0m" $?

# Case 2: パーミッションの問題
# 一時ファイルを作成
echo "cannot execute command due to permission"

echo "Normal infile/outfile, permission issue with intermediate command"
< test/tmp/infile_error_1 cat | awk '{print $0}' | /dev/null | wc -l > test/tmp/outfile_bonus_error_case_3
echo -e "\e[31merr number is\e[0m" $?

echo "Normal infile/outfile, permission issue with first command"
< test/tmp/infile_error_1 /dev/null | awk '{print $0}' | grep 'test' | wc -l > test/tmp/outfile_bonus_error_case_4
echo -e "\e[31merr number is\e[0m" $?

echo "Normal infile/outfile, permission issue with last command"
< test/tmp/infile_error_1 cat | awk '{print $0}' | grep 'test' | /dev/null > test/tmp/outfile_bonus_error_case_5
echo -e "\e[31merr number is\e[0m" $?

# Case 3: 有効な infile が存在しない場合
echo "=== Case 3 ==="
echo "File does not exist"
< nonexistent_infile cat | awk '{print $0}' | grep 'test' > test/tmp/outfile_bonus_error_case_6
echo -e "\e[31merr number is\e[0m" $?

# 権限が不足している outfile を使用する場合
echo "Permission denied on outfile"
touch test/tmp/outfile_bonus_error_case_7
chmod 000 test/tmp/outfile_bonus_error_case_7 # 読み取り専用に設定
< test/tmp/infile_error_1 cat | awk '{print $0}' | grep 't' > test/tmp/outfile_bonus_error_case_7
echo -e "\e[31merr number is\e[0m" $?

# Case 4: Case 1 と Case 3 を組み合わせたパターン
echo "=== Case 4 ==="
< nonexistent_infile cat | nonexistent_command | awk '{print $0}' | grep 'test' | wc -l > test/tmp/outfile_bonus_error_case_8
echo -e "\e[31merr number is\e[0m" $?

< nonexistent_infile nonexistent_command | ls | awk '{print $0}' | grep 'test' | wc -l > test/tmp/outfile_bonus_error_case_9
echo -e "\e[31merr number is\e[0m" $?

< nonexistent_infile cat | ls | awk '{print $0}' | grep 'test' | nonexistent_command > test/tmp/outfile_bonus_error_case_10
echo -e "\e[31merr number is\e[0m" $?


