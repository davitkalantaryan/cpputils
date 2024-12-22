//
// file:			cpputils_core_parser_conf01.cpp
// path:			src/core/cpputils_core_parser_conf01.cpp
// created on:		2022 Aug 06
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cpputils/parser/conf01.hpp>
#include <cpputils/hash/lhash.hpp>
#include <cinternal/wrapper.h>
#include <cinternal/disable_compiler_warnings.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils{ namespace parser{

typedef ::cpputils::hash::LHash<::std::string,::std::string>        TypeResults;

class CPPUTILS_DLL_PRIVATE Conf01_p
{
public:
    Conf01_p(const TypeComments& vectComments);
    Conf01_p(const Conf01_p& a_cM);

public:
    TypeComments    m_vectComments;
    TypeResults     m_result;
};


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

Conf01::~Conf01()
{
    delete m_parser_data_p;
}


Conf01::Conf01(const ::std::vector<::std::pair<::std::string,::std::string> >& a_vectComments)
    :
      m_parser_data_p(new Conf01_p(a_vectComments))
{
}


Conf01::Conf01(const Conf01& a_cM)
    :
      m_parser_data_p(new Conf01_p(*a_cM.m_parser_data_p))
{
}


Conf01::Conf01(Conf01&& a_mM)
    :
      m_parser_data_p(a_mM.m_parser_data_p)
{
    a_mM.m_parser_data_p= nullptr;
}


Conf01& Conf01::operator=(const Conf01& a_cM)
{
    m_parser_data_p->m_vectComments = a_cM.m_parser_data_p->m_vectComments;
    m_parser_data_p->m_result = a_cM.m_parser_data_p->m_result;
    return *this;
}


Conf01& Conf01::operator=(Conf01&& a_mM)
{
    Conf01_p*const thisDataPtr = m_parser_data_p;
    m_parser_data_p = a_mM.m_parser_data_p;
    a_mM.m_parser_data_p = thisDataPtr;
    return *this;
}


void Conf01::ParseString(const char* a_str)
{
    char* pcStrDp = CinternalWrapperStrdup(a_str);
    if(pcStrDp){
        ParseStringNC(pcStrDp);
        free(pcStrDp);
    }
}


#define CPPUTILS_WHITE_CHARS     " \t\r\n"

void Conf01::ParseStringNC(char* a_str)
{
    size_t unStrLen = strlen(a_str);
    size_t unRemoveCount;
    char* pcStrNext(a_str);
    char *pcDelim1, *pcDelim2;
    const size_t cunCommentsCount(m_parser_data_p->m_vectComments.size());
    const ::std::pair<::std::string,::std::string>* pComments = m_parser_data_p->m_vectComments.data();
    for(size_t i(0); i<cunCommentsCount;++i){
        const ::std::string& strCommentStr1 = pComments[i].first;
        pcDelim1 = strstr(pcStrNext,strCommentStr1.c_str());
        if(!pcDelim1){continue;}
        unStrLen -= static_cast<size_t>(pcDelim1-pcStrNext);
        pcStrNext = pcDelim1 + strCommentStr1.length();

        const ::std::string& strCommentStr2 = pComments[i].second;
        pcDelim2 = strstr(pcStrNext,strCommentStr2.c_str());
        if(!pcDelim2){/*throw "comment start without end";*/return;}
        pcStrNext = pcDelim2 + strCommentStr2.length();
        if(strCommentStr2=="\n"){--pcStrNext;}

        unRemoveCount = static_cast<size_t>(pcStrNext-pcDelim1);
        memmove(pcDelim1,pcStrNext,unStrLen-unRemoveCount);
        unStrLen -= unRemoveCount;
        pcStrNext = pcDelim1;
    }
    a_str[unStrLen]=0;

    char* pcQuote;
    char* pcEqual;
    size_t unOffsetToValid;
    size_t unOffsetToInvalid;
    size_t unOffsetToEqual;
    ::std::string keyStr;
    ::std::string valStr;

    pcStrNext = a_str;

    while(1){
        unOffsetToValid = strspn(pcStrNext,CPPUTILS_WHITE_CHARS);
        pcStrNext += unOffsetToValid;
        unOffsetToInvalid = strcspn(pcStrNext,CPPUTILS_WHITE_CHARS);
        pcEqual = strchr(pcStrNext,'=');
        if(!pcEqual){return;}
        unOffsetToEqual = static_cast<size_t>(pcEqual-pcStrNext);
        if(unOffsetToInvalid<unOffsetToEqual){
            if(unOffsetToInvalid<1){return;}
            keyStr = ::std::string(pcStrNext,unOffsetToInvalid);
            pcStrNext += unOffsetToInvalid;
            unOffsetToValid = strspn(pcStrNext,CPPUTILS_WHITE_CHARS);
            pcStrNext += unOffsetToValid;
            if(pcStrNext[0]!='='){return;}
            ++pcStrNext;
        }
        else{
            if(unOffsetToEqual<1){return;}
            keyStr = ::std::string(pcStrNext,unOffsetToEqual);
            pcStrNext += (unOffsetToEqual+1);
        }

        unOffsetToValid = strspn(pcStrNext,CPPUTILS_WHITE_CHARS);
        pcStrNext += unOffsetToValid;

        if(pcStrNext[0]=='\"'){
            pcQuote = strchr(++pcStrNext,'\"');
            if(!pcQuote){return;}
            unOffsetToInvalid = static_cast<size_t>(pcQuote-pcStrNext);
        }
        else{
            pcQuote = nullptr;
            unOffsetToInvalid = strcspn(pcStrNext,CPPUTILS_WHITE_CHARS);
        }

        if(unOffsetToInvalid<1){return;}
        valStr = ::std::string(pcStrNext,unOffsetToInvalid);
        pcStrNext += unOffsetToInvalid;
        if(pcQuote){++pcStrNext;}

        m_parser_data_p->m_result.AddEntryIfNotExistMv(TypePair(keyStr,valStr));
    }
}


::std::string Conf01::getValueFromKey(const ::std::string& a_key, const ::std::string& a_defaultValue, bool* a_ifExist)const
{
    TypeResults::const_iterator iter = m_parser_data_p->m_result.find(a_key);

    if(iter==TypeResults::s_constNullIter){
        if(a_ifExist){*a_ifExist=false;}
        return a_defaultValue;
    }

    if(a_ifExist){*a_ifExist=true;}
    return iter->second;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

Conf01_p::Conf01_p(const ::std::vector<::std::pair<::std::string,::std::string> >& a_vectComments)
    :
      m_vectComments(a_vectComments)
{
}


Conf01_p::Conf01_p(const Conf01_p& a_cM)
    :
      m_vectComments(a_cM.m_vectComments),
      m_result(a_cM.m_result)
{
}


}}  // namespace cpputils{ namespace parser{
