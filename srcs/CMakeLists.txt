#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.12...3.20)
project(TBMC)
#add_definitions(-DGEANT4_USE_GDML)
add_compile_definitions(GEANT4_USE_GDML)
#make using gdml the default
OPTION( GEANT4_USE_GDML "Use gdml Option" ON)
# printout the value of GEANT4_USE_GDML
MESSAGE("?GEANT4_USE_GDML " ${GEANT4_USE_GDML})
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#---------------------------------------------------------------------------- 
#Load the FindROOT.cmake file and this file can be downloaded from http://root.cern.ch/drupal/sites/default/files/event.tgz 
#
include(FindROOT.cmake)
#Tell cmake where to pick root-classes up
set(ROOT_header $ENV{ROOTSYS}/include/)
include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_header})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_header})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB detectors ${PROJECT_SOURCE_DIR}/gdml/*.gdml)
file(GLOB macros ${PROJECT_SOURCE_DIR}/*.mac)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(TBMC TBMC.cc ${sources} ${headers})
target_link_libraries(TBMC ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build TBMC. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(TBMC_SCRIPTS
    vis.mac)

foreach(_script ${TBMC_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY )
endforeach()

# Copy the gdml directory to the build directory so that geometry files
# are available alongside the executable.
file(COPY ${PROJECT_SOURCE_DIR}/gdml DESTINATION ${PROJECT_BINARY_DIR})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS TBMC DESTINATION bin)
install(FILES ${detectors} ${macros} DESTINATION bin)
