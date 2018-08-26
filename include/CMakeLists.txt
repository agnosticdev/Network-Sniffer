include_directories(${NetworkSniffer_SOURCE_DIR}/include)
link_directories(${NetworkSniffer_BINARY_DIR}/include)

#set(CORELIBS ${netinet_LIBRARY} m)
set(CORELIBS ${netinet_LIBRARY} m)

# Building just a library. 
add_library(NetworkSnifferManager NetworkSnifferManager.cpp)

add_executable(NetworkSniffer NetworkSniffer.cpp)

# Linking against a custom library
target_link_libraries(NetworkSniffer ${CORELIBS} NetworkSnifferManager)