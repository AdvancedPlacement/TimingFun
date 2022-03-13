#ifndef IQUEUE_HPP
#define IQUEUE_HPP

namespace data_structures
{
    template <class T>
    class IQueue
    {
    public:
        virtual ~IQueue() = default;
        virtual void Enqueue(T data) = 0;
        virtual T Dequeue() = 0;
        virtual T& Front() = 0;
        virtual size_t Size() const noexcept = 0;
        virtual bool Empty() const noexcept = 0;
        virtual void Clear() noexcept = 0;
    };

}
#endif