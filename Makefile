## No Header
## 28/11/2016 - 01:13:10
##

NAME=		scc
VERSION=	.1.0

SRC=		./src/
INC=		./inc/
OBJ=		./obj/

FILES=		main.c

OBJS=		$(FILES:%.c=$(OBJ)%.o)

DFLAGS=		-DDBG -g
#CFLAGS=		-W -Wall -Wextra -Werror $(DFLAGS) -I$(INC)

CC=		gcc

all:		$(NAME)

$(OBJ)%.o:	$(SRC)%.c
		@$(CC) $(CFLAGS) -c -o $@ $<
		@echo -e "[OK]\t$@"

$(NAME):	$(OBJS)
		@$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LDFLAGS)
		@echo -e "[DONE]\t$(NAME)"

clean:
		@rm -vf $(OBJS)

fclean:		clean
		@rm -vf $(NAME)

re:		fclean all

.PHONY: all clean fclean re
