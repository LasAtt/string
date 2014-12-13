#include <cstring>
#include <cctype>
#include <ostream>
#include <stdexcept>
#include "string.h"
#include "assert.h"


/**
* Constructors
*/

String::String(const char* s) {
	sz = cstrlen(s);
	capacity = sz + 1;
	str = new char[capacity];

	cstrncpy(str, s, capacity);
}

String::String(const String& s) : sz(s.sz), capacity(s.capacity + 1) {
	str = new char[capacity];
	cstrncpy(str, s.str, capacity);
}

String::String(std::initializer_list<char> li) : sz(li.size()), capacity(li.size() + 1) {
	str = new char[capacity];

	uint i = 0;
	for (auto it = li.begin(); it != li.end(); ++it)
		str[i++] = *it;
}

String::~String() {
	delete [] str;
}

/**
* Operators
*/


String String::operator=(String& other) {
	sz = other.sz;
	capacity = other.capacity;
	str = new char[capacity];
	cstrncpy(str, other.str, capacity);
}

char& String::operator[](int i) {
	if (i < 0 || i > sz) {
		throw std::domain_error("String operator [] called with an out of bounds integer.");
	}
	return str[i];
}

std::ostream& operator<<(std::ostream& out, const String s) {
	out << s.str;
	return out;
}

std::istream& operator>>(std::istream& is, String& s) {
	s.empty();
	char c;
	while(is.good()) {
		is.get(c);
		if (std::isspace(c, is.getloc())) {
			s.push_back(0);
			return is;
		}
		s.push_back(c);
	}
	s.push_back(0);
	return is;
}

/**
* Iterator
*/

typedef String::StringIterator str_it;

str_it& str_it::operator++() {
	index++;
	return *this;
}

str_it str_it::operator++(int) {
	str_it tmp(*this);
	operator++();
	return tmp;
}

char str_it::operator*() {
	return str[index];
}

bool str_it::operator==(str_it other) {
	return index == other.index;
}

str_it String::begin() const {
	str_it begin(0, str);
	return begin;
}

const str_it String::end() const {
	str_it end(sz, str);
	return end;
}

/**
* Basic operations
*/

void String::push_back(char c) {
	ensure_space(1);
	str[sz++] = c;
	str[sz] = 0;
}

void String::push_back(String s) {
	ensure_space(s.sz);
	cstrncpy(str + sz, s.str, s.sz);
	sz += s.sz;
}

char String::pop_back() {
	assert(sz != 0 && "Tried to pop an empty string.");
	str[sz] = 0;
	return str[sz--];
}

void String::insert(int index, char c) {
	String s(c);
	insert(index, s);
}

void String::insert(int index, String s) {
	assert((index <= sz && index >= 0) && "Inserted out of bounds");

	char* prev = str;
	str = new char[npowoftwo(sz + s.sz)];
	sz += s.sz;

	int k = 0;
	for (int i = 0; i < sz; ++i, k++) {
		if (i == index) 
			for (int j = 0; j < s.sz; ++j, ++i) 
				str[i] = s[j];
		str[i] = prev[k];
	}
	delete [] prev;	
}

void String::empty() {
	for (int i = 0; i < capacity; i++) {
		str[i] = 0;
	}
	sz = 0;
}

void String::erase(int index, int n) {
	assert((index >= 0 && index < sz && n > 0 && n < sz - index) && "Erased with invalid index or number of characters.");
	int i;
	for (i = index; i < sz - n; i++)
		str[i] = str[i + n];
	for (; i < sz; i++)
		str[i] = 0;
}

/**
* Memory operations 
*/

void String::ensure_space(int n) {
	if (sz + n >= capacity) {
		grow_capacity(npowoftwo(sz + n));
	}
}

void String::grow_capacity(int n) {
	char* str_new = new char[n];
	cstrncpy(str_new, str, capacity);
	delete [] str;

	capacity = n;	
	str = str_new;
}


/**
* Helpful functions
*/

int cstrlen(const char* s) {
	uint i = 0;
	while (s[i]) {
		i++;
	}
	return i;
}

char* cstrncpy(char* dst, const char* src, int n) {
	uint i = 0;
	do {
		dst[i] = src[i];
		i++;
	} while (src[i] && i < n);
	return dst;
}

int npowoftwo(int n) {
	int r = 2;
	while (n > r) {
		r *= 2;
	}
	return r; 
}