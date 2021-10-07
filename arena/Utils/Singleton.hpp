/**
 * @file Singleton.hpp
 * @author Siddharth Mishra
 * @brief Provides a way to easily create singleton classes.
 * @version 0.0
 * @date 2021-09-26
 * 
 */

#ifndef XVM_ARENA_UTIL_SINGLETON_HPP
#define XVM_ARENA_UTIL_SINGLETON_HPP

template<typename Derived>
class Singleton{
public:
    /// deleted copy constructor
    Singleton(const Singleton& other) = delete;
    /// deleted assignment operator
    Singleton& operator = (const Singleton& other) = delete;
    /// deleted copy constructor
    Singleton(Singleton&& other) = delete;
    /// deleted assignment operator
    Singleton& operator = (Singleton&& other) = delete;

    /**
     * @brief Get the Instance of Derived class type
     * 
     * @return Derived& 
     */
    static Derived* Get(){
        if(!derived){
            derived = new Derived();
        }

        return derived;
    };

protected:
    // protected singleton constructor
    Singleton(){}

private:
    // derived class instance
    static inline Derived* derived;
};

#endif//XVM_ARENA_UTIL_SINGLETON_HPP