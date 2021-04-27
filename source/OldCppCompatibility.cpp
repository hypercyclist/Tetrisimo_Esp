#include "new"

#if __cpp_sized_deallocation

void operator delete(void* ptr, std::size_t) _GLIBCXX_USE_NOEXCEPT {
    delete ptr;
}

void operator delete[](void* ptr, std::size_t) _GLIBCXX_USE_NOEXCEPT {
    delete[] ptr;
}

#endif

//For GCC version above 4.8.2 use this flag to use string header.
//-D_GLIBCXX_USE_CXX11_ABI=0