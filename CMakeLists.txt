cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(quality_assurance)
find_package(ROOT REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(AnalysisTree REQUIRED)
find_package(AnalysisTreeQA REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall")

add_executable(run_qa src/quality_assurance.cc src/branches_qa.cc)
target_link_libraries(run_qa ${Boost_LIBRARIES}  ${ROOT_LIBRARIES} AnalysisTreeBase AnalysisTreeInfra AnalysisTreeQA)