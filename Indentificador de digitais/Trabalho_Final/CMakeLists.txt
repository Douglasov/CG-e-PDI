set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 2.8)
project( Digital_Pattern )
find_package( OpenCV REQUIRED )
include_directories(include)
include_directories(src)
add_executable(Digital_Pattern src/main.cpp src/Imagem.cpp src/Histograma.cpp src/Dedo.cpp src/Base_Dados.cpp include/Imagem.h include/Dedo.h include/Histograma.h include/Base_Dados.h
 )
target_link_libraries( Digital_Pattern ${OpenCV_LIBS} )
