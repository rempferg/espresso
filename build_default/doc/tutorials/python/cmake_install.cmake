# Install script for directory: /Users/bindgens2/Documents/espresso_dev/espresso/doc/tutorials/python

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/bindgens2/Documents/espresso_dev/espresso/build_default/doc/tutorials/python/00-building_espresso/cmake_install.cmake")
  include("/Users/bindgens2/Documents/espresso_dev/espresso/build_default/doc/tutorials/python/01-lennard_jones/cmake_install.cmake")
  include("/Users/bindgens2/Documents/espresso_dev/espresso/build_default/doc/tutorials/python/02-charged_system/cmake_install.cmake")
  include("/Users/bindgens2/Documents/espresso_dev/espresso/build_default/doc/tutorials/python/04-lattice_boltzmann/cmake_install.cmake")
  include("/Users/bindgens2/Documents/espresso_dev/espresso/build_default/doc/tutorials/python/05-raspberry_electrophoresis/cmake_install.cmake")
  include("/Users/bindgens2/Documents/espresso_dev/espresso/build_default/doc/tutorials/python/07-electrokinetics/cmake_install.cmake")
  include("/Users/bindgens2/Documents/espresso_dev/espresso/build_default/doc/tutorials/python/08-visualization/cmake_install.cmake")

endif()

