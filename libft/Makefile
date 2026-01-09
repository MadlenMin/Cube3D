NAME = libft.a

SRCS = ft_itoa.c ft_strjoin.c ft_putnbr.c ft_substr.c ft_strdup.c ft_strlcpy.c ft_atoi.c ft_split.c ft_strlen.c ft_strncmp.c ft_strchr.c

OBJS = $(SRCS:.c=.o)

INClUDE = -I

CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror $(INCLUDE) 

all : $(NAME)

%.o:	%.c libft.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
			ar -rcs $(NAME) $(OBJS)

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re :	fclean $(NAME)

.PHONY:	all clean fclean re