#include "statusBar.h"

uint8_t partialUpdates = 0;

int statusBarPrint(Inkplate *pDisplay, String text)
{
    pDisplay->setTextSize(STATUSBAR_TXT_SIZE);
    pDisplay->setCursor(STATUSBAR_LOC_X, STATUSBAR_LOC_Y);
    pDisplay->print(text);

    if(partialUpdates > 9)
    {
        pDisplay->display(); //full refresh.
        partialUpdates = 0;
    }
    else
    {
        pDisplay->partialUpdate();
        partialUpdates++;
    }

    return 0;
}