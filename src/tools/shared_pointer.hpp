#ifndef ARKANOIDWITHOUTANENGINE_ABA38CA09CAF4405AB79274B4E04045B
#define ARKANOIDWITHOUTANENGINE_ABA38CA09CAF4405AB79274B4E04045B

#include <iostream>

template<class T>
class SharedPointer
{
private:
    T* m_resource_ = nullptr;
    int* m_references_count_ = nullptr;

    void Clear();
    void Assign(T *resource, int *references_count);

public:
    explicit SharedPointer(T* resource = nullptr, int* references = new int(0));
    ~SharedPointer();

    SharedPointer(const SharedPointer<T> &pointer);
    SharedPointer(SharedPointer<T> &&pointer);

    SharedPointer<T>& operator=(T* pointer);
    SharedPointer<T>& operator=(const SharedPointer<T> &pointer);
    SharedPointer<T>& operator=(SharedPointer<T> &&pointer);

    T& operator*();
    const T& operator*() const;

    T* operator->();
    const T* operator->() const;

    T* Get();
    const T* Get() const;

    template<class U>
    operator SharedPointer<U>();
};

template<class T>
void SharedPointer<T>::Clear()
{
    if (m_references_count_ == nullptr)
        return;

    --(*m_references_count_);
    if ((*m_references_count_) > 0)
        return;

    delete m_references_count_;
    if (m_resource_ != nullptr)
        delete m_resource_;
}

template<class T>
void SharedPointer<T>::Assign(T *resource, int *references_count)
{
    if (references_count == nullptr)
        return;

    m_resource_ = resource;
    m_references_count_ = references_count;
    ++(*m_references_count_);
}

template<class T>
SharedPointer<T>::SharedPointer(T *resource, int *references_count) { Assign(resource, references_count); }

template<class T>
SharedPointer<T>::~SharedPointer() { Clear(); }

template<class T>
SharedPointer<T>::SharedPointer(const SharedPointer<T> &pointer) { Assign(pointer.m_resource_, pointer.m_references_count_); }

template<class T>
SharedPointer<T>::SharedPointer(SharedPointer<T> &&pointer)
{
    m_references_count_ = pointer.m_references_count_;
    m_resource_ = pointer.m_resource_;
    pointer.m_resource_ = nullptr;
    pointer.m_references_count_ = nullptr;
}

template<class T>
SharedPointer<T>& SharedPointer<T>::operator=(T *pointer)
{
    if (pointer == m_resource_)
        return *this;

    Clear();
    Assign(pointer, new int(0));
    return *this;
}

template<class T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T> &pointer)
{
    if (&pointer == this)
        return *this;

    Clear();
    Assign(pointer.m_resource_, pointer.m_references_count_);
    return *this;
}

template<class T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T> &&pointer)
{
    if (&pointer == this)
        return *this;

    Clear();
    m_references_count_ = pointer.m_references_count_;
    m_resource_ = pointer.m_resource_;
    pointer.m_resource_ = nullptr;
    pointer.m_references_count_ = nullptr;
    return *this;
}

template<class T>
T& SharedPointer<T>::operator*() { return *m_resource_; }

template<class T>
const T& SharedPointer<T>::operator*() const { return *m_resource_; }

template<class T>
T* SharedPointer<T>::operator->() { return m_resource_; }

template<class T>
const T* SharedPointer<T>::operator->() const { return m_resource_; }

template<class T>
const T *SharedPointer<T>::Get() const { return m_resource_; }

template<class T>
T *SharedPointer<T>::Get() { return m_resource_; }

template<class T>
template<class U>
SharedPointer<T>::operator SharedPointer<U>()
{
    auto new_pointer = dynamic_cast<U*>(m_resource_);
    return SharedPointer<U>(new_pointer, m_references_count_);
}

#endif
