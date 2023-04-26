# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/onefore/projects/course-paper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/onefore/projects/course-paper

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/onefore/projects/course-paper/CMakeFiles /home/onefore/projects/course-paper//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/onefore/projects/course-paper/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named course-paper

# Build rule for target.
course-paper: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 course-paper
.PHONY : course-paper

# fast build rule for target.
course-paper/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/build
.PHONY : course-paper/fast

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/main.cpp.s
.PHONY : main.cpp.s

sources/Bot.o: sources/Bot.cpp.o
.PHONY : sources/Bot.o

# target to build an object file
sources/Bot.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Bot.cpp.o
.PHONY : sources/Bot.cpp.o

sources/Bot.i: sources/Bot.cpp.i
.PHONY : sources/Bot.i

# target to preprocess a source file
sources/Bot.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Bot.cpp.i
.PHONY : sources/Bot.cpp.i

sources/Bot.s: sources/Bot.cpp.s
.PHONY : sources/Bot.s

# target to generate assembly for a file
sources/Bot.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Bot.cpp.s
.PHONY : sources/Bot.cpp.s

sources/Eat.o: sources/Eat.cpp.o
.PHONY : sources/Eat.o

# target to build an object file
sources/Eat.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Eat.cpp.o
.PHONY : sources/Eat.cpp.o

sources/Eat.i: sources/Eat.cpp.i
.PHONY : sources/Eat.i

# target to preprocess a source file
sources/Eat.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Eat.cpp.i
.PHONY : sources/Eat.cpp.i

sources/Eat.s: sources/Eat.cpp.s
.PHONY : sources/Eat.s

# target to generate assembly for a file
sources/Eat.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Eat.cpp.s
.PHONY : sources/Eat.cpp.s

sources/Empty.o: sources/Empty.cpp.o
.PHONY : sources/Empty.o

# target to build an object file
sources/Empty.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Empty.cpp.o
.PHONY : sources/Empty.cpp.o

sources/Empty.i: sources/Empty.cpp.i
.PHONY : sources/Empty.i

# target to preprocess a source file
sources/Empty.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Empty.cpp.i
.PHONY : sources/Empty.cpp.i

sources/Empty.s: sources/Empty.cpp.s
.PHONY : sources/Empty.s

# target to generate assembly for a file
sources/Empty.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Empty.cpp.s
.PHONY : sources/Empty.cpp.s

sources/Graphics.o: sources/Graphics.cpp.o
.PHONY : sources/Graphics.o

# target to build an object file
sources/Graphics.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Graphics.cpp.o
.PHONY : sources/Graphics.cpp.o

sources/Graphics.i: sources/Graphics.cpp.i
.PHONY : sources/Graphics.i

# target to preprocess a source file
sources/Graphics.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Graphics.cpp.i
.PHONY : sources/Graphics.cpp.i

sources/Graphics.s: sources/Graphics.cpp.s
.PHONY : sources/Graphics.s

# target to generate assembly for a file
sources/Graphics.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Graphics.cpp.s
.PHONY : sources/Graphics.cpp.s

sources/Object.o: sources/Object.cpp.o
.PHONY : sources/Object.o

# target to build an object file
sources/Object.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Object.cpp.o
.PHONY : sources/Object.cpp.o

sources/Object.i: sources/Object.cpp.i
.PHONY : sources/Object.i

# target to preprocess a source file
sources/Object.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Object.cpp.i
.PHONY : sources/Object.cpp.i

sources/Object.s: sources/Object.cpp.s
.PHONY : sources/Object.s

# target to generate assembly for a file
sources/Object.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Object.cpp.s
.PHONY : sources/Object.cpp.s

sources/Poison.o: sources/Poison.cpp.o
.PHONY : sources/Poison.o

# target to build an object file
sources/Poison.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Poison.cpp.o
.PHONY : sources/Poison.cpp.o

sources/Poison.i: sources/Poison.cpp.i
.PHONY : sources/Poison.i

# target to preprocess a source file
sources/Poison.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Poison.cpp.i
.PHONY : sources/Poison.cpp.i

sources/Poison.s: sources/Poison.cpp.s
.PHONY : sources/Poison.s

# target to generate assembly for a file
sources/Poison.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Poison.cpp.s
.PHONY : sources/Poison.cpp.s

sources/Wall.o: sources/Wall.cpp.o
.PHONY : sources/Wall.o

# target to build an object file
sources/Wall.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Wall.cpp.o
.PHONY : sources/Wall.cpp.o

sources/Wall.i: sources/Wall.cpp.i
.PHONY : sources/Wall.i

# target to preprocess a source file
sources/Wall.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Wall.cpp.i
.PHONY : sources/Wall.cpp.i

sources/Wall.s: sources/Wall.cpp.s
.PHONY : sources/Wall.s

# target to generate assembly for a file
sources/Wall.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/Wall.cpp.s
.PHONY : sources/Wall.cpp.s

sources/World.o: sources/World.cpp.o
.PHONY : sources/World.o

# target to build an object file
sources/World.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/World.cpp.o
.PHONY : sources/World.cpp.o

sources/World.i: sources/World.cpp.i
.PHONY : sources/World.i

# target to preprocess a source file
sources/World.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/World.cpp.i
.PHONY : sources/World.cpp.i

sources/World.s: sources/World.cpp.s
.PHONY : sources/World.s

# target to generate assembly for a file
sources/World.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/course-paper.dir/build.make CMakeFiles/course-paper.dir/sources/World.cpp.s
.PHONY : sources/World.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... course-paper"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... sources/Bot.o"
	@echo "... sources/Bot.i"
	@echo "... sources/Bot.s"
	@echo "... sources/Eat.o"
	@echo "... sources/Eat.i"
	@echo "... sources/Eat.s"
	@echo "... sources/Empty.o"
	@echo "... sources/Empty.i"
	@echo "... sources/Empty.s"
	@echo "... sources/Graphics.o"
	@echo "... sources/Graphics.i"
	@echo "... sources/Graphics.s"
	@echo "... sources/Object.o"
	@echo "... sources/Object.i"
	@echo "... sources/Object.s"
	@echo "... sources/Poison.o"
	@echo "... sources/Poison.i"
	@echo "... sources/Poison.s"
	@echo "... sources/Wall.o"
	@echo "... sources/Wall.i"
	@echo "... sources/Wall.s"
	@echo "... sources/World.o"
	@echo "... sources/World.i"
	@echo "... sources/World.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

