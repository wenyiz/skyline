set(skyline_demo_src
    skyline_demo.cpp	
)

add_executable(skyline_demo ${skyline_demo_src})

target_include_directories(skyline_demo PUBLIC
                $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/modules/bld/include/>
		)

target_link_libraries(skyline_demo
	skyline_bld
)

set_property(TARGET skyline_demo PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET skyline_demo PROPERTY CXX_STANDARD 11)
