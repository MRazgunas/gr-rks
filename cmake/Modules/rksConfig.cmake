INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_RKS rks)

FIND_PATH(
    RKS_INCLUDE_DIRS
    NAMES rks/api.h
    HINTS $ENV{RKS_DIR}/include
        ${PC_RKS_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    RKS_LIBRARIES
    NAMES gnuradio-rks
    HINTS $ENV{RKS_DIR}/lib
        ${PC_RKS_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(RKS DEFAULT_MSG RKS_LIBRARIES RKS_INCLUDE_DIRS)
MARK_AS_ADVANCED(RKS_LIBRARIES RKS_INCLUDE_DIRS)

