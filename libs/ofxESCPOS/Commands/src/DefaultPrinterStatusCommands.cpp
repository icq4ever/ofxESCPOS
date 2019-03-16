//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/ESCPOS/Commands/DefaultPrinterStatusCommands.h"
#include "ofx/IO/ByteBufferUtils.h"


namespace ofx {
namespace ESCPOS {
namespace Commands {


DefaultPrinterStatusCommands::DefaultPrinterStatusCommands()
{
}


DefaultPrinterStatusCommands::~DefaultPrinterStatusCommands()
{
}


std::size_t DefaultPrinterStatusCommands::getPrinterStatusRealTime()
{
    const uint8_t command[3] = {
                                 BaseCodes::DLE,
                                 BaseCodes::EOT,
                                 BaseCodes::STATUS_PRINTER
                               };

    std::size_t numBytesWritten = writeBytes(command, 3);

    if (3 == numBytesWritten)
    {
        uint8_t data;

//        pSerial->waitByteTimes(3);



        std::size_t numBytesRead = readByte(data);

        if (numBytesRead > 0)
        {
            std::bitset<8> bits(data);
            // std::cout << "Data Read: " << bits << std::endl;

            bool isDrawerKickoutHigh = bits[2];
            bool isOnline = bits[3];

            // package these

        }
        else
        {
            ofLogError("DefaultPrinterStatusCommands::getPrinterStatus") << "No bytes read.";
        }

    }
    else
    {
        ofLogError("DefaultPrinterStatusCommands::getPrinterStatus") << "Number of bytes written was " << numBytesWritten;
    }

    return numBytesWritten;
}


std::size_t DefaultPrinterStatusCommands::getOfflineStatus()
{
    return 0; // TBI
}


std::size_t DefaultPrinterStatusCommands::getErrorStatus()
{
    return 0; // TBI
}


std::size_t DefaultPrinterStatusCommands::getPaperStatus(){
    // return 0; // TBI
    
    // 0 : paper out
    // 1 : paper ok
    // 2 : reserved for "almost paper out" not sure working. so not used now.
    uint8_t paperStatus;

    const uint8_t command[3] = {
        BaseCodes::DLE,
        BaseCodes::EOT,
        BaseCodes::STATUS_PAPER
      };

    std::size_t numBytesWritten = writeBytes(command, 3);

    if (3 == numBytesWritten) {
        uint8_t data;

        // pSerial->waitByteTimes(3);
        std::size_t numBytesRead = readByte(data);

        if (numBytesRead > 0)    {
            std::bitset<8> bits(data);
            std::cout << "Data Read: " << bits << std::endl;


            if(data == 114)         paperStatus = 0;
            // not sure almost paper out working. so just paper OK except paper out
            // else if (data == 18)    paperStatus = 2;
            else                    paperStatus = 1;    

            // package these

        } else {
            ofLogError("DefaultPrinterStatusCommands::getPrinterStatus") << "No bytes read.";
        }

    } else {
        ofLogError("DefaultPrinterStatusCommands::getPrinterStatus") << "Number of bytes written was " << numBytesWritten;
    }

    return paperStatus;
}


} } } // namespace ofx::ESCPOS::Commands
