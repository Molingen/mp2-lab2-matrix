set(target "gtest")

if(MSVC)
    add_compile_definitions(_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
    add_compile_options(/W0)
endif()

add_library(${target} STATIC gtest-all.cc)

if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(pthread "-pthread")
endif()

target_link_libraries(${target} ${pthread})
