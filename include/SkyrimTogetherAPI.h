#pragma once

// Skyrim Together Plugin API V1: party messages on a named channel.
// The server relays the opaque bytes to the sender's party; it does not interpret or store them.

#include <cstddef>
#include <cstdint>

namespace SkyrimTogetherAPI
{
enum class InterfaceVersion : std::uint8_t
{
    V1 = 1
};

enum class SendResult : std::uint8_t
{
    Ok,
    NotConnected,
    NotInParty,
    TooLarge,
    BadChannel
};

constexpr std::size_t kMaxMessageSize = 256;
constexpr std::size_t kMaxChannelNameSize = 64;

using ChannelHandle = std::uint32_t;
using MessageCallback = void (*)(std::uint32_t aSenderId, const char* apBytes, std::size_t aLength);
using PartyChangedCallback = void (*)(std::uint32_t aPlayerId, bool aJoined);

class IVSkyrimTogether1
{
public:
    virtual ~IVSkyrimTogether1() = default;

    // Returns 0 if the name is invalid or already registered. Channels live until the process exits.
    // Either callback may be null.
    virtual ChannelHandle RegisterChannel(const char* apName, MessageCallback aOnMessage, PartyChangedCallback aOnPartyChanged) noexcept = 0;

    // Sends to the local player's party, sender excluded. Callable from any thread.
    virtual SendResult Send(ChannelHandle aChannel, const char* apBytes, std::size_t aLength) noexcept = 0;

    // Sends to one member of the local player's party. Callable from any thread.
    virtual SendResult SendTo(ChannelHandle aChannel, std::uint32_t aPlayerId, const char* apBytes, std::size_t aLength) noexcept = 0;

    // 0 while not connected.
    virtual std::uint32_t GetLocalPlayerId() const noexcept = 0;
    virtual bool IsInParty() const noexcept = 0;
};

// Exported by SkyrimTogether.exe under kRequestPluginAPIName. Returns nullptr when V1 is unavailable.
using RequestPluginAPI_t = void* (*)(InterfaceVersion aVersion);

// Deliberately specific: other SKSE plugins export a function named RequestPluginAPI too.
constexpr const char* kRequestPluginAPIName = "SkyrimTogetherRequestPluginAPI";
} // namespace SkyrimTogetherAPI
