set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.cpp)
if(FALSE)
# Dodaj wywołanie Flex i Bison przed kompilacją
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/analyzer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/parsery.cpp
    COMMAND flex -o ${CMAKE_CURRENT_SOURCE_DIR}/analyzer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l
    COMMAND bison -d -o ${CMAKE_CURRENT_SOURCE_DIR}/parsery.cpp ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    COMMENT "Generating lexer and parser"
)

set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/analyzer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/parsery.cpp)
else()
set(SOURCES ${SOURCES})
endif()
add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})
