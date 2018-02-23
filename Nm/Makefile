# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/16 16:38:21 by galy              #+#    #+#              #
#    Updated: 2018/02/23 21:05:15 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_nm
# CFLAGS	=	-Wall -Werror -Wextra
CFLAGS	=	-Wall -Werror -Wextra -fsanitize=address
CC		=	clang 

LIBFLAG		=	-L./lib -lftall

####DIRECTORY####

SRCDIR		=	src
OBJDIR		=	objs
INCDIR		=	inc
LIBDIR		=	lib

####COLOR-SET####

CRESET		=	\033[0m
CRED		=	\033[31m
CGREEN		=	\033[32m
CYELLOW		=	\033[33m
CBLUE		=	\033[34m
CMAGENTA	=	\033[35m
CCYAN		=	\033[36m
CWHITE		=	\033[37m

####CURSOR-SET####
CUR_SVE		=	\033[s
CUR_RST		=	\033[u
CUR_CLR		=	\033[K


####FILES####

SRC			=	\
				main.c       open_file.c  to_exit.c    usage.c      vault_func.c


####FUNC####

OBJP		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))


####RULEZ####

all			:	make_lib OBJD $(NAME)

$(NAME)		: $(OBJP)
	@$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFLAG) $^ -o $(NAME)
	@printf "$(CUR_RST)$(CGREEN)BUILD $(NAME) : SUCCESS$(CRESET)$(CUR_CLR)\n"
	

clean		:
	@make fclean -C $(LIBDIR)
	@rm -f $(OBJP)
	@rm -rf $(OBJDIR)	
	
fclean		: clean
	@rm -f $(NAME)

re			: fclean all


####MORE_RULEZ####

$(OBJDIR)/%.o	:	$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@
	@printf "$(CUR_RST)$(CUR_SVE)$(CYELLOW)BUILD ASM OBJECTS : $<$(CRESET)$(CUR_CLR)"

make_lib	:
	@make -C $(LIBDIR)

tests	:
	@echo "\033[31mABORT => No tests are set\033[0m"
	
OBJD		:
	@mkdir -p $(OBJDIR)