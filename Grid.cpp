#include <iostream>
#include <cassert>


template <typename T>
class Grid{
private:
    T * data;

public:
    using size_type = unsigned;
    size_type y_size, x_size;

    // Конструкторы

    // Конструктор с параметрами для инициализации данных
    Grid(const T * data, size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size), data(new T[y_size * x_size]) {
        for(size_type i = 0; i < y_size * x_size; ++i) {
            this->data[i] = data[i];
        }
    }

    // Конструктор для одного элемента
    Grid(const T& data) : y_size(1), x_size(1), data(new T[1]) {
        this->data[0] = data;
    }

    // Конструктор для создания пустой сетки заданного размера
    Grid(size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size), data(new T[y_size * x_size]) {
    }

    // Конструктор для заполнения сетки одним значением
    Grid(const T& t, size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size), data(new T[y_size * x_size]) {
        std::fill_n(data, y_size * x_size, t);
    }

    // Конструктор копирования
    Grid(const Grid<T>& G) : y_size(G.y_size), x_size(G.x_size), data(new T[y_size * x_size]) {
        std::copy(G.data, G.data + y_size * x_size, data);
    }

    // Деструктор
    ~Grid() {
        delete[] data;
    }

    // Конструктор перемещения
    Grid(Grid&& other) noexcept : y_size(other.y_size), x_size(other.x_size), data(other.data) {
        other.y_size = 0;
        other.x_size = 0;
        other.data = nullptr;
    }

    // Операторы доступа
    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    // Оператор присваивания копированием
    Grid<T>& operator=(const Grid<T>& other) {
        if (this != &other) {
            Grid<T> temp(other);
            std::swap(data, temp.data);
            std::swap(y_size, temp.y_size);
            std::swap(x_size, temp.x_size);
        }
        return *this;
    }

    // Оператор присваивания перемещением
    Grid& operator=(Grid&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;
            other.data = nullptr;
            other.y_size = 0;
            other.x_size = 0;
        }
        return *this;
    }

    // Оператор индексации
    T* operator[](size_type idx){
            return data + idx * x_size;
    }

    // Геттеры для размеров
    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};


int main() {
    // Тест конструктора с параметрами
    int initData[4] = {1, 2, 3, 4};
    Grid<int> grid1(initData, 2, 2);
    assert(grid1(0, 0) == 1 && grid1(0, 1) == 2);
    assert(grid1(1, 0) == 3 && grid1(1, 1) == 4);

    // Тест конструктора для одного элемента
    int v = 5;
    Grid<int> grid2(v);
    assert(grid2(0, 0) == 5);

    // Тест конструктора для заполнения сетки одним значением
    v = 9;
    Grid<int> grid4(v, 2, 2);
    assert(grid4(0, 0) == 9 && grid4(0, 1) == 9);
    assert(grid4(1, 0) == 9 && grid4(1, 1) == 9);

    // Тест конструктора копирования
    Grid<int> grid5 = grid1;
    assert(grid5(0, 0) == 1 && grid5(0, 1) == 2);
    assert(grid5(1, 0) == 3 && grid5(1, 1) == 4);

    // Тест конструктора перемещения
    Grid<int> grid6 = std::move(grid5);
    assert(grid6(0, 0) == 1 && grid6(0, 1) == 2);
    assert(grid6(1, 0) == 3 && grid6(1, 1) == 4);

    // Тест оператора присваивания копированием
    v = 2;

    Grid<int> grid7(v, 2);
    grid7 = grid1;
    assert(grid7(0, 0) == 1 && grid7(0, 1) == 2);
    assert(grid7(1, 0) == 3 && grid7(1, 1) == 4);

    // Тест оператора индексации
    assert(grid1[0][0] == 1 && grid1[0][1] == 2);
    assert(grid1[1][0] == 3 && grid1[1][1] == 4);


    return 0;
}
