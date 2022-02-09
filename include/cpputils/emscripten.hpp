//
// file:			emscripten.hpp
// path:			include/cpputils/emscripten.hpp
// created on:		2022 Feb 09
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#pragma once

#include <cpputils_internal_header.h>
#include <string>

#ifdef CPPUTILS_EMSCRIPTEN_IS_USED
#include <emscripten/emscripten.h>
#endif

namespace cpputils { namespace emscripten {

CPPUTILS_EXPORT ::std::string  get_base_url_str(const ::std::string& a_hint);
CPPUTILS_EXPORT void mount_idbfs_file_system(const char* a_cpcMountPoint);
CPPUTILS_EXPORT void fs_sync(void);

}}  // namespace cpputils { namespace emscripten {

