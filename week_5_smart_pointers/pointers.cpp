#include<iostream>
#include<vector>
#include<memory>

// unique_ptr
// shared_ptr


namespace myPointers {
    template<class T>
    class UniquePtr {
        T* data;
        public:
        unique_ptr(): data{nullptr} {}
        unique_ptr(T* _data): data{_data} {}
        unique_ptr(const unique_ptr<T>&) = delete;
        unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
        unique_ptr(unique_ptr<T>&& o): data{o.data} {
            o.data = nullptr;
        }
        unique_ptr<T>& operator=(const unique_ptr<T>&& o) {
            data = o.data;
            o.data = nullptr;
        }
        ~unique_ptr() {delete data;}
        bool empty() const {
            return data == nullptr;
        }
        T* operator ->(){
            return data;
        }
        T& operator *(){
            *data;
        }
        explicit operator bool() const {
            return data == nullptr;
        }
    };
    template<class T>
    class Shared_ptr {
        T* data;
        int* refCount;
        public:
        shared_ptr(): data{nullptr}, refCount{nullptr} {}
        shared_ptr(T* _data): data{_data}, refCount{new int(1)} {}
        shared_ptr(const shared_ptr<T>& o): data{o.data}, refCount{o.refCount} {
            *refCount++;
        }
        ~shared_ptr() {
            if(refCount && *refCount > 1) {
                *refCount--;
            } else {
                delete data;
                delete refCount;
            }

        }
        shared_ptr<T>& operator=(const shared_ptr<T>& o) {
            if(this != &o) {
                data = o.data;
                refCount = o.refCount;
                *refCount++;
            }
            return *this;
        }
        T* operator ->(){
            return data;
        }
        T& operator *(){
            return *data;
        }
        explicit operator bool() const {
            return data == nullptr;
        }
    };
}
int main() {
    // int* num_ptr = new int{2};
    // *num_ptr;
    std::vector<int>* v_ptr = new std::vector<int>{1,2,3};
    // v_ptr->size();
    myPointers::unique_ptr<std::vector<int>> u_ptr{new std::vector<int>{1,2,3}};
    std::cout << std::boolalpha << u_ptr.empty() << std::endl;
    std::cout << u_ptr->size() << std::endl;
    myPointers::unique_ptr<std::vector<int>> u2_ptr{std::move(u_ptr)};
    std::cout << std::boolalpha << u_ptr.empty() << std::endl;
    std::cout << std::boolalpha << u2_ptr.empty() << std::endl;
    std::cout << u2_ptr->size() << std::endl;
    // if(u2_ptr) {

    // }
    myPointers::shared_ptr<std::vector<int>> sh1_ptr{new std::vector<int>{1,2,3}};
    myPointers::shared_ptr<std::vector<int>> sh2_ptr{sh1_ptr};
}