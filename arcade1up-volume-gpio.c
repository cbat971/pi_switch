// this is sort of a C equivalent of:
//  https://github.com/dmanlfc/arcade1up/blob/master/volume.py

// But this C code is public domain.  --ryan.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

int main(int argc, char **argv)
{
    int volumeState = 999;   /* force volume to be set at startup */

    wiringPiSetupPhys();

    pullUpDnControl(12, PUD_UP);
    pullUpDnControl(16, PUD_DOWN);

    while (1) {
        const int buttonState1 = digitalRead(12);
        const int buttonState2 = digitalRead(16);

        if (!buttonState1 && !buttonState2 && (volumeState != 96)) {
            printf("Switch was set to Vol HIGH (volstate %d => 96)\n", volumeState);
            system("amixer set PCM unmute");
            system("amixer set PCM 96%");
            volumeState = 96;
        } else if (buttonState1 && buttonState2 && (volumeState != 0)) {
            printf("Switch was set to MUTE (volstate %d => 0)\n", volumeState);
            system("amixer set PCM mute");
            volumeState = 0;
        } else if (buttonState1 && !buttonState2 && (volumeState != 75)) {
            printf("Switch was set to Vol LOW (volstate %d => 75)\n", volumeState);
            system("amixer set PCM unmute");
            system("amixer set PCM 75%");
            volumeState = 75;
        } else {
            usleep(300 * 1000);
        }
    }

    return 0;
}

// end of arcade1up-volume-gpio.c ...
