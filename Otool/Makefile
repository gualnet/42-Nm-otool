# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/04 16:03:36 by galy              #+#    #+#              #
#    Updated: 2018/04/05 16:27:45 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_otool
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
				main.c				open_file.c				check_magic.c	\
				usage.c				vault_init.c			\
				handle_64.c			offset_jumper.c			sect_dump_64.c	\
				handle_32.c			sect_dump_32.c			\
				handle_fat.c								\


####FUNC####

OBJP		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))


####RULEZ####

all			:	reset_cursor make_lib OBJD $(NAME)

$(NAME)		: $(OBJP)
	@$(CC) $(CFLAGS) -I$(INCDIR) $(LIBFLAG) $^ -o $(NAME)
	@printf "$(CUR_RST)$(CGREEN)                         $(CRESET)$(CUR_CLR)"
	@printf "$(CUR_RST)$(CGREEN)BUILD FT_OTOOL		: SUCCESS$(CRESET)$(CUR_CLR)\n"
	

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

# Vous utiliserez les codes suivants pour tester le rendu : 
# $> cat test_facile.c #include <stdio.h> int main(void) { puts("Test facile"); return (0); } 
# $> cat test_moins_facile.c #include <stdio.h> int une_globale = 40; int main(void) { printf("La globale vaut: %d\n", une_globale); return (0); } 
# $> cc test_facile.c -o test_facile 
# $> cc test_moins_facile.c -o test_moins_facile 
# $> cc -m32 test_moins_facile.c -o test_moins_facile_32-bit 
# $> En cas de doute, pour identifier un binaire (type/architecture): man 1 file 
# En cas de difficulté pour localiser un binaire universel, une recherche dans le PATH: (IFS=$'\n'; for d in ${PATH//:/$IFS}; do find "$d" -type f -exec file '{}' \+ | grep -i -A3 universal ; done) 
# Pour créer un binaire universel: clang/gcc: -m32 pour cross-compiler explicitement en 32-bit. lipo -create -output <universel> <binaire arch. 1> <binaire arch. 2> ... 
# En cas de difficulté pour localiser une bibliothèque dynamique (.so, .dylib): find /usr/lib -type f -iname '*\.dylib' 2>/dev/null