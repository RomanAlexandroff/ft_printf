
NAME = libftprintf.a

SRCS =	ft_printf.c put_hex_ptr.c \
		put_char_str.c put_ints.c \
		utilities.c
		
OBJS = ${SRCS:.c=.o}
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
TESTER = tester_for_ft_printf.c
TEMP = temp_test_roaleksa
COMMIT_MSG ?= Auto-commit from Makefile

# Detect the Operating System
UNAME := $(shell uname -s)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "Make: Library file and the Objects have been built"

all: $(NAME)

norm:
	@echo "\n\n========== RUNNING NORMINETTE ==========\n\n"
	@norminette -R CheckForbiddenSourceHeader
	@echo "\n\n========= THE RESULTS END HERE =========\n\n"

test:
	@$(CC) $(CFLAGS) $(TESTER) $(SRCS) -o $(TEMP)
	@echo "\n\n========== FT_PRINTF TESTER ==========\n\n"
	@./$(TEMP)
	@echo "\n\n=========== TEST ENDS HERE ===========\n\n"
	@$(RM) $(TEMP)

#this rule calls Valgrind or Leaks depending on the OS
valgrind:
ifeq ($(UNAME),Darwin)
	@echo "Using Leaks for memory checking."
	@$(CC) $(CFLAGS) $(TESTER) $(SRCS) -o $(TEMP)
	@leaks --atExit -- ./$(TEMP)
	@$(RM) $(TEMP)
	@$(RM) -r $(TEMP).dSYM
else
	@echo "Using Valgrind for memory checking."
	@$(CC) $(CFLAGS) $(TESTER) $(SRCS) -o $(TEMP)
	@valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --track-fds=yes --verbose ./$(TEMP)
	@$(RM) $(TEMP)
endif

#calls GDB or LLDB depending on the detected OS
gdb:
ifeq ($(UNAME),Darwin)
	@echo "Using LLDB."
	@$(CC) $(CFLAGS) $(TESTER) $(SRCS) -g -o $(TEMP)
	@lldb ./$(TEMP)
	@$(RM) $(TEMP)
	@$(RM) -r $(TEMP).dSYM
else
	@echo "Using GDB."
	@$(CC) $(CFLAGS) $(TESTER) $(SRCS) -g -o $(TEMP)
	@gdb ./$(TEMP)
	@$(RM) $(TEMP)
endif

git:
	@if [ -n "$$(git status --porcelain)" ]; then \
		read -p "Commit message: " msg; \
		if [ -z "$$msg" ]; then \
			msg="$(COMMIT_MSG)"; \
		fi; \
		echo "Committing with message: $$msg"; \
		git add .; \
		git commit -m "$$msg"; \
		git push; \
	else \
		echo "No changes detected."; \
	fi

clean:
	@$(RM) $(OBJS)
	@echo "Make: Object files have been deleted"

fclean: clean
	@$(RM) $(NAME)
	@echo "Make: Library file has been deleted"

re: fclean all

.PHONY: all norm test valgrind gdb git clean fclean re
