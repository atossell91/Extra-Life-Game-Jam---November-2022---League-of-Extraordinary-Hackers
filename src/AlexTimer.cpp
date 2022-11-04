#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int alexSeconds = 60;

void displayClock()
{
    cout <<alexSeconds;
}
void timer()
{
    while (true) {
        displayClock();
        sleep(1);
        alexSeconds--;
    }
}
