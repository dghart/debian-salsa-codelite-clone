# define minimum cmake version
cmake_minimum_required(VERSION 2.6.2)
 
# Our project is called 'plugin' this is how it will be called in
# visual studio, and in our makefiles. 
project(plugin)

# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
find_package(wxWidgets COMPONENTS ${WX_COMPONENTS} REQUIRED)

# wxWidgets include (this will do all the magic to configure everything)
include( "${wxWidgets_USE_FILE}" )

# Include paths
include_directories("${CL_SRC_ROOT}/Plugin" "${CL_SRC_ROOT}/sdk/wxsqlite3/include" "${CL_SRC_ROOT}/CodeLite" "${CL_SRC_ROOT}/PCH" "${CL_SRC_ROOT}/Interfaces")

## Macros
if(WIN32)
    add_definitions(-DWXMAKINGDLL_SDK)
endif(WIN32)

if ( USE_PCH )
    add_definitions(-include "${CL_PCH_FILE}")
    add_definitions(-Winvalid-pch)
endif ( USE_PCH )

## On UNIX we require GTK
if (UNIX AND NOT APPLE)

    if (GTK_VERSION EQUAL 3)
        set(OLD_CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}) # Cache the current value
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
        find_package(GTK3)
        set(CMAKE_MODULE_PATH ${OLD_CMAKE_MODULE_PATH}) # Reset, else the official path isn't used again :/
        if (GTK3_FOUND)
            include_directories(${GTK3_INCLUDE_DIRS})
        else (GTK3_FOUND)
            message(FATAL_ERROR "Could not locate GTK.")
        endif (GTK3_FOUND)
    else()
        find_package(GTK2)
        if (GTK2_FOUND)
            include_directories(${GTK2_INCLUDE_DIRS})
        else (GTK2_FOUND)
            message(FATAL_ERROR "Could not locate GTK.")
        endif (GTK2_FOUND)
    endif()

endif (UNIX AND NOT APPLE)

add_definitions(-DWXUSINGDLL_WXSQLITE3)
add_definitions(-DWXUSINGDLL_CL)

# Add RPATH
# Add RPATH
if ( WXC_APP )
    string( REPLACE "codelite" "wxcrafter" WXC_LIBS_DIR ${PLUGINS_DIR})
    set (LINKER_OPTIONS -Wl,-rpath,"${WXC_LIBS_DIR}:${PLUGINS_DIR}")
    message( "-- libplugin.so is using RPATH set to ${WXC_LIBS_DIR}:${PLUGINS_DIR}")
else ( WXC_APP )
    set (LINKER_OPTIONS -Wl,-rpath,"${PLUGINS_DIR}")
    message( "-- libplugin.so is using RPATH set to ${PLUGINS_DIR}")
endif ( WXC_APP )

FILE(GLOB SRCS "*.cpp")

# Define the output
add_library(plugin SHARED ${SRCS})
if(GTK2_FOUND)
    target_link_libraries(plugin ${LINKER_OPTIONS} ${GTK2_LIBRARIES} ${wxWidgets_LIBRARIES} -L"${CL_LIBPATH}" -lwxsqlite3 -lsqlite3lib -llibcodelite)
elseif (GTK3_FOUND)
    target_link_libraries(plugin ${LINKER_OPTIONS} ${GTK3_LIBRARIES} ${wxWidgets_LIBRARIES} -L"${CL_LIBPATH}" -lwxsqlite3 -lsqlite3lib -llibcodelite)
else()
    target_link_libraries(plugin ${LINKER_OPTIONS} ${wxWidgets_LIBRARIES} -L"${CL_LIBPATH}" -lwxsqlite3 -lsqlite3lib -llibcodelite)
endif()

install(TARGETS plugin DESTINATION ${PLUGINS_DIR})