# Attribution: Module generated by ChatGPT 3.5
#
# - Try to find XCB library and headers
# Once done, this will define
#
# XCB_FOUND - system has XCB
# XCB_INCLUDE_DIRS - the XCB include directory
# XCB_LIBRARIES - the libraries to link against

find_path(XCB_INCLUDE_DIR NAMES xcb/xcb.h)
find_library(XCB_LIBRARY NAMES xcb)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(XCB DEFAULT_MSG XCB_LIBRARY XCB_INCLUDE_DIR)

mark_as_advanced(XCB_INCLUDE_DIR XCB_LIBRARY)