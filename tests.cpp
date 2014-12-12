#include <iostream>
#include <stdexcept>
#include <cstring>
#include <functional>
#include "assert.h"
#include "string.h"

void test(std::function<void()> f) {
	try {
		f();
	} catch (std::logic_error e) {

	}
}

void default_constructor() {
	String s;
	assert(s.size() == 0);
	assert(s.get_capacity() == 2);
	const char* c = s.get_cstr();
	assert(c[0] == 0);
}

void cstr_constructor() {
	String s("qwerty");
	assert(s.size() == 6);
	assert(s.get_capacity() >= 6);
	assert(!strcmp(s.get_cstr(), "qwerty"));
}

void string_constructor() {
	String a = "qwerty";
	String b(a);
	assert(!strcmp(a.get_cstr(), b.get_cstr()));
}

void initializer_list_constructor() {
	String s = {'q', 'w', 'e', 'r', 't', 'y'};
	assert(!strcmp(s.get_cstr(), "qwerty"));
}

void access_operator() {
	String s = "qwerty";
	assert(s[0] == 'q');
	s[0] = 'o';
	assert(s[0] == 'o');
}

void iterating() {
	const char* c = "qwerty";
	String s = c;
	int i = 0;
	for (auto it = s.begin(); it != s.end(); it++, i++) {
		assert(c[i] == *it);
	}
}

void pushing_back_char() {
	String s = "qwerty";
	s.push_back('!');
	size_t sz = s.size(); const char* cstr = s.get_cstr();
	assert(sz == 7);
	assert(s[sz - 1] == '!');
}

void pushing_back_string() {
	String a = "qwerty";
	String b(a);
	a.push_back(b);
	assert(!strcmp(a.get_cstr(), "qwertyqwerty"));
	assert(a.size() == 12);
	assert(a.get_capacity() == 16);
}

void inserting_char() {
	String s = "qwerty";
	s.insert(0, 'p');
	assert(s[0] == 'p');
	assert(!strcmp(s.get_cstr(), "pqwerty"));
}

void inserting_string() {
	assert(!("lel"));
	String s = "qwerty";
	s.insert(0, "qwerty");
	assert(!strcmp(s.get_cstr(), "qwertyqwerty"));
}

int main() {
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


	/*
	//Creating strings - required:
	String str = "C-style string literal"; // is the same as: String str("C-style string literal");


	String str_2(str);
	String str_3;
	// //Optional - not required:
	String str_4 = { 'H','e','l','l','o' }; // list initializer construction
	// // Using strings
	// // access and modify:
	char ch = str[0]; // ch == 'C'
	str[0] = 'T';     // str[0] == 'T'
	cout << str.size() << endl; // prints: 22

	for (auto it = str.begin();it != str.end();++it)  // prints: T-style string literal
		cout << *it;
	str.push_back('!'); // str == String("T-style string literal!")
	str.push_back(" == ");
	str.push_back(str_4);
	char last = str.pop_back(); // last == '!'
	str.insert(0,'A');   // str_2 == String("AT-style string literal")
	str_3.insert(0,str_2); // str_3 == String("AT-style string literal")
	str_3.insert(str_3.size() - 1," another literal");  //str_3 == String("AT-style string literal another literal")
	str_3.erase(1,3); //str_3 == String("Atyle string literal another literal")
	str.swap(str_3);  // swap the contents with str_3

	// stream output and input
	std::cout << str_3;
	String input_str;
	std::cin >> input_str;

	// type conversions 
	// Required: const char* -> String
	void f(String s) 
	{
	 //...
	}

	f("a literal");  // implicit conversion from const char* 

	// Optional - not required: String -> char*  (C-style 0-terminated string)
	//
	String str_5 = "temporary";
	char* c_str = str_5.to_C_string();  // return a copy of the contents in a char array allocated with new[]
	strcmp("temporary",c_str);  // a standard C-function: char* values expected
	delete c_str;    // callers responsibility to delete the char array
	c_str = nullptr;
	*/
}