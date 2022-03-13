#ifndef list_queue_HPP
#define list_queue_HPP


#include "iqueue.h"
#include "LinkedList.h"

namespace data_structures
{
    template <class T>
    class ListQueue final : public IQueue<T>
    {
    public:
        ListQueue() = default;
        ListQueue(const ListQueue& copy);
        ListQueue& operator=(const ListQueue& rhs);
        ListQueue(ListQueue&& copy) noexcept;
        ListQueue& operator=(ListQueue&& rhs) noexcept;
        ~ListQueue() = default;

        void Enqueue(T data) override;
        T Dequeue() override;
        T& Front() override;
        void Clear() noexcept override;
        size_t Size() const noexcept override;
        bool Empty() const noexcept override;
        T Peek(); //removed overrride

    private:
        LinkedList<T> queue_;

    };
    template<class T>
     ListQueue<T>::ListQueue(const ListQueue& copy)
    {
         *this = copy;
    }
    template<class T>
    ListQueue<T>& ListQueue<T>::operator=(const ListQueue& rhs)
    {
        queue_ = rhs.queue_;
        return *this;
    }
    template<class T>
     ListQueue<T>::ListQueue(ListQueue&& copy) noexcept
    {
         *this = std::move(copy);
     }
    template<class T>
    ListQueue<T>& ListQueue<T>:: operator=(ListQueue&& rhs) noexcept
    {
        queue_ = std::move(rhs.queue_);

    }
    template<class T>
     void ListQueue<T>::Enqueue(T data)
    {
         queue_.Append(data);
         //append ez pz
    }
    template<class T>
     T ListQueue<T>::Dequeue()
    {
       auto temp = queue_.First();
         queue_.RemoveFirst(); //remove first item, then return it at same time

         return temp;
    }
    template<class T>
     T& ListQueue<T>::Front()
    {
        // TODO: insert return statement here
         return queue_.First();
    }
    template<class T>
     void ListQueue<T>::Clear() noexcept
    {
         queue_.Clear();
         //ez
    }
    template<class T>
     size_t ListQueue<T>::Size() const noexcept
    {
        return queue_.Size();
    }
    template<class T>
     bool ListQueue<T>::Empty() const noexcept
    {
        return queue_.Empty();
    }
     template <class T>
     T ListQueue<T>::Peek()
     {

         return queue_.Last();
     }

}
#endif