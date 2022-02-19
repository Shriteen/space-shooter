all: sprite.o movable.o environment.o ship.o asteroid.o bullet.o health_pack.o gameplay.o menu.o space_shooter.o
	g++ sprite.o movable.o environment.o ship.o asteroid.o bullet.o health_pack.o gameplay.o menu.o space_shooter.o -lncurses -o space_shooter

sprite.o: sprite.cpp sprite.h
	g++ sprite.cpp -c

movable.o: movable.cpp movable.h environment.h
	g++ movable.cpp -c

movable.h: sprite.h
	touch movable.h

environment.h: ship.h asteroid.h bullet.h health_pack.h gameplay.h
	touch environment.h

ship.h: movable.h gameplay.h
	touch ship.h

asteroid.h: movable.h
	touch asteroid.h

bullet.h: movable.h
	touch bullet.h

health_pack.h: movable.h
	touch health_pack.h

environment.o: environment.cpp ship.h asteroid.h bullet.h health_pack.h gameplay.h
	g++ environment.cpp -c

ship.o: ship.cpp ship.h environment.h
	g++ ship.cpp -c

asteroid.o: asteroid.cpp asteroid.h environment.h
	g++ asteroid.cpp -c

bullet.o: bullet.cpp bullet.h environment.h
	g++ bullet.cpp -c

health_pack.o: health_pack.cpp health_pack.h environment.h
	g++ health_pack.cpp -c

gameplay.o: gameplay.cpp gameplay.h environment.h
	g++ gameplay.cpp -c

menu.o: menu.cpp menu.h
	g++ menu.cpp -c

space_shooter.h: gameplay.h menu.h
	touch space_shooter.h

space_shooter.o: space_shooter.cpp space_shooter.h
	g++ space_shooter.cpp -c

clean:
	rm *.o
	rm space_shooter
	rm highscore
