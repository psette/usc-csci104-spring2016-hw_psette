######################################################################
# Automatically generated by qmake (2.01a) Tue Mar 22 01:18:23 2016
######################################################################
CONFIG += debug               # enables debugging (like the -g flag)
TARGET = debugger               # sets output executable name to debugger
QMAKE_CXXFLAGS += -std=c++11  # enable C++11 libraries
SOURCES -= msort_test.cpp   # Don't compile certain test files
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += debugger.h load_window.h values_window.h ../lib/Facile.h ../lib/ProgramState.h ../lib/stackint.h ../lib/llistint.h ../lib/LetStatement.h ../lib/PrALLStatement.h ../lib/PrintStatement.h ../lib/AddStatement.h ../lib/MultStatement.h ../lib/DivStatement.h ../lib/SubtStatement.h ../lib/GotoStatement.h ../lib/IfStatement.h ../lib/EndStatement.h ../lib/RetrStatement.h ../lib/GosubStatement.h ../lib/vec_filler.h

SOURCES += debugger.cpp load_window.cpp values_window.cpp main.cpp ../src/Facile.cpp ../src/ProgramState.cpp ../src/stackint.cpp ../src/llistint.cpp ../src/LetStatement.cpp ../src/PrALLStatement.cpp ../src/PrintStatement.cpp ../src/AddStatement.cpp ../src/MultStatement.cpp ../src/DivStatement.cpp ../src/SubtStatement.cpp ../src/GotoStatement.cpp ../src/IfStatement.cpp ../src/EndStatement.cpp ../src/RetrStatement.cpp ../src/GosubStatement.cpp ../src/vec_filler.cpp