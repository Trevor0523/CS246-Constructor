#include <iostream>
#include "window.h"

using namespace std;

int main() {
    Xwindow w;

    for (int i = Xwindow::White ; i <= Xwindow::Blue; i++) {
        w.fillRectangle(50 * i, 200, 50, 250, i);
    }

    w.drawString(50, 50, "Hello!");
    w.drawString(50, 100, "ABCD");
    w.drawString(50, 150, "Hello!");

    //Xwindow w2(199, 199);
    //w2.drawString(50, 100, "ABCD");

    // Wait for the user to input a character, which lets us see the windows; otherwise,
    // they'll be immediately destroyed when the program ends.
    char c;
    cin >> c;
}

