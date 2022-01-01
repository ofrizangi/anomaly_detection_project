cmake_minimum_required(VERSION 3.20)
project(seriesProjectNew)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(seriesProjectNew anomaly_detection_util.cpp anomaly_detection_util.h TimeSeries.cpp TimeSeries.h SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h minCircle.cpp HybridAnomalyDetector.cpp HybridAnomalyDetector.h MainTrain.cpp commands.h CLI.cpp CLI.h save.cpp Server.cpp Server.h)
