//
// file:			emscripten.hpp
// path:			include/cpputils/emscripten.hpp
// created on:		2022 Feb 09
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#pragma once

#include <cpputils/internal_header.h>
#include <string>

#ifdef CPPUTILS_EMSCRIPTEN_IS_USED
#include <emscripten/emscripten.h>
#endif

namespace cpputils { namespace emscripten {

typedef void (*FsSyncClbk)(void*);

extern "C" CPPUTILS_EXPORT void  get_base_url_str2(const char* a_hint, char* a_buff, int a_bufLen);
CPPUTILS_EXPORT ::std::string  get_base_url_str(const ::std::string& a_hint);
CPPUTILS_EXPORT void mount_idbfs_file_system(const char* a_cpcMountPoint, const FsSyncClbk& a_clbk, void* a_pData);
CPPUTILS_EXPORT void fs_sync(void);

}}  // namespace cpputils { namespace emscripten {
