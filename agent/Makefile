CC = gcc
CFLAGS = -fPIC -Wall
LDFLAGS = -ldl

all: livepatch_agent

livepatch_agent: livepatch_agent.c
	$(CC) $(CFLAGS) livepatch_agent.c -o livepatch_agent $(LDFLAGS)

clean:
	rm -f livepatch_agent
auto_update: auto_update.c
	$(CC) auto_update.c -o auto_update

all: livepatch_agent auto_update
