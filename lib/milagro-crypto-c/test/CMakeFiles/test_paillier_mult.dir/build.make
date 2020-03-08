# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c

# Include any dependencies generated for this target.
include test/CMakeFiles/test_paillier_mult.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_paillier_mult.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_paillier_mult.dir/flags.make

test/CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.o: test/CMakeFiles/test_paillier_mult.dir/flags.make
test/CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.o: test/test_paillier_mult.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object test/CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.o"
	cd /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.o   -c /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test/test_paillier_mult.c

test/CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.i"
	cd /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test/test_paillier_mult.c > CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.i

test/CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.s"
	cd /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test/test_paillier_mult.c -o CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.s

# Object files for target test_paillier_mult
test_paillier_mult_OBJECTS = \
"CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.o"

# External object files for target test_paillier_mult
test_paillier_mult_EXTERNAL_OBJECTS =

bin/test_paillier_mult: test/CMakeFiles/test_paillier_mult.dir/test_paillier_mult.c.o
bin/test_paillier_mult: test/CMakeFiles/test_paillier_mult.dir/build.make
bin/test_paillier_mult: lib/libamcl_core.a
bin/test_paillier_mult: lib/libamcl_paillier.a
bin/test_paillier_mult: lib/libamcl_core.a
bin/test_paillier_mult: test/CMakeFiles/test_paillier_mult.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/test_paillier_mult"
	cd /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_paillier_mult.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_paillier_mult.dir/build: bin/test_paillier_mult

.PHONY : test/CMakeFiles/test_paillier_mult.dir/build

test/CMakeFiles/test_paillier_mult.dir/clean:
	cd /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test && $(CMAKE_COMMAND) -P CMakeFiles/test_paillier_mult.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_paillier_mult.dir/clean

test/CMakeFiles/test_paillier_mult.dir/depend:
	cd /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test /home/jrml/devel/lua-multiparty/lib/milagro-crypto-c/test/CMakeFiles/test_paillier_mult.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_paillier_mult.dir/depend

