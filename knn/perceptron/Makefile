EXE=perceptron
CC=g++
CFLAGS=-ggdb -Wall -pedantic -ansi
CXXFLAGS=$(CFLAGS)
LFLAGS=
SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,$(SRCS))
DEPS:=$(patsubst %.cpp,%.d,$(SRCS))

$(EXE): $(DEPS) $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LFLAGS)

%.d: %.cpp
	$(CC) $(CFLAGS) -M $< > $@
	$(CC) $(CFLAGS) -M $< | sed s/\\.o/.d/ >> $@

clean:
	rm -f $(EXE) $(OBJS) $(DEPS)




-include $(DEPS)