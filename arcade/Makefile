CXX=/usr/bin/gcc
LIBS=-lstdc++ -lm -lSDL2 -lSDL2main
CFLAGS=-g -Wall -std=c++1y -D_REENTRANT -D_USE_MATH_DEFINES
LDFLAGS=-L/usr/lib/x86_64-linux-gnu
INCLUDES=-I../include -I../include/graphics -I../include/app -I../include/scene \
		 -I../include/input -I../include/games \
		 -I../include/games/breakout \
		 -I/usr/include/SDL2

src = $(wildcard $(abspath ../src/graphics/*.cpp)) \
	  $(wildcard $(abspath ../src/app/*.cpp)) \
	  $(wildcard $(abspath ../src/input/*.cpp)) \
	  $(wildcard $(abspath ../src/games/*.cpp)) \
	  $(wildcard $(abspath ../src/games/breakout/*.cpp)) \
	  $(wildcard $(abspath ../src/scene/*.cpp)) \
	  $(wildcard $(abspath ../src/*.cpp)) 

objs = $(patsubst %.cpp,%.o,$(src)) 

arcade: $(objs)
	$(CXX) $^ $@.cpp -o $@ $(LIBS) $(CFLAGS) $(INCLUDES) 
	./$@

%.o: %.cpp
	$(CXX) -c -o $@ $<  $(LIBS) $(CFLAGS) $(INCLUDES) 

clean:
	rm -fr arcade