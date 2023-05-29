file(GLOB COMMON_SOURCE_FILES *.cpp)

if (MSVC)
    add_library(common ${COMMON_SOURCE_FILES})
else()
    add_library(common SHARED ${COMMON_SOURCE_FILES})
endif()