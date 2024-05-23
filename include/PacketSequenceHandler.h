#ifndef PACKET_SEQUENCE_HANDLER_H
#define PACKET_SEQUENCE_HANDLER_H

#include <cstdint>

class PacketSequenceHandler final
{
public:
    static void print();
    static void write(const char *data, int size);
};

#endif // PACKET_SEQUENCE_HANDLER_H