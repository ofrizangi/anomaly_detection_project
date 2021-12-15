cmake_minimum_required(VERSION 3.20)
project(timeSeriesProject)

set(CMAKE_CXX_STANDARD 11)

add_executable(timeSeriesProject anomaly_detection_util.cpp anomaly_detection_util.h TimeSeries.cpp TimeSeries.h SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h minCircle.cpp HybridAnomalyDetector.cpp HybridAnomalyDetector.h MainTrain.cpp commands.h CLI.cpp CLI.h)
