# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afont <afont@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 09:25:13 by afont             #+#    #+#              #
#    Updated: 2026/01/05 09:54:36 by afont            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(shell find ./sources -name '*.c')
OBJ_DIR = obj_o
OBJS	= 	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -rf
NAME	=	libft.a
# OPTI_FLAGS = -Ofast -march=native -funroll-loops -fexpensive-optimizations -finline-functions -fomit-frame-pointer
TOTAL_FILES = $(words $(SRCS))

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(OPTI_FLAGS) -c $< -o $@
	count=$$(find $(OBJ_DIR) -name '*.o' | wc -l); \
	str="████████████████████"; \
	len_str=$$((($$count * 20) / $(TOTAL_FILES) * 3)); \
	len_space=$$(((20 - $$len_str / 3) + 1)); \
	percent=$$((($$count * 100) / $(TOTAL_FILES))); \
	# echo -n "$$percent"; \
	printf "\033[36m%.*s%*c\033[0m%% %d   \r" $$len_str $$str $$len_space ' ' $$percent; \

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

clean :
	@$(RM) $(OBJS) $(NAME)
	@rm -rf obj_o

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.SILENT:
.PHONY : all, libft.a, clean, fclean, re