#ifndef PACKET_SEQUENCE_HANDLER_H
#define PACKET_SEQUENCE_HANDLER_H

#include <cstdint>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <fstream>

class PacketSequenceHandler final
{
public:
    PacketSequenceHandler(const std::string &filename);
    ~PacketSequenceHandler();

    void write(const char *data, int size);

private:
    static uint16_t getSequenceNumber(const char *data);
    void writePayload(const char *payload, int32_t size);
    void writeBufferedPackets();

    std::map<uint16_t, std::vector<char>> m_packetBuffer;
    std::ofstream m_outputFile;

    bool m_initialSequenceSet{false};
    uint16_t m_nextSequenceNumber{0};
    std::set<uint16_t> m_receivedSequenceNumbers;
};

#endif // PACKET_SEQUENCE_HANDLER_H