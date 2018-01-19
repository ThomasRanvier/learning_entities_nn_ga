cmake_minimum_required(VERSION 3.9)
project(learning_entities_nn_ga)

set(CMAKE_CXX_STANDARD 11)

add_executable(learning_entities_nn_ga main.cpp classes/Entity.cpp headers/Entity.h classes/NeuralNetwork.cpp headers/NeuralNetwork.h classes/Neuron.cpp headers/Neuron.h classes/Food.cpp headers/Food.h classes/Map.cpp headers/Map.h classes/Point.cpp headers/Point.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(learning_entities_nn_ga ${SFML_LIBRARIES})
endif()
