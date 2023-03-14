CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = tag.o controller.o a3q3.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = a3q3

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
