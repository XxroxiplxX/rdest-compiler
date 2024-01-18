set(LIB_NAME compilerAstLib)

# Zbierz pliki źródłowe w katalogu lib
set(LIB_SOURCE_FILES
    Block.cpp
    CodeBlock.cpp
    Value.cpp
    ValueFactory.cpp
    TreeConfigurationProvider.cpp
)

# Utwórz bibliotekę współdzieloną
add_library(${LIB_NAME} SHARED ${LIB_SOURCE_FILES})

# Dodaj ścieżkę do pliku nagłówkowego
target_include_directories(${LIB_NAME} PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_ROOT}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )