NAME = log.a

SRCS =	log.c

OBJS = $(SRCS:.c=.o)

SRCS_DIR = .
OBJS_DIR = .
INCLUDES = .

SRCS_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS_PATH)
	ar rc $(NAME) $(OBJS_PATH)
	ranlib $(NAME)

$(OBJS_PATH): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	gcc $(FLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean | all
