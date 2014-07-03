#ifndef PATCH_HPP
#define PATCH_HPP

#include <memory>
#include <type_traits>
#include <utility>
#include <string>
#include <sstream>

namespace patch {
	template <typename T>
	std::string to_string(const T& n) {
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}

	template <typename T, typename... Args>
	T* make(Args&&... args) {
		return new T(std::forward<Args>(args)...);
	}

	template <typename T, typename... Args>
	std::unique_ptr<T> make_unique_helper(std::false_type, Args&&... args) {
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	template <typename T, typename... Args>
	std::unique_ptr<T> make_unique_helper(std::true_type, Args&&... args) {
		static_assert(std::extent<T>::value == 0,
		   "make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");

		typedef typename std::remove_extent<T>::type U;
		return std::unique_ptr<T>(new U[sizeof...(Args)]{std::forward<Args>(args)...});
	}
	
	template <typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args) {
		return make_unique_helper<T>(std::is_array<T>(), std::forward<Args>(args)...);	
	}
}

#endif