find_package(Boost 1.67.0 REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(StatiX
    main.cpp

    Common/General.h
    Common/Pool.h
    Common/Pool.inl
    Common/Queue.h
    Common/Queue.inl

    Files/General.h
    Files/Cache.h
    Files/Cache.cpp
    Files/FilesPool.h
    Files/FilesPool.cpp

    Network/General.h
    Network/Session.h
    Network/Session.cpp
    Network/Parser.h
    Network/Parser.cpp
    Network/NetPool.h
    Network/NetPool.cpp

    Server/Server.h
    Server/Server.cpp
)

target_link_libraries(StatiX stdc++fs -pthread ${Boost_LIBRARIES})
