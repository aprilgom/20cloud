# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hs/20cloud/skip

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hs/20cloud/skip

# Include any dependencies generated for this target.
include CMakeFiles/test.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.out.dir/flags.make

CMakeFiles/test.out.dir/test_ref.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/test_ref.o: test_ref.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hs/20cloud/skip/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test.out.dir/test_ref.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test.out.dir/test_ref.o   -c /home/hs/20cloud/skip/test_ref.c

CMakeFiles/test.out.dir/test_ref.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.out.dir/test_ref.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hs/20cloud/skip/test_ref.c > CMakeFiles/test.out.dir/test_ref.i

CMakeFiles/test.out.dir/test_ref.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.out.dir/test_ref.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hs/20cloud/skip/test_ref.c -o CMakeFiles/test.out.dir/test_ref.s

CMakeFiles/test.out.dir/test_ref.o.requires:

.PHONY : CMakeFiles/test.out.dir/test_ref.o.requires

CMakeFiles/test.out.dir/test_ref.o.provides: CMakeFiles/test.out.dir/test_ref.o.requires
	$(MAKE) -f CMakeFiles/test.out.dir/build.make CMakeFiles/test.out.dir/test_ref.o.provides.build
.PHONY : CMakeFiles/test.out.dir/test_ref.o.provides

CMakeFiles/test.out.dir/test_ref.o.provides.build: CMakeFiles/test.out.dir/test_ref.o


CMakeFiles/test.out.dir/kvsh.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/kvsh.o: kvsh.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hs/20cloud/skip/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/test.out.dir/kvsh.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test.out.dir/kvsh.o   -c /home/hs/20cloud/skip/kvsh.c

CMakeFiles/test.out.dir/kvsh.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.out.dir/kvsh.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hs/20cloud/skip/kvsh.c > CMakeFiles/test.out.dir/kvsh.i

CMakeFiles/test.out.dir/kvsh.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.out.dir/kvsh.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hs/20cloud/skip/kvsh.c -o CMakeFiles/test.out.dir/kvsh.s

CMakeFiles/test.out.dir/kvsh.o.requires:

.PHONY : CMakeFiles/test.out.dir/kvsh.o.requires

CMakeFiles/test.out.dir/kvsh.o.provides: CMakeFiles/test.out.dir/kvsh.o.requires
	$(MAKE) -f CMakeFiles/test.out.dir/build.make CMakeFiles/test.out.dir/kvsh.o.provides.build
.PHONY : CMakeFiles/test.out.dir/kvsh.o.provides

CMakeFiles/test.out.dir/kvsh.o.provides.build: CMakeFiles/test.out.dir/kvsh.o


CMakeFiles/test.out.dir/sl_list.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/sl_list.o: sl_list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hs/20cloud/skip/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/test.out.dir/sl_list.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test.out.dir/sl_list.o   -c /home/hs/20cloud/skip/sl_list.c

CMakeFiles/test.out.dir/sl_list.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test.out.dir/sl_list.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hs/20cloud/skip/sl_list.c > CMakeFiles/test.out.dir/sl_list.i

CMakeFiles/test.out.dir/sl_list.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test.out.dir/sl_list.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hs/20cloud/skip/sl_list.c -o CMakeFiles/test.out.dir/sl_list.s

CMakeFiles/test.out.dir/sl_list.o.requires:

.PHONY : CMakeFiles/test.out.dir/sl_list.o.requires

CMakeFiles/test.out.dir/sl_list.o.provides: CMakeFiles/test.out.dir/sl_list.o.requires
	$(MAKE) -f CMakeFiles/test.out.dir/build.make CMakeFiles/test.out.dir/sl_list.o.provides.build
.PHONY : CMakeFiles/test.out.dir/sl_list.o.provides

CMakeFiles/test.out.dir/sl_list.o.provides.build: CMakeFiles/test.out.dir/sl_list.o


# Object files for target test.out
test_out_OBJECTS = \
"CMakeFiles/test.out.dir/test_ref.o" \
"CMakeFiles/test.out.dir/kvsh.o" \
"CMakeFiles/test.out.dir/sl_list.o"

# External object files for target test.out
test_out_EXTERNAL_OBJECTS =

test.out: CMakeFiles/test.out.dir/test_ref.o
test.out: CMakeFiles/test.out.dir/kvsh.o
test.out: CMakeFiles/test.out.dir/sl_list.o
test.out: CMakeFiles/test.out.dir/build.make
test.out: CMakeFiles/test.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hs/20cloud/skip/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable test.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.out.dir/build: test.out

.PHONY : CMakeFiles/test.out.dir/build

CMakeFiles/test.out.dir/requires: CMakeFiles/test.out.dir/test_ref.o.requires
CMakeFiles/test.out.dir/requires: CMakeFiles/test.out.dir/kvsh.o.requires
CMakeFiles/test.out.dir/requires: CMakeFiles/test.out.dir/sl_list.o.requires

.PHONY : CMakeFiles/test.out.dir/requires

CMakeFiles/test.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.out.dir/clean

CMakeFiles/test.out.dir/depend:
	cd /home/hs/20cloud/skip && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hs/20cloud/skip /home/hs/20cloud/skip /home/hs/20cloud/skip /home/hs/20cloud/skip /home/hs/20cloud/skip/CMakeFiles/test.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.out.dir/depend

