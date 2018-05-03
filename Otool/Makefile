# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/04 16:03:36 by galy              #+#    #+#              #
#    Updated: 2018/05/03 12:12:34 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_otool
# CFLAGS	=	-Wall -Werror -Wextra
CFLAGS	=	-Wall -Werror -Wextra -fsanitize=address -g
CC		=	clang 

LIBFLAG		=	-L./$(LIBDIR) -lftall

####DIRECTORY####

SRCDIR		=	src
OBJDIR		=	objs
INCDIR		=	../inc
LIBDIR		=	../lib

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
				main.c				open_file.c				check_magic.c		\
				usage.c				vault_init.c			read_unlim_str.c 	\
				handle_64.c			offset_jumper.c			sect_dump_64.c		\
				handle_32.c			sect_dump_32.c			swap_endian.c		\
				handle_fat.c		get_fat_cpu_type_else.c	handle_32_fat.c		\
				handle_arch.c		jump_obj_hdr.c			handle_ppc_fat.c	\
				funcs_ppc_fat.c		print_object_path.c							\
#				dev.c


####FUNC####

OBJP		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))


####RULEZ####

all			:	reset_cursor OBJD $(NAME)

$(NAME)		: $(OBJP)
	@$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFLAG) $^ -o ../$(NAME)
	@printf "$(CUR_RST)$(CGREEN)                         $(CRESET)$(CUR_CLR)"
	@printf "$(CUR_RST)$(CGREEN)BUILD FT_OTOOL		: SUCCESS$(CRESET)$(CUR_CLR)\n"
	

clean		:
	@$(RM) -f $(OBJP)
	@$(RM) -r $(OBJDIR)
	@printf "$(CYELLOW)OTOOL	: CLEANED $(CRESET)\n"
	

mini_clean	:
	@$(RM)  $(OBJP)
	@$(RM) -r $(OBJDIR)

fclean		: mini_clean
	@$(RM) ../$(NAME)
	@printf "$(CYELLOW)RAZ FT_OTOOL	: Ok$(CRESET)\n"	

re			: fclean print_inter_line all


####MORE_RULEZ####

$(OBJDIR)/%.o	:	$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@
	@printf "$(CUR_RST)$(CUR_SVE)$(CYELLOW)BUILD FT_OTOOL OBJECTS	: $<$(CRESET)$(CUR_CLR)"

make_lib	:
	@make -C $(LIBDIR)

tests	:
	@echo "\033[31mABORT => No tests are set\033[0m"
	
OBJD		:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/_32
	@mkdir -p $(OBJDIR)/_64
	@mkdir -p $(OBJDIR)/_arch
	@mkdir -p $(OBJDIR)/_fat
	@mkdir -p $(OBJDIR)/_dev

reset_cursor	:
	@printf "$(CUR_SVE)"

print_inter_line	:
	@printf "$(CYELLOW+)	-----	-----	-----$(CRESET)\n"