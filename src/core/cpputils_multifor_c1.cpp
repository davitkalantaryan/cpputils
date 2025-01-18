//
// file:			cpputils_multifor_c1.cpp
// path:			src/core/cpputils_multifor.cpp
// created on:		2021 Sep 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cpputils/multifor/c1.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <assert.h>
#include <cinternal/undisable_compiler_warnings.h>


namespace cpputils { namespace  multifor {



/*///////////////////////////////////////////////////////////////////////////////////////////////////*/

C1::C1(size_t a_deepness, TypeIter a_iter, TypeLimit a_min, TypeLimit a_max)
    :
      m_pFirstDimesion(new Dimension(this,a_deepness,a_iter,a_min,a_max))
{
    assert(a_deepness);
}


C1::~C1()
{
    delete m_pFirstDimesion;
}


void C1::Break()
{
    m_pFirstDimesion->m_pCore->shouldMakeIter = false;
}


void C1::MakeIteation(const void* a_clbkData)
{
    m_pFirstDimesion->m_pCore->clbkData = a_clbkData;
    m_pFirstDimesion->m_pCore->shouldMakeIter = true;
    m_pFirstDimesion->Initialize();
    m_pFirstDimesion->NextIterations();
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////*/

C1::Dimension::Dimension(C1* a_pParent, size_t a_deepness, TypeIter a_iter, TypeLimit a_min, TypeLimit a_max)
    :
      m_pCore(new Core),
      m_dimensionIndex(0)
{
    assert(a_deepness);
    m_pCore->pParent = a_pParent;
    m_pCore->clbkData = nullptr;
    m_pCore->iter = a_iter;
    m_pCore->limitMin = a_min;
    m_pCore->limitMax = a_max;
    m_pCore->deepness = a_deepness;
    m_pCore->iterationPoints.resize(a_deepness);
    if(a_deepness<2){
        m_pNextDimension = nullptr;
    }
    else{
        m_pNextDimension = new Dimension(a_deepness-1,m_pCore,1);
    }
}


C1::Dimension::Dimension(size_t a_deepness, Core* a_pCore, size_t a_dimensionIndex)
    :
      m_pCore(a_pCore),
      m_dimensionIndex(a_dimensionIndex)
{
    if(a_deepness<2){
        m_pNextDimension = nullptr;
    }
    else{
        m_pNextDimension = new Dimension(a_deepness-1,m_pCore,a_dimensionIndex+1);
    }
}


C1::Dimension::~Dimension()
{
    delete m_pNextDimension;
    if(m_dimensionIndex==0){
        delete m_pCore;
    }
}


void C1::Dimension::Initialize()
{
    m_currentIterationPoint = m_pCore->limitMin(m_pCore->clbkData,m_dimensionIndex,m_pCore->iterationPoints);
    m_iterationPointsRightEnd = m_pCore->limitMax(m_pCore->clbkData,m_dimensionIndex,m_pCore->iterationPoints);
}


void C1::Dimension::NextIterations()
{
    if(m_pNextDimension){

        for(;(m_currentIterationPoint<m_iterationPointsRightEnd)&&m_pCore->shouldMakeIter;++m_currentIterationPoint){
            m_pCore->iterationPoints[m_dimensionIndex] = m_currentIterationPoint;
            m_pNextDimension->Initialize();
            m_pNextDimension->NextIterations();
        }
    }
    else{
        for(;(m_currentIterationPoint<m_iterationPointsRightEnd)&&m_pCore->shouldMakeIter;++m_currentIterationPoint){
            m_pCore->iterationPoints[m_dimensionIndex] = m_currentIterationPoint;
            m_pCore->iter(m_pCore->clbkData,m_dimensionIndex,m_pCore->iterationPoints);
        }
    }
}



}}  // namespace cpputils { namespace  multifor {
