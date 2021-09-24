//
// file:			cpputils_multifor.cpp
// path:			src/core/cpputils_multifor.cpp
// created on:		2021 Sep 24
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include "cpputils/multifor.hpp"


namespace cpputils {


/*///////////////////////////////////////////////////////////////////////////////////////////////////*/

MultiFor::~MultiFor()
{
    delete m_pChild;
    if(m_index==0){
        delete m_pCore;
    }
}


MultiFor::MultiFor(size_t a_deepness, TypeIter a_iter, TypeLimit a_min, TypeLimit a_max)
    :
      m_pCore(a_deepness?(new Core):nullptr),
      m_index(0)
{
    if(m_pCore){
        m_pCore->pParent = this;
        m_pCore->clbkData = nullptr;
        m_pCore->iter = a_iter;
        m_pCore->limitMin = a_min;
        m_pCore->limitMax = a_max;
        m_pCore->deepness = a_deepness;
        m_pCore->iterValues.resize(a_deepness);
        if(a_deepness<2){
            m_pChild = nullptr;
        }
        else{
            m_pChild = new MultiFor(a_deepness-1,m_pCore,1);
        }
    }
    else{
        m_pChild = nullptr;
    }
}


MultiFor::MultiFor(size_t a_deepness, Core* a_pCore, size_t a_index)
    :
      m_pCore(a_pCore),
      m_index(a_index)
{
    if(a_deepness<2){
        m_pChild = nullptr;
    }
    else{
        m_pChild = new MultiFor(a_deepness-1,m_pCore,a_index+1);
    }
}


void MultiFor::NextIterations()
{
    if(m_pChild){

        for(;(m_currentValue<m_currentRightEnd)&&m_pCore->shouldMakeIter;++m_currentValue){
            m_pCore->iterValues[m_index] = m_currentValue;
            m_pChild->Initialize();
            m_pChild->NextIterations();
        }

        //if((m_currentValue<m_currentRightEnd)&&m_pCore->shouldMakeIter){
        //    m_pCore->iterValues[m_index] = m_currentValue++;
        //    m_pChild->Initialize();
        //    m_pChild->NextIterations();
        //}
    }
    else{
        for(;(m_currentValue<m_currentRightEnd)&&m_pCore->shouldMakeIter;++m_currentValue){
            m_pCore->iterValues[m_index] = m_currentValue;
            m_pCore->iter(m_pCore->clbkData,m_pCore->pParent,m_pCore->iterValues);
        }
    }
}


void MultiFor::Initialize()
{
    m_currentValue = m_pCore->limitMin(m_pCore->clbkData,m_index,m_pCore->iterValues);
    m_currentRightEnd = m_pCore->limitMax(m_pCore->clbkData,m_index,m_pCore->iterValues);
}


void MultiFor::Break()
{
    m_pCore->shouldMakeIter = false;
}


void MultiFor::MakeIteation(const void* a_clbkData)
{
    if(m_pCore){
        m_pCore->clbkData = a_clbkData;
        m_pCore->shouldMakeIter = true;
        Initialize();
        NextIterations();
    }
}



}  // namespace cpputils {
