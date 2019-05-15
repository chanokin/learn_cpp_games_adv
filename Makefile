LIBS=-lstdc++
CFLAGS=-Wall -std=gnu++0x
INCLUDES=-Iinclude


Exercise_2_1: Exercise_2_1.cpp
	$(CXX) -o $@ $(LIBS) $(CFLAGS) $@.cpp
	./$@

Exercise_3_1: Exercise_3_1.cpp
	$(CXX) -o $@ $(LIBS) $(CFLAGS) $@.cpp
	./$@

Exercise_4_1: Exercise_4_1.cpp
	$(CXX) -o $@ $(LIBS) $(CFLAGS) $@.cpp
	./$@

Exercise_5_1: Exercise_5_1.cpp
	$(CXX) -o $@ $(LIBS) $(CFLAGS) $@.cpp
	./$@

Exercise_6_1: Exercise_6_1.cpp
	$(CXX) -o $@ $(LIBS) $(CFLAGS) $@.cpp
	./$@	

Exercise_7_1: Exercise_7_1.cpp
	$(CXX) -o $@ $(LIBS) $(CFLAGS) $@.cpp
	./$@