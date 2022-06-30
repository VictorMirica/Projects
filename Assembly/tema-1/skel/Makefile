build:
	gcc -m32 tema1.c -g -o tema

run:
	./tema

runv:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tema

clean:
	rm tema

checker:
	python3 checker.py

