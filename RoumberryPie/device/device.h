#ifndef DEVICE_H
#define DEVICE_H

#include <string>

/// The class Device is an abstract base class containing all
/// basic device interface functions.
/// This abstract class cannot be instantiated, because this type of
/// classes contains a least one abstract member function.
class Device
{
public:
    Device(const std::string &id): ID_{id} {}
    Device(const Device &d) = delete;//non-construction copyable
    Device& operator=(const Device&) = delete;//non copyable
    virtual ~Device() {}
    const std::string &getID() const { return ID_;}
    /// Abstract functions, must be implemented in the derived classes.
    virtual void initialise() = 0;
    virtual void reset() = 0;
    virtual void shutdown() = 0;

private:
    const std::string ID_;
};

#endif // DEVICE_H
