CXX=g++
CXXFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11
LD=g++
LDFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11
LIBFLAGS=-lcurses


all: doc compile


compile: main.o menu.o coord.o wmap.o worm.o mapItem.o game.o helper.o
	$(LD) $(LDFLAGS) main.o menu.o coord.o wmap.o worm.o mapItem.o game.o helper.o -o huzevmic $(LIBFLAGS)

huzevmic: main.o menu.o coord.o wmap.o worm.o mapItem.o game.o helper.o
	$(LD) $(LDFLAGS) main.o menu.o coord.o wmap.o worm.o mapItem.o game.o helper.o -o huzevmic $(LIBFLAGS)

run: huzevmic
	./huzevmic

clean:
	rm -rf huzevmic a.out *.o *~ core doc

doc:
	doxygen Doxyfile


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
