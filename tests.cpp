#include <iostream>
#include <stdexcept>
#include <cstring>
#include <functional>
#include <utility>
#include <sstream>
#include "assert.h"
#include "string.h"

int tests = 0;
int failed_tests = 0;
const char* func;

void test(std::function<void()> f) {
	tests++;
	try {
		f();
	} catch (std::logic_error e) {
		failed_tests++;
	}
}

void check_same(const char* result, const char* expected) {
	try {
		assert(!strcmp(result, expected));
	} catch (std::logic_error e) {
		std::cerr << "  test: " << func << "(); expected: '" << expected << "', was: '" << result << "'" << std::endl; 
		throw e;
	}
}

void check_same(int result, int expected) {
	try {
		assert(result == expected);
	} catch (std::logic_error e) {
		std::cerr << "  test: " << func << "(); expected: '" << expected << "', was: '" << result << "'" << std::endl; 
		throw e;
	}
}

void check_same(char result, char expected) {
	try {
		assert(result == expected);
	} catch (std::logic_error e) {
		std::cerr << "  test: " << func << "(); expected: '" << "', was: '" << result << "'" << std::endl; 
		throw e;
	}
}

void default_constructor() {
	func = __func__;

	String s;
	check_same(s.size(), 0);
	check_same(s.get_capacity(), 2);
	check_same(s[0], '\0');
}

void cstr_constructor() {
	func = __func__;

	String s("qwerty");
	check_same(s.size(), 6);
	check_same(s.get_capacity(), 8);
	check_same(s.get_str(), "qwerty");
}

void string_constructor() {
	func = __func__;

	String a = "qwerty";
	String b(a);
	check_same(a.get_str(), b.get_str());
}

void initializer_list_constructor() {
	func = __func__;

	String s = {'q', 'w', 'e', 'r', 't', 'y'};
	check_same(s.get_str(), "qwerty");
}

void access_operator() {
	func = __func__;

	String s = "qwerty";
	check_same(s[0], 'q');
	s[0] = 'o';
	check_same(s[0], 'o');
}

void iterating() {
	func = __func__;

	const char* c = "qwerty";
	String s = c;
	int i = 0;
	for (auto it = s.begin(); it != s.end(); it++, i++)
		check_same(c[i], *it);
}

void pushing_back_char() {
	func = __func__;

	String s = "qwerty";

	s.push_back('!');
	check_same(s.size(), 7);
	check_same(s[s.size() - 1], '!');
}

void pushing_back_string() {
	func = __func__;

	String a = "qwerty";
	String b(a);

	a.push_back(b);
	check_same(a.get_str(), "qwertyqwerty");
	check_same(a.size(), 12);
	check_same(a.get_capacity(), 16);
}

void inserting_char() {
	func = __func__;

	String s = "qwerty";

	s.insert(0, 'p');
	check_same(s[0], 'p');
	check_same(s.get_str(), "pqwerty");

	s.insert(3, 'p');
	check_same(s[3], 'p');
	check_same(s.get_str(), "pqwperty");
}

void inserting_string() {
	func = __func__;

	String s = "qwerty";

	s.insert(0, "qwerty");
	check_same(s.get_str(), "qwertyqwerty");

	s.insert(3, "qwerty");
	check_same(s.get_str(), "qweqwertyrtyqwerty");
}

void erasing() {
	func = __func__;

	String s = "qwerty";

	s.erase(0, 1);
	check_same(s.get_str(), "werty");

	s.erase(2, 3);
	check_same(s.get_str(), "we");

	s.erase(0, 2);
	check_same(s.get_str(), "");
}

void swapping() {
	func = __func__;

	String a = "qwerty";
	String b = "asd";
	std::swap(a, b);
	check_same(a.get_str(), "asd");
	check_same(b.get_str(), "qwerty");
}

void moving() {
	func = __func__;

	String a = "qwerty";
	String b = std::move(a);
	check_same(b.get_str(), "qwerty");

	String c(std::move(b));
	check_same(c.get_str(), "qwerty");

	check_same(a.get_str(), "");
	check_same(b.get_str(), "");
}

void iostreaming() {
	func = __func__;

	std::stringstream a, b;
	String s;

	a << "qwerty";
	a >> s;
	check_same(s.get_str(), "qwerty");

	b << s;
	b >> s;
	check_same(s.get_str(), "qwerty");
}

int main() {
	std::cout << "running tests..." << std::endl;
	test(default_constructor);
	test(cstr_constructor);
	test(string_constructor);
	test(initializer_list_constructor);
	test(access_operator);
	test(iterating);
	test(pushing_back_char);
	test(pushing_back_string);
	test(inserting_char);
	test(inserting_string);
	test(erasing);
	test(swapping);
	test(moving);
	test(iostreaming);
	std::cout << "finished; " << failed_tests << '/' << tests << " tests failed" << std::endl;
}