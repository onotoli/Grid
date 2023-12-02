#include <iostream>

template <typename T>
class Grid final {
private:
    using value_type = T;
    T * data;

public:
    using size_type = unsigned;
    size_type y_size, x_size;

    // конструкторы

    Grid(T * data, size_type y_size, size_type x_size) {
        this->y_size = y_size;
        this->x_size = x_size;
        this->data = new T[y_size * x_size];
        for(int i = 0; i < y_size * x_size; ++i) {
            this->data[i] = data[i];
        }
    }


    Grid(T& data) {
        this->y_size = 1;
        this->x_size = 1;
        this->data = new T[1];
        data[0] = data;
    }

    Grid(size_type y_size, size_type x_size) {
        this->y_size = y_size;
        this->x_size = x_size;
        this->data = new T[y_size * x_size];
    }

    Grid(T& t, size_type y_size, size_type x_size) {
        this->y_size = y_size;
        this->x_size = x_size;
        this->data = new T[y_size * x_size];
        for (int i = 0; i < x_size * y_size; ++i) {
            this->data[i] = t;
        }
    }

    // конструктор копирования
    Grid(Grid<T> const& G) {
        x_size = G.x_size;
        y_size = G.y_size;
        data = new T[y_size * x_size];
        for (int i = 0; i < x_size * y_size; ++i) {
            data[i] = G.data[i];
        }

    }

    // деструктор
    ~Grid() {
        delete[] data;
    }
    
    // конструктор премещения
    Grid(Grid&& other) : y_size(0), x_size(0), data(nullptr) {
        // перемещаем ресурсы из 'other' в этот объект
        y_size = other.y_size;
        x_size = other.x_size;
        data = other.data;

        // обнуляем other, чтобы он больше не ссылался на перемещенные ресурсы
        other.y_size = 0;
        other.x_size = 0;
        other.data = nullptr;

        // удаляем other
        ~Grid(other);
    }


    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    // оператор присваивания
    Grid<T>& operator=(T &t) {
        for (
            auto it = data , end = data + x_size * y_size;
            it != end; ++it
         ) *it = t;
        return * this;
        }

    // оператор перемещения
    Grid& operator=(Grid&& other) {
        if (this != &other) {
            // Освобождаем текущие данные
            delete[] data;

            // Перемещаем данные из other
            data = std::move(other.data);
            y_size = std::move(other.y_size);
            x_size = std::move(other.x_size);

            // Обнуляем данные в other
            other.data = nullptr;
            other.y_size = 0;
            other.x_size = 0;

            // удаляем other
            ~Grid(other);
        }
        return *this;
    }

    T* operator[](size_type idx) {
        return data + idx * x_size;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};


#include <cassert>
int main() {
    float x = 0.0f;
    Grid<float> g(x, 3, 2);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<int>::size_type;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx){
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx){
            assert(0.0f == g[y_idx][x_idx]);
        }
    }

    return 0;
}