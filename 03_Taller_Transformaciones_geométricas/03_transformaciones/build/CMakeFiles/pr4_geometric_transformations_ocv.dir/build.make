# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity/build"

# Include any dependencies generated for this target.
include CMakeFiles/pr4_geometric_transformations_ocv.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pr4_geometric_transformations_ocv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pr4_geometric_transformations_ocv.dir/flags.make

CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.o: CMakeFiles/pr4_geometric_transformations_ocv.dir/flags.make
CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.o: ../04_geometric_transformations_ocv.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.o -c "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity/04_geometric_transformations_ocv.cxx"

CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity/04_geometric_transformations_ocv.cxx" > CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.i

CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity/04_geometric_transformations_ocv.cxx" -o CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.s

# Object files for target pr4_geometric_transformations_ocv
pr4_geometric_transformations_ocv_OBJECTS = \
"CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.o"

# External object files for target pr4_geometric_transformations_ocv
pr4_geometric_transformations_ocv_EXTERNAL_OBJECTS =

pr4_geometric_transformations_ocv: CMakeFiles/pr4_geometric_transformations_ocv.dir/04_geometric_transformations_ocv.cxx.o
pr4_geometric_transformations_ocv: CMakeFiles/pr4_geometric_transformations_ocv.dir/build.make
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_gapi.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_highgui.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_ml.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_objdetect.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_photo.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_stitching.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_video.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_videoio.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_dnn.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_imgcodecs.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_calib3d.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_features2d.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_flann.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_imgproc.4.5.1.dylib
pr4_geometric_transformations_ocv: /usr/local/lib/libopencv_core.4.5.1.dylib
pr4_geometric_transformations_ocv: CMakeFiles/pr4_geometric_transformations_ocv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pr4_geometric_transformations_ocv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pr4_geometric_transformations_ocv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pr4_geometric_transformations_ocv.dir/build: pr4_geometric_transformations_ocv

.PHONY : CMakeFiles/pr4_geometric_transformations_ocv.dir/build

CMakeFiles/pr4_geometric_transformations_ocv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pr4_geometric_transformations_ocv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pr4_geometric_transformations_ocv.dir/clean

CMakeFiles/pr4_geometric_transformations_ocv.dir/depend:
	cd "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity" "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity" "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity/build" "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity/build" "/Users/juanfelipemarinflorez/Desktop/Pontificia Universidad Javeriana/Semestres/Noveno/visión/Talleres/03_Taller_Transformaciones_geométricas/03_rescale_intensity/build/CMakeFiles/pr4_geometric_transformations_ocv.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/pr4_geometric_transformations_ocv.dir/depend

