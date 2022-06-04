//
// file:			c1.hpp
// path:			include/cpputils/multifor/c1.hpp
// created on:		2021 Sep 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#pragma once


#include <cpputils/internal_header.h>
#include <cpputils/functional.hpp>
#include <stddef.h>
#include <stdint.h>
#include <vector>


namespace cpputils { namespace  multifor {

class C1
{
public:
    typedef ::cpputils::function<void(const void*, size_t,const ::std::vector<int64_t>&)> TypeIter;
    typedef ::cpputils::function<int64_t(const void*, size_t,const ::std::vector<int64_t>&)> TypeLimit;

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
        };

        friend class C1;

    }*const m_pFirstDimesion;

};


}}  // namespace cpputils { namespace  multifor {
