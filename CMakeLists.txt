cmake_minimum_required(VERSION 3.2)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")

project(sequencer)

add_definitions(-DOGL_DEBUG)

set(CMAKE_CXX_FLAGS "/MP /arch:AVX2")

file(GLOB_RECURSE libsCollection "vcpkg/installed/x64-windows/lib/*.lib")

file(GLOB_RECURSE fileCollection "src/*.cpp" "src/*.h")


add_executable(sequencer
    ${fileCollection}
)

add_custom_command(
    TARGET sequencer 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/src/res
        $<TARGET_FILE_DIR:sequencer>/res
)

# add_custom_command(
#     TARGET sequencer 
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${PROJECT_SOURCE_DIR}/share
#         $<TARGET_FILE_DIR:sequencer>/share
# )

foreach(FILE ${fileCollection}) 
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    ## Group into "Source Files" and "Header Files"
    # if ("${FILE}" MATCHES ".*\\.cpp")
    #    set(GROUP "Source Files${GROUP}")
    # elseif("${FILE}" MATCHES ".*\\.h")
    #    set(GROUP "Header Files${GROUP}")
    # endif()


    set(GROUP "Source Files${GROUP}")

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

target_include_directories(
    sequencer PRIVATE

    vcpkg/installed/x64-windows/include/

    include/
)

target_link_directories(
    sequencer PUBLIC

    vcpkg/installed/x64-windows/lib/
)

target_link_libraries(sequencer

    ${libsCollection}

)