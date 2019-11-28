#ifndef RFID_H_
#define RFID_H_

#include "LibRobus.h"

#define SerialRFID Serial1 // 19 (RX1)

struct Tag {
    String id, name;
    int value;
};

Tag tags[] = {
    {"0E008E637F", "RFTC014", 0},
    {"0E008E6F32", "RFTC015", 1},
    {"0E008E9C42", "RFTC016", 2}
};

struct RFID
{
    RFID() {}

    void init()
    {
        SerialRFID.begin(9600);
    }

    // return id of tag (-1 if no tag detected)
    int read() 
    {
        if (SerialRFID.available() && SerialRFID.read() == 0x02) 
        {
            AX_BuzzerON();
            char crecu = '0';
            String idTag = "";
            Serial.print("crecu"); Serial.println(crecu == 0x03);

            while (crecu != 0x03) 
            {
                if (SerialRFID.available())
                {
                    crecu = SerialRFID.read();
                    idTag += crecu;
                    Serial.println(idTag);
                }
            }
            AX_BuzzerOFF();
            // while (SerialRFID.available() > 0) {
            //     char t = SerialRFID.read();
            // }
            // SerialRFID.flush();
            // remove checksum
            idTag = idTag.substring(0, 10);
            for (Tag tag: tags)
            {
                if (tag.id == idTag)
                {
                    Serial.println(tag.name);
                    return tag.value;
                }
            }
            return -1;
        }
        else 
            return -1;
    }
};

#endif