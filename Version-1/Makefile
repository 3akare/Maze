CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
INCLUDE =  -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/System/Library/Frameworks/OpenGL.framework/Headers -I/Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/System/Library/Frameworks/GLUT.framework/Headers
FRAMEWORK = -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework OpenGL -framework GLUT

main: $(SRC)
	$(CC) $(CFLAGS) *.c $(INCLUDE) $(FRAMEWORK) -o a.out
	./a.out
