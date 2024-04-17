#===============================
#=Used for compiling C project==
#===============================

CC = gcc
RM = rm -f
CFLAGS = -Wall -g
SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj
BIN_DIR = ./bin
DEP_DIR = ./dep
VPATH = $(SRC_DIR):$(OBJ_DIR):$(INC_DIR):$(BIN_DIR):$(DEP_DIR)

# 列出所有源代码文件（包含路径）
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEP_FILES = $(patsubst $(SRC_DIR)/%.c, $(DEP_DIR)/%.d, $(SRC_FILES))
INC_FILES = $(wildcard $(INC_DIR)/*.h)

# 定义目标和依赖关系
all : $(BIN_DIR)/main.exe

# 包含依赖文件
include $(DEP_FILES)

$(BIN_DIR)/main.exe : $(OBJ_FILES)
	-@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	-@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -I$(INC_DIR) -o $@ $<

# 自动生成依赖文件
$(DEP_DIR)/%.d: $(SRC_DIR)/%.c
	-@mkdir -p $(DEP_DIR)
	$(CC) -MM -MT '$(OBJ_DIR)/$*.o' -MF $@ -I$(INC_DIR) $<

clean:
	-@$(RM) $(DEP_FILES) $(OBJ_FILES) $(BIN_DIR)/main.exe

.PHONY : all clean

