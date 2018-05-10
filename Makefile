# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galy <galy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 15:15:34 by galy              #+#    #+#              #
#    Updated: 2018/05/10 10:51:50 by galy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####DIRECTORY####

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
CBLUE+		=	\033[34;1m
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

fclean		:
	@make fclean -C $(LIBDIR)
	@make fclean -C $(NMDIR)
	@make fclean -C $(OTDIR)

re			: fclean print_inter_line all

####MORE_RULEZ####

build_lib	:
	@make -C $(LIBDIR)

build_nm	:
	@make -C $(NMDIR)

build_otool	:
	@make -C $(OTDIR)

print_inter_line	:
	@printf "$(CBLUE+)	-----$(CRESET)	$(CWHITE)-----	$(CRED)-----$(CRESET)\n"