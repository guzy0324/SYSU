#include <iostream>
#include <omp.h>
#define Q_MAX_SIZE 10
#define PRODUCER_NUM 4
#define CONSUMER_NUM 3
#define ITEM_NUM 3
int itemCount = 0;
struct Buffer
{
    int queue[Q_MAX_SIZE];
    size_t front;
    size_t back;
    omp_lock_t front_mutex;
    omp_lock_t back_mutex;
    Buffer();
    ~Buffer();
    void push(int item);
    int pop();
};
Buffer::Buffer()
{
    front = back = 0;
    omp_init_lock(&front_mutex);
    omp_init_lock(&back_mutex);
}
Buffer::~Buffer()
{
    omp_destroy_lock(&front_mutex);
    omp_destroy_lock(&back_mutex);
}
void Buffer::push(int item)
{
    queue[back] = item;
    back = (back + 1) % Q_MAX_SIZE;
}
int Buffer::pop()
{
    int item = queue[front];
    front = (front + 1) % Q_MAX_SIZE;
    return item;
}
int main()
{
    Buffer *bp = new Buffer;
    omp_set_nested(1);
#pragma omp parallel sections
    {
#pragma omp section
        {
#pragma omp parallel for
            for (int i = 0; i < PRODUCER_NUM; i++)
            {
                for (int item = 0; item < ITEM_NUM; item++)
                {
                    printf("producer: %d, thread: %d, item: %d\n", i, omp_get_thread_num(), item);
                    omp_set_lock(&(bp->back_mutex));
                    while (bp->front == (bp->back + 1) % Q_MAX_SIZE)
                        ;
                    bp->push(item);
                    omp_unset_lock(&(bp->back_mutex));
                }
            }
        }
#pragma omp section
        {
#pragma omp parallel for
            for (int i = 0; i < CONSUMER_NUM; i++)
            {
                for (int j = 0; j < PRODUCER_NUM * ITEM_NUM / CONSUMER_NUM; j++)
                {
                    omp_set_lock(&(bp->front_mutex));
                    while (bp->front == bp->back)
                        ;
                    int item = bp->pop();
                    omp_unset_lock(&(bp->front_mutex));
                    printf("consumer: %d, thread: %d, item: %d\n", i, omp_get_thread_num(), item);
                }
            }
        }
    }
    delete bp;
}