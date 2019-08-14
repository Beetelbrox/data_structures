CCC=g++

TARGET=array

${TARGET}: test.o 
	$(CCC) -g -Wall -o ${TARGET} test.o

test.o: test/test.cpp src/${TARGET}.h
	$(CCC) -g -Wall -I src/ -c test/test.cpp

clean:
	rm --force ${TARGET} *.o
