cmake_minimum_required(VERSION 3.9)
project(course_work_test)

set(CMAKE_CXX_STANDARD 11)

add_executable(test test.cpp Command.cpp Command.h Parser.cpp Parser.h Shell.cpp Shell.h Parser.cpp Parser.h Table.cpp Table.h Row.cpp Row.h CustomType.h DBMS.cpp DBMS.h Error.cpp Error.h TypeError.cpp TypeError.h DBMSError.cpp DBMSError.h)
