#include <iostream>
#include <functional>


template <typename T>
class vector_t {
public:
    vector_t<T>(int size_initial): size(size_initial), array(new T[size_initial]) {};
    int size;
    T* array;
    void vec_free() {
        delete[] array;
    }
};

class user_t {
public:
    int userId;
    int frequency;
    friend bool operator>(const user_t &l, const user_t &r)
    {
        return l.frequency > r.frequency;
    }
};

template <typename T>
class DefaultComparator
{
public:
    bool operator()(const T &l, const T &r)
    {
        return l > r;
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class heap_t {
public:
    heap_t(vector_t<T> vec_input): vec(vec_input) {
    }
    vector_t<T> vec;
    void buildHeap(Comparator cmp);
    void siftDown(int i, Comparator cmp);
    void siftUp(int i, Comparator cmp);
    T ExtractTop(Comparator cmp);
    void print_heap();
    void insert(user_t element, Comparator cmp);
};

template<typename T, typename Comparator>
void heap_t<T, Comparator>::siftDown(int i, Comparator cmp) {
    int left = 2 * i + 1;
    int right = 2 * i +2;
    int largest = i;

    if ((left < this->vec.size) && cmp(vec.array[left] , vec.array[i])) {
        largest = left;
    }
    if ((right < this->vec.size) && cmp(vec.array[right] , vec.array[largest])) {
        largest = right;
    }
    if (largest != i ) {
        std::swap(vec.array[i], vec.array[largest]);
        siftDown(largest, cmp);
    }

}

template<typename T, typename Comparator>
void heap_t<T, Comparator>::buildHeap(Comparator cmp) {
    for (int i = this->vec.size/2 - 1; i >= 0; --i) {
        siftDown(i, cmp);
    }
}

template<typename T, typename Comparator>
T heap_t<T, Comparator>::ExtractTop(Comparator cmp) {
    T result = vec.array[0];
    vec.array[0] = vec.array[vec.size - 1];
    vec.size -= 1;
    if (vec.size > 0) {
        siftDown(0, cmp);
    }
    return result;
}

template<typename T, typename Comparator>
void heap_t<T, Comparator>::print_heap() {
    for (int i = 0; i < vec.size; i++) {
        std::cout << vec.array[i] << " ";
    }
    std::cout << std::endl;

}

template<typename T, typename Comparator>
void heap_t<T, Comparator>::insert(user_t element, Comparator cmp) {
    vec.array[vec.size++] = element;
    siftUp(vec.size - 1, cmp);
}

template<typename T, typename Comparator>
void heap_t<T, Comparator>::siftUp(int i, Comparator cmp) {
    while (i > 0) {
        int parent = (i - 1)/2;
        if (!cmp(vec.array[i], vec.array[parent]))
            return;
        std::swap(vec.array[i], vec.array[parent]);
        i = parent;
    }
}


int main(int argc, const char * argv[]) {
    int n = 0;
    int k = 0;
    std::cin >> n;
    std::cin >> k;
    vector_t<user_t> vec(n);
    for (int i = 0; i < n ; i++)
    {
        std::cin >> vec.array[i].userId;
        std::cin >> vec.array[i].frequency;
    }
    heap_t<user_t> heap(vec);
    DefaultComparator<user_t> a;
    heap.buildHeap(a);
    vector_t<user_t> activeUsersDecentOrder(k);
    int* arr = new int[k];

    for (int i = 0; i < k; i++) {
        user_t u = heap.ExtractTop(a);
//        std::cout << u.userId << "\n";
        arr[i] = u.userId;
//        activeUsersDecentOrder.array[i] = u;
    }

    for (int i = k-1; i > 0; i--) {
        std::cout << arr[i] << " ";
    }
    std::cout << arr[0];
    delete[] arr;
    heap.vec.vec_free();
    return 0;
}
