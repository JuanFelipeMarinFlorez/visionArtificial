
cmake_minimum_required(VERSION 2.8)

project(TextureImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(TextFeaturesWindow textureFeaturesWindow.cxx)
target_link_libraries(TextFeaturesWindow ${ITK_LIBRARIES})

add_executable(TextFeaturesImage textureFeaturesImage.cxx)
target_link_libraries(TextFeaturesImage ${ITK_LIBRARIES})
