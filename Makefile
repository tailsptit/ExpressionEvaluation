# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tails/Documents/Project/C++/ExpressionEvaluation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tails/Documents/Project/C++/ExpressionEvaluation

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/tails/Documents/Project/C++/ExpressionEvaluation/CMakeFiles /home/tails/Documents/Project/C++/ExpressionEvaluation/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/tails/Documents/Project/C++/ExpressionEvaluation/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ExpressionEvaluation

# Build rule for target.
ExpressionEvaluation: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ExpressionEvaluation
.PHONY : ExpressionEvaluation

# fast build rule for target.
ExpressionEvaluation/fast:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/build
.PHONY : ExpressionEvaluation/fast

mainServer.o: mainServer.cpp.o

.PHONY : mainServer.o

# target to build an object file
mainServer.cpp.o:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/mainServer.cpp.o
.PHONY : mainServer.cpp.o

mainServer.i: mainServer.cpp.i

.PHONY : mainServer.i

# target to preprocess a source file
mainServer.cpp.i:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/mainServer.cpp.i
.PHONY : mainServer.cpp.i

mainServer.s: mainServer.cpp.s

.PHONY : mainServer.s

# target to generate assembly for a file
mainServer.cpp.s:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/mainServer.cpp.s
.PHONY : mainServer.cpp.s

src/common/EventManager.o: src/common/EventManager.cpp.o

.PHONY : src/common/EventManager.o

# target to build an object file
src/common/EventManager.cpp.o:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/EventManager.cpp.o
.PHONY : src/common/EventManager.cpp.o

src/common/EventManager.i: src/common/EventManager.cpp.i

.PHONY : src/common/EventManager.i

# target to preprocess a source file
src/common/EventManager.cpp.i:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/EventManager.cpp.i
.PHONY : src/common/EventManager.cpp.i

src/common/EventManager.s: src/common/EventManager.cpp.s

.PHONY : src/common/EventManager.s

# target to generate assembly for a file
src/common/EventManager.cpp.s:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/EventManager.cpp.s
.PHONY : src/common/EventManager.cpp.s

src/common/FileDescriptor.o: src/common/FileDescriptor.cpp.o

.PHONY : src/common/FileDescriptor.o

# target to build an object file
src/common/FileDescriptor.cpp.o:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/FileDescriptor.cpp.o
.PHONY : src/common/FileDescriptor.cpp.o

src/common/FileDescriptor.i: src/common/FileDescriptor.cpp.i

.PHONY : src/common/FileDescriptor.i

# target to preprocess a source file
src/common/FileDescriptor.cpp.i:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/FileDescriptor.cpp.i
.PHONY : src/common/FileDescriptor.cpp.i

src/common/FileDescriptor.s: src/common/FileDescriptor.cpp.s

.PHONY : src/common/FileDescriptor.s

# target to generate assembly for a file
src/common/FileDescriptor.cpp.s:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/FileDescriptor.cpp.s
.PHONY : src/common/FileDescriptor.cpp.s

src/common/Socket.o: src/common/Socket.cpp.o

.PHONY : src/common/Socket.o

# target to build an object file
src/common/Socket.cpp.o:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/Socket.cpp.o
.PHONY : src/common/Socket.cpp.o

src/common/Socket.i: src/common/Socket.cpp.i

.PHONY : src/common/Socket.i

# target to preprocess a source file
src/common/Socket.cpp.i:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/Socket.cpp.i
.PHONY : src/common/Socket.cpp.i

src/common/Socket.s: src/common/Socket.cpp.s

.PHONY : src/common/Socket.s

# target to generate assembly for a file
src/common/Socket.cpp.s:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/Socket.cpp.s
.PHONY : src/common/Socket.cpp.s

src/common/ThreadPool.o: src/common/ThreadPool.cpp.o

.PHONY : src/common/ThreadPool.o

# target to build an object file
src/common/ThreadPool.cpp.o:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/ThreadPool.cpp.o
.PHONY : src/common/ThreadPool.cpp.o

src/common/ThreadPool.i: src/common/ThreadPool.cpp.i

.PHONY : src/common/ThreadPool.i

# target to preprocess a source file
src/common/ThreadPool.cpp.i:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/ThreadPool.cpp.i
.PHONY : src/common/ThreadPool.cpp.i

src/common/ThreadPool.s: src/common/ThreadPool.cpp.s

.PHONY : src/common/ThreadPool.s

# target to generate assembly for a file
src/common/ThreadPool.cpp.s:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/common/ThreadPool.cpp.s
.PHONY : src/common/ThreadPool.cpp.s

src/factory/DataFactory.o: src/factory/DataFactory.cpp.o

.PHONY : src/factory/DataFactory.o

# target to build an object file
src/factory/DataFactory.cpp.o:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/factory/DataFactory.cpp.o
.PHONY : src/factory/DataFactory.cpp.o

src/factory/DataFactory.i: src/factory/DataFactory.cpp.i

.PHONY : src/factory/DataFactory.i

# target to preprocess a source file
src/factory/DataFactory.cpp.i:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/factory/DataFactory.cpp.i
.PHONY : src/factory/DataFactory.cpp.i

src/factory/DataFactory.s: src/factory/DataFactory.cpp.s

.PHONY : src/factory/DataFactory.s

# target to generate assembly for a file
src/factory/DataFactory.cpp.s:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/factory/DataFactory.cpp.s
.PHONY : src/factory/DataFactory.cpp.s

src/math/Evaluation.o: src/math/Evaluation.cpp.o

.PHONY : src/math/Evaluation.o

# target to build an object file
src/math/Evaluation.cpp.o:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/math/Evaluation.cpp.o
.PHONY : src/math/Evaluation.cpp.o

src/math/Evaluation.i: src/math/Evaluation.cpp.i

.PHONY : src/math/Evaluation.i

# target to preprocess a source file
src/math/Evaluation.cpp.i:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/math/Evaluation.cpp.i
.PHONY : src/math/Evaluation.cpp.i

src/math/Evaluation.s: src/math/Evaluation.cpp.s

.PHONY : src/math/Evaluation.s

# target to generate assembly for a file
src/math/Evaluation.cpp.s:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/math/Evaluation.cpp.s
.PHONY : src/math/Evaluation.cpp.s

src/math/Evaluation2.o: src/math/Evaluation2.cpp.o

.PHONY : src/math/Evaluation2.o

# target to build an object file
src/math/Evaluation2.cpp.o:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/math/Evaluation2.cpp.o
.PHONY : src/math/Evaluation2.cpp.o

src/math/Evaluation2.i: src/math/Evaluation2.cpp.i

.PHONY : src/math/Evaluation2.i

# target to preprocess a source file
src/math/Evaluation2.cpp.i:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/math/Evaluation2.cpp.i
.PHONY : src/math/Evaluation2.cpp.i

src/math/Evaluation2.s: src/math/Evaluation2.cpp.s

.PHONY : src/math/Evaluation2.s

# target to generate assembly for a file
src/math/Evaluation2.cpp.s:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/math/Evaluation2.cpp.s
.PHONY : src/math/Evaluation2.cpp.s

src/math/Expression.o: src/math/Expression.cpp.o

.PHONY : src/math/Expression.o

# target to build an object file
src/math/Expression.cpp.o:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/math/Expression.cpp.o
.PHONY : src/math/Expression.cpp.o

src/math/Expression.i: src/math/Expression.cpp.i

.PHONY : src/math/Expression.i

# target to preprocess a source file
src/math/Expression.cpp.i:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/math/Expression.cpp.i
.PHONY : src/math/Expression.cpp.i

src/math/Expression.s: src/math/Expression.cpp.s

.PHONY : src/math/Expression.s

# target to generate assembly for a file
src/math/Expression.cpp.s:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/math/Expression.cpp.s
.PHONY : src/math/Expression.cpp.s

src/server/TcpServer.o: src/server/TcpServer.cpp.o

.PHONY : src/server/TcpServer.o

# target to build an object file
src/server/TcpServer.cpp.o:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/server/TcpServer.cpp.o
.PHONY : src/server/TcpServer.cpp.o

src/server/TcpServer.i: src/server/TcpServer.cpp.i

.PHONY : src/server/TcpServer.i

# target to preprocess a source file
src/server/TcpServer.cpp.i:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/server/TcpServer.cpp.i
.PHONY : src/server/TcpServer.cpp.i

src/server/TcpServer.s: src/server/TcpServer.cpp.s

.PHONY : src/server/TcpServer.s

# target to generate assembly for a file
src/server/TcpServer.cpp.s:
	$(MAKE) -f CMakeFiles/ExpressionEvaluation.dir/build.make CMakeFiles/ExpressionEvaluation.dir/src/server/TcpServer.cpp.s
.PHONY : src/server/TcpServer.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... ExpressionEvaluation"
	@echo "... mainServer.o"
	@echo "... mainServer.i"
	@echo "... mainServer.s"
	@echo "... src/common/EventManager.o"
	@echo "... src/common/EventManager.i"
	@echo "... src/common/EventManager.s"
	@echo "... src/common/FileDescriptor.o"
	@echo "... src/common/FileDescriptor.i"
	@echo "... src/common/FileDescriptor.s"
	@echo "... src/common/Socket.o"
	@echo "... src/common/Socket.i"
	@echo "... src/common/Socket.s"
	@echo "... src/common/ThreadPool.o"
	@echo "... src/common/ThreadPool.i"
	@echo "... src/common/ThreadPool.s"
	@echo "... src/factory/DataFactory.o"
	@echo "... src/factory/DataFactory.i"
	@echo "... src/factory/DataFactory.s"
	@echo "... src/math/Evaluation.o"
	@echo "... src/math/Evaluation.i"
	@echo "... src/math/Evaluation.s"
	@echo "... src/math/Evaluation2.o"
	@echo "... src/math/Evaluation2.i"
	@echo "... src/math/Evaluation2.s"
	@echo "... src/math/Expression.o"
	@echo "... src/math/Expression.i"
	@echo "... src/math/Expression.s"
	@echo "... src/server/TcpServer.o"
	@echo "... src/server/TcpServer.i"
	@echo "... src/server/TcpServer.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

