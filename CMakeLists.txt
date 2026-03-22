cmake_minimum_required(VERSION 4.2.3)

project(Chess_Engine)

add_executable(engine engine.c init.c bitboards.c)
