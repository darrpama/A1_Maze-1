CC = g++
CCFLAGS = -g -std=c++17 -Wall -Werror -Wextra 
LDFLAGS = -fprofile-arcs -ftest-coverage
PROJECTDIR = $(CURDIR)
BUILDDIR = $(PROJECTDIR)/build
EXECUTABLE = test.out
STATICLIB = Maze.a
DISTDIR = ../distributive

HEADERS = \
	$(PROJECTDIR)/models/cave/cave.h \
	$(PROJECTDIR)/models/maze/maze_generator.h \
	$(PROJECTDIR)/models/maze/maze_parser.h \
	$(PROJECTDIR)/models/maze/maze_saver.h \
	$(PROJECTDIR)/models/maze/maze.h \
	$(PROJECTDIR)/models/utils.h

SOURCES = \
	$(PROJECTDIR)/models/cave/cave.cc \
	$(PROJECTDIR)/models/maze/maze_generator.cc \
	$(PROJECTDIR)/models/maze/maze_parser.cc \
	$(PROJECTDIR)/models/maze/maze_saver.cc \
	$(PROJECTDIR)/models/maze/maze.cc \
	$(PROJECTDIR)/tests/cave_test.cc \
	$(PROJECTDIR)/tests/maze_generator_test.cc \
	$(PROJECTDIR)/tests/maze_parser_test.cc \
	$(PROJECTDIR)/tests/maze_resolver_test.cc \
	$(PROJECTDIR)/tests/maze_saver_test.cc \
	$(PROJECTDIR)/tests/run_all_tests.cc

OTHERS = \
	$(PROJECTDIR)/controllers/controller_singleton.h \
	$(PROJECTDIR)/controllers/controller_singleton.cc

OBJECTS = $(SOURCES:.cc=.o)
GCDA = $(SOURCES:.cc=.gcda)
GCNO = $(SOURCES:.cc=.gcno)

all: install

tests: $(SOURCES) $(EXECUTABLE)

dvi:
	open ./README.pdf

build:
	cd $(PROJECTDIR) && ls -la && mkdir $(BUILDDIR) && cd $(BUILDDIR) && cmake .. && make

install:
	@read -p "Enter path to install: " path; \
	if [ -z "$$path" ]; then \
        path="./"; \
    fi; \
	cd $$path && ls -la && mkdir $(BUILDDIR) && cd $(BUILDDIR) && cmake .. && make
	$(BUILDDIR)/Maze.app/Contents/MacOS/Maze 

uninstall: clean

dist: build
	rm -rf $(DISTDIR)
	mkdir $(DISTDIR)
	cp -r $(PROJECTDIR) $(DISTDIR)
	cd .. && tar -czvf distributive.tgz distributive
	rm -rf $(DISTDIR)

check:
	clang-format -i --style="Google" $(SOURCES) $(HEADERS) $(OTHERS)
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=unusedStructMember --suppress=unusedFunction --suppress=missingInclude --suppress=missingIncludeSystem $(SOURCES) $(OTHERS) $(HEADERS)

leaks: $(EXECUTABLE)
	leaks -atExit -- ./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) -lgtest
	./$(EXECUTABLE) 

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $< $(LDFLAGS)

$(STATICLIB): $(OBJECTS)
	ar rcs $(STATICLIB) $^

gcov_report: $(EXECUTABLE)
	./$(EXECUTABLE)
	lcov -t "./test.out" -o test.info --no-external -c -d . --ignore-errors mismatch,mismatch
	genhtml -o report test.info 
	open report/index.html

.PHONY: clean test dvi dist check leaks gcov_report
clean:
	rm -rf $(OBJECTS)
	rm -rf $(EXECUTABLE)
	rm -rf $(STATICLIB)
	rm -rf $(BUILDDIR)
	rm -rf *.gcno $(GCDA) $(GCNO) *.info
	rm -rf report
	rm -rf *.tgz ../*.tgz
