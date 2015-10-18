#include <graphics.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <conio.h>
#include <stdlib.h>

#define cor (M_PI/2)
#define PI 3.1415926

using namespace std;

int xmax, ymax, a, b;
double fir, T, g, r1, r2, w, fr;
double xx, yy, x2, y2, u, teta, ba, masa, tetag;
double timefix;
int v1, v2;
char s[1000];
clock_t begin, end;

void Error_Real(double &x)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while(x <= 0)
    {
        SetConsoleTextAttribute(hConsole, RED);
        cout << "\nWrong input. Insert a positive real number!\n";
        SetConsoleTextAttribute(hConsole, WHITE);
        cin >> x;
    }
    SetConsoleTextAttribute(hConsole, WHITE);
}

void Error12(double &x)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while(x != 1 && x != 2)
    {
        SetConsoleTextAttribute(hConsole, RED);
        cout << "\nWrong input. Press Key 1 or Key 2!\n";
        SetConsoleTextAttribute(hConsole, WHITE);
        cin >> x;
    }
    SetConsoleTextAttribute(hConsole, WHITE);
}

void Error123(double &x)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while(x != 1 && x != 2 && x != 3)
    {
        SetConsoleTextAttribute(hConsole, RED);
        cout << "\nWrong input. Press Key 1, Key 2 or Key 3!\n";
        SetConsoleTextAttribute(hConsole, WHITE);
        cin >> x;
    }
    SetConsoleTextAttribute(hConsole, WHITE);
}

void Pendul_Keys()
{
    if(kbhit())
        {
            double start = clock();
            char c = getch();
            if(c == '\r')
            {
                for(int i = 1; i ; i++)
                    if(kbhit())
                    {
                         char c = getch();

                         double stop = clock();
                         timefix += double(stop - start) / CLOCKS_PER_SEC;

                         if(c == '\r')
                            break;
                         else if(c == 27)
                            exit(0);
                    }
            }
            else if(c == 27)
                exit(0);
        }
}

void Add(char a[], char b[])
{
    int n = strlen(a);
    for(int i = 0; i < strlen(b); i++)
        a[n + i] = b[i];
    a[n + strlen(b)] = NULL;
}

void Transform(double x)
{
    s[0] = NULL;
    char s1[1000], s2[1000];

    v1 = (int)x;
    itoa(v1, s1, 10);
    double zec = (x - (double)(v1));
    if(zec < 0.1)
    {
           if(zec < 0.01)
            s2[0] = s2[1] = '0', s2[2] = NULL;
           else
           {
                v2 = zec * 100;
                itoa(v2, s2, 10);
                s2[1] = s2[0];
                s2[0] = '0';
                s2[2] = NULL;
           }
    }
    else
    {
        zec *= 100;
        v2 = zec;
        itoa(v2, s2, 10);
    }

    s1[strlen(s1) + 1] = NULL;
    s1[strlen(s1)] = '.';

    Add(s, s1);
    Add(s, s2);
}

void Display_Data_Constants()
{
    settextstyle(10, HORIZ_DIR, 5);
    outtextxy(xmax / 8, ymax / 10, "GRAVITATIONAL PENDULUM");

    settextstyle(6, HORIZ_DIR, 2);

    Transform(T);
    outtextxy(xmax / 8, ymax / 4, "Period(s): ");
    outtextxy(xmax / 8 + 150, ymax / 4, s);

    Transform(w);
    outtextxy(xmax / 8, ymax / 4 + 30, "Pulsat.(rad/s): ");
    outtextxy(xmax / 8 + 180, ymax / 4 + 30, s);

    Transform(fr);
    outtextxy(xmax / 8, ymax / 4 + 60, "Frequency(Hz): ");
    outtextxy(xmax / 8 + 190, ymax / 4 + 60, s);

    Transform(fir);
    outtextxy(xmax / 8, ymax / 4 + 90, "Wire length(m): ");
    outtextxy(xmax / 8 + 260, ymax / 4 + 90, s);

    Transform(g);
    outtextxy(xmax / 8, ymax / 4 + 120, "Gravitational acceleration(m/s^2): ");
    outtextxy(xmax / 8 + 340, ymax / 4 + 120, s);
}

void Display_Data_Variables(double angle, double timp, bool ok)
{
    double g_angle = fabs(angle * 180.0 / 3.1415926);
    double elongatie = fabs(angle * fir);
    double faza = fabs(w * timp);

    Transform(g_angle);
    if(ok) outtextxy(xmax / 8, ymax / 2, "Teta(degr.): ");
    outtextxy(xmax / 8 + 160, ymax / 2, s);

    Transform(elongatie);
    if(ok) outtextxy(xmax / 8, ymax / 2 + 30, "Elongation(m): ");
    outtextxy(xmax / 8 + 180, ymax / 2 + 30, s);

    Transform(faza);
    if(ok) outtextxy(xmax / 8, ymax / 2 + 60, "Phaze: ");
    outtextxy(xmax / 8 + 80, ymax / 2 + 60, s);

    Transform(timp);
    if(ok) outtextxy(xmax / 8, ymax / 2 + 90, "Time(s): ");
    outtextxy(xmax / 8 + 110, ymax / 2 + 90, s);
}

double lastsec, lastx, lasty;
void Display_Graphic(double sec)
{
    if(lastx > xmax / 2 - 100) return;

     setcolor(GREEN);
     setlinestyle(0, 0, 2);

    lastsec = sec;
    tetag = teta * 200;
    line(lastx, lasty, xmax / 8 + sec * 20, ymax / 1.25 + tetag);

    lastx = xmax / 8 + sec * 20;
    lasty = ymax / 1.25 + tetag;


    setcolor(BLACK);
    setlinestyle(0, 0, 1);
}

void Initial_Graphic()
{
    setcolor(BLACK);
    line(xmax / 8, ymax / 1.25 + u * 200, xmax / 8, ymax / 1.25 - u * 200);
    line(lastx, lasty, xmax / 2 - 50, lasty);

    line(xmax / 8 + 5, ymax / 1.25 + u * 200 + 5, xmax / 8, ymax / 1.25 + u * 200);
    line(xmax / 8 - 5, ymax / 1.25 + u * 200 + 5, xmax / 8, ymax / 1.25 + u * 200);
    line(xmax / 2 - 50 - 5, lasty - 5, xmax / 2 - 50, lasty);
    line(xmax / 2 - 50 - 5, lasty + 5, xmax / 2 - 50, lasty);

    for(int i = 1; i <= 23; i++)
        line(xmax / 8 + i * 20, ymax / 1.25 - 5, xmax / 8 + i * 20, ymax / 1.25 + 5);

    outtextxy(xmax / 8 , ymax / 1.25 - 80, "Elongation");
    outtextxy(xmax / 2 - 40, ymax / 1.25 - 10, "Time");
}

void Next_Frame()
{
    setcolor(BLACK);
    end = clock();
    double sec = double(end - begin) / CLOCKS_PER_SEC - timefix;

    teta  = u * sin(w * sec);
    Display_Graphic(sec);

    xx = r1 * cos(teta + cor), yy = r1 * sin(teta + cor);
    x2 = r2 * cos(teta + cor), y2 = r2 * sin(teta + cor);

    setlinestyle(0, 0, 2);
    fillellipse(a, b, 5, 5);
    line(a, b, a + x2, b + y2);
    circle(a + xx, b + yy, 40);
}

void Pendul_Ideal()
{
    double xx2, yy2, x22, y22;

    while(1)
    {
        end = clock();
        double sec = double(end - begin) / CLOCKS_PER_SEC - timefix;

        teta  = u * sin(w * sec);
        Display_Graphic(sec);

        xx = r1 * cos(teta + cor), yy = r1 * sin(teta + cor);
        x2 = r2 * cos(teta + cor), y2 = r2 * sin(teta + cor);

        setcolor(BLACK);
        Display_Data_Variables(teta, sec, 1);

        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(a, b, 5, 5);
        line(a, b, a + x2, b + y2);
        circle(a + xx, b + yy, 40);

        xx2 = xx, yy2 = yy, x22 = x2, y22 = y2;
        Next_Frame();

        Pendul_Keys();
        setlinestyle(0, 0, 100);
        setcolor(WHITE);
        //delay(10);
        circle(a + xx2, b + yy2, 40);
        line(a, b, a + x22, b + y22);

        setlinestyle(0, 0, 2);
        Next_Frame();
    }

    getch();
    closegraph();
}

void Next_Frame2()
{
    setcolor(BLACK);
    end = clock();
    double sec = double(end - begin) / CLOCKS_PER_SEC - timefix;

    teta  = u * pow(2.71828, -ba*sec/2*masa) * sin(w * sec);
    Display_Graphic(sec);

    xx = r1 * cos(teta + cor), yy = r1 * sin(teta + cor);
    x2 = r2 * cos(teta + cor), y2 = r2 * sin(teta + cor);

    setlinestyle(0, 0, 2);
    fillellipse(a, b, 5, 5);
    line(a, b, a + x2, b + y2);
    circle(a + xx, b + yy, 40);
}

void Pendul_Real()
{
    double xx2, yy2, x22, y22;

    while(1)
    {
        end = clock();
        double sec = double(end - begin) / CLOCKS_PER_SEC - timefix;

        double amplitude = u * pow(2.71828, -ba*sec/2*masa);
        teta  = amplitude * sin(w * sec);

        Display_Graphic(sec);

        xx = r1 * cos(teta + cor), yy = r1 * sin(teta + cor);
        x2 = r2 * cos(teta + cor), y2 = r2 * sin(teta + cor);

        setcolor(BLACK);
        Display_Data_Variables(teta, sec, 1);

        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(a, b, 5, 5);
        line(a, b, a + x2, b + y2);
        circle(a + xx, b + yy, 40);

        xx2 = xx, yy2 = yy, x22 = x2, y22 = y2;
        Next_Frame2();

        Pendul_Keys();
        setlinestyle(0, 0, 100);
        setcolor(WHITE);
        circle(a + xx2, b + yy2, 40);
        line(a, b, a + x22, b + y22);

        setlinestyle(0, 0, 2);
        Next_Frame2();

        if(-amplitude < 0.001) u = 0;
    }
}

void Initiate_Graphics(bool type)
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");

    xmax = getmaxwidth();
    ymax = getmaxheight() - 45;
    initwindow(xmax, ymax, "Pendulul gravitational");

    lastx = xmax / 8, lasty = ymax / 1.25;

    a = 0.75 * xmax, b = ymax / 4;
    xx, yy, x2, y2;
    u = -0.2616666666, teta; // 15 degrees in radians

    setbkcolor(WHITE);
    cleardevice();

    r1 = 400, r2 = 360;
    teta = u;
    begin = clock();

    setcolor(BLACK);
    Display_Data_Constants();

    Initial_Graphic();

    if(!type) Pendul_Ideal();
    else Pendul_Real();
}

void Menu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, RED);

    double key;
    cout << "Gravitational Pendulum. Program created by Cristian Bodnar.\n\n";

    SetConsoleTextAttribute(hConsole, GREEN);
    cout << "Before starting the exeriment you have to set a couple of parameters. \n";
    cout << "After pressing a key or inserting a value, press enter! \n\n";

    SetConsoleTextAttribute(hConsole, WHITE);
    cout << "Press:\n";
    cout << "Key 1: To run the experiment in an ideal scenario.\n";
    cout << "Key 2: To run the experiment in a real scenario.\n";
    cin >> key;
    Error12(key);

    if(key == 1)
    {
        cout << "Inset the value of the gravitational acceleration measured in in m/s^2(eg: 9.80)\n";
        cin >> g;
        Error_Real(g);

        cout << "Press:\n";
        cout << "Key 1: To set the length of the wire\n";
        cout << "Key 2: to set the period, the frequency or the pulsation\n";
        cin >> key;
        Error12(key);

        if(key == 1)
        {
            cout << "Insert the length of the wire in meters\n";
            cin >> fir;
            Error_Real(fir);

            w = sqrt(g/fir);
            T = 2 * PI / w;
            fr = 1.0 / T;
        }
        else if(key == 2)
        {
            cout << "Press:\n";
            cout << "Key 1: To insert the Period\n";
            cout << "Key 2: To insert the Frequency\n";
            cout << "Key 3: To insert the Pulsation\n";
            cin >> key;
            Error123(key);


            if(key == 1)
            {
                cout << "Insert the value of the Period in seconds\n";
                cin >>  T;
                Error_Real(T);

                fr = 1.0 / T;
                w = 2 * PI / T;
                fir = T*T * g / (4 * PI * PI);
            }
            else if(key == 2)
            {
                cout << "Insert the value of the frequency in Hz\n";
                cin >> fr;
                Error_Real(fr);

                T = 1.0 / fr;
                w = 2 * PI / T;
                fir = T*T * g / (4 * PI * PI);
            }
            else
            {
                cout << "Insert the value of the Pulsation in rad/s\n";
                cin >> w;
                Error_Real(w);

                T = 2 * PI / w;
                fr = 1.0 / T;
                fir = T*T * g / (4 * PI * PI);
            }
        }
        Initiate_Graphics(0);
    }

    else if(key == 2) // Cazul Real
    {
        cout << "Insert the friction constant in kg/s: \n";
        cin >> ba;
        Error_Real(ba);

        cout << "Insert the mass of the body in kg\n";
        cin >> masa;
        Error_Real(masa);

        cout << "Insert the value of gravitational acceleration in m/s^2(eg: 9.80)\n";
        cin >> g;
        Error_Real(g);

        cout << "Apasati:\n";
        cout << "Key 1: To set the wire length\n";
        cout << "Key 2: To set the period, the frequency or the pulsation\n";
        cin >> key;
        Error12(key);

        if(key == 1)
        {
            cout << "Insert the lenth of the wire in meters\n";
            cin >> fir;
            Error_Real(fir);

            double val = (g/fir) - (ba / (2*masa))*(ba / (2*masa));
            if(val < 0.0) val = (g/fir) / ((ba / (2*masa))*(ba / (2*masa)));

            w = sqrt(val);
            T = 2 * PI / w;
            fr = 1.0 / T;
        }
        else if(key == 2)
        {
            cout << "Press:\n";
            cout << "Key 1: Pentru a introduce Perioada\n";
            cout << "Key 2: Pentru a introduce Frecventa\n";
            cout << "Key 3: Pentru a introduce Pulsatia\n";
            cin >> key;
            Error123(key);


            if(key == 1)
            {
                cout << "Insert the Period in seconds\n";
                cin >>  T;
                Error_Real(T);

                fr = 1.0 / T;
                w = 2 * PI / T;
                fir = sqrt(g / (w*w + ba*ba/(4*masa*masa)));
            }
            else if(key == 2)
            {
                cout << "Insert the Frequency in Hz\n";
                cin >> fr;
                Error_Real(fr);

                T = 1.0 / fr;
                w = 2 * PI / T;
                fir = sqrt(g / (w*w + ba*ba/(4*masa*masa)));
            }
            else
            {
                cout << "Insert the value of the pulsation in rad/s\n";
                cin >> w;
                Error_Real(w);

                T = 2 * PI / w;
                fr = 1 / T;
                fir = sqrt(g / (w*w + ba*ba/(4*masa*masa)));
            }
        }
        Initiate_Graphics(1);
    }
}

int main()
{
    Menu();
    return 0;
}
