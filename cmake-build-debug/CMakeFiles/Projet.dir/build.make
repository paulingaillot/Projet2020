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
CMAKE_SOURCE_DIR = "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Projet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Projet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Projet.dir/flags.make

CMakeFiles/Projet.dir/main.c.o: CMakeFiles/Projet.dir/flags.make
CMakeFiles/Projet.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Projet.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Projet.dir/main.c.o   -c "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/main.c"

CMakeFiles/Projet.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Projet.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/main.c" > CMakeFiles/Projet.dir/main.c.i

CMakeFiles/Projet.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Projet.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/main.c" -o CMakeFiles/Projet.dir/main.c.s

CMakeFiles/Projet.dir/UART.c.o: CMakeFiles/Projet.dir/flags.make
CMakeFiles/Projet.dir/UART.c.o: ../UART.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Projet.dir/UART.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Projet.dir/UART.c.o   -c "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/UART.c"

CMakeFiles/Projet.dir/UART.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Projet.dir/UART.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/UART.c" > CMakeFiles/Projet.dir/UART.c.i

CMakeFiles/Projet.dir/UART.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Projet.dir/UART.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/UART.c" -o CMakeFiles/Projet.dir/UART.c.s

CMakeFiles/Projet.dir/seven-seg.c.o: CMakeFiles/Projet.dir/flags.make
CMakeFiles/Projet.dir/seven-seg.c.o: ../seven-seg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Projet.dir/seven-seg.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Projet.dir/seven-seg.c.o   -c "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/seven-seg.c"

CMakeFiles/Projet.dir/seven-seg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Projet.dir/seven-seg.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/seven-seg.c" > CMakeFiles/Projet.dir/seven-seg.c.i

CMakeFiles/Projet.dir/seven-seg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Projet.dir/seven-seg.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/seven-seg.c" -o CMakeFiles/Projet.dir/seven-seg.c.s

# Object files for target Projet
Projet_OBJECTS = \
"CMakeFiles/Projet.dir/main.c.o" \
"CMakeFiles/Projet.dir/UART.c.o" \
"CMakeFiles/Projet.dir/seven-seg.c.o"

# External object files for target Projet
Projet_EXTERNAL_OBJECTS =

Projet: CMakeFiles/Projet.dir/main.c.o
Projet: CMakeFiles/Projet.dir/UART.c.o
Projet: CMakeFiles/Projet.dir/seven-seg.c.o
Projet: CMakeFiles/Projet.dir/build.make
Projet: CMakeFiles/Projet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable Projet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Projet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Projet.dir/build: Projet

.PHONY : CMakeFiles/Projet.dir/build

CMakeFiles/Projet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Projet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Projet.dir/clean

CMakeFiles/Projet.dir/depend:
	cd "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet" "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet" "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/cmake-build-debug" "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/cmake-build-debug" "/mnt/c/Users/Pauli/OneDrive - yncréa/dossier paulin/ISEN/Année 1/Algo/TPs/Projet/cmake-build-debug/CMakeFiles/Projet.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Projet.dir/depend

