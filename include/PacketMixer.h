#ifndef PACKET_MIXER_H
#define PACKET_MIXER_H

#include "Sender.h"
#include <vector>
#include <random>

class PacketMixer
{
public:
    PacketMixer();

    // Function to shuffle the packets randomly
    void shufflePackets(std::vector<Packet> &packets);

private:
    std::mt19937 m_engine; // Random number engine
};

#endif // PACKET_MIXER_H