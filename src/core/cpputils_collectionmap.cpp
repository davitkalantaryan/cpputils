//
// repo:            cpputils
// file:			cpputils_named_types.cpp
// path:			src/core/cpputils_named_types.cpp
// created on:		2024 Dec 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#include <cpputils/collectionmap.hpp>
#include <cinternal/disable_compiler_warnings.h>
#include <new>
#include <stddef.h>
#include <string.h>
#include <cinternal/undisable_compiler_warnings.h>

namespace cpputils { namespace collectionmap{


static size_t WithAnyKeyHasherStatic(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static bool WithAnyKeyIsKeyTheSameStatic(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT;
static bool WithAnyKeyStoreKeyStatic(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static void WithAnyKeyStoreKeyUnstoreStatic(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;


Base::~Base() noexcept
{
    delete m_clmp_data_p;
}


Base::Base()
    :
    m_clmp_data_p(new CollectionMap_p())
{
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

WithIntKey::WithIntKey(size_t a_numberOfBaskets,TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    Base()
{
    m_clmp_data_p->m_hash = CInternalHashCreateSmlIntEx(a_numberOfBaskets, a_allocator, a_deallocator);
    if (!(m_clmp_data_p->m_hash)) {
        throw ::std::bad_alloc();
    }
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

WithAnyKey::WithAnyKey(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
    :
    Base()
{
    m_clmp_data_p->m_hash = CInternalHashCreateAnyEx(
        a_numberOfBaskets,
        &WithAnyKeyHasherStatic, 
        &WithAnyKeyIsKeyTheSameStatic,
        &WithAnyKeyStoreKeyStatic, 
        &WithAnyKeyStoreKeyUnstoreStatic, 
        a_allocator, a_deallocator);
    if (!(m_clmp_data_p->m_hash)) {
        throw ::std::bad_alloc();
    }
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

CollectionMap_p::~CollectionMap_p() noexcept
{
    __private::ItemVoid* pItemNext, * pItem;

    for (int i(0); i < m_numberOfTypes; ++i) {
        pItem = m_lists[i].m_first;
        while (pItem) {
            pItemNext = static_cast<__private::ItemVoid*>(pItem->next);
            CInternalHashRemoveDataEx(m_hash, pItem->hashIter);
            pItem->~ItemVoid();
            (*(m_hash->deallocator))(pItem);
            pItem = pItemNext;
        }  //  while(pItem){
    }  //  for (size_t i(0); i < m_clmp_data_p->m_numberOfTypes; ++i) {

    m_hash->deallocator(m_lists);

    CInternalHashDestroy(m_hash);
}


CollectionMap_p::CollectionMap_p()
    :
    m_hash(CPPUTILS_NULL),
    m_bufferSize(0),
    m_numberOfTypes(0),
    m_lists(CPPUTILS_NULL)
{
    (void)m_reserved01;
}


const Base::Item<void>* CollectionMap_p::getFirstByTypeIndex(int a_typeIndex)const
{
    if (a_typeIndex < m_numberOfTypes) {
        return m_lists[a_typeIndex].m_first;
    }  //  if (a_typeIndex < m_numberOfTypes) {
    return CPPUTILS_NULL;
}


const Base::Item<void>* CollectionMap_p::getLastByTypeIndex(int a_typeIndex)const
{
    if (a_typeIndex < m_numberOfTypes) {
        return m_lists[a_typeIndex].m_last;
    }  //  if (a_typeIndex < m_numberOfTypes) {
    return CPPUTILS_NULL;
}


void CollectionMap_p::AddToTheListBegPrivate(Base::Item<void>* CPPUTILS_ARG_NN a_item_p, int a_typeIndex)
{
    const int requieredNumberOfTypes = a_typeIndex + 1;
    if (requieredNumberOfTypes > m_numberOfTypes) {
        const size_t requieredBufferSize = static_cast<size_t>(requieredNumberOfTypes) * sizeof(__private::SnglListItem);
        char* const pTmpList = (char*)m_hash->allocator(requieredBufferSize);
        if (!pTmpList) {
            throw ::std::bad_alloc();
        }
        memcpy(pTmpList, m_lists, m_bufferSize);
        memset(pTmpList + m_bufferSize, 0, (requieredBufferSize - m_bufferSize));
        m_hash->deallocator(m_lists);
        m_lists = (__private::SnglListItem*)pTmpList;
        m_bufferSize = requieredBufferSize;
        m_numberOfTypes = requieredNumberOfTypes;
    }  //  if (a_typeIndex >= (m_clmp_data_p->m_numberOfTypes)) {

    a_item_p->prev = CPPUTILS_NULL;
    a_item_p->next = m_lists[a_typeIndex].m_first;
    if (m_lists[a_typeIndex].m_first) {
        m_lists[a_typeIndex].m_first->prev = a_item_p;
    }
    else {
        m_lists[a_typeIndex].m_last = (__private::ItemVoid*)a_item_p;
    }
    m_lists[a_typeIndex].m_first = (__private::ItemVoid*)a_item_p;
    ++(m_lists[a_typeIndex].m_count);
}


void CollectionMap_p::AddBegWithKnownHash(int a_typeIndex, void* CPPUTILS_ARG_NN a_pNewItem, void* CPPUTILS_ARG_NN a_key, size_t a_keySize, size_t a_hash)
{
    __private::ItemVoid* const pNewItemVoid = (__private::ItemVoid*)a_pNewItem;
    pNewItemVoid->prev = pNewItemVoid->next = CPPUTILS_NULL;
    pNewItemVoid->hashIter = CPPUTILS_NULL;

    pNewItemVoid->hashIter = CInternalHashAddDataWithKnownHash(m_hash, a_pNewItem, a_key, a_keySize, a_hash);
    if (!(pNewItemVoid->hashIter)) {
        throw ::std::bad_alloc();
    }

    AddToTheListBegPrivate(pNewItemVoid, a_typeIndex);
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

static size_t WithAnyKeyHasherStatic(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    const __private::SWithAnyKeyKeyExt* const pKeyExt = (const __private::SWithAnyKeyKeyExt*)a_key;
    (void)a_keySize;
    const uint64_t typeIndex = (uint64_t)(pKeyExt->typeIndex);
    const uint64_t hashByRawKey = (uint64_t)pKeyExt->fncHasher(pKeyExt->getKeyRawPtr<void>());
    const uint64_t wholeHash = (typeIndex << 32) | ((uint64_t)((uint32_t)hashByRawKey));
    return (size_t)wholeHash;
}


static bool WithAnyKeyIsKeyTheSameStatic(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT
{
    const __private::SWithAnyKeyKeyExt* const pKeyExt1 = (const __private::SWithAnyKeyKeyExt*)a_key1;
    const __private::SWithAnyKeyKeyExt* const pKeyExt2 = (const __private::SWithAnyKeyKeyExt*)a_key2;
    (void)a_keySize1;
    (void)a_keySize2;
    return pKeyExt1->fncIsEq(pKeyExt1->getKeyRawPtr<void>(), pKeyExt2->getKeyRawPtr<void>());
}


// SWithAnyKeyKeyExt* CPPUTILS_ARG_NN a_this_p, const void* a_key

static bool WithAnyKeyStoreKeyStatic(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    const __private::SWithAnyKeyKeyExt* const pKeyExt = (const __private::SWithAnyKeyKeyExt*)a_key;
    __private::SWithAnyKeyKeyExt* const pKeyToStoreExt = __private::SWithAnyKeyKeyExt::MakeCopy(*pKeyExt);
    *a_pKeyStore = (void*)pKeyToStoreExt;

    (void)a_pKeySizeStore;
    (void)a_keySize;

    return true;
}


static void WithAnyKeyStoreKeyUnstoreStatic(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    __private::SWithAnyKeyKeyExt* const pKeyExt = (__private::SWithAnyKeyKeyExt*)a_key;
    delete pKeyExt;
    (void)a_keySize;
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

namespace __private{

CPPUTILS_EXPORT int GetNextIndex(void) noexcept
{
    static int snCounter = 0;
    return (snCounter++);
}


SWithAnyKeyKeyExt::~SWithAnyKeyKeyExt()
{
    (*(this->fncDeleteKey))(this->keyRaw_p);
}


SWithAnyKeyKeyExt::SWithAnyKeyKeyExt(
        const void* a_keyRaw_p, TypeWithAnyKeyHasher a_fncHasher,
        TypeWithAnyKeyIsMemoriesIdentical a_fncIsEq, TypeWithAnyKeyDublicateKey a_fncDublicateKey,
        TypeWithAnyKeyDeleteKey a_fncDeleteKey, int a_typeIndex) noexcept
    :
    fncHasher(a_fncHasher),
    fncIsEq(a_fncIsEq),
    typeIndex((size_t)a_typeIndex),
    keyRaw_p((void*)a_keyRaw_p),
    fncDublicateKey(a_fncDublicateKey),
    fncDeleteKey(a_fncDeleteKey)
{
}


SWithAnyKeyKeyExt* SWithAnyKeyKeyExt::MakeCopy(const SWithAnyKeyKeyExt& a_cM)
{
    SWithAnyKeyKeyExt* const retVal = new SWithAnyKeyKeyExt(a_cM);
    if (a_cM.keyRaw_p) {
        retVal->keyRaw_p = a_cM.fncDublicateKey(a_cM.keyRaw_p);
    }
    return retVal;
}


}  //  namespace collectionmap{ namespace __private{ 


}}  //  namespace cpputils { namespace collectionmap{
