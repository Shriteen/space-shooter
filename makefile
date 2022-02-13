all:
	echo "ToDo"

sprite.o: sprite.cpp sprite.h
	g++ sprite.cpp -c

movable.o: movable.cpp movable.h
	g++ movable.cpp -c

clean:
	rm *.o
