#include <iostream>
#include <initializer_list>
#include <iterator>


class String {
public:
	class StringIterator;

	String() : str(new char[1] {0}), sz(0), capacity(2) {};
	String(const char c) : str(new char[1] {c}), sz(1), capacity(2) {};
	String(const char*);
	String(const String&);
	String(String&& other);
	String(std::initializer_list<char>);
	

	String operator=(String&);
	String& operator=(String&&);
	char& operator[](int);
	friend std::ostream& operator<<(std::ostream&, String);

	StringIterator begin() const;
	const StringIterator end() const;
	
	const char* get_cstr() const noexcept(true) { return str; }
	size_t get_capacity() const noexcept(true) { return capacity; }
	size_t size() const noexcept(true) { return sz; }
	void push_back(char);
	void push_back(String);
	char pop_back();

	void insert(int, char);
	void insert(int, String);

	~String();
private:
	char* str;
	size_t sz;
	size_t capacity;

	void grow_capacity(int);

	void ensure_space(int);
};

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