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
CMAKE_SOURCE_DIR = "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones/build"

# Include any dependencies generated for this target.
include CMakeFiles/Transformation_ocv.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Transformation_ocv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Transformation_ocv.dir/flags.make

CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.o: CMakeFiles/Transformation_ocv.dir/flags.make
CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.o: ../04_Transformation_ocv.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.o -c "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones/04_Transformation_ocv.cxx"

CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones/04_Transformation_ocv.cxx" > CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.i

CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones/04_Transformation_ocv.cxx" -o CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.s

# Object files for target Transformation_ocv
Transformation_ocv_OBJECTS = \
"CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.o"

# External object files for target Transformation_ocv
Transformation_ocv_EXTERNAL_OBJECTS =

Transformation_ocv: CMakeFiles/Transformation_ocv.dir/04_Transformation_ocv.cxx.o
Transformation_ocv: CMakeFiles/Transformation_ocv.dir/build.make
Transformation_ocv: /usr/local/lib/libopencv_gapi.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_highgui.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_ml.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_objdetect.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_photo.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_stitching.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_video.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_videoio.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_dnn.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_imgcodecs.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_calib3d.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_features2d.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_flann.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_imgproc.4.5.1.dylib
Transformation_ocv: /usr/local/lib/libopencv_core.4.5.1.dylib
Transformation_ocv: CMakeFiles/Transformation_ocv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Transformation_ocv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Transformation_ocv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Transformation_ocv.dir/build: Transformation_ocv

.PHONY : CMakeFiles/Transformation_ocv.dir/build

CMakeFiles/Transformation_ocv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Transformation_ocv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Transformation_ocv.dir/clean

CMakeFiles/Transformation_ocv.dir/depend:
	cd "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones" "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones" "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones/build" "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones/build" "/Users/paulavalentinasanchezpena/Desktop/OneDrive - Pontificia Universidad Javeriana/Semestres/9/Visión/visionArtificial/Talleres/03_Taller_Transformaciones_geométricas/03_transformaciones/build/CMakeFiles/Transformation_ocv.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Transformation_ocv.dir/depend

