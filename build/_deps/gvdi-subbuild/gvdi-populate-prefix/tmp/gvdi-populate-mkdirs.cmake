# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/arvk/Code/cpp/Pixie/build/_deps/gvdi-src"
  "/home/arvk/Code/cpp/Pixie/build/_deps/gvdi-build"
  "/home/arvk/Code/cpp/Pixie/build/_deps/gvdi-subbuild/gvdi-populate-prefix"
  "/home/arvk/Code/cpp/Pixie/build/_deps/gvdi-subbuild/gvdi-populate-prefix/tmp"
  "/home/arvk/Code/cpp/Pixie/build/_deps/gvdi-subbuild/gvdi-populate-prefix/src/gvdi-populate-stamp"
  "/home/arvk/Code/cpp/Pixie/build/_deps/gvdi-subbuild/gvdi-populate-prefix/src"
  "/home/arvk/Code/cpp/Pixie/build/_deps/gvdi-subbuild/gvdi-populate-prefix/src/gvdi-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/arvk/Code/cpp/Pixie/build/_deps/gvdi-subbuild/gvdi-populate-prefix/src/gvdi-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/arvk/Code/cpp/Pixie/build/_deps/gvdi-subbuild/gvdi-populate-prefix/src/gvdi-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
