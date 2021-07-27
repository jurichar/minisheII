#include "../includes/minishell.h"

void set_term_ncan(void)
{
	struct termios new;

	tcgetattr(STDIN_FILENO, &new);
	new.c_lflag &= ~(ICANON | ISIG | ECHO);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &new);
}

void set_term_can(struct termios term)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
}
