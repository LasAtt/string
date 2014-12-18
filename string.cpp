#include <cstring>
#include <cctype>
#include <utility>
#include <ostream>
#include <stdexcept>
#include "string.h"
#define NDEBUG
#include "assert.h"


/**
* Constructors
*/

//Constructor with a chararray as a parameter.
String::String(const char* s) : sz(cstrlen(s)),  capacity(npowoftwo(sz)) {
	str = new (std::nothrow) char[capacity]();
	cstrncpy(str, s, capacity);
	check();
}

//Constructor with reference to another String as a parameter.
String::String(const String& s) : sz(s.sz), capacity(s.capacity) {
	str = new (std::nothrow) char[capacity]();
	cstrncpy(str, s.str, capacity);
	check();
}

//Initializer list constructor
String::String(std::initializer_list<char> li) : sz(li.size()), capacity(npowoftwo(li.size())) {
	str = new (std::nothrow) char[capacity]();
	uint i = 0;
	for (auto it = li.begin(); it != li.end(); ++it)
		str[i++] = *it;
	check();
}

//Move constructor.
String::String(String&& other) : sz(other.sz), capacity(other.capacity), str(other.str) {
	other.sz = 0;
	other.capacity = 2;
	other.str = new (std::nothrow) char[2]();
}

//Destructor. Deletes the memory allocated for str.
String::~String() {
	delete [] str;
}

/**
* Operators
*/

//
String& String::operator=(const String& other) {
	swap(other);
	return (*this);
}

//Move assignment operator
String& String::operator=(String&& other) {
	if (this == &other)
		return (*this);

	delete [] str;
	sz = other.sz;
	capacity = other.capacity;
	str = other.str;

	other.sz = 0;
	other.capacity = 2;
	other.str = new (std::nothrow) char[2]();
	check();
}

//Accesses the given index in str. Invalid index will throw an error.
char& String::operator[](int i) {
	if (!(i >= 0 && i <= sz))
		throw std::logic_error("String operator [] called with an out of bounds integer.");
	return str[i];
}

//Implements << operation for output of String. Outputs str to out.
std::ostream& operator<<(std::ostream& out, const String s) {
	out << s.str;
	return out;
}

//Implements >> operation for reading input to a String. Reads characters to string until eof or 
//white-space. Using with extremely large inputs will have unknown results.
std::istream& operator>>(std::istream& is, String& s) {
	s.clear();
	char c;
	while(true) {
		is.get(c);
		if (std::isspace(c, is.getloc()) || is.eof())
			break;
		s.push_back(c);
	}
	s.check();
	return is;
}

//Swaps the contents of two Strings.
String& String::swap(String other) {
	std::swap(sz, other.sz);
	std::swap(capacity, other.capacity);
	std::swap(str, other.str); 

	check();

	return (*this);
}

/**
* Iterator
*/

typedef String::StringIterator str_it;

//Moves the iterator one step forward.
str_it& str_it::operator++() {
	index++;
	return *this;
}

//Post-increment that moves the iterator one-step forward.
str_it str_it::operator++(int) {
	str_it tmp(*this);
	operator++();
	return tmp;
}

//Returns the character the iterator is pointing at.
char str_it::operator*() {
	return str[index];
}

//Checks whether two iterators are the same. Should only be used on iterators of same instance 
//of a String.
bool str_it::operator==(str_it other) {
	return index == other.index;
}

//Returns the start-point of the String's iterator.
str_it String::begin() const {
	str_it begin(0, str);
	return begin;
}

//Returns the ending point of the String's iterator.
const str_it String::end() const {
	str_it end(sz, str);
	return end;
}

/**
* Basic operations
*/

//Returns the contents of the String as a newly allocated c-string. Responsibility for deletion 
//lies with the caller.
char* String::to_C_string() const {
	char* cstr = new (std::nothrow) char[sz + 1];
	cstrncpy(cstr, str, capacity);

	cstr[sz] = 0;
	return cstr;
}

//Pushes a String to the back of this string. Also for char and c-string. 
void String::push_back(String s) {
	ensure_capacity(s.sz);
	cstrncpy(str + sz, s.str, s.sz);
	sz += s.sz;
	check();
}

//Removes the last character from the String.
void String::pop_back() {
	if(sz == 0) 
		throw std::logic_error("Tried to pop an empty string.");

	str[sz] = 0;
	sz--;
	check();
}

//Inserts a string at position indicated by index. Also works for c-strings and a char due to 
//conversions defined in constructors.
void String::insert(int index, String s) {
	if (!(index <= sz && index >= 0))
		throw std::logic_error("Inserted out of bounds");

	char* prev = str;
	sz += s.sz;
	capacity = npowoftwo(sz);
	str = new (std::nothrow) char[capacity]();
	
	int k = 0;
	for (int i = 0; i < sz; ++i, k++) {
		if (i == index) 
			for (int j = 0; j < s.sz; ++j, ++i) 
				str[i] = s[j];
		str[i] = prev[k];
	}
	check();
	delete [] prev;	
}

void String::clear() {
	for (int i = 0; i < capacity; i++) 
		str[i] = 0;
	sz = 0;
}

//Erases n characters from index onwards. If n characters between index and sz don't exist, 
//an error is thrown.
void String::erase(int index, int n) {
	if (!(index >= 0 && index < sz && n > 0 && n <= sz - index))
		throw std::logic_error("Called erase with invalid index or number of characters.");
	int i;
	for (i = index; i < sz - n; i++)
		str[i] = str[i + n];
	for (; i < sz; i++)
		str[i] = 0;
	sz -= n;
	check();
}


/**
* Memory operations 
*/


//When called, ensures that the class has enough memory space for n characters.
void String::ensure_capacity(int n) {
	if (sz + n >= capacity) {
		capacity = npowoftwo(sz + n);
		allocate_space();
	}
	check();
}

//Allocates a new memory block for str and copies the contents of the old one to the new 
//destination. The old str is deleted.
void String::allocate_space() {
	char* str_new = new (std::nothrow) char[capacity]();
	cstrncpy(str_new, str, capacity);
	delete [] str;

	str = str_new;
}


/**
* Check
*/

inline void String::check() {
	assert(sz >= 0 && "The size can't be negative.");
	assert(capacity >= 2 && "The String doesn't have enough capacity for one char.");
	assert(sz < capacity && "Size of the string must be smaller than the capacity");
	assert(cstrlen(str) == sz && "The sz variable is incorrect.");
	assert(str[sz] == 0 && "The String is not a valid c-string.");
}

/**
* Helpful functions
*/

//Calculates the length of a (valid) c-string
int cstrlen(const char* s) {
	uint i = 0;
	while (s[i]) {
		i++;
	}
	return i;
}

//Copies up to n characters from one c-string to another.
char* cstrncpy(char* dst, const char* src, int n) {
	uint i = 0;
	while (i < n) {
		if (src[i] == 0)
			break;
		dst[i] = src[i];
		i++;
	}
	return dst;
}

//Finds the next power of two from the given number.
int npowoftwo(int n) {
	int r = 2;
	while (n >= r) {
		r *= 2;
	}
	return r; 
}