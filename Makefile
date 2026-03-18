.PHONY: all clean help pedantic rebuild

# 编译器
CC := gcc

# 基础编译选项
CFLAGS := -Wall -O2

# 严格编译选项（C89 兼容性检查）
PEDANTIC_FLAGS := -Wall -Wextra -Wpedantic -O2

# 源文件和输出文件
SRC := md5.c
# Windows 下输出 .exe，其他平台不加扩展名
ifeq ($(OS),Windows_NT)
    TARGET := md5.exe
    RM := del /Q
else
    TARGET := md5
    RM := rm -f
endif

# 默认目标
all: $(TARGET)

# 编译目标
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<
	@echo "Compilation successful! $(TARGET) created."

# 严格标准检查（C89 兼容性验证）
pedantic: $(SRC)
	$(CC) -std=c89 $(PEDANTIC_FLAGS) -o $(TARGET) $<
	@echo "Pedantic compilation successful! $(TARGET) created."

# 清理
clean:
	$(RM) $(TARGET)
	@echo "Cleaned up $(TARGET)"

# 重新编译
rebuild: clean all
	@echo "Rebuild complete!"

# 帮助信息
help:
	@echo "Available targets:"
	@echo "  make          - Compile using default flags"
	@echo "  make pedantic - Compile with strict C89 compatibility checks"
	@echo "  make rebuild  - Clean and compile"
	@echo "  make clean    - Remove compiled binary"
	@echo "  make help     - Show this message"
