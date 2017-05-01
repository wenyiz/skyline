if (ENABLE_CPPCHECK)
    find_package(cppcheck REQUIRED)

    if(CPPCHECK_EXECUTABLE)
        set(_cppcheck_flags "-I${CMAKE_CURRENT_BINARY_DIR}")
        get_directory_property(_inc_dirs INCLUDE_DIRECTORIES)
        
        foreach(_current ${_inc_dirs})
            set(_cppcheck_flags ${_cppcheck_flags} "-I${_current}")
        endforeach()
        
        get_directory_property(_defs COMPILE_DEFINITIONS)
        foreach(_current ${_defs})
            set(_cppcheck_flags ${_cppcheck_flags} "-D${_current}")
        endforeach()

        add_custom_target(cppcheck
            COMMAND ${CPPCHECK_EXECUTABLE} --enable=all -j4 --inconclusive -f ${_cppcheck_flags}
            -i "${CMAKE_CURRENT_SOURCE_DIR}/vendor"
            --suppressions-list="${CMAKE_CURRENT_SOURCE_DIR}/cmake/cppcheck_supressions.txt"
            -UOPENCV_NOSTL
            -UOPENCV_NOSTL_TRANSITIONAL
            -UCV_COLLECT_IMPL_DATA
            -UCV_NO_FUNC_NAMES
            -UHAVE_TERGRA_OPTIMIZATIONS
            ${CMAKE_CURRENT_SOURCE_DIR} 2> ${CMAKE_BINARY_DIR}/cppcheck.log
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Running the cppcheck static code checker"
            )
    else()
        message(SEND_ERROR "Error: Cannot find CPPCHECK executable while ENABLE_CPPCHECK is enabled. Please ensure you've installed cppcheck.")
    endif()
endif(ENABLE_CPPCHECK)

