#include "PacketMixer.h"

#include <algorithm>

PacketMixer::PacketMixer()
    : m_engine(std::random_device{}())
{
}

void PacketMixer::shufflePackets(std::vector<Packet> &packets)
{
    std::shuffle(packets.begin(), packets.end(), m_engine);
}