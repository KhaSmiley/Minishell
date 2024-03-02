NAME			=	minishell

LIBFT			=	libft.a

DIR_SRCS		=	srcs

DIR_OBJS		=	.objs

SRCS_NAMES		=	expand.c \
					minishell.c \
					lst_utils.c \
					quotes.c \
					syntax.c 

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iinclude -Ilibft/include

LIB				=	-Llibft -lft

CC				=	cc

CDFLAGS 		= 	-MMD -MP

CFLAGS			=	-g3 -Wall -Werror -Wextra

all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS) 
	make -C libft
	$(CC) $(CFLAGS) ${INC} $(CDFLAGS) $(OBJS) $(LIB) -lreadline -o $(NAME)
	@echo "\033[31;7mminishell\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean:
	make clean -C libft
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	rm -rf ${LIBFT}
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)
-include $(DEPS_B)

.PHONY:	all clean fclean re
# .SILENT: