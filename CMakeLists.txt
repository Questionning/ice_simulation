cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(MuonIron)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Automatically gather all source files
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(muon_iron main.cc ${sources} ${headers})
target_link_libraries(muon_iron ${Geant4_LIBRARIES})
