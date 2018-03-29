# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/16 16:38:21 by galy              #+#    #+#              #
#    Updated: 2018/03/28 19:20:50 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_nm
# CFLAGS	=	-Wall -Werror -Wextra -g
CFLAGS	=	-Wall -Werror -Wextra -fsanitize=address -g
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
CGREEN+		=	\033[32;1;5m
CYELLOW		=	\033[33m
CYELLOW+	=	\033[33;1m
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
				_dev_func.c \
				handle_arch.c    main.c           to_exit.c \
				check_seg_sect.c iter_cmds.c      open_file.c      usage.c \
				display.c        lst_func.c       sort_alnum.c     vault_func.c \
				read_undelimited_str.c


####FUNC####

OBJP		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))


####RULEZ####

all			:	reset_cursor make_lib OBJD $(NAME)

$(NAME)		: $(OBJP)
	@$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFLAG) $^ -o $(NAME)
	@printf "$(CUR_RST)$(CGREEN)                         $(CRESET)$(CUR_CLR)"
	@printf "$(CUR_RST)$(CGREEN)BUILD FT_NM		: SUCCESS$(CRESET)$(CUR_CLR)\n"
	

clean		:
	@make clean -C $(LIBDIR)
	@$(RM) -f $(OBJP)
	@$(RM) -r $(OBJDIR)
	@printf "$(CYELLOW)NM	: CLEANED $(CRESET)\n"
	

mini_clean	:
	@$(RM)  $(OBJP)
	@$(RM) -r $(OBJDIR)

fclean		: mini_clean
	@make fclean -C $(LIBDIR)
	@$(RM) $(NAME)
	@printf "$(CYELLOW)RAZ FT_NM	: Ok$(CRESET)\n"	

re			: fclean print_inter_line all


####MORE_RULEZ####

$(OBJDIR)/%.o	:	$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@
	@printf "$(CUR_RST)$(CUR_SVE)$(CYELLOW)BUILD FT_NM OBJECTS	: $<$(CRESET)$(CUR_CLR)"

make_lib	:
	@make -C $(LIBDIR)

tests	:
	@echo "\033[31mABORT => No tests are set\033[0m"
	
OBJD		:
	@mkdir -p $(OBJDIR)

reset_cursor	:
	@printf "$(CUR_SVE)"

print_inter_line	:
	@printf "$(CYELLOW+)	-----	-----	-----$(CRESET)\n"