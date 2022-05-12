// Prob 1. heap을 이용한 정렬 vs Selection 정렬 비교
// Prob 2. 하프만 코드 인코딩, 디코딩
#define PROB 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if PROB == 1

#define SIZE 5

typedef int element;

typedef struct heap
{
    element data[SIZE + 1]; // 생성되는 데이터 개수는 SIZE 만큼인데 힙은 첫번째 인덱스(0)을 사용하지 않으므로
    int count;              // SIZE - 1 개 만큼이 됨. 때문에 +1 을 해줌.
} heap;

heap *create();
void init(heap *);
int is_empty(heap *);
int is_full(heap *);
void insert(heap *, element);
element delete_heap(heap *);

void heap_sort(element *, element *, int);
void selection_sort(element *, element *, int);

int main(void)
{
    element *list, *sorted_list;
    int i, s_time, e_time;
    srand(15);
    list = (element *)malloc(sizeof(element) * SIZE);
    sorted_list = (element *)malloc(sizeof(element) * SIZE);
    for (i = 0; i < SIZE; i++)
        list[i] = rand();

    s_time = clock();
    heap_sort(list, sorted_list, SIZE);
    e_time = clock();
    printf("Heap Sort 걸린 시간 : %d msec\n", e_time - s_time);

    for (int i = 0; i < SIZE; ++i)
        printf("%d ", sorted_list[i]);
    printf("\n");

    s_time = clock();
    selection_sort(list, sorted_list, SIZE);
    e_time = clock();
    printf("Selection Sort 걸린 시간 : %d msec\n", e_time - s_time);

    for (int i = 0; i < SIZE; ++i)
        printf("%d ", sorted_list[i]);
    printf("\n");

    return 0;
}

heap *create()
{
    return (heap *)malloc(sizeof(heap));
}

void init(heap *heap)
{
    heap->count = 0;
}

int is_empty(heap *heap)
{
    if (heap->count == 0)
        return 1;
    else
        return 0;
}

int is_full(heap *heap)
{
    if (heap->count == SIZE + 1)
        return 1;
    else
        return 0;
}

void insert(heap *heap, element item)
{
    int idx;
    idx = ++heap->count;

    while ((idx != 1) && (item < heap->data[idx / 2]))
    {
        heap->data[idx] = heap->data[idx / 2];
        idx /= 2;
    }
    heap->data[idx] = item;
}

element delete_heap(heap *heap)
{
    int parent, child;
    element item, tmp;

    item = heap->data[1];
    tmp = heap->data[heap->count--];
    parent = 1;
    child = 2;
    while (child <= heap->count)
    {
        if (child < heap->count && heap->data[child] < heap->data[child + 1])
            ++child;
        if (tmp >= heap->data[child])
            break;
        heap->data[parent] = heap->data[child];
        parent = child;
        child *= 2;
    }
    heap->data[parent] = tmp;
    return item;
}

void heap_sort(element *list, element *sorted_list, int size)
{
    heap *h = create();
    init(h);
    for (int i = 0; i < size; ++i)
        insert(h, list[i]);

    for (int i = 0; i < size; ++i)
        sorted_list[i] = delete_heap(h);
}

void selection_sort(element *list, element *sorted_list, int size)
{
    int temp;
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (list[i] > list[j])
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
        sorted_list[i] = list[i];
    }
}

#elif PROB == 2

#endif