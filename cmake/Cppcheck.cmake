option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)

if(ENABLE_CPPCHECK)
    find_program(CMAKE_CXX_CPPCHECK cppcheck)
    if(CMAKE_CXX_CPPCHECK)
        # Check CppCheck version
        set(CPP_CHECK_CMD ${CMAKE_CXX_CPPCHECK} --version)
        execute_process(COMMAND ${CPP_CHECK_CMD}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE CPP_CHECK_RESULT
            OUTPUT_VARIABLE CPP_CHECK_VERSION
            ERROR_VARIABLE CPP_CHECK_ERROR
        )
        # Check if version could be extracted
        if(CPP_CHECK_RESULT EQUAL 0)
            # Append desired arguments to CppCheck
            list(APPEND CMAKE_CXX_CPPCHECK
                --enable=all
                --enable=style
                --suppress=missingIncludeSystem
                --inline-suppr
                --inconclusive
                --quiet
                "--template \"${CMAKE_SOURCE_DIR}/{file}({line}): {severity} ({id}): {message}\""
                --output-file=${CMAKE_BINARY_DIR}/cppcheck.xml
                ${CMAKE_CURRENT_SOURCE_DIR}/src/
            )
            # Note: the option ALL which allows to build the docs together with the application
            add_custom_target(analyze_cppcheck ALL
                COMMAND ${CMAKE_CXX_CPPCHECK}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMENT "Cppcheck static code analysis results are saved in ${CMAKE_BINARY_DIR}/cppcheck.xml"
            )
        endif()
    else()
        message(SEND_ERROR "cppcheck requested but executable not found")
    endif()
endif()