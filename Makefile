COMPILER = c++
ADD_CFLAGS = -Wall -O3 -g
NO_PKG_LIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
CXXFLAGS = $(ADD_CFLAGS)
LINKS = $(NO_PKG_LIBS)
SOURCES = $(wildcard *.cpp)
EXEC_NAME = cg_task1
OBJECTS = $(SOURCES:.cpp=.o)
.PRECIOUS : %.o
.PHONY : clean
.PHONY : run


all: $(OBJECTS)
	$(COMPILER) -o $(EXEC_NAME) $(OBJECTS) $(LINKS)

%.o : %.cpp %.h
	$(COMPILER) -c $(CXXFLAGS) $< -o $@

run: clean all
	./$(EXEC_NAME)

clean:
	rm -f $(OBJECTS) $(EXEC_NAME)
