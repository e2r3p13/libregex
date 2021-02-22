# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glafond- <glafond-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/13 03:12:43 by glafond-          #+#    #+#              #
#    Updated: 2021/02/22 17:39:27 by bccyv            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ****************
#	Varriables:

LIBNAME	=	libregex.a

AR		=	ar
ARFLAGS	=	rc

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address

SRCDIR	=	src
INCDIR	=	inc
OBJDIR	=	obj
SRCS	=	$(notdir $(shell ls -1 $(SRCDIR)/*.c))
OBJS	=	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
DPDCS	=	$(OBJS:.o=.d)

# ****************
#	Rules:

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(LIBNAME) $(OBJS)
	@printf "[\e[32mOK\e[0m] %s\n" $@

-include $(DPDCS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -MMD -I$(INCDIR) -c $< -o $@
	@printf "[\e[32mOK\e[0m] %s\n" $@

clean: _clean

fclean: _clean
ifeq ($(shell ls -1 | grep $(LIBNAME)),$(LIBNAME))
	@rm -rf $(LIBNAME)
	@printf "[\e[31mCLEAN\e[0m] %s\n" $(LIBNAME)
endif

_clean:
ifeq ($(shell ls -1 | grep $(OBJDIR)),$(OBJDIR))
	@rm -rf $(OBJS) $(DPDCS)
	@printf "[\e[31mCLEAN\e[0m] %s\n" $(OBJS)
	@rm -rf $(OBJDIR)
endif

re: fclean all
