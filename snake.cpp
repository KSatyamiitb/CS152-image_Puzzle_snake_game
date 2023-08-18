/*
author: KSatyam , 200050064
lab6 snake.cpp
motive : to use fltk along with inheritance to develop a basic game
*/
#include <iostream>
#include <FL/Fl.H>        // needed in every fltk program
#include <FL/Fl_Window.H> // needed to use the Fl_Window class
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
using namespace std;

class Shape : public Fl_Widget
{
public:
    int oldx, oldy, x, y, w, h;
    Shape(int x, int y, int w, int h) : Fl_Widget(x, y, w, h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
    virtual void refresh(int dx, int dy) = 0;
    virtual int handle(int e) { return 1; }
};

class Head : public Shape
{
public:
    Head(int x, int y, int w) : Shape(x, y, w + 10, w + 10) {}
    virtual void draw()
    {
        fl_color(FL_RED);
        fl_pie(x, y, w, h, 0, 360);
    }
    virtual void refresh(int dx, int dy)
    {
        fl_color(FL_WHITE);
        fl_pie(x, y, w, h, 0, 360);
        hide();
        oldx = x;
        x = x + dx;
        oldy = y;
        y = y + dy;
        resize(x, y, w, h);
        fl_color(FL_RED);
        fl_pie(x, y, w, h, 0, 360);
        show();
    }
};

class MyCircle : public Shape
{
public:
    int code;
    MyCircle(int x, int y, int w, int n) : Shape(x, y, w + 10, w + 10) { code = n; }
    virtual void draw()
    {
        if (code == 1)
            fl_color(FL_BLUE);
        else
            fl_color(FL_GREEN);
        fl_pie(x, y, w, h, 0, 360);
    }

    virtual void refresh(int dx, int dy)
    {
        fl_color(FL_WHITE);
        fl_pie(x, y, w, h, 0, 360);
        hide();
        oldx = x;
        x = x + dx;
        oldy = y;
        y = y + dy;
        resize(x, y, w, h);
        if (code == 1)
            fl_color(FL_BLUE);
        else
            fl_color(FL_GREEN);
        fl_pie(x, y, w, h, 0, 360);
        show();
    }
};

class snake
{
public:
    Head *H;
    MyCircle *units[10];
    MyCircle *food[10];
    int count;

    snake()
    {
        H = new Head(45, 10, 5);
        for (int i = 0; i < 3; i++)
        {
            units[i] = new MyCircle(30 - i * 15, 10, 5, 1);
        }
        for (int i = 3; i < 10; i++)
        {
            units[i] = NULL;
        }
        count = 3;
        srand(time(0));
        for (int i = 0; i < 10; i++)
        {
            food[i] = new MyCircle(((rand() % 60)) * 10, ((rand() % 53)) * 10, 5, 2);
        }
    }

    void movement()
    {
        units[0]->refresh((H->oldx) - (units[0]->x), (H->oldy) - (units[0]->y));
        for (int i = 1; i < count; i++)
        {
            units[i]->refresh((units[i - 1]->oldx) - (units[i]->x), (units[i - 1]->oldy) - (units[i]->y));
        }
    }

    void increase()
    {
        units[count] = new MyCircle(units[count - 1]->oldx, units[count - 1]->oldy, 5, 1);
        count++;
    }

    void search()
    {
        for (int i = 0; i < 10; i++)
        {
            if (abs(H->x - food[i]->x) + abs(H->y - food[i]->y) < 15)
            {
                food[i]->refresh(1000, 1000);
                increase();
            }
        }
    }
};

class MyWindow : public Fl_Window
{
public:
    snake A;
    MyWindow(int x, int y, const char *l, snake s) : Fl_Window(x, y, l) { A = s; };
    virtual int handle(int e)
    {
        if (e == FL_KEYBOARD)
        {
            if (Fl::event_key() == 65362)
                A.H->refresh(0, -15);
            else if (Fl::event_key() == 65364)
                A.H->refresh(0, 15);
            else if (Fl::event_key() == 65361)
                A.H->refresh(-15, 0);
            else if (Fl::event_key() == 65363)
                A.H->refresh(15, 0);
            A.movement();
            A.search();
        }
        return 1;
    }
};

int main(int argc, char *argv[])
{
    MyWindow *window;
    snake A;
    window = new MyWindow(600, 600, "SNAKE", A); // outer window

    //new MyCircle(500, 500, 10);

    window->color(FL_WHITE);
    window->end();
    window->show();
    return (Fl::run()); // the process waits from here on for events
}
