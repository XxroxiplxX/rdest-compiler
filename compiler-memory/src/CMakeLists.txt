set(LIB_NAME compilerMemoryLib)

# Zbierz pliki źródłowe w katalogu lib
set(LIB_SOURCE_FILES
    MemoryManager.cpp
    ProcedureMemoryModel.cpp
    Register.cpp
)

# Utwórz bibliotekę współdzieloną
add_library(${LIB_NAME} SHARED ${LIB_SOURCE_FILES})

# Dodaj ścieżkę do pliku nagłówkowego
target_include_directories(${LIB_NAME} PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_ROOT}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )