cmake_minimum_required(VERSION 3.27)
project(TPSPRING2024_MODULE3_TASK1)

set(CMAKE_CXX_STANDARD 17)

add_executable(TPSPRING2024_MODULE3_TASK1 main.cpp
        ArcGraph.h
        IGraph.h
        ListGraph.h
        MatrixGraph.h
        SetGraph.h
        "IGraph .cpp"
        ListGraph.cpp
        MatrixGraph.cpp
        SetGraph.cpp
        ArcGraph.cpp)
