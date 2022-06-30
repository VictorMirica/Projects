# Protocoale de comunicatii:
# Laborator 8: Multiplexare
# Makefile

CFLAGS = -Wall -g

# Portul pe care asculta serverul (de completat)
PORT = 4242

# Adresa IP a serverului (de completat)
IP_SERVER = 127.0.0.1

# ID-ul clientului
ID = VICTOR

all: server subscriber

# Compileaza server.c
server: server.c
	gcc ${CFLAGS} -o server server.c

# Compileaza client.c
subscriber: subscriber.c
	gcc ${CFLAGS} -o subscriber subscriber.c

.PHONY: clean run_server run_subscriber

# Ruleaza serverul
run_server:
	./server ${PORT}

# Ruleaza clientul
run_subscriber:
	./subscriber ${ID} ${IP_SERVER} ${PORT}

clean:
	rm -f server subscriber
