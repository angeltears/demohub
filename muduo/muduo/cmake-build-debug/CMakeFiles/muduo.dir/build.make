# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/onter/software/clion-2017.3.4/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/onter/software/clion-2017.3.4/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/onter/project/hub/demohub/muduo/muduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/muduo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/muduo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/muduo.dir/flags.make

CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o: CMakeFiles/muduo.dir/flags.make
CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o: ../muduo/base/Timestamp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Timestamp.cc

CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Timestamp.cc > CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.i

CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Timestamp.cc -o CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.s

CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o.requires:

.PHONY : CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o.requires

CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o.provides: CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o.requires
	$(MAKE) -f CMakeFiles/muduo.dir/build.make CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o.provides.build
.PHONY : CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o.provides

CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o.provides.build: CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o


CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o: CMakeFiles/muduo.dir/flags.make
CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o: ../muduo/test/base/Atomic_unittest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/test/base/Atomic_unittest.cpp

CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/test/base/Atomic_unittest.cpp > CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.i

CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/test/base/Atomic_unittest.cpp -o CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.s

CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o.requires:

.PHONY : CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o.requires

CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o.provides: CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo.dir/build.make CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o.provides.build
.PHONY : CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o.provides

CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o.provides.build: CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o


# Object files for target muduo
muduo_OBJECTS = \
"CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o" \
"CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o"

# External object files for target muduo
muduo_EXTERNAL_OBJECTS =

muduo: CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o
muduo: CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o
muduo: CMakeFiles/muduo.dir/build.make
muduo: CMakeFiles/muduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable muduo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/muduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/muduo.dir/build: muduo

.PHONY : CMakeFiles/muduo.dir/build

CMakeFiles/muduo.dir/requires: CMakeFiles/muduo.dir/muduo/base/Timestamp.cc.o.requires
CMakeFiles/muduo.dir/requires: CMakeFiles/muduo.dir/muduo/test/base/Atomic_unittest.cpp.o.requires

.PHONY : CMakeFiles/muduo.dir/requires

CMakeFiles/muduo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/muduo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/muduo.dir/clean

CMakeFiles/muduo.dir/depend:
	cd /home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/onter/project/hub/demohub/muduo/muduo /home/onter/project/hub/demohub/muduo/muduo /home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug /home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug /home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles/muduo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/muduo.dir/depend
