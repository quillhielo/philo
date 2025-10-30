# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 19:18:03 by acarbajo          #+#    #+#              #
#    Updated: 2025/10/30 17:32:38 by acarbajo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJDIR = objs

SRC = main.c 

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)


$(OBJDIR)/%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
