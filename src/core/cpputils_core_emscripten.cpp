//
// file:			cpputils_core_emscripten.cpp
// path:			src/core/cpputils_core_emscripten.cpp
// created on:		2022 Feb 09
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// remember alert("The URL of this page is: " + window.location.href); makes alert for browser, that can be used in the future
//

#include <cpputils/emscripten.hpp>


#ifdef CPPUTILS_EMSCRIPTEN_IS_USED
#include <stdlib.h>
#endif

namespace cpputils { namespace emscripten {

#ifdef CPPUTILS_EMSCRIPTEN_IS_USED

EM_JS(char*, get_base_url_str_private, (), {
  var jsString = window.location.href;
  var lengthBytes = lengthBytesUTF8(jsString)+1;
  var stringOnWasmHeap = _malloc(lengthBytes);
  stringToUTF8(jsString, stringOnWasmHeap, lengthBytes);
  return stringOnWasmHeap;
});


::std::string  get_base_url_str(const ::std::string&)
{
    char* pcBaseUrl = get_base_url_str_private();
    ::std::string returnString(pcBaseUrl);
    free(pcBaseUrl);
    return returnString;
}

#else   //  #ifdef CPPUTILS_EMSCRIPTEN_IS_USED


::std::string  get_base_url_str(const ::std::string& a_hint)
{
    return a_hint;
}

#endif   //  #ifdef CPPUTILS_EMSCRIPTEN_IS_USED


}}  // namespace cpputils { namespace emscripten {
