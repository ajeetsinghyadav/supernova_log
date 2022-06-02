option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY clang-tidy)
    if(CLANG_TIDY)
        # Check Clang-tidy version
        set(CLANG_TIDY_CMD ${CLANG_TIDY} --version)
        execute_process(COMMAND ${CLANG_TIDY_CMD}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE CLANG_TIDY_RESULT
            OUTPUT_VARIABLE CLANG_TIDY_VERSION
            ERROR_VARIABLE  CLANG_TIDY_ERROR
        )
        set(CLANG_TIDY_CMD
            ${CLANG_TIDY}
            -p=${CMAKE_BINARY_DIR}
        )
        if(CLANG_TIDY_RESULT EQUAL 0)
            set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_CMD})
            message("---------------------------------------------------------")
            message(STATUS "clang-tidy has been found: ${CLANG_TIDY_VERSION}")
            message("---------------------------------------------------------")
        endif()
    else()
        message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()
endif()


