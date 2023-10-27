#include <iostream>

template <typename T>
class Grid final {
private:
    using value_type = T;
    T * data;

public:
    unsigned dim;
    using size_type = unsigned;
    size_type * const sizes = new size_type[dim];

    size_type n(){
        size_type c = 1;
        for (int i = 0; i < dim; ++i) {
            c *= sizes[i];
        }
        return c;
    }

    // конструкторы

    Grid(T * data, unsigned dim, size_type * sizes):
            data(data), dim(dim), sizes(sizes) {  }

    Grid(T& data):
            data(data), dim(1), sizes(new size_type[1]) {
        sizes[0] = 1;
    }

    Grid(unsigned dim, size_type * sizes):
            data(new T[n()]), dim(dim), sizes(sizes) {  }

    Grid(T& t, unsigned dim, size_type * sizes):
            data(new T[n()]), dim(dim), sizes(sizes) {
        for (int i = 0; i < n(); ++i) {
            data[i] = t;
        }
    }

    // конструктор копирования
    Grid(Grid<T> const& G):
            data(G.data), sizes(G.sizes) {  }

    // деструктор
    ~Grid() {
        delete[] data;
        delete[] sizes;
    }

    // конструктор премещения
    Grid(Grid&& other) : sizes(0), data(nullptr) {
        // перемещаем ресурсы из 'other' в этот объект
        sizes = other.sizes;
        data = other.data;

        // обнуляем other, чтобы он больше не ссылался на перемещенные ресурсы
        other.sizes = 0;
        other.data = nullptr;

        // удаляем other
        ~Grid(other);
    }

    // оператор присваивания
    Grid& operator=(const Grid& other) {
        if (this != &other) {
            delete[] data;
            delete[] sizes;

            dim = other.dim;
            data = other.data;
            sizes = other.sizes;
        }
        return *this;
    }

    Grid& operator=(Grid&& other) {
        if (this != &other) {
            // Освобождаем текущие данные
            delete[] data;
            delete[] sizes;

            // Перемещаем данные из other
            dim = std::move(other.dim);
            data = std::move(other.data);
            sizes = std::move(other.sizes);

            // Обнуляем данные в other
            other.dim = 0;
            other.data = nullptr;
            other.sizes = nullptr;

            // удаляем other
            ~Grid(other);
        }
        return *this;
    }


    T* operator[](size_type idx) {
        return data + idx * sizes[1];
    }

    size_type get_sizes() const { return *sizes; }
};

