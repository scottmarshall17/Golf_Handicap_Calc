# Author: Scott Marshall
# Netid: Scottmarshall
# Date: 10/18/2014
# ECE275
# Assignment X: handicapper

set( CMAKE_C_FLAGS "-Wall -g")

file(GLOB SRCS *.c *.h)

add_executable( handicapper ${SRCS} )