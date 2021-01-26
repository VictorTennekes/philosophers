# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vtenneke <vtenneke@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/23 11:18:15 by vtenneke      #+#    #+#                  #
#    Updated: 2020/02/11 14:20:34 by victor        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	philo_two
SRCS			=	main.c\
					parser.c\
					philo.c\
					threads.c\
					utils.c\
					time.c
CFILES			=	$(SRCS:%=src/%)
OFILES			=	$(CFILES:.c=.o)
FLAGS			=	-Wall -Wextra -Werror -O3
TAIL			=	-pthread
INCLUDES		=	-I include
TARGETS 		=	$(OFILES)

# COLORS
WHITE   = \x1b[37;01m
CYAN    = \x1b[36;01m
PINK    = \x1b[35;01m
BLUE    = \x1b[34;01m
YELLOW  = \x1b[33;01m
GREEN   = \x1b[32;01m
RED     = \x1b[31;01m
BLACK   = \x1b[30;01m
RESET   = \x1b[0m

ifeq ($(DEBUG),1)
FLAGS += -g -fsanitize=address -DDEBUG
endif

all: $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) $(INCLUDES) $< $(TAIL) -o $@

$(NAME): $(TARGETS)
	@echo "$(WHITE)/-----		Compiling $(NAME)	-----\\ $(RESET)"
	$(CC) $(FLAGS) $(INCLUDES) $(TAIL) $^ -o $@

clean:
	@echo "$(WHITE)/-----		Cleaning $(NAME)		-----\\ $(RESET)"
	rm -f $(BONUS_OFILES) $(OFILES)

fclean: clean
	@echo "$(WHITE)/-----		Fcleaning $(NAME)	-----\\ $(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
