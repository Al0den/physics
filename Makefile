CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lSDL2 -lrenderer -lphysics -lSDL2_ttf -O3

TARGET = ./lib/libphysics.a

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $^

clean:
	rm -rf $(OBJS) $(TARGET)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

simple: $(TARGET)
	g++ -lphysics ./test/simple.cpp && mv a.out ./build/simple.out && rm -rf include/*.gch

balls: $(TARGET)
	g++ -lSDL2 ./test/balls/*.cpp && mv a.out ./build/balls.out && rm -rf include/*.gch test/balls/*.gch

pendulum: $(TARGET)
	g++ -lSDL2 -lphysics -lrenderer -lSDL2_ttf -O3 ./test/pendulum/*.cpp -std=c++17 && mv a.out ./build/pendulum.out && rm -rf include/*.gch test/pendulum/*.gch 

debug: $(TARGET)
	g++ -lphysics mains/debug.cpp -std=c++17 -fsanitize=address -o ./build/debug.out && ./build/debug.out

