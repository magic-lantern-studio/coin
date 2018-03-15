cmake_minimum_required(VERSION 2.8.12)
project(Coin)
set (COIN_MAJOR_VERSION 4)
set (COIN_MINOR_VERSION 0)
set (COIN_MICRO_VERSION 0)
set (COIN_BETA_VERSION "a")
set (COIN_VERSION "${COIN_MAJOR_VERSION}.${COIN_MINOR_VERSION}.${COIN_MICRO_VERSION}${COIN_BETA_VERSION}")

# option controlled helper for cmake variable dumping during config
function(dump_variable)
  if (COIN_VERBOSE)
    foreach(f ${ARGN})
      message("${f} = ${${f}}")
    endforeach()
  endif(COIN_VERBOSE)
endfunction(dump_variable)

# modifies the install directory passed by postfix, either substituting 'Coin' 
# with 'Coin${COIN_MAJOR_VERSION}' or adding the same versioned name after the 
# postfix part.
#
# Example: 
# versionize(INCLUDEDIR DOCDIR) will modify
#
# CMAKE_INSTALL_DOCDIR          'share/doc/Coin'          --> 'share/doc/Coin4'
# CMAKE_INSTALL_FULL_DOCDIR     '<prefix>/share/doc/Coin' --> '<prefix>/share/doc/Coin4'
#
# CMAKE_INSTALL_INCLUDEDIR      'include'          --> 'include/Coin4'
# CMAKE_INSTALL_FULL_INCLUDEDIR '<prefix>/include' --> '<prefix>/include/Coin4'
function(versionize)
  foreach(dir ${ARGN})
    set(name      "CMAKE_INSTALL_${dir}")
    set(full-name "CMAKE_INSTALL_FULL_${dir}")
    if(${name} MATCHES ${PROJECT_NAME})
      string(REPLACE "${PROJECT_NAME}" "${PROJECT_NAME}${COIN_MAJOR_VERSION}" value      "${${name}}")
      string(REPLACE "${PROJECT_NAME}" "${PROJECT_NAME}${COIN_MAJOR_VERSION}" full-value "${${full-name}}")
    else()
      set(value      "${${name}}/${PROJECT_NAME}${COIN_MAJOR_VERSION}")
      set(full-value "${CMAKE_INSTALL_PREFIX}/${value}")
    endif()
    set(${name}      ${value}      PARENT_SCOPE)
    set(${full-name} ${full-value} PARENT_SCOPE)
  endforeach()
endfunction()

option(COIN_VERBOSE          "Add verbose debugging information during the configure process")
option(COIN_MULTIPLE_VERSION "Forces versioned paths for includes and documentation when ON, usual behaviour otherwise.")
option(COIN_QT_HELP          "Generate QTHelp Documentation files")

include(GNUInstallDirs)

if (COIN_MULTIPLE_VERSION)
  # modifies the installation path for both the distributed includes and docs
  versionize(INCLUDEDIR DOCDIR)
endif (COIN_MULTIPLE_VERSION)

dump_variable(
CMAKE_INSTALL_INCLUDEDIR
CMAKE_INSTALL_FULL_INCLUDEDIR
CMAKE_INSTALL_DOCDIR
CMAKE_INSTALL_FULL_DOCDIR
)

option(COIN_BUILD_SHARED_LIBS "Build shared library when ON, static when OFF." ON)
if(WIN32)
	if(COIN_BUILD_SHARED_LIBS)
		set(CMAKE_RELEASE_POSTFIX "")
		set(CMAKE_MINSIZEREL_POSTFIX "")
		set(CMAKE_RELWITHDEBINFO_POSTFIX "")
		set(CMAKE_DEBUG_POSTFIX "d")
	else(COIN_BUILD_SHARED_LIBS)
		set(CMAKE_RELEASE_POSTFIX "s")
		set(CMAKE_MINSIZEREL_POSTFIX "s")
		set(CMAKE_RELWITHDEBINFO_POSTFIX "s")
		set(CMAKE_DEBUG_POSTFIX "sd")
	endif(COIN_BUILD_SHARED_LIBS)
endif(WIN32)

option(COIN_THREADSAFE "Thread safe traversals.")
option(COIN_HAVE_JAVASCRIPT "Javascript capabilities." ON)
option(HAVE_VRML97 "VRML97 support." ON)
option(HAVE_NODEKITS "Nodekit support." ON)
option(HAVE_DRAGGERS "Dragger support." ON)
option(HAVE_MANIPULATORS "Manipulator support." ON)
option(HAVE_SOUND "Sound support." ON)
option(HAVE_3DS_IMPORT_CAPABILITIES "3ds import capabilities." ON)
option(SIMAGE_RUNTIME_LINKING "Runtime linkage of simage library.")
option(HAVE_MAN "build and install Coin man pages.")

if(NOT SIMAGE_RUNTIME_LINKING)
	find_package(simage)
	if(simage_FOUND)
		set(HAVE_LIBSIMAGE ON)
	else()
		set(HAVE_LIBSIMAGE OFF)
	endif()
endif()

# Checks all specified types for existence and sets variable and sets a variable HAVE_<type_name>
# if so. Additionally a variable named <type_name> is set to the size of the type.
# Moreover, ${TYPE_VARIABLE} will be set to the first type matching the specified ${TYPE_SIZE}.
include(CheckTypeSize)
macro(find_int_type_with_size TYPE_VARIABLE TYPE_SIZE)
	set(${TYPE_VARIABLE} "")
	foreach(TYPE ${ARGN})
		string(TOUPPER ${TYPE} TYPE_VAR)
		string(REPLACE " " "_" TYPE_VAR ${TYPE_VAR})
		check_type_size(${TYPE} ${TYPE_VAR})
		if((${TYPE_VAR} STREQUAL ${TYPE_SIZE}) AND (NOT ${TYPE_VARIABLE}))
			set(${TYPE_VARIABLE} ${TYPE})
		endif()
	endforeach(TYPE ${ARGN})
endmacro()

find_int_type_with_size(COIN_INT8_T 1 "int8_t" "char")
find_int_type_with_size(COIN_UINT8_T 1 "uint8_t" "u_int8_t" "unsigned char")
find_int_type_with_size(COIN_INT16_T 2 "int16_t" "short" "int")
find_int_type_with_size(COIN_UINT16_T 2 "uint16_t" "u_int16_t" "unsigned short" "unsigned int")
find_int_type_with_size(COIN_INT32_T 4 "int32_t" "int" "long")
find_int_type_with_size(COIN_UINT32_T 4 "uint32_t" "u_int32_t" "unsigned int" "unsigned long")
find_int_type_with_size(COIN_INT64_T 8 "int64_t" "long" "int" "long long" "__int64")
find_int_type_with_size(COIN_UINT64_T 8 "uint64_t" "u_int64_t" "unsigned long" "unsigned int" "unsigned long long" "unsigned __int64")

if(MSVC)
	option(COIN_BUILD_SINGLE_LIB "Build only one library when ON, multiple when OFF." ON)
	if (MSVC_VERSION GREATER 1500 OR MSVC_VERSION EQUAL 1500)
		option(COIN_BUILD_MSVC_MP "Enable build with multiple processes in Visual Studio" ON)
	else()
		set(COIN_BUILD_MSVC_MP OFF CACHE BOOL "Compiler option /MP requires at least Visual Studio 2008 (VS9) or newer" FORCE)
	endif()
	if(COIN_BUILD_MSVC_MP)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	endif ()
	if(COIN_BUILD_SHARED_LIBS)
		add_definitions(-DCOIN_MAKE_DLL)
	endif()

	# enable C++ exception handling (for code that uses boost in SbByteBuffer)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

	add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
	option(COIN_BUILD_SINGLE_LIB "Build only one library when ON, multiple when OFF." OFF)
endif()

if(WIN32)
	set(HAVE_WIN32_API 1)
	set(HAVE_WGL 1)
	# on Windows the major version number is part of the library name
	set(CMAKE_RELEASE_POSTFIX "${COIN_MAJOR_VERSION}${CMAKE_RELEASE_POSTFIX}")
	set(CMAKE_MINSIZEREL_POSTFIX "${COIN_MAJOR_VERSION}${CMAKE_MINSIZEREL_POSTFIX}")
	set(CMAKE_RELWITHDEBINFO_POSTFIX "${COIN_MAJOR_VERSION}${CMAKE_RELWITHDEBINFO_POSTFIX}")
	set(CMAKE_DEBUG_POSTFIX "${COIN_MAJOR_VERSION}${CMAKE_DEBUG_POSTFIX}")
elseif(APPLE)
	cmake_policy(SET CMP0042 NEW)
	set(CMAKE_SHARED_LINKER_FLAGS "-framework CoreFoundation -framework CoreGraphics")

	# let's enable all OS X specific code
	set(COIN_MACOSX_FRAMEWORK 1)
	set(COIN_MACOS_10 1)
	set(COIN_MACOS_10_3 1)
else()
	add_compile_options(-fPIC)
endif()
include_directories(${CMAKE_BINARY_DIR}/include)

include(CheckIncludeFile)
check_include_file(dlfcn.h HAVE_DLFCN_H)
check_include_file(inttypes.h HAVE_INTTYPES_H)
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(stddef.h HAVE_STDDEF_H)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(sys/time.h HAVE_SYS_TIME_H)
check_include_file(sys/types.h HAVE_SYS_TYPES_H)
check_include_file(io.h HAVE_IO_H)
check_include_file(libgen.h HAVE_LIBGEN_H)
check_include_file(sys/param.h HAVE_SYS_PARAM_H)
check_include_file(OpenGL/gl.h HAVE_OPENGL_GL_H)
check_include_file(OpenGL/CGLCurrent.h HAVE_OPENGL_CGLCURRENT_H)
check_include_file(OpenGL/glext.h HAVE_OPENGL_GLEXT_H)
check_include_file(OpenGL/glu.h HAVE_OPENGL_GLU_H)
check_include_file(superglu.h HAVE_SUPERGLU)
check_include_file(windows.h HAVE_WINDOWS_H)
check_include_file(X11/Xlib.h HAVE_X11_AVAILABLE)

include(CheckLibraryExists)
check_library_exists(dl dlopen "" HAVE_DL_LIB)
check_library_exists(GL glXChooseVisual "" HAVE_GLX)
check_library_exists(pthread pthread_create "" USE_PTHREAD)

include(CheckSymbolExists)
check_symbol_exists(GetEnvironmentVariable windows.h HAVE_GETENVIRONMENTVARIABLE)
if(NOT USE_PTHREAD)
	check_symbol_exists(CreateThread windows.h USE_W32THREAD)
endif()

if(HAVE_3DS_IMPORT_CAPABILITIES)
	set(FEAT_HAVE_3DS 1)
else()
	set(FEAT_HAVE_3DS 0)
endif()
if(HAVE_VRML97)
	set(FEAT_HAVE_VRML97 1)
else()
	set(FEAT_HAVE_VRML97 0)
endif()
if(HAVE_SOUND)
	set(FEAT_HAVE_SOUND 1)
else()
	set(FEAT_HAVE_SOUND 0)
endif()
if(HAVE_SUPERGLU)
	set(FEAT_HAVE_SUPERGLU 1)
else()
	set(FEAT_HAVE_SUPERGLU 0)
endif()
if(USE_PTHREAD OR USE_W32THREAD)
	set(FEAT_HAVE_THREADS 1)
else()
	set(FEAT_HAVE_THREADS 0)
endif()
if(COIN_THREADSAFE)
	set(FEAT_HAVE_SAFETHREAD 1)
else()
	set(FEAT_HAVE_SAFETHREAD 0)
endif()

check_symbol_exists(va_copy stdarg.h HAVE_VA_COPY_MACRO)
check_symbol_exists(strncasecmp string.h HAVE_STRNCASECMP)
check_symbol_exists(gettimeofday sys/time.h HAVE_GETTIMEOFDAY)
check_symbol_exists(getcwd unistd.h HAVE_GETCWD)
check_symbol_exists(isinf math.h HAVE_ISINF)
check_symbol_exists(isnan math.h HAVE_ISNAN)
check_symbol_exists(finite math.h HAVE_FINITE)
check_symbol_exists(__builtin_expect assert.h HAVE___BUILTIN_EXPECT)
check_symbol_exists(ilogb math.h HAVE_ILOGB)
check_symbol_exists(LoadLibrary windows.h HAVE_WINDLL_RUNTIME_BINDING)
check_symbol_exists(CGL_VERSION_1_0 OpenGL/OpenGL.h HAVE_CGL)
set(HAVE_CGL_PBUFFER ${HAVE_CGL})

check_symbol_exists(__func__ "" FUNC)
check_symbol_exists(__PRETTY_FUNCTION__ "" PRETTY_FUNCTION)
check_symbol_exists(__FUNCTION__ "" FUNCTION)
if(FUNC)
	set(HAVE_CPP_COMPILER_FUNCTION_NAME_VAR __func__)
elseif(PRETTY_FUNCTION)
	set(HAVE_CPP_COMPILER_FUNCTION_NAME_VAR __PRETTY_FUNCTION__)
elseif(FUNCTION)
	set(HAVE_CPP_COMPILER_FUNCTION_NAME_VAR __FUNCTION__)
endif()
check_symbol_exists(_splitpath stdlib.h HAVE__SPLITPATH)

if(NOT HAVE_UNISTD_H)
	add_definitions(-DYY_NO_UNISTD_H)
endif()

# COIN_DOCUMENTATION_FILES is filled with all source files.
unset(COIN_DOCUMENTATION_FILES CACHE)
# COIN_INTERNAL_DOCUMENTATION_FILES is filled with source files that are not part of the public API.
# If COIN_BUILD_INTERNAL_DOCUMENTATION is YES then these files are added to DOXYGEN_INPUT, otherwise
# they are put in DOXYGEN_EXCLUDE.
unset(COIN_INTERNAL_DOCUMENTATION_FILES CACHE)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(data)

# CPACK global settings
set(CPACK_COMPONENT_DEVELOPMENT_DEPENDS runtime)
# CPACK Debian
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_DOCUMENTATION_PACKAGE_NAME "libcoin80-doc")
set(CPACK_DEBIAN_DOCUMENTATION_PACKAGE_SECTION "doc")
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_DEPENDS "libcoin80")
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_NAME "libcoin80-dev")
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_SECTION "libdevel")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://bitbucket.org/Coin3D/coin")
set(CPACK_DEBIAN_PACKAGE_NAME "libcoin80")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_RUNTIME_PACKAGE_NAME "libcoin80-dev")
set(CPACK_DEBIAN_RUNTIME_PACKAGE_SECTION "libs")
# CPACK Windows
set(CPACK_NSIS_PACKAGE_NAME "Coin ${COIN_MAJOR_VERSION}.${COIN_MINOR_VERSION}.${COIN_MICRO_VERSION}")
set(CPACK_NSIS_URL_INFO_ABOUT ${CPACK_DEBIAN_PACKAGE_HOMEPAGE})
# CPACK generic
set(CPACK_PACKAGE_CONTACT "coin-support@coin3d.org")
set(CPACK_PACKAGE_DISPLAY_NAME "Coin ${COIN_MAJOR_VERSION}.${COIN_MINOR_VERSION}.${COIN_MICRO_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Coin-${COIN_MAJOR_VERSION}.${COIN_MINOR_VERSION}.${COIN_MICRO_VERSION}")
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}${COIN_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION ${COIN_MAJOR_VERSION}.${COIN_MINOR_VERSION}.${COIN_MICRO_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${COIN_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${COIN_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${COIN_MICRO_VERSION})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
# CPACK RPM
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_PACKAGE_LICENSE "BSD")
set(CPACK_RPM_PACKAGE_NAME "${PROJECT_NAME}${COIN_MAJOR_VERSION}")
set(CPACK_RPM_PACKAGE_URL ${CPACK_DEBIAN_PACKAGE_HOMEPAGE})
set(CPACK_RPM_DEVELOPMENT_PACKAGE_NAME "${PROJECT_NAME}${COIN_MAJOR_VERSION}-devel")
set(CPACK_RPM_DEVELOPMENT_PACKAGE_REQUIRES "${PROJECT_NAME}${COIN_MAJOR_VERSION}")
set(CPACK_RPM_RUNTIME_PACKAGE_PROVIDES "${PROJECT_NAME}${COIN_MAJOR_VERSION}")
# workaround for erroneous inclusion of system directories
# see https://stackoverflow.com/questions/24983181/cpack-generates-rpms-with-files-entries-that-conflict-with-the-rpm-spec-how-to
set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/lib64/cmake")

if(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
endif()

include(CPack)