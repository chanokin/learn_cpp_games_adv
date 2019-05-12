LIBS=-lstdc++
CFLAGS=-Wall


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