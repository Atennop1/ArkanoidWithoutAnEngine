#ifndef ARKANOIDWITHOUTANENGINE_ABA38CA09CAF4405AB79274B4E04045B
#define ARKANOIDWITHOUTANENGINE_ABA38CA09CAF4405AB79274B4E04045B

template<class T>
class SharedPointer
{
private:
    T* m_resource_ = nullptr;
    int* m_references_count_ = nullptr;

    void Clear()
    {
        if (m_references_count_ != nullptr && (--*m_references_count_) > 0)
            return;

        delete m_references_count_;
        delete m_resource_;
    }

    void Move(SharedPointer<T> &pointer)
    {
        m_references_count_ = pointer.m_references_count_;
        m_resource_ = pointer.m_resource_;
        pointer.m_resource_ = nullptr;
        pointer.m_references_count_ = nullptr;
    }

    void Assign(T *resource, int *references_count)
    {
        if (resource == nullptr || references_count == nullptr)
            return;

        m_resource_ = resource;
        m_references_count_ = references_count;
        ++(*m_references_count_);
    }

public:
    explicit SharedPointer(T* resource = nullptr, int* references_count = new int(0)) { Assign(resource, references_count); }
    SharedPointer(const SharedPointer<T> &pointer) { Assign(pointer.m_resource_, pointer.m_references_count_); }
    SharedPointer(SharedPointer<T> &&pointer) { Move(pointer); }
    ~SharedPointer() { Clear(); }

    T& operator*() { return *m_resource_; }
    const T& operator*() const { return *m_resource_; }

    T* operator->() { return m_resource_; }
    const T* operator->() const { return m_resource_; }

    T* Get() { return m_resource_; }
    const T* Get() const { return m_resource_; }

    friend bool operator==(const SharedPointer<T> &first, const SharedPointer<T> &second) { return first.Get() == second.Get(); }
    friend bool operator==(const SharedPointer<T> &&first, const SharedPointer<T> &&second) { return operator==(first, second);}

    template<class U>
    operator SharedPointer<U>() { return SharedPointer<U>(dynamic_cast<U*>(m_resource_), m_references_count_); }

    SharedPointer<T>& operator=(T* pointer)
    {
        if (pointer != m_resource_)
            return *this;

        Clear();
        Assign(pointer, new int(0));
        return *this;
    }

    SharedPointer<T>& operator=(const SharedPointer<T> &pointer)
    {
        if (&pointer == this)
            return *this;

        Clear();
        Assign(pointer.m_resource_, pointer.m_references_count_);
        return *this;
    }

    SharedPointer<T>& operator=(SharedPointer<T> &&pointer)
    {
        if (&pointer == this)
            return *this;

        Clear();
        Move(pointer);
        return *this;
    }
};

#endif
