#ifndef MP3_H_
#define MP3_H_

#include "SerialMP3Player.h"

struct MP3
{
    SerialMP3Player _player;

    MP3() {}

    void init() 
    {
        _player = SerialMP3Player(14, 15); // Serial3
        _player.begin(9600);
        delay(500); // wait for init
        _player.sendCommand(CMD_SEL_DEV, 0, 2); // select sd-card
    }

    void play() 
    {
        _player.play();
    }

    void playNext()
    {
        _player.playNext();
    }

    void playLast()
    {
        _player.playPrevious();
    }
    
    void pause()
    {
        _player.pause();
    }

    // max 30
    void volUp()
    {
        _player.volUp();
    }

    // min 0
    void volDown()
    {
        _player.volDown();
    }
};


#endif