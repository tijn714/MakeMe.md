cmake_minimum_required(VERSION 3.10)
project(makeme_md)

# Zoek naar wxWidgets inclusief de richtext component
find_package(wxWidgets REQUIRED COMPONENTS core base richtext)

# Voeg de benodigde flags toe voor wxWidgets
include(${wxWidgets_USE_FILE})

# Voeg de bronbestanden toe
add_executable(makeme_md src/main.cpp)

# Koppel de wxWidgets bibliotheken
target_link_libraries(makeme_md ${wxWidgets_LIBRARIES})
