cmake_minimum_required(VERSION 3.17)
project(smart-rockets)

set(CMAKE_CXX_STANDARD 14)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

add_executable(smart-rockets main.cpp include/GeneticAlgorithm/Population.h src/GeneticAlgorithm/Population.cpp include/GeneticAlgorithm/DNA.h src/GeneticAlgorithm/DNA.cpp include/Helpers/Helpers.h src/Helpers/Helpers.cpp include/Game.h src/Game.cpp include/GameObjects/Asteroid.h include/Helpers/PoissonDiskSampling.h include/Helpers/PoissonPoint.h src/Helpers/PoissonPoint.cpp src/Helpers/PoissonDiskSampling.cpp include/Helpers/Vector2.h include/AsteroidsManager.h src/GameObjects/Asteroid.cpp src/AsteroidsManager.cpp include/Helpers/Random.h src/Helpers/Random.cpp include/Enums/ShapeType.h include/GameObjects/GameObject.h src/GameObjects/GameObject.cpp include/GameObjects/Rocket.h src/GameObjects/Rocket.cpp include/Helpers/Collision.h include/GameObjects/Circle.h include/GameObjects/Rectangle.h src/GameObjects/Rectangle.cpp src/GameObjects/Circle.cpp include/GameObjects/GameObjectBuilder.h src/Helpers/Collision.cpp include/Helpers/Matrix.h include/GeneticAlgorithm/NeuralNetwork.h include/GeneticAlgorithm/NeuronsLayer.h src/GeneticAlgorithm/NeuralNetwork.cpp src/GeneticAlgorithm/NeuronsLayer.cpp src/Helpers/Matrix.cpp include/Enums/CollisionType.h include/Enums/GameObjectType.h include/GameObjects/Ray.h src/GameObjects/Ray.cpp include/RocketsManager.h src/RocketsMangager.cpp include/GameObjects/Window.h src/GameObjects/Window.cpp include/GameObjects/Target.h src/GameObjects/Target.cpp)

# Windows Path
include_directories(c:/SFML/include)
# WSL 2 Path
#include_directories(/usr/include/SFML)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(smart-rockets ${SFML_LIBRARIES})
endif()

# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)
# target_link_libraries(your_target_name PRIVATE Threads::Threads)

# Copy dlls to build directory
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()