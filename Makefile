SRCS = $(shell find ./sources -name '*.c')
HEADER = $(shell find ./includes -name '*.h')
OBJ_DIR = Objects
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = woody_woodpacker
LIB = _libft/libft.a
# MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11
# OPTI_FLAGS = -Ofast -flto -march=native -funroll-loops -fexpensive-optimizations -finline-functions -fomit-frame-pointer
# MATH_FLAGS = -lm
TOTAL_FILES = $(words $(SRCS))

ASM_PAYLOAD = sources/asm/payload
ASM_CODE = sources/asm/print.s
C_TESTER = sources/asm/test_shellcode.c
C_TESTER_EXE = test_shellcode

all: $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@tput civis
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(OPTI_FLAGS) -c $< -o $@
	count=$$(find $(OBJ_DIR) -name '*.o' | wc -l); \
	str="████████████████████"; \
	len_str=$$((($$count * 20) / $(TOTAL_FILES) * 3)); \
	len_space=$$(((20 - $$len_str / 3) + 1)); \
	printf "\033[36m%.*s%*c\033[0m%% %d\r" $$len_str $$str $$len_space ' ' $$((($$count * 100) / $(TOTAL_FILES))); \

$(NAME): $(OBJS)
	@make -C _libft --no-print-directory
	@printf "\033[2K\r"
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)
	@echo -n "   \033[37;46;1m$(NAME) created\033[0m\n"
	@tput cnorm

clean:
	@make clean -C _libft --no-print-directory
	@rm -rf $(OBJS) $(OBJ_DIR)
	@rm -rf $(ASM_PAYLOAD) 
	@echo "   \033[41;1mObject file deleted\033[0m"

fclean: clean
	@make fclean -C _libft --no-print-directory
	@rm -rf $(NAME)
	@rm -rf $(C_TESTER_EXE)
	@echo "   \033[41;1m$(NAME) deleted\033[0m"

re: fclean all

asm_compil_tester:		# to test exe of asm code
	nasm -f elf64 -o $(OBJ_DIR)/print.o $(ASM_CODE)
	ld -o print_asm $(OBJ_DIR)/print.o

asm_compil:				# to generate the payload, usable in c 
	nasm -f bin -o $(ASM_PAYLOAD) $(ASM_CODE)
	hexdump -v -e '"\\\x\" 1/1 "%02x"' $(ASM_PAYLOAD)

asm_test_c:				# to compile the c tester for the asm payload
	$(CC) $(CFLAGS) -z execstack -o $(C_TESTER_EXE) $(C_TESTER)

.SILENT:
.PHONY: all clean fclean re run asm_compil asm_compil_tester


# readelf -h <file> 		to check if x64 or x32