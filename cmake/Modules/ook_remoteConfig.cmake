INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_OOK_REMOTE ook_remote)

FIND_PATH(
    OOK_REMOTE_INCLUDE_DIRS
    NAMES ook_remote/api.h
    HINTS $ENV{OOK_REMOTE_DIR}/include
        ${PC_OOK_REMOTE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    OOK_REMOTE_LIBRARIES
    NAMES gnuradio-ook_remote
    HINTS $ENV{OOK_REMOTE_DIR}/lib
        ${PC_OOK_REMOTE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OOK_REMOTE DEFAULT_MSG OOK_REMOTE_LIBRARIES OOK_REMOTE_INCLUDE_DIRS)
MARK_AS_ADVANCED(OOK_REMOTE_LIBRARIES OOK_REMOTE_INCLUDE_DIRS)

