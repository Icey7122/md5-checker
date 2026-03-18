#!/bin/bash

# MD5 Cross-platform Compilation Script

echo "Compiling md5..."

# 检测操作系统
OS_TYPE=$(uname -s)

# 编译
gcc -Wall -O2 -o md5 md5.c

# 检查编译结果
if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo "✓ Executable: md5"
    echo ""
    echo "Usage: ./md5 file1 [file2 ...]"
    echo "Example: ./md5 test.txt"
    
    # 最后赋予执行权限
    chmod +x md5
    echo "✓ Executable permissions set"
else
    echo "✗ Compilation failed!"
    exit 1
fi
