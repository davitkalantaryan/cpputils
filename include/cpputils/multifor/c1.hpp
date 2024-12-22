//
// file:			c1.hpp
// path:			include/cpputils/multifor/c1.hpp
// created on:		2021 Sep 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#pragma once


#include <cpputils/export_symbols.h>
#include <cpputils/functional.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace  multifor {

class C1
{
public:
    typedef CPPUTILS_DECLARE_FUNC(TypeIter,void,const void*, size_t,const ::std::vector<int64_t>&);
    typedef CPPUTILS_DECLARE_FUNC(TypeLimit,int64_t,const void*, size_t,const ::std::vector<int64_t>&);
    //typedef ::cpputils::function<void(const void*, size_t,const ::std::vector<int64_t>&)> TypeIter;
    //typedef ::cpputils::function<int64_t(const void*, size_t,const ::std::vector<int64_t>&)> TypeLimit;

public:
    C1(size_t a_deepness, TypeIter a_iter, TypeLimit a_min, TypeLimit a_max);
    ~C1();

    void MakeIteation(const void* clbkData=nullptr);
    void Break();

private:
    class Dimension{
        struct Core;
        Dimension(C1* a_pParent, size_t a_deepness, TypeIter a_iter, TypeLimit a_min, TypeLimit a_max);
        Dimension(size_t a_deepness, Core*, size_t a_dimensionIndex);
        ~Dimension();
        void Initialize();
        void NextIterations();

        //
        Core*const  m_pCore;
        const size_t m_dimensionIndex;
        int64_t m_currentIterationPoint;
        int64_t m_iterationPointsRightEnd;
        Dimension* m_pNextDimension;

        //
        struct Core{
            C1* pParent;
            const void* clbkData;
            size_t   deepness;
            TypeIter iter;
            TypeLimit limitMin;
            TypeLimit limitMax;
            ::std::vector<int64_t>  iterationPoints;
            bool shouldMakeIter;
            bool reserved01[7];
        };

        friend class C1;

#ifdef CPPUTILS_CPP_11_DEFINED
        Dimension(const Dimension&) = delete;
        Dimension& operator=(const Dimension&) = delete;
#endif

    }*const m_pFirstDimesion;

#ifdef CPPUTILS_CPP_11_DEFINED
    C1(const C1&) = delete;
    C1& operator=(const C1&) = delete;
#endif

};


}}  // namespace cpputils { namespace  multifor {
