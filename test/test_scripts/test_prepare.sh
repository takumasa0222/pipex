#!/bin/bash

rm -rf test/tmp
rm -rf test/tmp2
rm -f test.out

mkdir test/tmp
mkdir test/tmp2

< /dev/urandom tr -dc 'A-Za-z0-9\n' | head -c 8000 > test/tmp/infile_positive_1
< /dev/urandom tr -dc 'A-Za-z0-9\n' | head -c 2000 > test/tmp/infile_error_1

echo $PATH > test/backup_path

touch test/tmp/test_cmd_1
echo "#!/bin/bash" > test/tmp/test_cmd_1
echo "echo" >> test/tmp/test_cmd_1
echo "echo hello world" >> test/tmp/test_cmd_1
echo "echo" >> test/tmp/test_cmd_1
chmod 755 test/tmp/test_cmd_1

touch test/tmp/test_cmd_2
echo "#!/bin/bash" > test/tmp/test_cmd_2
echo "ls" >> test/tmp/test_cmd_2
echo "echo this is executable file" >> test/tmp/test_cmd_2
chmod 755 test/tmp/test_cmd_2

cc test/test.c -o test.out
