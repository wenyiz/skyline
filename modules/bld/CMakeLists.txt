set(bld_srcs 
    src/building_utils.cpp
    src/skyline_vector.cpp	
)

set(bld_public_hdrs
    include/skyline/bld/skyline_vector.h	
    include/skyline/bld/building.h
)

add_library(skyline_bld ${bld_srcs} ${bld_public_hdrs})
add_cppcheck(skyline_bld)

target_include_directories(skyline_bld PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:include/> 
        $<INSTALL_INTERFACE:include/bld>
        )	

set_property(TARGET skyline_bld PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET skyline_bld PROPERTY CXX_STANDARD 11)

install(TARGETS skyline_bld 
        EXPORT skylineTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
	COMPONENT skyline
        )

install(DIRECTORY include/
        DESTINATION include/)

install(EXPORT skylineTargets
        FILE skylineTargets.cmake
        COMPONENT bld
        NAMESPACE skyline::
        DESTINATION cmake)
