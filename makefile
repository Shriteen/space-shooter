all:
	echo "ToDo"

sprite.o: sprite.cpp sprite.h
	g++ sprite.cpp -c

movable.o: movable.cpp movable.h
	g++ movable.cpp -c

movable.h: sprite.h
	touch movable.h

environment.h: ship.h asteroid.h bullet.h health_pack.h
	touch environment.h

ship.h: movable.h
	touch ship.h

asteroid.h: movable.h
	touch asteroid.h

bullet.h: movable.h
	touch bullet.h

health_pack.h: movable.h
	touch health_pack.h

ship.o: ship.cpp ship.h environment.h
	g++ ship.cpp -c

asteroid.o: asteroid.cpp asteroid.h environment.h
	g++ asteroid.cpp -c

bullet.o: bullet.cpp bullet.h environment.h
	g++ bullet.cpp -c

health_pack.o: health_pack.cpp health_pack.h environment.h
	g++ health_pack.cpp -c

clean:
	rm *.o
