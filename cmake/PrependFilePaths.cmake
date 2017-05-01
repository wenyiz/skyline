#
# Prepends a path prefix to a list of files
#
# preprend_file_paths(<path_prefix> <files_var>)
#
function(prepend_file_paths path_prefix files_var)
    # Check the path_prefix for a trailing '/' or '\'
    # TODO: Handle Windows paths
    string(REGEX MATCH ".*/$" trailing_slash ${path_prefix})
    if(NOT trailing_slash)
        string(CONCAT path_prefix ${path_prefix} "/")
    endif()

    set(filepaths)
    set(files_tmp ${${files_var}})
    foreach(f ${files_tmp})
        string(CONCAT filepath ${path_prefix} ${f})
        list(APPEND filepaths ${filepath})
    endforeach()

    set(${files_var} ${filepaths} PARENT_SCOPE)
endfunction()
