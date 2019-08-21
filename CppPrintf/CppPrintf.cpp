#include <iostream>
#include <string>
#include <type_traits>
#include <tuple>

template<typename T>
T sum(T x) {
	return x;
}

template<typename T, typename... Args>
auto sum(T x, Args... args) {
	return x + sum(args...);
}
/*
template<typename T, typename... Args>
T sum(T x, Args... args) {
	if constexpr(sizeof...(args) == 0) { return x; }
	else return x + sum(args...);
}
*/
/*
template <class T, class ...Rest> // requires SameType<T, Rest...>
inline constexpr T const & min(T const &first, Rest const &... rest) {
  return do_min(first, rest...);
}

template<typename T, typename T, typename... Args>
constexpr auto const &do_min(T const &v0, T const &v1, Args const &...rest) {
    return do_min(v0 < v1 ? v0 : v1, rest...);
}

template <class T>
  constexpr T const &do_min(T const &v) {
    return v;
}
*/
/*
template <typename Arg1, typename Arg2>
constexpr typename std::common_type<Arg1, Arg2>::type min(Arg1&& arg1, Arg2&& arg2){
    return arg1 < arg2 ? std::forward<Arg1>(arg1) : std::forward<Arg2>(arg2);
}

template <typename Arg, typename... Args>
constexpr typename std::common_type<Arg, Args...>::type min(Arg&& arg, Args&&... args){
    return min(std::forward<Arg>(arg), min(std::forward<Args>(args)...));
}
*/
template<typename T, typename Q>
auto min(T x, Q y) {
	return x < y ? x : y;
}


template<typename T, typename... Args>
auto min(T x, Args... args) {
	auto tmp = min(args...);
	return x < tmp ? x : tmp;
}

//<typename T>
bool my_printf(const char* format) {
	std::cout << format;
}

template<typename T, typename... Args>
bool my_printf(const char* format,T t, Args... args) {
	std::string str(format);
	int i = sizeof...(args);
	for (std::string::iterator it=str.begin(); it!=str.end(); ++it) {
		if( *it != '%' ){
			std::cout << *it;
		} else {
			++it;
			switch(*it) {
				case 's':
					if (std::is_pointer<T>::value){
						std::cout<< t;
						my_printf(format +(int)(it-str.begin()+1), args...);
						return true;
					} else {
						std::cerr << std::endl << "Incorrect type" << std::endl;
						return true;
					}
					break;
				case 'd':
					if (std::is_integral<T>::value) {
						std::cout<< t;
						my_printf(format +(int)(it-str.begin()+1), args...);
						return true;
					} else {
						std::cerr << std::endl << "Incorrect type" << std::endl;
						return true;
					}
					break;
				case 'f':
					if(std::is_floating_point<T>::value) {
						std::cout<< t;
						my_printf(format +(int)(it-str.begin()+1), args...);
						return true;
					} else {
						std::cerr << std::endl << "Incorrect type" << std::endl;
						return true;
					}
					break;
				default:
					std::cout << '%' << *it;
			}
		}
	}
}


int main() {
	// sum = 17.4
	std::cout << sum(2, 1.8, 3.8, 4, 5.8) << std::endl;
	// sum = 17.4
	std::cout << sum(1.8, 2, 3.8, 4, 5.8) << std::endl;

	// min = 1.1
	std::cout << min(2.2, 1.1, 4, 4, 58) << std::endl;
	// min = -58
	std::cout << min(2.2, 1.1, 4, 4, -58) << std::endl;

	// Test #1: OK
	// Simple check
	// New line
	// Again new line
	my_printf("Simple check\nNew line\nAgain new line\n");
	// Test #2: Invalid number of arguments
	my_printf(" text %s, integral value %d than something %d\n", "SUCCESSFULLY", 85);
	// Test #3: Incorrect type
	my_printf(" text %s, integral value %d than something %d\n", "SUCCESSFULLY", 85, 6.67);
	// Test #4: Invalid number of arguments
	my_printf("Some text %s, some floating point number %f again something %k\n", "45", 89.7, 56);
	// Test #5: OK - Ignoring %k
	// Some text 45, some floating point number 89.700000 again something %k
	my_printf("Some text %s, some floating point number %f again something %k\n", "45", 89.7);
	// Test #6: OK
	// Some text 45, some floating point number 89.700000 again something 56
	my_printf("Some text %s, some floating point number %f again something %d\n", "45", 89.7, 56);

	return 0;
}
