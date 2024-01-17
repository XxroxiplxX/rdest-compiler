set(LIB_NAME compilerAssemblerLib)

# Zbierz pliki źródłowe w katalogu lib
set(LIB_SOURCE_FILES
    Assembler.cpp
)

# Utwórz bibliotekę współdzieloną
add_library(${LIB_NAME} SHARED ${LIB_SOURCE_FILES})

# Dodaj ścieżkę do pliku nagłówkowego
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_ROOT})