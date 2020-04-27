//
// Created by murmur wheel on 2020/4/26.
//

#ifndef VKUT_DEVICE_H
#define VKUT_DEVICE_H

#include "utility.h"

namespace vkut {

class Device;
class DeviceResource;

struct DeviceData;
class Device {
public:
    static void startup_offscreen();
    static void startup_game();
    static void shutdown();
    static Device *get();

    [[nodiscard]] const VkInstance &vk_instance() const;
    [[nodiscard]] const VkPhysicalDevice &vk_physical_device() const;
    [[nodiscard]] const VkDevice &vk_device() const;

    [[nodiscard]] VkCommandBuffer begin_transient(uint32_t family);
    [[nodiscard]] VkCommandBuffer begin_transient_universal();
    void flush_transient(VkCommandBuffer command_buffer);

    [[nodiscard]] uint32_t get_memory_type(uint32_t type_bits,
        VkMemoryPropertyFlags property_flags) const;

private:
    Device();
    ~Device();

    DeviceData *data_{ nullptr };
};

class DeviceResource {
public:
    // disable copy and move operation
    DeviceResource(const DeviceResource &) = delete;
    DeviceResource(DeviceResource &&) = delete;
    DeviceResource &operator=(const DeviceResource &) = delete;
    DeviceResource &operator=(DeviceResource &&) = delete;

    explicit DeviceResource() : ref_count_{ 1 } {}
    virtual ~DeviceResource() = default;

    uint32_t add_ref();
    uint32_t release();

private:
    int32_t ref_count_;
};

template<typename T>
class DefaultDeleter {
public:
    void operator()(T *ptr) { delete ptr; }
};

template<typename T, typename Deleter = DefaultDeleter<T>>
class Ptr;

template<typename T>
class Ptr<T, DefaultDeleter<T>> {
    static_assert(std::is_base_of<DeviceResource, T>::value,
        "T must be classes derived from DeviceResource");

public:
    using Self = Ptr<T, DefaultDeleter<T>>;

    Ptr() = default;
    // copy from other object
    Ptr(const Self &other) { set(other.ptr_); }

    // move from other object
    Ptr(Self &&other) noexcept {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    // copy from derived class
    template<typename Derived>
    explicit Ptr(const Ptr<Derived, DefaultDeleter<T>> &other) {
        static_assert(std::is_base_of<T, Derived>::value,
            "Derived must be classes derived from T");
        set(other.ptr_);
    }

    // move from derived class
    template<typename Derived>
    explicit Ptr(Ptr<Derived, DefaultDeleter<T>> &other) noexcept {
        static_assert(std::is_base_of<T, Derived>::value,
            "Derived must be classes derived from T");
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    ~Ptr() { set(nullptr); }

    Ptr<T, DefaultDeleter<T>> &operator=(const Self &other) {
        if (this != &other) {
            set(other.ptr_);
        }
        return *this;
    }

    Ptr<T, DefaultDeleter<T>> &operator=(Self &&other) noexcept {
        set(nullptr);
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }

    // assignment copy from derived object
    template<typename Derived>
    Ptr<T, DefaultDeleter<T>> &operator=(
        const Ptr<Derived, DefaultDeleter<T>> &other) noexcept {
        static_assert(std::is_base_of<T, Derived>::value,
            "Derived must be classes derived from T");
        set(other.ptr_);
        return *this;
    }

    // assignment move from derived object
    template<typename Derived>
    Ptr<T, DefaultDeleter<T>> &operator=(
        Ptr<Derived, DefaultDeleter<T>> &&other) noexcept {
        // check type
        static_assert(std::is_base_of<T, Derived>::value,
            "Derived must be classes derived from T");

        set(nullptr);
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }

    T *operator->() const { return ptr_; }

    explicit operator bool() const { return ptr_ != nullptr; }

    void set(T *ptr) {
        if (ptr) {
            ptr->add_ref();
        }

        reset();

        ptr_ = ptr;
    }

    void set_directly(T *ptr) {
        reset();
        ptr_ = ptr;
    }

    void reset() {
        if (ptr_) {
            if (ptr_->release() == 0) {
                DefaultDeleter<T>()(ptr_);
            }
            ptr_ = nullptr;
        }
    }

private:
    T *ptr_{ nullptr };
};

template<typename T, typename... Args>
Ptr<T> make_ptr(Args &&... args) {
    auto p = new T(std::forward<Args &&>(args)...);
    Ptr<T> res;
    res.set_directly(p);
    return res;
}

using DeviceResourcePtr = Ptr<DeviceResource>;

}

#endif // VKUT_DEVICE_H
