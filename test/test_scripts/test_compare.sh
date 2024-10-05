#!/bin/bash

# ファイルの共通部分
base_name="./test/tmp/outfile_positive_"
base_name2="./test/tmp2/outfile_positive_"
extension=".txt"  # もし拡張子が必要な場合


for i in {0..13}; do
	file1="${base_name}${i}"
	file2="${base_name2}${i}"

	# ファイルの存在確認
	if [[ ! -f "$file1" ]]; then
		echo "Error: $file1 does not exist."
		continue
	fi

	if [[ ! -f "$file2" ]]; then
		echo "Error: $file2 does not exist."
		continue
	fi

	# 各ファイルの権限を設定
	chmod 644 "$file1"
	chmod 644 "$file2"

	# 比較
	if diff "$file1" "$file2" > /dev/null; then
		echo "Files $file1 and $file2 are identical."
	else
		echo "Files $file1 and $file2 differ."
	fi
done

base_name="./test/tmp/outfile_error_"
base_name2="./test/tmp2/outfile_error_"
# 比較するファイルの番号の範囲（例: 0から30まで）
for i in {0..30}; do
	file1="${base_name}${i}"
	file2="${base_name2}${i}"

	# ファイルの存在確認
	if [[ ! -f "$file1" ]]; then
		echo "Error: $file1 does not exist."
		continue
	fi

	if [[ ! -f "$file2" ]]; then
		echo "Error: $file2 does not exist."
		continue
	fi

	# 各ファイルの権限を設定
	chmod 644 "$file1"
	chmod 644 "$file2"

	# 比較
	if diff "$file1" "$file2" > /dev/null; then
		echo "Files $file1 and $file2 are identical."
	else
		echo "Files $file1 and $file2 differ."
	fi
done

base_name="./test/tmp/outfile_bonus_positive_"
base_name2="./test/tmp2/outfile_bonus_positive_"
# 比較するファイルの番号の範囲（例: 0から30まで）
for i in {0..1}; do
	file1="${base_name}${i}"
	file2="${base_name2}${i}"

	# ファイルの存在確認
	if [[ ! -f "$file1" ]]; then
		echo "Error: $file1 does not exist."
		continue
	fi

	if [[ ! -f "$file2" ]]; then
		echo "Error: $file2 does not exist."
		continue
	fi

	# 各ファイルの権限を設定
	chmod 644 "$file1"
	chmod 644 "$file2"

	# 比較
	if diff "$file1" "$file2" > /dev/null; then
		echo "Files $file1 and $file2 are identical."
	else
		echo "Files $file1 and $file2 differ."
	fi
done

base_name="./test/tmp/outfile_bonus_error_case_"
base_name2="./test/tmp2/outfile_bonus_error_case_"
# 比較するファイルの番号の範囲（例: 0から30まで）
for i in {0..10}; do
	file1="${base_name}${i}"
	file2="${base_name2}${i}"

	# ファイルの存在確認
	if [[ ! -f "$file1" ]]; then
		echo "Error: $file1 does not exist."
		continue
	fi

	if [[ ! -f "$file2" ]]; then
		echo "Error: $file2 does not exist."
		continue
	fi

	# 各ファイルの権限を設定
	chmod 644 "$file1"
	chmod 644 "$file2"

	# 比較
	if diff "$file1" "$file2" > /dev/null; then
		echo "Files $file1 and $file2 are identical."
	else
		echo "Files $file1 and $file2 differ."
	fi
done
