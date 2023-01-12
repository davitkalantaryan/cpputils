//
// file:			cpputils_core_emscripten.cpp
// path:			src/core/cpputils_core_emscripten.cpp
// created on:		2022 Feb 09
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// remember alert("The URL of this page is: " + window.location.href); makes alert for browser, that can be used in the future
//

#include <cpputils/emscripten.hpp>


#ifdef CINTERNAL_EMSCRIPTEN_IS_USED
#include <stdlib.h>
#else
#include <string.h>
#endif

#ifdef _MSC_VER
#define strncpy(_buff,_hint,_bufLen)    strncpy_s(_buff,_bufLen,_hint,_bufLen)
#endif

#ifdef CINTERNAL_EMSCRIPTEN_IS_USED

CINTERNAL_BEGIN_C

struct CpputilsFsSyncSClbkData{
    ::cpputils::emscripten::FsSyncClbk  m_clbk;
    void*       m_clbkData;
};

//CPPUTILS_DLL_PUBLIC void CpputilsCallCallbackFunction(const struct CpputilsFsSyncSClbkData* a_pData);

CINTERNAL_END_C

#endif  // #ifdef CPPUTILS_EMSCRIPTEN_IS_USED


namespace cpputils { namespace emscripten {    

#ifdef CPPUTILS_EMSCRIPTEN_IS_USED

EM_JS(void, get_base_url_str2, (const char*, char* a_buff, int a_bufLen), {
  var jsString = window.location.href;
  var lengthBytes = lengthBytesUTF8(jsString)+1;
  if(lengthBytes>a_bufLen){
      lengthBytes = a_bufLen;
  }
  stringToUTF8(jsString, a_buff, lengthBytes);
});


//EM_JS(char*, get_base_url_str_private, (), {
//  var jsString = window.location.href;
//  var lengthBytes = lengthBytesUTF8(jsString)+1;
//  var stringOnWasmHeap = _malloc(lengthBytes);
//  stringToUTF8(jsString, stringOnWasmHeap, lengthBytes);
//  return stringOnWasmHeap;
//});
//
//
//::std::string  get_base_url_str(const ::std::string&)
//{
//    char* pcBaseUrl = get_base_url_str_private();
//    ::std::string returnString(pcBaseUrl);
//    free(pcBaseUrl);
//    return returnString;
//}


CPPUTILS_EXPORT ::std::string  get_base_url_str(const ::std::string&)
{
    char* pcBaseUrl = (char*)EM_ASM_INT({
        var jsString = window.location.href;
        var lengthBytes = lengthBytesUTF8(jsString)+1;
        // 'jsString.length' would return the length of the string as UTF-16
        // units, but Emscripten C strings operate as UTF-8.
        var stringOnWasmHeap = _malloc(lengthBytes);
        stringToUTF8(jsString, stringOnWasmHeap, lengthBytes);
        return stringOnWasmHeap;
    });
    ::std::string returnString(pcBaseUrl);
    free(pcBaseUrl);
    return returnString;
}



CPPUTILS_EXPORT void mount_idbfs_file_system(const char* a_cpcMountPoint, const FsSyncClbk& a_clbk, void* a_pData)
{
    CpputilsFsSyncSClbkData aClbk({a_clbk,a_pData});
    EM_ASM({

        // Make a directory other than '/'
        console.log(UTF8ToString($0));
        FS.mkdir(UTF8ToString($0));
        // Then mount with IDBFS type
        FS.mount(IDBFS, {}, UTF8ToString($0));
        // Then sync
        FS.syncfs(true, function (err) {
            //assert(!err);
            console.log(err);
            // todo: analize errpr and call callback
            //_CpputilsCallCallbackFunction($1);
        });

    }, a_cpcMountPoint,&aClbk);
}


CPPUTILS_EXPORT void fs_sync(void)
{
    EM_ASM({
        FS.syncfs(false,function (err) {
            //assert(!err);
            console.log(err);
        });
    });
}


#else   //  #ifdef CPPUTILS_EMSCRIPTEN_IS_USED


extern "C" CPPUTILS_EXPORT void  get_base_url_str2(const char* a_hint, char* a_buff, int a_bufLen)
{
    :: strncpy(a_buff,a_hint,static_cast<size_t>(a_bufLen));
}


CPPUTILS_EXPORT ::std::string  get_base_url_str(const ::std::string& a_hint)
{
    return a_hint;
}


CPPUTILS_EXPORT void mount_idbfs_file_system(const char*, const FsSyncClbk& a_clbk, void* a_pData)
{
    a_clbk(a_pData);
}


CPPUTILS_EXPORT void fs_sync(void)
{
}


#endif   //  #ifdef CPPUTILS_EMSCRIPTEN_IS_USED


}}  // namespace cpputils { namespace emscripten {


#ifdef CPPUTILS_EMSCRIPTEN_IS_USED

CINTERNAL_BEGIN_C


CPPUTILS_DLL_PUBLIC void EMSCRIPTEN_KEEPALIVE CpputilsCallCallbackFunction(const struct CpputilsFsSyncSClbkData* a_pData)
{
    a_pData->m_clbk(a_pData->m_clbkData);
}

CINTERNAL_END_C

#endif  // #ifdef CPPUTILS_EMSCRIPTEN_IS_USED
