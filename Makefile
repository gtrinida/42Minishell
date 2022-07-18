CC			:=	clang
BUILDDIR	:=	object
CFLAGS		:=	-Wall -Wextra -Werror -g -fPIE
INC			:=	-I./includes/ -I./gnl/ -I./libft/
INCLUDES	:=	minishell.h color.h
LIB			:=	libft/libft.a -ltermcap -lreadline

EXECUTE_SRC	=	cd.c					env.c							env_sort.c				env_utils_3.c					\
				find_cmd.c				history.c						redirect.c				unset.c							\
				defenv_init.c			env_copy.c						env_utils.c				err_handler.c					\
				free_struct.c			heredoc.c						pipe.c					signal.c						\
				echo.c					env_list.c						env_utils_2.c			exec_cmd.c						\
				heredoc_utils.c			pwd.c							std_backup.c			utils_2.c						\
				exec_command_line.c		exit.c							utils.c					export.c						\
				minishell_init.c		argv_crutch.c					utils_exec.c

PARSER_SRC	=	argument_count.c		fast_qout_check_utils.c			parser_utils.c			rdir_count.c					\
				rewrite_dollar_utils.c	work_with_dollar_utils.c 		work_with_pipe.c		before_inside_quotes.c			\
				fast_quot_check.c		preparing_for_the_structure.c	rdir_fast_check.c		work_with_dollar.c				\
				work_with_env.c			work_with_quotes.c				check_dollar.c			fill_argument.c					\
				not_env.c    			preparser.c						rdir_fast_check_utils.c	work_with_dollar_env.c			\
				work_with_node.c		work_with_quotes_utils.c		check_flag_env.c		fill_command.c					\
				parser.c				preparser_utils.c				rewrite_dollar.c		work_with_dollar_env_utils.c	\
				work_with_node_utils.c	work_with_rdir.c

GNL_SRC		=	get_next_line.c			get_next_line_utils.c

SOURCES := $(PARSER_SRC:%=parser/%) $(EXECUTE_SRC:%=sources/%) $(GNL_SRC:%=gnl/%) main.c
OBJECTS := $(patsubst %,$(BUILDDIR)/%,$(SOURCES:.c=.o))


NAME	=	minishell

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "Linking..."
	@make -C ./libft/
	$(CC) $^ -o $(NAME) $(LIB)

$(BUILDDIR)/%.o: ./%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -g -c -o $@ $<

clean:
	@make -C ./libft/ clean
	$(RM) -r $(BUILDDIR)

fclean:	clean
	@make -C ./libft/ fclean
	$(RM) -r $(NAME)

re: fclean all

norm:
	@norminette *.c *.h

.PHONY: clean fclean re
