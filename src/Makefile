.PHONY: install uninstall dvi dist test check valgrind clean git gcov_report
CXX = gcc
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++17
LIBS = -lstdc++ -lpthread -lm 
LTEST = -lgtest

GCOVFLAGS = --coverage
SRC = $(wildcard model/*.cc controller/*.cc)
OBJS = $(SRC:.cc=.o)

OS := $(shell uname -s)

ifeq ($(OS),Linux)
	OPEN_CMD := xdg-open
else ifeq ($(OS),Darwin)
	OPEN_CMD := open
endif

all: clean build

build: install

rebuild: clean all

tests: $(OBJS)
	@echo "┏-------------------┓"
	@echo "┃   Testing models  ┃"
	@echo "┗-------------------┛"
	$(CXX) $(CXXFLAGS) tests/viever_test.cc $^ -o viever_test $(LTEST) $(LIBS)
	./viever_test

	
gcov_report: clean
	@echo "┏------------------------------------┓"
	@echo "┃       Generating html report       ┃"
	@echo "┗------------------------------------┛"
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $(SRC) tests/viever_test.cc -o viever_test $(LTEST) $(LIBS)
	./viever_test
	lcov -t "Report" -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	rm -rf *.gcno *.gcov *.gcda *.info *.a *.dSYM tests/*.o
	@echo "┏-----------------------------┓"
	@echo "┃     HTML report is ready    ┃"
	@echo "┗-----------------------------┛"
	$(OPEN_CMD) ./report/index.html
	


	
clang:
	@echo "┏------------------------------┓"
	@echo "┃    Clang format correction   ┃"
	@echo "┗------------------------------┛"
	clang-format -style=Google -i **/*.cc **/*.h

clang_check:
	@echo "┏------------------------------┓"
	@echo "┃   Checnking to clang-format  ┃"
	@echo "┗------------------------------┛"
	clang-format -style=Google -n **/*.cc **/*.h

	
install: clean	
	@echo "┏-----------------------------┓"
	@echo "┃     Start installation      ┃"
	@echo "┗-----------------------------┛"
	make clean
	mkdir -p ../build
	cd view && qmake6 && make && make clean
	rm -f ./view/Makefile
	mv ./view/3D_VIEVER_V0_2 ../build
	@echo "┏-------------------------------------------------┓"
	@echo "┃        The installation was successful          ┃"
	@echo "┃    The executable file is located in build      ┃"
	@echo "┗-------------------------------------------------┛"


uninstall:
	@echo "┏---------------------------------┓"
	@echo "┃     Uninstalling a program      ┃"
	@echo "┗---------------------------------┛"
	rm -rf build
	@echo "┏---------------------------------┓"
	@echo "┃    The programm is uninstalled  ┃"
	@echo "┗---------------------------------┛"

dist:
	@echo "┏---------------------------------┓"
	@echo "┃     Creating distribution       ┃"
	@echo "┗---------------------------------┛"
		rm -drf ./dist
	mkdir -p ./dist
	cp  ../build/3D_VIEVER_V0_2 ./dist
	cp ./settings.ini ./dist
	cp ../README.md ./dist
	cd ./dist && tar cvzf 3D_VIEVER_V0_2.tgz *
	rm ./dist/3D_VIEVER_V0_2
	rm ./dist/settings.ini
	rm ../dist/README.md
	@echo "┏------------------------------------┓"
	@echo "┃    Distribution tgz is ready       ┃"
	@echo "┗------------------------------------┛"

	
dvi:
	open ../README.md
	
valgrind: clean tests
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./viever_test 2>>1.txt
	grep ERROR 1.txt

clean:
	@echo "┏-----------------------------┓"	
	@echo "┃   Deleting temporary files  ┃"
	@echo "┗-----------------------------┛"
	rm -rf *.o main viever_test *.gcno *.gcda *.dSYM model/*.o view/*.o report
	rm -rf 1.txt
	rm -rf controller/*.o
	rm -drf ./dist
