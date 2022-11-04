#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int seconds = 60;

void displayClock()
{
    cout <<seconds;
}
void timer()
{
    while (true) {
        displayClock();
        sleep(1);
        seconds--;
        }
    }
int MagicMain()
{
    timer();
    return 0;
}
