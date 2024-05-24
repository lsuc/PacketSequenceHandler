#include <iostream>

#include "PacketSequenceHandler.h"
#include "Sender.h"
#include "PacketMixer.h"

int main(int, char **)
{
    std::cout << "Hello!\n";

    const char data1[] = {
        0x00, 0x00, 0x30, 0x39, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 'H', 'e', 'l', 'l', 'o'};
    const char data2[] = {
        0x00, 0x00, 0x30, 0x3A, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 'W', 'o', 'r', 'l', 'd'};

    PacketSequenceHandler handler("output.bin");

    /*
    Sender sender;
    std::vector<Packet> packets;
    const int packetNum = 15;
    packets.reserve(packetNum);

    PacketMixer mixer;

    for (int i = 0; i < packetNum; i++)
    {
        const auto packet = sender.generateNextPacket();
        packets[i] = packet;
    }
    // mixer.shufflePackets(packets);
    for (int i = packetNum - 1; i >= 0; i--)
    {
        handler.write(packets[i].data.data(), packets[i].data.size());
    }*/
    handler.write(data2, sizeof(data2));
    handler.write(data1, sizeof(data1));
}
