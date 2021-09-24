//
// file:			multifor.cpp
// path:			include/cpputils/multifor.cpp
// created on:		2021 Sep 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#pragma once


#include <cpputils_internal_header.h>
#include <stddef.h>
#include <stdint.h>
#include <vector>


namespace cpputils {

class MultiFor
{
public:
    typedef void (*TypeIter)(const void* clbkData, MultiFor*multifor, const ::std::vector<int64_t>&iterIndexes);
    typedef int64_t (*TypeLimit)(const void* clbkData, size_t childIndex,const ::std::vector<int64_t>&parentsIterIndexes); // size of second arg is equal to childIndex

private:
    struct Core;
public:
    ~MultiFor();
    MultiFor(size_t a_deepness, TypeIter a_iter, TypeLimit a_min, TypeLimit a_max);
private:
    MultiFor(size_t a_deepness, Core*, size_t a_index);

public:
    void MakeIteation(const void* clbkData=nullptr);
    void Break();

private:
    void Initialize();
    void NextIterations();

private:
    struct Core{
        MultiFor* pParent;
        const void* clbkData;
        size_t   deepness;
        TypeIter iter;
        TypeLimit limitMin;
        TypeLimit limitMax;
        ::std::vector<int64_t>  iterValues;
        bool shouldMakeIter;
    }*const m_pCore;

    int64_t m_currentValue;
    int64_t m_currentRightEnd;
    const size_t  m_index;
    MultiFor* m_pChild;

    //friend class MultiFor;
};


}  // namespace cpputils {
