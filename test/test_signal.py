#!/usr/bin/python3
import os
import signal
import sys

def send_signal_from_arg():
    # コマンドライン引数が正しく渡されているかを確認
    if len(sys.argv) != 2:
        print("Usage: python script.py <signal_number>")
        sys.exit(1)
    
    try:
        # コマンドライン引数を整数に変換
        sig_num = int(sys.argv[1])
        
        # シグナル番号が有効か確認
        if sig_num not in [s.value for s in signal.Signals]:
            print(f"Error: {sig_num} is not a valid signal number.")
            sys.exit(1)
    
    except ValueError:
        print("Error: Signal number must be an integer.")
        sys.exit(1)
    
    # 現在のプロセスIDを取得
    pid = os.getpid()
    print(f"Sending signal {sig_num} to process {pid}")
    
    # 自プロセスに指定されたシグナルを送信
    os.kill(pid, sig_num)


# 関数を実行
send_signal_from_arg()