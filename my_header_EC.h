/**************************************************************

EXTRA CREDIT - HEADER FILE

Author: Alice Zhu
Course: CSCE 1030.002 (2307)
Date: 2 May 2918
Description: 

Library Database - Allows user to add a book, check out a book,
return a book, search for a book based on author or title, and
search for a list of books borrowed by a user. Reads external
files books.txt and students.txt.

***************************************************************/

#include <ctime>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;
void get_date(int &m, int &d, int &y);

struct Date{
	int month, day, year;
};

struct Book{
	string author, title, euid;
	long int isbn;
	Date borrowed;
};

struct Student{
	string euid;
	int number_of_books;
	typedef Book* bkPtr;
	bkPtr b;
};