message(STATUS "CXX Compiler is " ${CMAKE_CXX_COMPILER_ID})

if (${CMAKE_CXX_COMPILER_ID} MATCHES ".*lang")
    # Warnings
    add_compile_options("-Wall" "-Wextra" "-Werror" "-pedantic")

    # Compiler constants
    add_compile_options("-fconstexpr-depth=4096" "-ftemplate-depth=1024" "-foperator-arrow-depth=1024")

    # General purpose optimizations / code gen
    add_compile_options("-pipe" "-march=native" "-frtti" "-fexceptions" "-fcxx-exceptions")

    # Work around gtest -- disable these warnings
    add_compile_options("-Wno-missing-field-initializers" "-Wno-variadic-macros" "-Wno-c++11-long-long")

    # Extra stuff for particular build types
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        message(STATUS "Configuring CLANG debug build")

        # Add sanitizers here; NOTE: if you add a sanitizer to the compile args, make sure you include it in the link
        # args as well. Unfortunately, can't do this with LTO because it is known to cause false positives
    endif ()

    if ("${CMAKE_SYSTEM}" MATCHES "Linux")
        add_compile_options("-stdlib=libstdc++")
    endif ()

elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    # Warnings
    add_compile_options("-Wall" "-Wextra" "-Werror" "-pedantic")

    # Compiler constants
    add_compile_options("-ftemplate-depth=1024")

    # General purpose optimizations / code gen
    add_compile_options("-pipe" "-march=native" "-frtti" "-fexceptions")

    # Work around gtest -- disable these warnings
    add_compile_options("-Wno-error=long-long" "-Wno-error=variadic-macros")

    # Extra stuff for particular build types
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        message(STATUS "Configuring GCC debug build")

        # Add sanitizers here; NOTE: if you add a sanitizer to the compile args, make sure you include it in the link
        # args as well. Unfortunately, can't do this with LTO because it is known to cause false positives
    endif ()

endif ()
