//
// file:			cpputils_multifor.cpp
// path:			src/core/cpputils_multifor.cpp
// created on:		2021 Sep 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include "cpputils/multifor.hpp"
#include <assert.h>


namespace cpputils {


/*///////////////////////////////////////////////////////////////////////////////////////////////////*/

MultiFor::MultiFor(size_t a_deepness, TypeIter a_iter, TypeLimit a_min, TypeLimit a_max)
    :
      m_pFirstDimesion(new Dimension(this,a_deepness,a_iter,a_min,a_max))
{
    assert(a_deepness);
}


MultiFor::~MultiFor()
{
    delete m_pFirstDimesion;
}


void MultiFor::Break()
{
    m_pFirstDimesion->m_pCore->shouldMakeIter = false;
}


void MultiFor::MakeIteation(const void* a_clbkData)
{
    m_pFirstDimesion->m_pCore->clbkData = a_clbkData;
    m_pFirstDimesion->m_pCore->shouldMakeIter = true;
    m_pFirstDimesion->Initialize();
    m_pFirstDimesion->NextIterations();
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////*/

MultiFor::Dimension::Dimension(MultiFor* a_pParent, size_t a_deepness, TypeIter a_iter, TypeLimit a_min, TypeLimit a_max)
    :
      m_pCore(a_deepness?(new Core):nullptr),
      m_dimensionIndex(0)
{
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


MultiFor::Dimension::Dimension(size_t a_deepness, Core* a_pCore, size_t a_dimensionIndex)
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


MultiFor::Dimension::~Dimension()
{
    delete m_pNextDimension;
    if(m_dimensionIndex==0){
        delete m_pCore;
    }
}


void MultiFor::Dimension::Initialize()
{
    m_currentIterationPoint = m_pCore->limitMin(m_pCore->clbkData,m_dimensionIndex,m_pCore->iterationPoints);
    m_iterationPointsRightEnd = m_pCore->limitMax(m_pCore->clbkData,m_dimensionIndex,m_pCore->iterationPoints);
}


void MultiFor::Dimension::NextIterations()
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



}  // namespace cpputils {
