PROJECTDIR = $(CURDIR)
BUILDDIR = $(PROJECTDIR)/build
EXE = Maze.exe
TEST_EXE = MazeTests.exe
DISTDIR = ../distributive


HEADERS = \
	$(PROJECTDIR)/views/*.h \
	$(PROJECTDIR)/controllers/*.h \
	$(PROJECTDIR)/models/*/*.h \
	$(PROJECTDIR)/models/*/*.h \
	$(PROJECTDIR)/models/*.h


SOURCES = \
	$(PROJECTDIR)/main.cc \
	$(PROJECTDIR)/views/*.cc \
	$(PROJECTDIR)/controllers/*.cc \
	$(PROJECTDIR)/models/*/*.cc \
	$(PROJECTDIR)/models/*/*.cc \
	$(PROJECTDIR)/tests/*.cc \


ifeq ($(shell uname), Darwin)
	EXE = Maze
	TEST_EXE = MazeTests
endif

ifeq ($(shell uname), Linux)
	EXE = Maze
	TEST_EXE = MazeTests
endif


all: install tests gcov_report clean dist check dvi


install: | $(BUILDDIR)-release
	read -p "Enter path to install: " path; \
	if [ -z "$$path" ]; then \
        path="./"; \
    fi; \
	if [ ! -d $$path ]; then mkdir -p $$path; fi; \
	if ! [ "$$path" != "$${path#/}" ]; then \
		path="$(PROJECTDIR)/$$path"; \
	fi; \
	cd $(BUILDDIR)-release && \
	cmake .. -DINSTALL=ON -DCMAKE_INSTALL_PREFIX=$$path -G "Unix Makefiles" && \
	cmake --build . --config=Release
	

uninstall: clean
	rm -rf ./bin ./Maze.exe ./$(TEST_EXE)


tests: | $(BUILDDIR)-testing
	cd $(BUILDDIR)-testing && \
	cmake .. -DTESTING=ON -G "Unix Makefiles" && \
	cmake --build . --config=RelWithDebInfo


gcov_report: | $(BUILDDIR)-coverage
	cd $(BUILDDIR)-coverage && \
	cmake .. -DTESTING=ON -DCOVERAGE=ON -G "Unix Makefiles" && \
	cmake --build . --config=RelWithDebInfo
	./$(TEST_EXE)
	lcov -t "$(TEST_EXE)" -o test.info --no-external -c -d $(BUILDDIR)-coverage
	genhtml -o report test.info 
	open report/index.html


dvi:
	open ./README.pdf


dist:
	rm -rf $(DISTDIR)
	mkdir -p $(DISTDIR)
	cp -r $(PROJECTDIR) $(DISTDIR)
	cd .. && tar -czvf distributive.tgz distributive
	rm -rf $(DISTDIR)


check:
	clang-format -i --style="Google" $(SOURCES) $(HEADERS)
# cppcheck --std=c++17 --language=c++ --enable=all --suppress=unusedStructMember --suppress=unusedFunction --suppress=missingInclude --suppress=missingIncludeSystem $(SOURCES) $(HEADERS)


leaks: tests
	-leaks --atExit -- ./$(TEST_EXE)
	leaks --atExit -- "./build/Maze.app/Contents/MacOS/Maze"


$(BUILDDIR)-%:
	mkdir -p $@


.PHONY: clean test dvi dist check leaks gcov_report
clean:
	rm -rf $(BUILDDIR)-*
	rm -rf report *.info
	rm -rf *.tgz ../*.tgz

