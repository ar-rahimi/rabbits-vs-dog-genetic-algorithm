cmake_minimum_required(VERSION 3.9.3)
project(toets)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${toets_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wno-narrowing")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Og -fsanitize=address -std=c++14")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -fsanitize=address")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} game/headers engine game/src content)

set(SOURCE_FILES main.cpp
        game/headers/Helper.h
        game/headers/globals.h
        game/headers/Game.h
        engine/headers/Graphics.h
        game/Helper.cpp
        game/Game.cpp
        engine/headers/RenderManager.h
        engine/headers/InputManager.h
        engine/RenderManager.cpp
        engine/InputManager.cpp
        game/Map.cpp game/headers/Map.h
        game/Tile.cpp
        game/headers/Tile.h
        game/MoveableObject.cpp
        game/headers/MoveableObject.h
        engine/KmPoint.cpp
        engine/headers/KmPoint.h
        game/Dog.cpp
        game/headers/Dog.h
        engine/CRect.cpp
        engine/headers/CRect.h
        game/Text.cpp game/headers/Text.h
        engine/CPriorityQueue.cpp
        engine/headers/CPriorityQueue.h
        game/Mister.cpp
        game/headers/Mister.h
        game/RabbitGenerator.cpp
        engine/state_machine/StateMachine.h
        engine/state_machine/State.h
        engine/state_machine/NullState.h
        game/states/Dog/DogWanderState.cpp
        game/states/Dog/headers/DogWanderState.h
        game/states/Dog/DogThirstyState.cpp
        game/states/Dog/headers/DogThirstyState.h
        game/states/Dog/DogSleepState.cpp
        game/states/Dog/headers/DogSleepState.h
        game/states/dog/DogGoToCaveState.cpp
        game/states/dog/headers/DogGoToCaveState.h
        game/states/dog/DogCatchRabbitState.cpp
        game/states/dog/headers/DogCatchRabbitState.h
        game/states/mister_states/MisterWanderState.cpp
        game/states/mister_states/MisterPictureState.cpp
        game/states/mister_states/headers/MisterWanderState.h
        game/states/mister_states/headers/MisterPictureState.h
        game/states/mister_states/headers/MisterGiveDogWaterState.h
        game/headers/Missus.h
        game/Missus.cpp
        game/states/missus_states/headers/MissusWanderState.h
        game/states/missus_states/MissusWanderState.cpp
        game/states/missus_states/headers/MissusIdleState.h
        game/states/missus_states/MissusIdleState.cpp
        game/states/Dog/headers/DogGlobalState.h
        game/states/Dog/DogGlobalState.cpp
        game/headers/RabbitGenerator.h
        game/RabbitGenerator.cpp
        game/headers/RabbitGenerator.h
        engine/Debug.cpp
        engine/headers/Debug.h
        game/GameObject.cpp
        game/headers/GameObject.h
        engine/FPoint.cpp
        engine/headers/FPoint.h
        game/ForceDrivenEntity.cpp
        game/headers/ForceDrivenEntity.h
        game/Rabbit.cpp
        game/headers/Rabbit.h
        game/DogOwner.cpp
        game/headers/DogOwner.h
        engine/Seconds.cpp
        engine/headers/Seconds.h
        engine/Random.cpp
        engine/headers/Random.h
        engine/Timer.cpp
        engine/headers/Timer.h
        game/ForceDrivenEntity.cpp
        game/headers/ForceDrivenEntity.h
        game/Rabbit.cpp
        game/headers/Rabbit.h
        game/GeneticPopulator.cpp
        game/headers/GeneticPopulator.h
        game/Chromosome.cpp
        game/headers/Chromosome.h)
add_executable(toets ${SOURCE_FILES})
target_link_libraries(toets ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})