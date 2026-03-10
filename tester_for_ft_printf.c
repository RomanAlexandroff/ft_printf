#include <limits.h>
#include <stdio.h>
#include <signal.h>
#include "ft_printf.h"

static void	reset_stdout(int saved_stdout)
{
	dup2(saved_stdout, STDOUT_FILENO);
}

static void	test_char(int saved_stdout)
{
	int pipefd[2];
	int r1, r2;

	pipe(pipefd);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	r1 = printf("%c", 'A');
	r2 = ft_printf("%c", 'A');

	reset_stdout(saved_stdout);

	fprintf(stderr, "----- ERROR HANDLING %%c -----\n");
	fprintf(stderr, "printf     returned: %d\n", r1);
	fprintf(stderr, "ft_printf  returned: %d\n", r2);
	perror("write");
}

static void	test_string(int saved_stdout)
{
	int pipefd[2];
	int r1, r2;

	pipe(pipefd);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	r1 = printf("%s", "Hello");
	r2 = ft_printf("%s", "Hello");

	reset_stdout(saved_stdout);

	fprintf(stderr, "\n----- ERROR HANDLING %%s -----\n");
	fprintf(stderr, "printf     returned: %d\n", r1);
	fprintf(stderr, "ft_printf  returned: %d\n", r2);
	perror("write");
}

static void	test_pointer(int saved_stdout)
{
	int pipefd[2];
	int r1, r2;

	pipe(pipefd);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	r1 = printf("%p", (void *)0x42);
	r2 = ft_printf("%p", (void *)0x42);

	reset_stdout(saved_stdout);

	fprintf(stderr, "\n----- ERROR HANDLING %%p -----\n");
	fprintf(stderr, "printf     returned: %d\n", r1);
	fprintf(stderr, "ft_printf  returned: %d\n", r2);
	perror("write");
}

static void	test_int(int saved_stdout)
{
	int pipefd[2];
	int r1, r2;

	pipe(pipefd);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	r1 = printf("%d", 42);
	r2 = ft_printf("%d", 42);

	reset_stdout(saved_stdout);

	fprintf(stderr, "\n----- ERROR HANDLING %%d and %%i -----\n");
	fprintf(stderr, "printf     returned: %d\n", r1);
	fprintf(stderr, "ft_printf  returned: %d\n", r2);
	perror("write");
}

static void	test_unsigned(int saved_stdout)
{
	int pipefd[2];
	int r1, r2;

	pipe(pipefd);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	r1 = printf("%u", 42u);
	r2 = ft_printf("%u", 42u);

	reset_stdout(saved_stdout);

	fprintf(stderr, "\n----- ERROR HANDLING %%u -----\n");
	fprintf(stderr, "printf     returned: %d\n", r1);
	fprintf(stderr, "ft_printf  returned: %d\n", r2);
	perror("write");
}

static void	test_hex_lowercase(int saved_stdout)
{
	int pipefd[2];
	int r1, r2;

	pipe(pipefd);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	r1 = printf("%x", 42);
	r2 = ft_printf("%x", 42);

	reset_stdout(saved_stdout);

	fprintf(stderr, "\n----- ERROR HANDLING %%x -----\n");
	fprintf(stderr, "printf     returned: %d\n", r1);
	fprintf(stderr, "ft_printf  returned: %d\n", r2);
	perror("write");
}

static void	test_HEX_uppercase(int saved_stdout)
{
	int pipefd[2];
	int r1, r2;

	pipe(pipefd);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	r1 = printf("%X", 42);
	r2 = ft_printf("%X", 42);

	reset_stdout(saved_stdout);

	fprintf(stderr, "\n----- ERROR HANDLING %%X -----\n");
	fprintf(stderr, "printf     returned: %d\n", r1);
	fprintf(stderr, "ft_printf  returned: %d\n", r2);
	perror("write");
}

static void	test_percent(int saved_stdout)
{
	int pipefd[2];
	int r1, r2;

	pipe(pipefd);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	r1 = printf("%%");
	r2 = ft_printf("%%");

	reset_stdout(saved_stdout);

	fprintf(stderr, "\n----- ERROR HANDLING %% -----\n");
	fprintf(stderr, "printf     returned: %d\n", r1);
	fprintf(stderr, "ft_printf  returned: %d\n", r2);
	perror("write");
}

static void	test_normal_formats(void)
{
	int		ret1;
	int		ret2;
	int		num = 42;
	char	*str = "Hello, world!";
	char	*null_str = NULL;

	printf("----- CHAR TESTS -----\n");
	ret1 = printf("printf   : %c\n", 'A');
	ret2 = ft_printf("ft_printf: %c\n", 'A');
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- STRING TESTS -----\n");
	ret1 = printf("printf   : %s\n", str);
	ret2 = ft_printf("ft_printf: %s\n", str);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- NULL STRING -----\n");
	ret1 = printf("printf   : %s\n", null_str);
	ret2 = ft_printf("ft_printf: %s\n", null_str);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- POINTER TESTS -----\n");
	ret1 = printf("printf   : %p\n", str);
	ret2 = ft_printf("ft_printf: %p\n", str);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- NULL POINTER -----\n");
	ret1 = printf("printf   : %p\n", NULL);
	ret2 = ft_printf("ft_printf: %p\n", NULL);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- INTEGER TESTS -----\n");
	ret1 = printf("printf   : %d\n", 42);
	ret2 = ft_printf("ft_printf: %d\n", 42);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- NEGATIVE INTEGER -----\n");
	ret1 = printf("printf   : %d\n", -42);
	ret2 = ft_printf("ft_printf: %d\n", -42);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- INT LIMITS -----\n");
	ret1 = printf("printf   : %d %d\n", INT_MAX, INT_MIN);
	ret2 = ft_printf("ft_printf: %d %d\n", INT_MAX, INT_MIN);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- UNSIGNED TESTS -----\n");
	ret1 = printf("printf   : %u\n", 4294967295U);
	ret2 = ft_printf("ft_printf: %u\n", 4294967295U);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- HEX LOWER -----\n");
	ret1 = printf("printf   : %x\n", 305441741);
	ret2 = ft_printf("ft_printf: %x\n", 305441741);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- HEX UPPER -----\n");
	ret1 = printf("printf   : %X\n", 305441741);
	ret2 = ft_printf("ft_printf: %X\n", 305441741);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- ZERO VALUES -----\n");
	ret1 = printf("printf   : %d %u %x %X\n", 0, 0, 0, 0);
	ret2 = ft_printf("ft_printf: %d %u %x %X\n", 0, 0, 0, 0);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- MIXED FORMAT -----\n");
	ret1 = printf("printf   : %c %s |%s| %d %u %x %X %p %p\n",
		'Z', "test", "\0ShouldNotPrint", -123, 123U, 255, 255, &num, (void *)0);
	ret2 = ft_printf("ft_printf: %c %s |%s| %d %u %x %X %p %p\n",
		'Z', "test", "\0ShouldNotPrint", -123, 123U, 255, 255, &num, (void *)0);
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- WALL OF FORMATS -----\n");
	ret1 = printf("%s%s%s%s%s%s%s%s%s%s%s%s\n", 
		"AAA", "BBB", "CCC", "DDD", "aa", "bb", "cc", "dd", "AAA", "BBB", "CCC", "DDD");
	ret2 = ft_printf("%s%s%s%s%s%s%s%s%s%s%s%s\n", 
		"AAA", "BBB", "CCC", "DDD", "aa", "bb", "cc", "dd", "AAA", "BBB", "CCC", "DDD");
	printf("return: %d vs %d\n\n", ret1, ret2);

	printf("----- PERCENT SIGN -----\n");
	ret1 = printf("printf   : %%\n");
	ret2 = ft_printf("ft_printf: %%\n");
	printf("return: %d vs %d\n\n", ret1, ret2);
}

int	main(void)
{
	int saved_stdout;

	/* common tests */
	test_normal_formats();
	/* error handling tests */
	signal(SIGPIPE, SIG_IGN);			// ignore broken pipe signals
	setvbuf(stdout, NULL, _IONBF, 0);	// turn off buffering for printf()
	saved_stdout = dup(STDOUT_FILENO);
	test_char(saved_stdout);
	test_string(saved_stdout);
	test_pointer(saved_stdout);
	test_int(saved_stdout);
	test_unsigned(saved_stdout);
	test_hex_lowercase(saved_stdout);
	test_HEX_uppercase(saved_stdout);
	test_percent(saved_stdout);
	close(saved_stdout);
	return (0);
}