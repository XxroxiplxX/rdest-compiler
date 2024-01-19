set(LIB_NAME compilerAstLib)

# Zbierz pliki źródłowe w katalogu lib
set(LIB_SOURCE_FILES
    fields/Block.cpp
    fields/CodeBlock.cpp
    fields/Value.cpp
    fields/Instruction.cpp
    builders/ValueFactory.cpp
    builders/InstructionBuilder.cpp
    builders/ExpressionBuilder.cpp
    builders/CodeBlockBuilder.cpp
    TreeConfigurationProvider.cpp
    EdgeProvider.cpp
)

# Utwórz bibliotekę współdzieloną
add_library(${LIB_NAME} SHARED ${LIB_SOURCE_FILES})

# Dodaj ścieżkę do pliku nagłówkowego
target_include_directories(${LIB_NAME} PUBLIC
        $<BUILD_INTERFACE:${PROJECT_ROOT}/fields>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fields>
        $<BUILD_INTERFACE:${PROJECT_ROOT}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${PROJECT_ROOT}/builders>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/builders>
    )