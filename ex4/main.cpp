/*
 * Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
 * Определить за сколько подходов Вовочка съест все фрукты в корзине.
 * Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов. Затем K - "грузоподъемность".
 * Формат выходных данных. Неотрицательное число - количество подходов к корзине.
 *
 * Я в классе кучи оставил конструктор для инициализации вектором,
 * он в проге не используется, но я его решил оставить для полноты класса,
 * для самой структуры данных он нужен.
 *
 * */

#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>

namespace VectorNS {
    template<class T>
    class Vector {
    public:
        Vector();

        ~Vector();

        Vector(const Vector<T> &copying);

        Vector<T> &operator=(const Vector<T> &eq);

        void Add(const T &elem);

        int Size() const { return size; }

        T &operator[](int index);

        T &PopBack();

        bool IsEmpty() { return size == 0; }

    private:
        T *arr;
        int size;
        int capacity;

        void resizeVector();
    };

    template<class T>
    Vector<T>::Vector() {
        size = 0;
        capacity = 1;
        arr = new T[1];
    }

    template<class T>
    Vector<T>::Vector(const Vector<T> &copying) :
            size(copying.size),
            capacity(copying.capacity) {
        if (this == &copying) {
            return;
        }

        this->arr = new T[this->capacity];
        memcpy(this->arr, copying.arr, sizeof(T) * this->capacity);
    }

    template<class T>
    Vector<T>::~Vector() {
        delete[] arr;
    }

    template<class T>
    Vector<T> &Vector<T>::operator=(const Vector<T> &eq) {
        if (this == &eq) {
            return *this;
        }

        this->size = eq.size;
        this->capacity = eq.capacity;
        this->arr = new T[this->capacity];
        memcpy(this->arr, eq.arr, sizeof(T) * this->capacity);
        return *this;
    }

    template<class T>
    void Vector<T>::resizeVector() {
        T *tmp = new T[this->capacity * 2];
        memcpy(tmp, this->arr, sizeof(T) * this->capacity);

        T *old_ptr = this->arr;
        this->arr = tmp;
        delete[] old_ptr;

        this->capacity *= 2;
    }

    template<class T>
    void Vector<T>::Add(const T &elem) {
        if (size == capacity) {
            resizeVector();
        }

        arr[size] = elem;
        ++size;
    }

    template<class T>
    T &Vector<T>::operator[](int index) {
        assert(index < size);
        return arr[index];
    }

    template<class T>
    T &Vector<T>::PopBack() {
        --size;
        return arr[size];
    }
}

namespace HeapNS {
    template<class T>
    bool isLessDefault(const T &l, const T &r) {
        return l <= r;
    }

    template<class T>
    class Heap {
    public:
        explicit Heap(bool (*_isLess)(const T &l, const T &r) = isLessDefault) : arr(VectorNS::Vector<T>()),
                                                                                 isLess(_isLess) {}

        Heap(const VectorNS::Vector<T> &_arr, bool (*_isLess)(const T &l, const T &r));

        void Insert(const T &elem);

        T &ShowTop();

        T ExtractMax();

        bool IsEmpty() { return arr.IsEmpty(); }

        int Size() const { return arr.Size(); }

    private:
        VectorNS::Vector<T> arr;

        bool (*isLess)(const T &l, const T &r);

        void buildHeap();

        void siftDown(int i);

        void siftUp(int i);
    };

    template<class T>
    void Heap<T>::siftDown(int i) {
        int largest = i;
        while (true) {
            int left = 2 * largest + 1;
            int right = 2 * largest + 2;
            int prev_largest = largest;
            if (left < arr.Size() && !isLess(arr[left], arr[largest])) {
                largest = left;
            }

            if (right < arr.Size() && !isLess(arr[right], arr[largest])) {
                largest = right;
            }

            if (prev_largest == largest) {
                return;
            }

            std::swap(arr[prev_largest], arr[largest]);
        }
    }

    template<class T>
    void Heap<T>::siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (isLess(arr[i], arr[parent])) {
                return;
            }
            std::swap(arr[i], arr[parent]);
            i = parent;
        }
    }


    template<class T>
    void Heap<T>::buildHeap() {
        for (int i = (int) arr.Size() / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    template<class T>
    Heap<T>::Heap(const VectorNS::Vector<T> &_arr, bool (*_isLess)(const T &l, const T &r))
            : arr(_arr), isLess(_isLess) {
        buildHeap();
    }

    template<class T>
    void Heap<T>::Insert(const T &elem) {
        arr.Add(elem);
        siftUp((int) arr.Size() - 1);
    }

    template<class T>
    T &Heap<T>::ShowTop() {
        return arr[0];
    }

    template<class T>
    T Heap<T>::ExtractMax() {
        T ret_val = arr[0];

        const T &tmp = arr.PopBack();
        if (!arr.IsEmpty()) {
            arr[0] = tmp;
            siftDown(0);
        }

        return ret_val;
    }

}

int eating(HeapNS::Heap<int> &basket, int lifting_capacity) {
    if (lifting_capacity <= 0) {
        return 0;
    }

    int count = 0;
    while (!basket.IsEmpty()) {
        ++count;

        int capacity = lifting_capacity;
        int curr_basket_size = basket.Size();
        VectorNS::Vector<int> hands;
        for (int i = 0; !basket.IsEmpty() && capacity - basket.ShowTop() >= 0 && i < curr_basket_size; ++i) {
            int fruit = basket.ExtractMax();
            capacity -= fruit;
            if (fruit > 1) {
                hands.Add(fruit / 2);
            }
        }

        for (int i = 0; i < hands.Size(); ++i) {
            basket.Insert(hands[i]);
        }
    }

    return count;
}

bool isLessExample(const int &l, const int &r) {
    return l < r;
}

int main() {
    int amount;
    std::cin >> amount;

    HeapNS::Heap<int> basket(isLessExample);
    for (int i = 0; i < amount; ++i) {
        int tmp;
        std::cin >> tmp;
        basket.Insert(tmp);
    }

    int capacity;
    std::cin >> capacity;

    std::cout << eating(basket, capacity) << std::endl;
    return 0;
}
