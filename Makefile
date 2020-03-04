build: tema1


tema1: tema1.c
	gcc tema1.c -Wall -Wextra -lm -o tema1

run:
	./tema1

clean:
	rm -f tema1
