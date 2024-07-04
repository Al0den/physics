build:
	g++ -c ./src/*.cpp -std=c++17
	ar rcs physics.a *.o
	mv physics.a ./lib/libphysics.a
	rm *.o
simple:
	g++ ~lphysics ./test/simple.cpp && mv a.out ./build/simple.out && rm -rf include/*.gch
balls:
	g++ -lSDL2 ./test/balls/*.cpp && mv a.out ./build/balls.out && rm -rf include/*.gch test/balls/*.gch
pendulum:
	make -B build
	g++ -lSDL2 -lphysics -lrenderer -lSDL2_ttf -O3 ./test/pendulum/*.cpp && mv a.out ./build/pendulum.out && rm -rf include/*.gch test/pendulum/*.gch 


