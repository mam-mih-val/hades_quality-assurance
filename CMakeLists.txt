cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(quality_assurance)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
list(APPEND CMAKE_PREFIX_PATH $ENV{AnalysisTree_HOME})
list(APPEND CMAKE_PREFIX_PATH $ENV{AnalysisTreeQA_HOME})
list(APPEND CMAKE_PREFIX_PATH ${AnalysisTree_HOME})
list(APPEND CMAKE_PREFIX_PATH ${AnalysisTreeQA_HOME})

find_package(ROOT REQUIRED COMPONENTS RIO Tree)
find_package(AnalysisTree REQUIRED)
find_package(AnalysisTreeQA REQUIRED)
add_definitions(-DUSEBOOST)

set(CMAKE_CXX_FLAGS "-Wall")

include(${ROOT_USE_FILE})

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${ROOT_INCLUDE_DIRS}
        ${AnalysisTree_INCLUDE_DIR}
        ${AnalysisTreeQA_INCLUDE_DIR}
)

link_directories(
        $ENV{HADDIR}/lib
        ${CMAKE_SOURCE_DIR}
        ${AnalysisTree_LIBRARY_DIR}
        ${AnalysisTreeQA_LIBRARY_DIR}
)

set(HEADERS
        src/mdc_vertex_tracks.h
)
set(SOURCES
        src/mdc_vertex_tracks.cc

)
add_definitions(${ROOT_CXX_FLAGS})

add_executable(run_qa src/quality_assurance.cc ${HEADERS} ${SOURCES})
target_link_libraries(run_qa ${ROOT_LIBRARIES} AnalysisTreeBase AnalysisTreeQA)