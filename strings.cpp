#include <iostream>
#include "string.h"


using std::endl;
using std::cout;

int main() {

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
	cout << str << endl;
	cout << str.size() << endl; // prints: 22

	for (auto it = str.begin();it != str.end();++it)  // prints: T-style string literal
		cout << *it;
	cout << endl;
	str.push_back('!'); // str == String("T-style string literal!")
	cout << str << endl;
	str.push_back(" == ");
	cout << str << endl;
	str.push_back(str_4);
	cout << str << endl;
	char last = str.pop_back(); // last == '!'
	str.insert(0,'A');   // str_2 == String("AT-style string literal")
	cout << str << endl;
	str_3.insert(0,str_2); // str_3 == String("AT-style string literal")
	cout << str_3 << endl;
	// str_3.insert(str_3.size() - 1," another literal");  //str_3 == String("AT-style string literal another literal")
	// str_3.erase(1,3); //str_3 == String("Atyle string literal another literal")
	// str.swap(str_3);  // swap the contents with str_3

	// // stream output and input
	// std::cout << str_3;
	// String input_str;
	// std::cin >> input_str;

	// // type conversions 
	// // Required: const char* -> String
	// void f(String s) 
	// {
	//  //...
	// }

	// f("a literal");  // implicit conversion from const char* 

	// // Optional - not required: String -> char*  (C-style 0-terminated string)
	// //
	// String str_5 = "temporary";
	// char* c_str = str_5.to_C_string();  // return a copy of the contents in a char array allocated with new[]
	// strcmp("temporary",c_str);  // a standard C-function: char* values expected
	// delete c_str;    // callers responsibility to delete the char array
	// c_str = nullptr;
}