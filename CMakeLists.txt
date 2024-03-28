cmake_minimum_required(VERSION 3.27)
project(NeuralNetwork)

set(CMAKE_CXX_STANDARD 17)

# include(/Users/alexandrubuzescu/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake)

# find_package(Matplot++ CONFIG REQUIRED)
#find_package(Matplot++ REQUIRED)


add_executable(
        NeuralNetwork main.cpp
        NeuralNetwork/NeuralNetwork.cpp
        NeuralNetwork/NeuralNetwork.h
        Matrix/Matrix.cpp
        Matrix/Matrix.h
)
#target_link_libraries(NeuralNetwork PUBLIC Matplot++::matplot)
# target_link_libraries(NeuralNetwork PRIVATE Matplot++::cimg  Matplot++::matplot)






