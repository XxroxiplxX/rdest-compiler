set(LIB_NAME compilerAssemblerLib)

# Zbierz pliki źródłowe w katalogu lib
set(LIB_SOURCE_FILES
    fields/Assembler.cpp
    builders/AssemblerBuilders.cpp
)

# Utwórz bibliotekę współdzieloną
add_library(${LIB_NAME} SHARED ${LIB_SOURCE_FILES})
target_link_libraries(${LIB_NAME} PUBLIC compilerAstLib)
# Dodaj ścieżkę do pliku nagłówkowego
target_include_directories(${LIB_NAME} PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_ROOT}/fields>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fields>
    $<BUILD_INTERFACE:${PROJECT_ROOT}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_ROOT}/builders>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/builders>
    )