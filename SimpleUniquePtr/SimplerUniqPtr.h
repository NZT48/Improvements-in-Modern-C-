#include <cstdint>
#include <algorithm>


class SimpleUniquePtr {

public:
    SimpleUniquePtr() : ptr(nullptr) {}

    SimpleUniquePtr(int8_t& sup) {
        ptr = &sup;
    }

    void swap(SimpleUniquePtr& other) noexcept {
        using std::swap;
        swap(ptr, other.ptr);
    }

    SimpleUniquePtr(SimpleUniquePtr&& sup)  noexcept : ptr(nullptr) {
        this->swap(sup);
    }

    SimpleUniquePtr& operator= (SimpleUniquePtr&& sup) noexcept {
       this->swap(sup);
       return *this;
   }

    ~SimpleUniquePtr() {
        ptr = nullptr;
        delete ptr;
    }

    SimpleUniquePtr(const SimpleUniquePtr& sup) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr& sup) = delete;

    int8_t* operator->() const { return ptr; }
    int8_t& operator*() const { return *ptr; }

    int8_t* get() const {return ptr;}


private:
    int8_t* ptr;

};
