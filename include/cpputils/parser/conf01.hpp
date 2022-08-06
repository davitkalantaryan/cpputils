//
// file:			conf01.hpp
// path:			include/cpputils/parser/conf01.hpp
// created on:		2022 Aug 06
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// info:            This header is valid only for c++11 and higher
//

#pragma once

#include <cpputils/internal_header.h>
#include <vector>
#include <string>
#include <utility>


namespace cpputils{ namespace parser{

class CPPUTILS_DLL_PRIVATE Conf01_p;

typedef ::std::pair<::std::string,::std::string>    TypePair;
typedef ::std::vector<TypePair >    TypeComments;

class CPPUTILS_EXPORT Conf01
{
public:
    ~Conf01();
    Conf01(const TypeComments& vectComments);
    Conf01(const Conf01& a_cM);
    Conf01(Conf01&& a_mM);

    Conf01& operator=(const Conf01& a_cM);
    Conf01& operator=(Conf01&& a_mM);

    void ParseStringNC(char* a_str);
    void ParseString(const char* a_str);
    //void ParseFile(const char* a_filePath);

    ::std::string getValueFromKey(const ::std::string& key, const ::std::string& defaultValue, bool* ifExist=nullptr)const;

private:
    Conf01_p*       m_parser_data_p;
};


}}  // namespace cpputils{ namespace parser{
