cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(quality_assurance)
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(ROOT REQUIRED)
find_package(AnalysisTree REQUIRED)
find_package(AnalysisTreeQA REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall")

include(${ROOT_USE_FILE})

include_directories(
#        ${CMAKE_SOURCE_DIR}
#        ${CMAKE_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIRS}
        ${ROOT_INCLUDE_DIRS}
        ${AnalysisTree_INCLUDE_DIR}
        ${AnalysisTreeQA_INCLUDE_DIR}
)

link_directories(
        ${CMAKE_SOURCE_DIR}
        ${AnalysisTree_LIBRARY_DIR}
        ${AnalysisTreeQA_LIBRARY_DIR}
)

add_definitions(${ROOT_CXX_FLAGS})

add_executable(run_qa src/quality_assurance.cc src/branches_qa.cc)
target_link_libraries(run_qa ${Boost_LIBRARIES}  ${ROOT_LIBRARIES} AnalysisTreeBase AnalysisTreeInfra AnalysisTreeQA)
#
#add_executable(make_grid src/pT_rapidity_grid.cc )
#target_link_libraries(make_grid ${ROOT_LIBRARIES})