#include <iomanip>
#include <iostream>

#include "BoardView.h"
#include "Person.h"

using namespace std;

BoardView::BoardView() : size(11), scale(2.0), origin(0, 0) {
    clear();
}

void BoardView::insert(char code, int id, Real_Pair coord) {
    const Real_Pair normalized = (coord - origin) / scale;
    const int x_location = static_cast<int>(normalized.x);
    const int y_location = static_cast<int>(normalized.y);

    if (x_location >= size || y_location >= size || x_location < 0 || y_location < 0) {
        cout << "Object " << code << id << " is outside the display" << endl;
        return;
    }

    if (display_array[x_location][y_location][0] == '.') {
        display_array[x_location][y_location][0] = code;
        display_array[x_location][y_location][1] = static_cast<char>('0' + (id % 10));
    } else {
        display_array[x_location][y_location][0] = '*';
        display_array[x_location][y_location][1] = ' ';
    }
}

void BoardView::set_origin(double x, double y) {
    origin.x = x;
    origin.y = y;
    cout << "set board origin to (" << x << ", " << y << ")" << endl;
}

void BoardView::set_scale(double s) {
    scale = s;
    cout << "set board scale to " << scale << endl;
}

void BoardView::set_size(int s) {
    if (s > maxsize || s < 3) {
        cout << "board size should in [3, 20]" << endl;
        return;
    }

    size = s;
    cout << "set board size to " << size << endl;
}

void BoardView::clear() {
    for (int i = 0; i < maxsize; ++i) {
        for (int j = 0; j < maxsize; ++j) {
            display_array[i][j][0] = '.';
            display_array[i][j][1] = ' ';
        }
    }
}

void BoardView::plot(const Person* object) {
    if (object == nullptr) {
        return;
    }

    insert(object->get_code(), object->get_ID(), object->get_location());
}

void BoardView::draw() {
    double current_x = origin.x;
    double current_y = origin.y + scale * (size - 1);

    cout << "Display size: " << size << ", scale: " << scale << ", origin: " << origin << endl;
    for (int j = size - 1; j >= 0; --j) {
        if (j % 2 == 0) {
            cout << setw(2) << current_y << ' ';
        } else {
            cout << "   ";
        }

        for (int i = 0; i < size; ++i) {
            cout << display_array[i][j][0] << display_array[i][j][1];
        }
        cout << endl;

        if (j != 0) {
            current_y -= scale;
        }
    }

    cout << "   ";
    for (int i = 0; i < size; ++i) {
        if (i % 2 == 0) {
            cout << setw(2) << current_x;
        } else {
            cout << "  ";
        }
        current_x += scale;
    }
    cout << endl;
}
