cmake_minimum_required(VERSION 3.20)
project(project)

set(CMAKE_CXX_STANDARD 11)

add_executable(project anomaly_detection_util.cpp anomaly_detection_util.h MainTrain.cpp timeseries.cpp timeseries.h SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h minCircle.cpp minCircle.h)
