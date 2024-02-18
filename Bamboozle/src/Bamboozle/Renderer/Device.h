#pragma once

class VidDeviceInterface
{
public:
    VidDeviceInterface() = default;

    // Not copyable or movable
    VidDeviceInterface(const VidDeviceInterface&) = delete;
    void operator=(const VidDeviceInterface&) = delete;
    VidDeviceInterface(VidDeviceInterface&&) = delete;
    VidDeviceInterface& operator=(VidDeviceInterface&&) = delete;

private:

};