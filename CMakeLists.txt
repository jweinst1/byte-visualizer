cmake_minimum_required(VERSION 3.5)

PROJECT(byte-visualizer)

add_definitions(-DPVIS_NAME="byte-visualizer")

add_executable(byte-visualizer main.c)
