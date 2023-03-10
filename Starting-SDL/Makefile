CC = gcc
SRC = main.c
CFLAGS = -Wall -Werror -Wextra -pedantic
INCLUDE =  -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers
FRAMEWORK = -F/Library/Frameworks -framework SDL2 -framework SDL2_image

main: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) $(FRAMEWORK) -o a.out
	./a.out
