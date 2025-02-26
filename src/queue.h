#ifndef QUEUE_H
#define QUEUE_H

    #include <vector>

    using namespace std;

    template <typename T>
    class Queue_
    {

        vector<T> queue;
    
    public:

        Queue_()
        {
        }

        ~Queue_()
        {
        }
        
        void Enqueue(T item)
        {
            queue.push_back(item);
        }
        
        T Dequeue(){
            T item = queue[0];
            queue.erase(queue.begin());
            return item;
        }

        void Clear(){
            queue.clear();
        }

        bool Contains(T item){
            return find(queue.begin(), queue.end(), item) != queue.end();
        }

        uint Length(){
            return queue.size();
        }

    };

#endif