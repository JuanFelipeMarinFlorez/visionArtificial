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
CMAKE_SOURCE_DIR = /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia/build

# Include any dependencies generated for this target.
include CMakeFiles/08_Morfologia.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/08_Morfologia.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/08_Morfologia.dir/flags.make

CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o: CMakeFiles/08_Morfologia.dir/flags.make
CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o: ../08_Morfologia.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o -c /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia/08_Morfologia.cxx

CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia/08_Morfologia.cxx > CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.i

CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia/08_Morfologia.cxx -o CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.s

CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o.requires:

.PHONY : CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o.requires

CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o.provides: CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o.requires
	$(MAKE) -f CMakeFiles/08_Morfologia.dir/build.make CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o.provides.build
.PHONY : CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o.provides

CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o.provides.build: CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o


# Object files for target 08_Morfologia
08_Morfologia_OBJECTS = \
"CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o"

# External object files for target 08_Morfologia
08_Morfologia_EXTERNAL_OBJECTS =

08_Morfologia: CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o
08_Morfologia: CMakeFiles/08_Morfologia.dir/build.make
08_Morfologia: /usr/local/lib/libopencv_gapi.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_highgui.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_ml.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_objdetect.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_photo.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_stitching.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_video.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_videoio.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_dnn.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_imgcodecs.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_calib3d.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_features2d.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_flann.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_imgproc.so.4.5.1
08_Morfologia: /usr/local/lib/libopencv_core.so.4.5.1
08_Morfologia: CMakeFiles/08_Morfologia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 08_Morfologia"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/08_Morfologia.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/08_Morfologia.dir/build: 08_Morfologia

.PHONY : CMakeFiles/08_Morfologia.dir/build

CMakeFiles/08_Morfologia.dir/requires: CMakeFiles/08_Morfologia.dir/08_Morfologia.cxx.o.requires

.PHONY : CMakeFiles/08_Morfologia.dir/requires

CMakeFiles/08_Morfologia.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/08_Morfologia.dir/cmake_clean.cmake
.PHONY : CMakeFiles/08_Morfologia.dir/clean

CMakeFiles/08_Morfologia.dir/depend:
	cd /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia/build /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia/build /home/marlon_linares16/Documentos/VA/Repository/visionArtificial/Talleres/08_Morfologia/build/CMakeFiles/08_Morfologia.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/08_Morfologia.dir/depend
