CXX=/usr/bin/gcc
LIBS=-lstdc++ -lm -lSDL2 -lSDL2main
CFLAGS=-Wall -std=c++1y -D_REENTRANT -D_USE_MATH_DEFINES
LDFLAGS=-L/usr/lib/x86_64-linux-gnu
INCLUDES=-I../include -I../include/graphics -I../include/app -I../include/scene \
		 -I../include/input -I../include/games -I/usr/include/SDL2

src = $(wildcard ../src/graphics/*.cpp) \
	  $(wildcard ../src/scene/*.cpp) \
	  $(wildcard ../src/app/*.cpp) \
	  $(wildcard ../src/input/*.cpp) \
	  $(wildcard ../src/games/*.cpp) \
	  $(wildcard ../src/*.cpp) 

# obj = $(patsubst %.cpp,%.o,$(src)) 

arcade: $(src)
	$(CXX) $^ $@.cpp -o $@ $(LIBS) $(CFLAGS) $(INCLUDES) 
	./$@

clean:
	rm -fr arcade