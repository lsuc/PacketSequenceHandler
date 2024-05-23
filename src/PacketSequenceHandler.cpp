#include "PacketSequenceHandler.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h> // For ntohs
#include <fstream>

constexpr uint8_t c_headerSizeBytes = 12;
constexpr uint8_t c_sequenceStartByte = 2;

PacketSequenceHandler::PacketSequenceHandler(const std::string &filename) : m_outputFile(filename, std::ios::out | std::ios::binary)
{
    if (!m_outputFile)
    {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return; // TODO should this throw instead if the file can't be open?
    }
}

PacketSequenceHandler::~PacketSequenceHandler()
{
    // We also might want to save all the buffered data to another file before exiting
    if (m_outputFile)
    {
        if (!m_initialSequenceSet)
        {
            const auto initialSequenceNumber = *m_receivedSequenceNumbers.begin();
            m_nextSequenceNumber = initialSequenceNumber;
        }
        writeBufferedPackets();
        m_outputFile.close();
    }
}

void PacketSequenceHandler::write(const char *data, int size)
{
    if (size <= c_headerSizeBytes)
    {
        return;
    }
    uint16_t sequenceNumber = getSequenceNumber(data);
    const char *payload = data + c_headerSizeBytes;
    int payloadSize = size - c_headerSizeBytes;

    std::vector<char> payloadData(payload, payload + payloadSize);
    m_packetBuffer[sequenceNumber] = payloadData;

    std::cout << "Sequence Number: " << sequenceNumber << ", Payload Size: " << payloadSize << std::endl;

    if (!m_initialSequenceSet)
    {
        m_receivedSequenceNumbers.insert(sequenceNumber);
        if (m_receivedSequenceNumbers.size() >= NUM_PACKETS_TO_DETERMINE_INITIAL_SEQ)
        {
            const auto initialSequenceNumber = *m_receivedSequenceNumbers.begin();
            m_nextSequenceNumber = initialSequenceNumber;
            m_initialSequenceSet = true;
            std::cout << "Initial sequence number determined: " << initialSequenceNumber << std::endl;
            writeBufferedPackets();
        }
    }

    if (sequenceNumber == m_nextSequenceNumber)
    {
        writePayload(payload, payloadSize);
        m_nextSequenceNumber++;

        writeBufferedPackets();
    }
    else
    {
        // Buffer the packet if it's out of order
        std::cout << "Buffering the packet with sequence number " << sequenceNumber << std::endl;
        std::vector<char> payloadData(payload, payload + payloadSize);
        m_packetBuffer[sequenceNumber] = payloadData;
    }
}

void PacketSequenceHandler::writePayload(const char *payload, int32_t size)
{
    // Write the payload data
    m_outputFile.write(payload, size);
}

void PacketSequenceHandler::writeBufferedPackets()
{
    // Check buffer for subsequent packets
    for (auto it = m_packetBuffer.begin(); it != m_packetBuffer.end();)
    {
        if (it->first == m_nextSequenceNumber)
        {
            writePayload(it->second.data(), it->second.size());
            it = m_packetBuffer.erase(it);
            m_nextSequenceNumber++;
        }
        else
        {
            break;
        }
    }
}

uint16_t PacketSequenceHandler::getSequenceNumber(const char *data)
{
    const uint16_t *sequenceNumberPtr = reinterpret_cast<const uint16_t *>(data + c_sequenceStartByte);
    // Convert from network byte order (big-endian) to host byte order if needed
    uint16_t sequenceNumber = ntohs(*sequenceNumberPtr);
    return sequenceNumber;
}