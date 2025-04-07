NAME = nemergent
MAIN = src/main.c

LIST_UTILS = inc/lilst_utils.a
LU_SRCS = src/list_utils.c
LU_OBJS = $(LU_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc
AR = ar rcs
RM = rm -rf

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RESET = \033[0m

$(NAME) : $(LIST_UTILS) $(MAIN)
	@echo "$(YELLOW)Compiling ./nemergent executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(LIST_UTILS)
	@echo "$(GREEN)./nemergent executable created successfully.$(RESET)"

$(LIST_UTILS) : $(LU_OBJS)
	@echo "$(YELLOW)Compiling list_utils.a library...$(RESET)"
	$(AR) $(LIST_UTILS) $(LU_OBJS)
	@echo "$(GREEN)list_utils.a created successfully.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean:
	@echo "$(YELLOW)Deleting all the object files...$(RESET)"
	$(RM) $(LU_OBJS)
	@echo "$(GREEN)All the object files deleted succesfully.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Deleting the object files, *.a and executable file...$(RESET)"
	$(RM) $(LIST_UTILS) $(NAME) 
	@echo "$(GREEN)Everything deleted succesfully.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
