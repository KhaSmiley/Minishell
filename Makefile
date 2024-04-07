NAME			=	minishell

LIBFT			=	libft.a

DIR_SRCS		=	srcs
DIR_SUBDIRS		=	built_ins \
					expand \
					exec \
					parsing \
					utils \

DIR_OBJS		=	.objs

SRCS_NAMES		=	minishell.c \
					parsing/syntax.c \
					parsing/tokens.c \
					parsing/quotes.c \
					parsing/quotes_utils.c \
					utils/memory.c \
					utils/tab_utils.c \
					utils/lst_utils.c \
					utils/signals.c \
					exec/pipex.c \
					exec/exec_prep.c \
					exec/utils_exec_two.c \
					exec/utils_exec.c \
					exec/here_docs.c \
					exec/redirections.c \
					built_ins/built_ins.c \
					built_ins/built_ins_utils.c \
					built_ins/export.c \
					built_ins/export_utils.c \
					built_ins/unset.c \
					expand/expand.c \
					expand/expand_utils_two.c

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:%.c=$(DIR_OBJS)/%.d}

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
	@ echo "GOD HELP US"  | toilet -f future -F border --gay

$(OBJS): | $(DIR_OBJS)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CDFLAGS) $(INC) -c $< -o $@

$(DIR_OBJS)/%.d: $(DIR_SRCS)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MM -MT '$(DIR_OBJS)/$*.o' -MF $@ $(INC) $<

-include $(DEPS)

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

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=del.supp  ./minishell

.PHONY:	all clean fclean re
# .SILENT:
