#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

// WAYS OF DOING EXAPND AFTER QUOTES
// calculate length of new output incl any expands e.g.
	// {123 $USER 456} -> {123 kboulkri 456} [16]
	// {$SHLVL} -> {1} [1]
	// {$PATH} -> {/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin} [41]
	// {$PATH$DSFSDFSEFSDFSDFSDFSDF} -> {/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin} [41]
// $USER already mallocked in input after readline
// value of $USER already mallocked in env_cpy
// option 1 - create copy of $USER (tok->env->key), malloc and free later
// ... malloc tok->env->value and free later
// option 2 - no more mallocs - tok->env->key = ptr -> certain chars of input
// ... tok->env->value = ptr -> certain chars of env_cpy


int isvalid(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
void get_value(char *str, char **env)
{
	int i = 0;
	while (env[i])
	{
		if (strncmp(env[i], str, strlen(str)) == 0)
		{
			// USER=kboulkri
			printf("my value is {%s}\n", &env[i][strlen(str) + 1]);
			// kboulkri
			return ;
		}
		i++;
	}
}

void get_key(char *str, char **env)
{
	// USER+DSFDFSFD
	int i = 0;
	while (str[i] && isvalid(str[i]))
		i++;
	// USER+DSFDFSFD
	char c = str[i];
	// USER\0DSFDFSFD
	str[i] = '\0';
	// USER\0
	printf("my key is {%s}\n", str);
	get_value(str, env);
	// USER+DSFDFSFD
	str[i] = c;
}

int main(int ac, char **av, char **env)
{
	while (1)
	{
		char *str = readline("> ");
		if (!str)
			break ;
		if (!*str)
			continue ;
		printf("input {%s}\n", str);
		int i = 0;
		// $USER+DSFDFSFD
		while (str[i])
		{
			if (str[i] == '$')
			{
				i++;
				// USER+DSFDFSFD
				get_key(&str[i], env);
			}
			else
				i++;
		}
		printf("output {%s}\n", str);
	}

}
