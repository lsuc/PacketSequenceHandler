#ifndef SENDER_H
#define SENDER_H

#include <cstdint>
#include <vector>

struct Packet
{
    const char *data;
    int size;
};

class Sender
{
public:
    Sender();
    Packet generateNextPacket();

private:
    uint16_t getSequenceNumber(const char *data);
    uint16_t m_sequenceNumber;
};

#endif // SENDER_H