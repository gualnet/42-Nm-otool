# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/16 16:38:21 by galy              #+#    #+#              #
#    Updated: 2018/05/02 19:33:34 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_nm
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
				main.c					run.c						\
				open_file.c				usage.c						\
				read_undelimited_str.c	vault_func.c				\
				sort_alnum.c			offset_jumper.c				\
				check_magic.c 			arg_pars.c					\
				ft_strlen_cap.c										\
				_64/handle_64.c			_64/iter_cmds.c				\
				_64/lst_func.c			_64/display.c				\
				_64/check_seg_sect.c								\
				_32/handle_32.c			_32/iter_cmds_32.c			\
				_32/lst_func_32.c		_32/display_32.c			\
				_32/check_seg_sect_32.c								\
				_arch/handle_arch.c		_arch/printers_arch.c		\
				_arch/jumpers_arch.c								\
				_fat/handle_fat.c		_fat/swap_endian.c			\
				_fat/handle_32_in_fat.c _fat/handle_ppc_in_fat.c	\
				_fat/iter_cmds_ppc.c 	_fat/display_list_ppc.c		\
				_fat/handle_64_swap.c 	_fat/display_list_64_swap.c	\
				_fat/get_indirection_name.c							\
				_fat/check_seg_sect_64_swap.c						\
				_fat/check_seg_sect_ppc.c							\
				_dev/_dev_func.c


####FUNC####

OBJP		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))


####RULEZ####

all			:	reset_cursor OBJD $(NAME)

$(NAME)		: $(OBJP)
	@$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFLAG) $^ -o ../$(NAME)
	@printf "$(CUR_RST)$(CGREEN)                         $(CRESET)$(CUR_CLR)"
	@printf "$(CUR_RST)$(CGREEN)BUILD FT_NM		: SUCCESS$(CRESET)$(CUR_CLR)\n"
	

clean		:
	@$(RM) -f $(OBJP)
	@$(RM) -r $(OBJDIR)
	@printf "$(CYELLOW)NM	: CLEANED $(CRESET)\n"
	

mini_clean	:
	@$(RM)  $(OBJP)
	@$(RM) -r $(OBJDIR)

fclean		: mini_clean
	@$(RM) ../$(NAME)
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
	@mkdir -p $(OBJDIR)/_32
	@mkdir -p $(OBJDIR)/_64
	@mkdir -p $(OBJDIR)/_arch
	@mkdir -p $(OBJDIR)/_fat
	@mkdir -p $(OBJDIR)/_dev

reset_cursor	:
	@printf "$(CUR_SVE)"

print_inter_line	:
	@printf "$(CYELLOW+)	-----	-----	-----$(CRESET)\n"

# Vous utiliserez les codes suivants pour tester le rendu : 
# $> cat test_facile.c #include <stdio.h> int main(void) { puts("Test facile"); return (0); } 
# $> cat test_moins_facile.c #include <stdio.h> int une_globale = 40; int main(void) { printf("La globale vaut: %d\n", une_globale); return (0); } 
# $> cc test_facile.c -o test_facile 
# $> cc test_moins_facile.c -o test_moins_facile 
# $> cc -m32 test_moins_facile.c -o test_moins_facile_32-bit 
# $> En cas de doute, pour identifier un binaire (type/architecture): man 1 file 
#En cas de difficulté pour localiser un binaire universel, une recherche dans le PATH: (IFS=$'\n'; for d in ${PATH//:/$IFS}; do find "$d" -type f -exec file '{}' \+ | grep -i -A3 universal ; done) 
#Pour créer un binaire universel: clang/gcc: -m32 pour cross-compiler explicitement en 32-bit. lipo -create -output <universel> <binaire arch. 1> <binaire arch. 2> ... 
#En cas de difficulté pour localiser une bibliothèque dynamique (.so, .dylib): find /usr/lib -type f -iname '*\.dylib' 2>/dev/null