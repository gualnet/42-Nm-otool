# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 15:15:34 by galy              #+#    #+#              #
#    Updated: 2018/04/10 15:43:18 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_nm
# CFLAGS	=	-Wall -Werror -Wextra
CFLAGS	=	-Wall -Werror -Wextra -fsanitize=address -g
CC		=	clang 

LIBFLAG		=	-L./lib -lftall

####DIRECTORY####

SRCDIR		=	src
OBJDIR		=	objs
INCDIR		=	inc
LIBDIR		=	lib
NMDIR		=	Nm
OTDIR		= 	Otool

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

####RULEZ####

all			: build_lib build_nm build_otool

clean		:
	@make clean -C $(LIBDIR)
	@make clean -C $(NMDIR)
	@make clean -C $(OTDIR)

mini_clean		:
	@make fclean -C $(LIBDIR)
	@make fclean -C $(NMDIR)
	@make fclean -C $(OTDIR)

fclean		: mini_clean

####MORE_RULEZ####

build_lib	:
	@make -C $(LIBDIR)

build_nm	:
	@make -C $(NMDIR)

build_otool	:
	@make -C $(OTDIR)