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
include CMakeFiles/muduo_base.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/muduo_base.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/muduo_base.dir/flags.make

CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o: ../muduo/base/Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Thread.cpp

CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Thread.cpp > CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.i

CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Thread.cpp -o CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.s

CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o.requires

CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o.provides: CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o.provides

CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o


CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o: ../muduo/base/Exception.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Exception.cpp

CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Exception.cpp > CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.i

CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Exception.cpp -o CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.s

CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o.requires

CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o.provides: CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o.provides

CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o


CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o: ../muduo/base/Timestamp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Timestamp.cc

CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Timestamp.cc > CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.i

CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Timestamp.cc -o CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.s

CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o.requires

CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o.provides: CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o.provides

CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o


CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o: ../muduo/base/ThreadPoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/ThreadPoll.cpp

CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/ThreadPoll.cpp > CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.i

CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/ThreadPoll.cpp -o CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.s

CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o.requires

CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o.provides: CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o.provides

CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o


CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o: ../muduo/base/ProcessInfo.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/ProcessInfo.cc

CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/ProcessInfo.cc > CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.i

CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/ProcessInfo.cc -o CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.s

CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o.requires

CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o.provides: CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o.provides

CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o


CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o: ../muduo/base/FileUtil.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/FileUtil.cc

CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/FileUtil.cc > CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.i

CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/FileUtil.cc -o CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.s

CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o.requires

CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o.provides: CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o.provides

CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o


CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o: ../muduo/base/LogStream.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/LogStream.cc

CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/LogStream.cc > CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.i

CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/LogStream.cc -o CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.s

CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o.requires

CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o.provides: CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o.provides

CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o


CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o: ../muduo/base/Loggin.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Loggin.cc

CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Loggin.cc > CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.i

CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Loggin.cc -o CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.s

CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o.requires

CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o.provides: CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o.provides

CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o


CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o: ../muduo/base/TimeZone.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/TimeZone.cc

CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/TimeZone.cc > CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.i

CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/TimeZone.cc -o CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.s

CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o.requires

CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o.provides: CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o.provides

CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o


CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o: ../muduo/base/Date.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Date.cc

CMakeFiles/muduo_base.dir/muduo/base/Date.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/Date.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Date.cc > CMakeFiles/muduo_base.dir/muduo/base/Date.cc.i

CMakeFiles/muduo_base.dir/muduo/base/Date.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/Date.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/Date.cc -o CMakeFiles/muduo_base.dir/muduo/base/Date.cc.s

CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o.requires

CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o.provides: CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o.provides

CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o


CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o: CMakeFiles/muduo_base.dir/flags.make
CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o: ../muduo/base/LogFile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o -c /home/onter/project/hub/demohub/muduo/muduo/muduo/base/LogFile.cpp

CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/onter/project/hub/demohub/muduo/muduo/muduo/base/LogFile.cpp > CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.i

CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/onter/project/hub/demohub/muduo/muduo/muduo/base/LogFile.cpp -o CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.s

CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o.requires:

.PHONY : CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o.requires

CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o.provides: CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o.requires
	$(MAKE) -f CMakeFiles/muduo_base.dir/build.make CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o.provides.build
.PHONY : CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o.provides

CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o.provides.build: CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o


# Object files for target muduo_base
muduo_base_OBJECTS = \
"CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o" \
"CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o" \
"CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o" \
"CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o" \
"CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o" \
"CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o" \
"CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o" \
"CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o" \
"CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o" \
"CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o" \
"CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o"

# External object files for target muduo_base
muduo_base_EXTERNAL_OBJECTS =

libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o
libmuduo_base.a: CMakeFiles/muduo_base.dir/build.make
libmuduo_base.a: CMakeFiles/muduo_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library libmuduo_base.a"
	$(CMAKE_COMMAND) -P CMakeFiles/muduo_base.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/muduo_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/muduo_base.dir/build: libmuduo_base.a

.PHONY : CMakeFiles/muduo_base.dir/build

CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/Thread.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/Exception.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/Timestamp.cc.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/ThreadPoll.cpp.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/ProcessInfo.cc.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/FileUtil.cc.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/LogStream.cc.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/Loggin.cc.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/TimeZone.cc.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/Date.cc.o.requires
CMakeFiles/muduo_base.dir/requires: CMakeFiles/muduo_base.dir/muduo/base/LogFile.cpp.o.requires

.PHONY : CMakeFiles/muduo_base.dir/requires

CMakeFiles/muduo_base.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/muduo_base.dir/cmake_clean.cmake
.PHONY : CMakeFiles/muduo_base.dir/clean

CMakeFiles/muduo_base.dir/depend:
	cd /home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/onter/project/hub/demohub/muduo/muduo /home/onter/project/hub/demohub/muduo/muduo /home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug /home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug /home/onter/project/hub/demohub/muduo/muduo/cmake-build-debug/CMakeFiles/muduo_base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/muduo_base.dir/depend
