cmake_minimum_required(VERSION 3.9)
project(course_work)

set(CMAKE_CXX_STANDARD 11)

add_executable(course_work main.cpp Command.cpp Command.h Parser.cpp Parser.h Shell.cpp Shell.h Parser.cpp Parser.h Table.cpp Table.h Row.cpp Row.h CustomType.h DBMS.cpp DBMS.h Error.cpp Error.h TypeError.cpp TypeError.h DBMSError.cpp DBMSError.h)
#add_executable(test test/test.cpp Command.cpp Command.h Parser.cpp Parser.h Shell.cpp Shell.h Parser.cpp Parser.h Table.cpp Table.h Row.cpp Row.h CustomType.h DBMS.cpp DBMS.h Error.cpp Error.h TypeError.cpp TypeError.h DBMSError.cpp DBMSError.h)