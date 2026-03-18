MD5 文件校验工具 - 使用说明
============================

## 功能说明
该程序可以计算文件的 MD5 哈希值，支持同时计算多个文件的 MD5。

## 跨平台支持
✓ **Windows / Linux / macOS**
✓ **C89 标准兼容** - 支持最小化的 C 编译器环境

源代码使用标准 C 库，无平台依赖，可在任何支持 C89 及更高版本的编译器上编译。

## 使用方法

### Windows
```
md5.exe file1 [file2 ...]
```

### Linux / macOS
```
./md5 file1 [file2 ...]
```

### 示例
```
# Windows
md5.exe test.txt
md5.exe file1.txt file2.txt file3.txt

# Linux / macOS
./md5 test.txt
./md5 file1.txt file2.txt file3.txt
```

### 输出格式
```
Filename                                   MD5
========================================== ================================
file1.txt                                  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
very_long_filename_that_exceeds_limit.txt  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
...
```

### 输出特性
- ✓ **对齐显示** - MD5 值列对齐，便于比较
- ✓ **文件名简化** - 自动提取文件名，隐藏长路径
- ✓ **超长名截断** - 超过 40 字符的文件名自动截断显示为 "...filename"

## 编译说明

### 前置条件
- **Windows**: MinGW (GCC) 编译器
- **Linux**: gcc 或 clang
- **macOS**: Xcode 命令行工具 (`xcode-select --install`)

### 编译方式

#### 方法 1：Makefile (推荐 - 跨平台)

**支持的目标：**
```bash
make              # 编译（-Wall -O2）
make pedantic      # 严格编译（C89 兼容性验证）
make rebuild       # 清理后重新编译
make clean        # 删除编译生成的文件
make help         # 显示所有可用命令
```

**用途：**
- 日常编译使用 `make`
- 验证 C89 兼容性使用 `make pedantic`

#### 方法 2：编译脚本

**Windows：**
```cmd
compile.bat
```

**Linux / macOS：**
```bash
chmod +x compile.sh
./compile.sh
```

#### 方法 3：手动编译

**基础编译：**
```bash
gcc -Wall -O2 -o md5 md5.c
```

**严格检查（验证 C89 兼容性）：**
```bash
gcc -std=c89 -Wall -Wextra -Wpedantic -O2 -o md5 md5.c
```

## 功能特性
- ✓ 完整的 MD5 算法实现（无需外部库）
- ✓ **C89 标准兼容** - 最大程度的编译器支持
- ✓ 完全跨平台支持
- ✓ 支持任意大小的文件
- ✓ 支持多个文件同时处理
- ✓ **对齐输出** - MD5 值列对齐，便于比较
- ✓ **文件名简化** - 自动提取文件名，隐藏长路径
- ✓ **超长名截断** - 超过 40 字符的文件名自动截断
- ✓ 完善的错误处理

## 注意事项
- 程序使用标准 MD5 算法，兼容所有操作系统的 MD5 校验工具
- 文件路径可使用相对路径或绝对路径
- Windows 路径中的反斜杠需按原样输入或使用双反斜杠
- Linux/macOS 下需要给执行文件设置执行权限：`chmod +x md5`

## 许可证

本项目采用 **MIT 许可证**

详见 [LICENSE](LICENSE) 文件。

