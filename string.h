#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <iostream>
#include <initializer_list>
#include <iterator>

class String {
public:
	class StringIterator;

	String() : sz(0), capacity(2), str(new char[2] {0}) {};
	String(const char c) : sz(1), capacity(2), str(new char[2] {c, 0}) {};
	String(const char*);
	String(const String&);
	String(String&&);
	String(std::initializer_list<char>);
	
	String& operator=(const String&);
	String& operator=(String&&);
	String& operator+=(const String& s) { push_back(s); }
	char& operator[](int);
	friend std::ostream& operator<<(std::ostream&, const String);
	friend std::istream& operator>>(std::istream&, String&);
	String& swap(String other);

	StringIterator begin() const;
	const StringIterator end() const;

	char* to_C_string() const;
	size_t get_capacity() const noexcept(true) { return capacity; }
	size_t size() const noexcept(true) { return sz; }
	void push_back(String);
	void pop_back();
	void clear();
	void erase(int, int);
	void insert(int, String);

	//!solely for testing!
	char* get_str() const { return str; }

	~String();
private:
	//Char array that holds the contents of the string as a c-string.
	char* str;
	//Number of characters in str. The length of the string.
	size_t sz;
	//Number of chars str can hold.
	size_t capacity;

	void ensure_capacity(int);
	void allocate_space();

	inline void check();
};

//Iterator for the String class. Overrides operators to function like a standard 
//C++ iterator
class String::StringIterator {
public:
	StringIterator() : index(0), str(nullptr) {};
	StringIterator(uint i, char* s) : index(i), str(s){};

	StringIterator& operator++();
	StringIterator operator++(int);
	char operator*();
	bool operator==(StringIterator other);
	bool operator!=(StringIterator other) {return !(operator==(other));};
private:
	uint index;
	char* str;

};

int cstrlen(const char*);
char* cstrncpy(char* dst, const char* src, int n);
int npowoftwo(int);

#endif