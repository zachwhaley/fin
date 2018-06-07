CFLAGS = -std=gnu11 -g -ggdb -Wall -Werror -MMD -MP

PRGM  = fin
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

all: $(PRGM)

$(PRGM): $(OBJS)
	$(CC) $(OBJS) -o $(PRGM)

clean:
	$(RM) $(OBJS) $(DEPS) $(PRGM)

-include $(DEPS)
