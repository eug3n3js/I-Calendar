CXX = g++
LD = g++
CXXFLAGS = -std=c++17 -Wall -pedantic
HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

all: compile doc

compile: bilouyev

bilouyev: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -c -o $@

clean:
	rm -rf bilouyev build/ doc/ 

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile



build/andExpression.o: src/andExpression.cpp src/andExpression.h src/expression.h src/event.h \
 src/time.h
build/baseCalendar.o: src/baseCalendar.cpp src/baseCalendar.h src/event.h src/time.h \
 src/loadConfig.h
build/calendarApp.o: src/calendarApp.cpp src/calendarApp.h src/time.h src/event.h src/csvrw.h \
 src/parser.h src/expression.h src/calendarFactory.h src/baseCalendar.h src/dayCalendar.h \
 src/weekCalendar.h src/monthCalendar.h src/groupCalendar.h 
build/calendarFactory.o: src/calendarFactory.cpp src/calendarFactory.h src/event.h src/time.h \
 src/baseCalendar.h src/dayCalendar.h src/weekCalendar.h src/monthCalendar.h \
 src/groupCalendar.h
build/csvrw.o: src/csvrw.cpp src/csvrw.h src/event.h src/time.h
dateExpression.o: src/dateExpression.cpp src/dateExpression.h src/time.h src/expression.h \
 src/event.h
build/dayCalendar.o: src/dayCalendar.cpp src/dayCalendar.h src/event.h src/time.h \
 src/baseCalendar.h src/loadConfig.cpp src/loadConfig.h
build/durationExpression.o: src/durationExpression.cpp src/durationExpression.h src/time.h \
 src/expression.h src/event.h
build/event.o: src/event.cpp src/event.h src/time.h
build/expression.o: src/expression.cpp src/expression.h src/event.h src/time.h
build/groupCalendar.o: src/groupCalendar.cpp src/groupCalendar.h src/baseCalendar.h src/event.h \
 src/time.h src/monthCalendar.h
build/loadConfig.o: src/loadConfig.cpp src/loadConfig.h
build/locationExpression.o: src/locationExpression.cpp src/locationExpression.h \
 src/expression.h src/event.h src/time.h
build/main.o: src/main.cpp src/calendarApp.h src/time.h src/event.h src/csvrw.h src/parser.h \
 src/expression.h src/calendarFactory.h src/baseCalendar.h src/dayCalendar.h \
 src/weekCalendar.h src/monthCalendar.h src/groupCalendar.h
build/monthCalendar.o: src/monthCalendar.cpp src/monthCalendar.h src/baseCalendar.h src/event.h \
 src/time.h src/loadConfig.h
build/moveExpression.o: src/moveExpression.cpp src/moveExpression.h src/expression.h \
 src/event.h src/time.h
build/nameExpression.o: src/nameExpression.cpp src/nameExpression.h src/expression.h \
 src/event.h src/time.h
build/notExpression.o: src/notExpression.cpp src/notExpression.h src/expression.h src/event.h \
 src/time.h
build/orExpression.o: src/orExpression.cpp src/orExpression.h src/expression.h src/event.h \
 src/time.h
build/parser.o: src/parser.cpp src/parser.h src/time.h src/event.h src/expression.h src/andExpression.h \
 src/orExpression.h src/notExpression.h src/dateExpression.h src/durationExpression.h \
 src/locationExpression.h src/tagExpression.h src/moveExpression.h src/nameExpression.h \
 src/participantsExpression.h
build/participantsExpression.o: src/participantsExpression.cpp \
 src/participantsExpression.h src/expression.h src/event.h src/time.h
build/tagExpression.o: src/tagExpression.cpp src/tagExpression.h src/expression.h src/event.h \
 src/time.h
build/time.o: src/time.cpp src/time.h
build/weekCalendar.o: src/weekCalendar.cpp src/weekCalendar.h src/baseCalendar.h src/event.h \
 src/time.h src/loadConfig.h

