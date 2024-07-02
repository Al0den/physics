simple:
	g++ ./include/*.hpp ./src/*.cpp ./test/simple.cpp && mv a.out ./build/simple.out && rm -rf include/*.gch
balls:
	g++ -lSDL2 ./test/balls/*.cpp && mv a.out ./build/balls.out && rm -rf include/*.gch test/balls/*.gch
pendulum:
	g++ -lSDL2 -O3 ../render_engine/src/*.cpp src/*.cpp ./test/pendulum/*.cpp && mv a.out ./build/pendulum.out && rm -rf include/*.gch test/pendulum/*.gch 
