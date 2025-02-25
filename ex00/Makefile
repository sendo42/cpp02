CC = c++
CFLAGS = -Wall -Werror -Wextra
TARGET = ./a.out
SRCS = Fixed.cpp \
	main.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

$(OBJS): $(SRCS)
	$(CC) -c $^

.PHONY: all re clean fclean

all: $(TARGET)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all