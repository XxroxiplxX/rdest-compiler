
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/analyzer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/parsery.cpp
    COMMAND flex -o ${CMAKE_CURRENT_SOURCE_DIR}/analyzer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l
    COMMAND bison -d -o ${CMAKE_CURRENT_SOURCE_DIR}/parsery.cpp ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    COMMENT "Generating lexer and parser"
)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(compiler_rt ${SOURCES})

target_link_libraries(compiler_rt PRIVATE 
    compilerAssemblerLib
    compilerAstLib
    compilerMemoryLib
    compilerUtilsLib
    )