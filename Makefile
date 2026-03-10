SRCS =	ft_printf.c put_hex_ptr.c\
		put_char_str.c put_ints.c \
		utilities.c
		
OBJS = ${SRCS:.c=.o}
TESTER = tester_for_ft_printf.c
COMMIT_MSG ?= Auto-commit from Makefile
NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	@${AR} ${NAME} ${OBJS}
	@echo "Make: Library file and the Objects have been built"

all: ${NAME}

norm:
	@echo "\n\n========== RUNNING NORMINETTE ==========\n\n"
	@norminette -R CheckForbiddenSourceHeader
	@echo "\n\n========= THE RESULTS END HERE =========\n\n"

test:
	@$(CC) $(CFLAGS) $(TESTER) $(SRCS) -o temp_test_roaleksa
	@echo "\n\n========== FT_PRINTF TESTER ==========\n\n"
	@./temp_test_roaleksa
	@echo "\n\n=========== TEST ENDS HERE ===========\n\n"
	@${RM} temp_test_roaleksa

git:
	@if [ -n "$$(git status --porcelain)" ]; then \
		echo "Changes detected. Committing..."; \
		git add .; \
		git commit -m "$(COMMIT_MSG)"; \
		git push; \
	else \
		echo "No changes detected."; \
	fi

clean:
	@${RM} ${OBJS}
	@echo "Make: Object files have been deleted"

fclean: clean
	@${RM} ${NAME}
	@echo "Make: Library file has been deleted"

re: fclean all

.PHONY: all norm test clean fclean re
