/*
 please read in maximized state of texteditor
 author : KSatyam,200050064
 LAB 4 = 15puzzle.cpp

 DESCRIPTION: program a 15puzzle game using fltk library

 NOTE: you must take care of abstractions and paradigm
*/

#include <FL/Fl.H>              // needed in every fltk program
#include <FL/Fl_Window.H>       // needed to use the Fl_Window class
#include <FL/Fl_Button.H>       // needed to use the Fl_Box class
#include <FL/Fl_Radio_Button.H> // needed to use the Fl_Box class
#include <FL/Fl_Light_Button.H> // needed to use the Fl_Box class
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

char *int2charstar(int v)
{
    char *s = new char[sizeof(int)];
    sprintf(s, "%d", v);
    return s;
};

class MyButton : public Fl_Button
{
public:
    int neighbourcount;  //number of neighbours of this particular button
    MyButton *neighbours[4]; //array of neighbours button pointers
    MyButton(int x, int y, int w, int h, const char *l);
    int handle(int e); // e is incoming mouse event of different kinds
};

MyButton ::MyButton(int x, int y, int w, int h, const char *l = 0) : Fl_Button(x, y, w, h, l)
{
}

int MyButton ::handle(int e)
{
    if (e == FL_PUSH)  //to customize to drag replace FL_PUSH with FL_DRAG
    {
        if (label() != 0)
        {
            for (int i = 0; i < neighbourcount + 1; i++)
            {
                if (neighbours[i]->label() == 0)
                {
                    neighbours[i]->label(label());
                    neighbours[i]->color(FL_GREEN);
                    label(0);
                    color(FL_RED);
                }
            }
        }
    }

    return 1;
};

class puzzle
{
    Fl_Window *window;
    int dim; //dimension
    MyButton *buttons[20][20];  //for just keeping a bar on buttons matrix if want big puzzle increase it in both [][]
    void allocateNeighbours();
    void randomize();
    float windowsize;

public:
    puzzle(int dim);
};

puzzle::puzzle(int k)
{
    windowsize = 600.0;  //change pixels value by editing 600.0 to customize
    dim = k;
    window = new Fl_Window(windowsize, windowsize, "PUZZLE           try getting all numbers in order"); // outer window
    window->color(FL_WHITE);
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (i != (dim - 1) || j != (dim - 1))
            {
                buttons[i][j] = new MyButton(((windowsize/2) / dim) * (2 * i), ((windowsize/2)/ dim) * (2 * j), (windowsize/ dim), (windowsize/ dim), int2charstar(i + dim * j + 1));
                buttons[i][j]->labelsize((0.4*windowsize) / dim);
                buttons[i][j]->color(FL_GREEN);
            }
            else
            {
                buttons[i][j] = new MyButton(((windowsize/2) / dim) * (2 * i), ((windowsize/2) / dim) * (2 * j), (windowsize/ dim), (windowsize/ dim));
                buttons[i][j]->labelsize((0.4*windowsize)/ dim);
                buttons[i][j]->color(FL_RED);
            }
        }
    }
    allocateNeighbours();
    randomize();
    window->end();
    window->show();
}

void puzzle::allocateNeighbours()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            int k = -1;
            if (j != 0)
            {
                k++;
                buttons[i][j]->neighbours[k] = buttons[i][j - 1];
            }
            if (j != dim - 1)
            {
                k++;
                buttons[i][j]->neighbours[k] = buttons[i][j + 1];
            }
            if (i != 0)
            {
                k++;
                buttons[i][j]->neighbours[k] = buttons[i - 1][j];
            }
            if (i != dim - 1)
            {
                k++;
                buttons[i][j]->neighbours[k] = buttons[i + 1][j];
            }
            for (int l = k + 1; l < 4; l++)
            {
                buttons[i][j]->neighbours[l] = NULL;
            }
            buttons[i][j]->neighbourcount = k;
        }
    }
    return;
}

void puzzle::randomize()
{
    srand(time(0));
    for (int i = 0; i < dim*dim*100; i++)
    {
        int a = (rand() % dim);
        int b = (rand() % dim);
        buttons[a][b]->handle(1);  //to customize to drag replace 1 with 5
    }
    return;
}

int main(int argc, char *argv[])
{
    //commands written to display all puzzles at once 
    //can edit or add more puzzles too
    //enter the dimension of square box as argument to the puzzle

    puzzle A(7);
    //int a = (Fl::run());   uncomment it to go step by step 
    puzzle B(6);
    //int b = (Fl::run());   uncomment it to go step by step 
    puzzle C(5);
    //int c = (Fl::run());   uncomment it to go step by step 
    puzzle D(4);
    //int d = (Fl::run());   uncomment it to go step by step 
    puzzle E(3);
    int e = (Fl::run()); 
    
    return 0;
}
