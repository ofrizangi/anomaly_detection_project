<<<<<<< HEAD
﻿# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.22
=======
# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20
>>>>>>> origin/main

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

<<<<<<< HEAD
=======
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

>>>>>>> origin/main
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

<<<<<<< HEAD
!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f
=======
# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/ofrizangi/Download/cmake-3.20.6-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/ofrizangi/Download/cmake-3.20.6-linux-x86_64/bin/cmake -E rm -f
>>>>>>> origin/main

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
<<<<<<< HEAD
CMAKE_SOURCE_DIR = C:\Users\LENOVO\CLionProjects\project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\LENOVO\CLionProjects\project\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\ex1.dir\depend.make
# Include the progress variables for this target.
include CMakeFiles\ex1.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\ex1.dir\flags.make

CMakeFiles\ex1.dir\anomaly_detection_util.cpp.obj: CMakeFiles\ex1.dir\flags.make
CMakeFiles\ex1.dir\anomaly_detection_util.cpp.obj: ..\anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\LENOVO\CLionProjects\project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex1.dir/anomaly_detection_util.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ex1.dir\anomaly_detection_util.cpp.obj /FdCMakeFiles\ex1.dir\ /FS -c C:\Users\LENOVO\CLionProjects\project\anomaly_detection_util.cpp
<<

CMakeFiles\ex1.dir\anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/anomaly_detection_util.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe > CMakeFiles\ex1.dir\anomaly_detection_util.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\LENOVO\CLionProjects\project\anomaly_detection_util.cpp
<<

CMakeFiles\ex1.dir\anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/anomaly_detection_util.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ex1.dir\anomaly_detection_util.cpp.s /c C:\Users\LENOVO\CLionProjects\project\anomaly_detection_util.cpp
<<

# Object files for target ex1
ex1_OBJECTS = \
"CMakeFiles\ex1.dir\anomaly_detection_util.cpp.obj"
=======
CMAKE_SOURCE_DIR = /mnt/c/Users/Ofri/CLionProjects/ex1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Ofri/CLionProjects/ex1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex1.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/ex1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex1.dir/flags.make

CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o: ../anomaly_detection_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ofri/CLionProjects/ex1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o -c /mnt/c/Users/Ofri/CLionProjects/ex1/anomaly_detection_util.cpp

CMakeFiles/ex1.dir/anomaly_detection_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/anomaly_detection_util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Ofri/CLionProjects/ex1/anomaly_detection_util.cpp > CMakeFiles/ex1.dir/anomaly_detection_util.cpp.i

CMakeFiles/ex1.dir/anomaly_detection_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/anomaly_detection_util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Ofri/CLionProjects/ex1/anomaly_detection_util.cpp -o CMakeFiles/ex1.dir/anomaly_detection_util.cpp.s

CMakeFiles/ex1.dir/MainTrain.cpp.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/MainTrain.cpp.o: ../MainTrain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ofri/CLionProjects/ex1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ex1.dir/MainTrain.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex1.dir/MainTrain.cpp.o -c /mnt/c/Users/Ofri/CLionProjects/ex1/MainTrain.cpp

CMakeFiles/ex1.dir/MainTrain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex1.dir/MainTrain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Ofri/CLionProjects/ex1/MainTrain.cpp > CMakeFiles/ex1.dir/MainTrain.cpp.i

CMakeFiles/ex1.dir/MainTrain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex1.dir/MainTrain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Ofri/CLionProjects/ex1/MainTrain.cpp -o CMakeFiles/ex1.dir/MainTrain.cpp.s

# Object files for target ex1
ex1_OBJECTS = \
"CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o" \
"CMakeFiles/ex1.dir/MainTrain.cpp.o"
>>>>>>> origin/main

# External object files for target ex1
ex1_EXTERNAL_OBJECTS =

<<<<<<< HEAD
ex1.exe: CMakeFiles\ex1.dir\anomaly_detection_util.cpp.obj
ex1.exe: CMakeFiles\ex1.dir\build.make
ex1.exe: CMakeFiles\ex1.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\LENOVO\CLionProjects\project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ex1.exe"
	"C:\Program Files\CMake\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\ex1.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\ex1.dir\objects1.rsp @<<
 /out:ex1.exe /implib:ex1.lib /pdb:C:\Users\LENOVO\CLionProjects\project\cmake-build-debug\ex1.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\ex1.dir\build: ex1.exe
.PHONY : CMakeFiles\ex1.dir\build

CMakeFiles\ex1.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ex1.dir\cmake_clean.cmake
.PHONY : CMakeFiles\ex1.dir\clean

CMakeFiles\ex1.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\LENOVO\CLionProjects\project C:\Users\LENOVO\CLionProjects\project C:\Users\LENOVO\CLionProjects\project\cmake-build-debug C:\Users\LENOVO\CLionProjects\project\cmake-build-debug C:\Users\LENOVO\CLionProjects\project\cmake-build-debug\CMakeFiles\ex1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\ex1.dir\depend
=======
ex1: CMakeFiles/ex1.dir/anomaly_detection_util.cpp.o
ex1: CMakeFiles/ex1.dir/MainTrain.cpp.o
ex1: CMakeFiles/ex1.dir/build.make
ex1: CMakeFiles/ex1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Ofri/CLionProjects/ex1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ex1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex1.dir/build: ex1
.PHONY : CMakeFiles/ex1.dir/build

CMakeFiles/ex1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex1.dir/clean

CMakeFiles/ex1.dir/depend:
	cd /mnt/c/Users/Ofri/CLionProjects/ex1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Ofri/CLionProjects/ex1 /mnt/c/Users/Ofri/CLionProjects/ex1 /mnt/c/Users/Ofri/CLionProjects/ex1/cmake-build-debug /mnt/c/Users/Ofri/CLionProjects/ex1/cmake-build-debug /mnt/c/Users/Ofri/CLionProjects/ex1/cmake-build-debug/CMakeFiles/ex1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex1.dir/depend
>>>>>>> origin/main

