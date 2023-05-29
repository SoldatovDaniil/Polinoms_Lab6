set(target "Interface")

file(GLOB hdrs "*.h*" "${MP2_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

add_executable(${target} ${srcs} ${hdrs})