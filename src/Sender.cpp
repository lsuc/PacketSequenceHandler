#include "Sender.h"
#include <iostream>
#include <random>
#ifdef _WIN32
#include <Winsock2.h>              // For networking functions on Windows
#pragma comment(lib, "Ws2_32.lib") // Link with Winsock library
#else
#include <arpa/inet.h> // For networking functions on Linux
#endif
#include <cstring>

constexpr uint8_t c_headerSizeBytes = 12;

Sender::Sender()
{
    // Initialize random seed
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> dis(0, (std::numeric_limits<uint16_t>::max)());
    m_sequenceNumber = dis(gen);
}

uint16_t Sender::getSequenceNumber(const char *data)
{
    const uint16_t *sequenceNumberPtr = reinterpret_cast<const uint16_t *>(data + 2);
    // Convert from network byte order (big-endian) to host byte order if needed
    uint16_t sequenceNumber = ntohs(*sequenceNumberPtr);
    return sequenceNumber;
}

Packet Sender::generateNextPacket()
{
    // Generate random payload size (between 1 and 100 bytes)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> sizeDis(1, 100);
    int payloadSize = sizeDis(gen);

    // Generate random payload data
    std::vector<char> payload(payloadSize);
    std::uniform_int_distribution<int> dataDis(0, 255);
    for (char &byte : payload)
    {
        byte = static_cast<char>(dataDis(gen));
    }

    // Create packet with header (header + payload)
    std::vector<char> packet(c_headerSizeBytes + payloadSize);

    // Set sequence number in header (in network byte order)
    uint16_t sequenceNumberNetwork = htons(m_sequenceNumber);
    std::cout << "Packet sequence number: " << m_sequenceNumber << std::endl;
    std::memcpy(&packet[2], &sequenceNumberNetwork, sizeof(uint16_t)); // Copy sequence number to packet header
    // Copy payload data to packet
    std::copy(payload.begin(), payload.end(), packet.begin() + c_headerSizeBytes);

    // Print payload sequence number, size and bytes before returning the packet
    std::cout << "Payload size: " << payloadSize << " bytes" << std::endl;
    std::cout << "Payload bytes: ";
    for (const char &byte : payload)
    {
        std::cout << byte << " ";
    }
    std::cout << std::endl;

    // Increment sequence number for next packet
    m_sequenceNumber++;

    // Create a Packet struct and return it
    Packet packetStruct;
    packetStruct.data = new char[packet.size()];                                      // Allocate memory for data, since it has variable size
    std::memcpy(const_cast<char *>(packetStruct.data), packet.data(), packet.size()); // Copy packet data
    packetStruct.size = packet.size();

    return packetStruct;
}