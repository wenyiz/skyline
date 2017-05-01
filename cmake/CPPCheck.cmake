find_package(cppcheck QUIET)

if (CPPCHECK_EXECUTABLE)
    if (NOT TARGET merge_cppcheck)
        # TODO
        # This is where we run a command to find and merge all the _cppcheck.xml files into one big one.
        add_custom_target(merge_cppcheck ALL
                COMMAND python ${CMAKE_SOURCE_DIR}/cmake/merge-cppcheck.py ${CMAKE_BINARY_DIR}
                BYPRODUCTS ${CMAKE_BINARY_DIR}/merged_cppcheck.xml
                COMMENT "Merging CPP Check output"
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

        add_custom_target(cppcheck_report
                COMMAND cppcheck-htmlreport --title=${PROJECT_NAME} --file=${CMAKE_BINARY_DIR}/merged_cppcheck.xml --report-dir=${CMAKE_BINARY_DIR}/cppcheck --source-dir=${CMAKE_SOURCE_DIR}
                DEPENDS merge_cppcheck
                COMMENT "Generating CPP Check report")
    endif()
endif()

function(add_cppcheck _targetname)
    if (CPPCHECK_EXECUTABLE)
        if (NOT TARGET ${_targetname})
           message(FATAL_ERROR "add_cppcheck should only be called on targets (got " ${_targetname} ")")
        endif()

        # Build up a list of -I<directory> arguments
        get_target_property(_cppcheck_includes ${_targetname} INCLUDE_DIRECTORIES)
        set(_includes)

        foreach(_include ${_cppcheck_includes})
            list(APPEND _includes "-I${_include}")
        endforeach()

        # Build up a list of -DTHING=VALUE arguments
        get_target_property(_cppcheck_defines ${_targetname} COMPILE_DEFINITIONS)
        set(_defines)

        foreach(_define ${_cppcheck_defines})
            list(APPEND _defines "-D${_define}")
        endforeach()

        # figure out which sources this should be applied to
        get_target_property(_cppcheck_sources ${_targetname} SOURCES)
        set(_sources)
        foreach(_source ${_cppcheck_sources})
            get_source_file_property(_cppcheck_lang "${_source}" LANGUAGE)
            get_source_file_property(_cppcheck_loc "${_source}" LOCATION)

            if ("${_cppcheck_lang}" MATCHES "CXX")
                list(APPEND _sources ${_cppcheck_loc})
            endif()
        endforeach()

        get_target_property(_cppcheck_output_location ${_targetname} BINARY_DIR)


        # TODO:
        #
        # 1) Fix how we grab output from cppcheck. At some point, we should probably have a script wrap cppcheck for us
        # or, better, add a -o option to cppcheck to control where its output goes. This should work on unix-y platforms
        # but I have no clue if it will work on Windows
        add_custom_target(${_targetname}_cppcheck ALL
                COMMAND ${CPPCHECK_EXECUTABLE} --quiet --enable=warning,performance,portability --std=c++11 --platform=unix64 --inline-suppr --xml --xml-version=2 -f ${_sources} 2> ${_cppcheck_output_location}/${_targetname}_cppcheck.xml
                COMMENT "Running CPP check for ${_targetname}"
                BYPRODUCTS ${_targetname}_cppcheck.xml
                SOURCES ${_sources})

        add_dependencies(merge_cppcheck ${_targetname}_cppcheck)
    endif()
endfunction()