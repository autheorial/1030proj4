/**************************************************************

EXTRA CREDIT - MAIN FILE

Author: Alice Zhu
Course: CSCE 1030.002 (2307)
Date: 2 May 2918
Description: 

Library Database - Allows user to add a book, check out a book,
return a book, search for a book based on author or title, and
search for a list of books borrowed by a user. Reads external
files books.txt and students.txt.

***************************************************************/

#include "my_header_EC.h" // libraries, get_date, and structs

// GLOBAL VARIABLES

// streams
	ifstream insBk;
	ofstream ofsBk;
	ifstream insStu;
	ofstream ofsStu;
	
// book struct and pointer
	Book book;
	typedef Book* bkPtr;
	bkPtr b; // cleared at the end of every scope

// student struct and pointer
	Student student;
	typedef Student* stuPtr;
	stuPtr d;

// numbooks and numstudents initialized in main after respective functions
	int numbooks, numstudents;

// file
	FILE *file;

/**************************************** provided functions ****************************************/

int number_of_students()
{
	string line;int count=0;
	ifstream fin;fin.open("students.txt");
	while(getline(fin, line))
	{
		++count;
	}
	return count;
}

int number_of_books()
{
	string line;int count=0;
	ifstream fin;fin.open("books.txt");
	while(getline(fin, line))
	{
		++count;
	}
	return count;
}

/**************************************** project functions ****************************************/

/**************************************** called from other functions ****************************************/

void stream_in_books(ifstream& insBk){
	// opens books.txt, does NOT close
	insBk.open("books.txt");
	if(!insBk.is_open()){
			cout << "Error accessing book database." << endl;
			exit(EXIT_FAILURE);
		} // end fail

	return;
}

void stream_in_students(ifstream& insStu){
	// opens students.txt, does NOT close
	insStu.open("students.txt");
	if(!insStu.is_open()){
			cout << "Error accessing student database." << endl;
			exit(EXIT_FAILURE);
		} // end fail

	return;
}

void update_books(struct Book * b, int numbooks, ofstream& ofsBk){

	// calls an updated array struct b, overwrites contents of books.txt with array struct
	ofsBk.open("books.txt");
	if(!ofsBk.is_open()){
		cout << "Error accessing book database." << endl;
		exit(EXIT_FAILURE);
	} // end fail

	for (int i = 0; i < numbooks; ++i){ // printing all elements of struct on row of array
		ofsBk << (b[i]).author << '\t' 
				<< (b[i]).title << '\t'
				<< (b[i]).isbn << '\t'
				<< (b[i]).euid << '\t'
				<< (b[i]).borrowed.month << '\t'
				<< (b[i]).borrowed.day << '\t'
				<< (b[i]).borrowed.year;

	} // done printing elements of current row

	ofsBk.close();

	return;
}

void update_students(struct Student * d, int numstudents, ofstream& ofsStu){

	// calls an updated array struct d, overwrites contents of students.txt with array struct
	ofsStu.open("students.txt");
			if(!ofsStu.is_open()){
				cout << "Error accessing student database." << endl;
				exit(EXIT_FAILURE);
			} // end fail

	for (int j = 0; j < numstudents; ++j){ // printing all elements of struct on row of array
		ofsStu << (d[j]).euid << '\t' 
				<< (d[j]).number_of_books
				<< endl;
			} // done printing elements of current row

	ofsStu.close();
	
	return;

}

void printBooksNoEuid(struct Book * b, int i){ 

	// prints book data without euid; inside a search conditional from respective search function
	cout << (b[i]).author << '\t' 
		<< (b[i]).title << '\t'
		<< (b[i]).isbn << '\t'
		<< (b[i]).borrowed.month << '\t' 
		<< (b[i]).borrowed.day << '\t' 
		<< (b[i]).borrowed.year;
		return;

}

/**************************************** searching ****************************************/

void search_by_author(){
	
	bool nameFound = false; // search result
	numbooks = number_of_books(); // count books

	stream_in_books(insBk);
		b = new Book [numbooks]; // create pointer array for reading in the books // create pointer array for reading in the books

		// read in data from books.txt to array b
		for (int i = 0; i < numbooks; ++i){
				getline(insBk, (b[i]).author, '\t');
				getline(insBk, (b[i]).title, '\t');
				insBk >> (b[i]).isbn >> (b[i]).euid >> (b[i]).borrowed.month >> (b[i]).borrowed.day >> (b[i]).borrowed.year;
			} // end for

	insBk.close();

	// user input
	cout << "Enter a part of the author's name: ";
		cin >> book.author;

	// searches through newly allocated array b for user input
	for (int i = 0; i < numbooks; ++i){
		if(b[i].author.find(book.author) != std::string::npos){ 
			nameFound = true;	
			// print results
				printBooksNoEuid(b, i);
		} // end if
	} // end for

	// not found; initialized value
	if(nameFound == false){
		cout << "Author not found in database." << endl;
	}
	else{
		cout << endl;
	}

	delete [] b; // clear memory

	return;

}

void search_by_title(){

	bool titleFound = false; // search result
	numbooks = number_of_books(); // count books
	
	stream_in_books(insBk);
		b = new Book [numbooks]; // create pointer array for reading in the books

		// read in data from books.txt to array b
		for (int i = 0; i < numbooks; ++i){
				getline(insBk, (b[i]).author, '\t');
				getline(insBk, (b[i]).title, '\t');
				insBk >> (b[i]).isbn >> (b[i]).euid >> (b[i]).borrowed.month >> (b[i]).borrowed.day >> (b[i]).borrowed.year;
			} // end for

	insBk.close();

	// user input
	cout << "Enter a part of the title: ";
		cin >> book.title;

	// searches through newly allocated array b for user input
	for (int i = 0; i < numbooks; ++i){ 

		if(b[i].title.find(book.title) != std::string::npos){
			titleFound = true;
				// print results
				printBooksNoEuid(b, i);
		} // end if

	} // end for

	// not found; initialized value
	if(titleFound == false){
		cout << "Title not found in database." << endl;
	}
	else{
		cout << endl;
	}

	delete [] b;

	return;

}

void sort_student_books(struct Student * d, int std, int number_of_books){
	struct Book t; // temp variable
	for (int e = 0; e < d[std].number_of_books; ++e){
		for(int i = e + 1; i < d[std].number_of_books; ++i){
			if((d[std]).b[e].title.compare(d[std].b[i].title) > 0){
				t = d[std].b[e];
				d[std].b[e] = d[std].b[i];
				d[std].b[i] = t;
			}
		}
	}
}

void search_by_student(){

	bool euidFound = false; // search result
	int std; // int variable of location of a found student to be used in d[]
	numstudents = number_of_students(); // count students
	numbooks = number_of_books(); // count books

	stream_in_students(insStu);
		d = new Student [numstudents]; // create pointer array for reading in the students

		// read in data from students.txt to array d
		for (int j = 0; j < numstudents; ++j){
			insStu >> (d[j]).euid >> (d[j]).number_of_books;
		} // end for
	insStu.close();

	// user input
	cout << "Enter the student's EUID: ";
		cin >> student.euid;

	// searches through newly allocated array d for user input
	for (int j = 0; j < numstudents; ++j){
		if(d[j].euid.find(student.euid) != std::string::npos){
			euidFound = true;
			std = j;
			break;
		} // end if
	} // end for

	// when user input euid exists
	if(euidFound == true){

		// user has checked out no books
		if((d[std]).number_of_books == 0){
				cout << "Student has not borrowed any books." << endl;
				}
		
		// user has books checked out
		else{

			// creates dynamic array in d[std] under student book struct of isbns
			d[std].b = new Book [d[std].number_of_books];

			stream_in_books(insBk);
			b = new Book [numbooks]; // create pointer array for reading in the books
				for (int i = 0; i < numbooks; ++i){ // read in data from books.txt to array b
						getline(insBk, (b[i]).author, '\t');
						getline(insBk, (b[i]).title, '\t');
						insBk >> (b[i]).isbn >> (b[i]).euid >> (b[i]).borrowed.month >> (b[i]).borrowed.day >> (b[i]).borrowed.year;
					} // end for (reading in data to b)
			insBk.close();

			// copy struct into each other as per array
				for (int e = 0; e < d[std].number_of_books; ){ // count # of books in isbn array
					for (int i = 0; i < numbooks; ++i){ // check books to see if euid matches the user's
						if((b[i]).euid == d[std].euid){ // store and print
							 d[std].b[e] = b[i];
							++e;
						} // end if (cmp euids)
					} // end for (book position)
				} // end for (user borrowed array position)
			delete [] b; // empty memory
		} // end else of user having checked out books
	} // end of input euid existing

	else{ // euidFound still false
		cout << "Student not in database." << endl;
	}

	sort_student_books(d, std, d[std].number_of_books);

	cout << "ISBN#s of books user " << d[std].euid << " has checked out:" << endl;

	for (int e = 0; e < d[std].number_of_books; ++e){
		printBooksNoEuid(d[std].b, e);
	}

	cout << endl;

	delete [] d; // empty memory

	return;

}

/**************************************** given ****************************************/

void search_book()
{
	cout<<"What do you want to search with?"<<endl;
	cout<<"1. Author"<<endl;
	cout<<"2. Title"<<endl;
	cout<<"3. Student"<<endl;
	cout<<"Enter your choice:";
	int choice;
	cin>>choice;
	cin.ignore();
	bool success=false;
	do
	{
		switch(choice)
		{
		case 1:
			search_by_author();
			success=true;
			break;	
		case 2:
			search_by_title();
			success=true;
			break;
		case 3:
			search_by_student();
			success=true;
			break;
		default:
			cout<<"Wrong choice. Enter again.";
			success=false;
			break;
		}
	}while(!success);

	return;
}

/**************************************** menu option functions ****************************************/

void enter_book(){

	// initialize struct elements of a new book
	Book book = {.euid = "NA", .borrowed.month = 0, .borrowed.day = 0, .borrowed.year = 0};

	// user input
	cout << "Enter author name: ";
		getline(cin, book.author);
	cout << "Enter title: ";
		getline(cin, book.title);
	cout << "Enter ISBN#: ";
		cin >> book.isbn;

	// open file to append
	file = fopen("books.txt", "a");
		if(file==NULL){
	       printf("Error\n");
	       exit(EXIT_FAILURE);
	   	} // end fail

		// append data in book struct to file
		fprintf(file, "%s\t%s\t%ld\t%s\t%d\t%d\t%d\n", book.author.c_str(), book.title.c_str(), book.isbn, book.euid.c_str(), book.borrowed.month, book.borrowed.day, book.borrowed.day);
	
	fclose(file);

	return;

}

void check_out(){

	bool euidFound = false; // check if valid euid
	int std; // index of found student in file/dynamic array
	numstudents = number_of_students(); // count students
	numbooks = number_of_books(); // count books

	stream_in_students(insStu);
		d = new Student [numstudents]; // allocate memory

		// read in data from students.txt to d
		for (int j = 0; j < numstudents; ++j){
			insStu >> (d[j]).euid >> (d[j]).number_of_books;
		} // end for

	insStu.close();

	// user input
	cout << "Enter the student's EUID: ";
		cin >> student.euid;

	// check if input euid is valid
	for (int j = 0; j < numstudents; ++j){
		if(d[j].euid.compare(student.euid) == 0){
			euidFound = true;
			std = j; // index in d where user's euid is
			break;
		} // end if
	} // end for

	if(euidFound == false){
		cout << "EUID does not exist." << endl;
	} // end if, will skip over the entire following

	if(euidFound == true){

		// cannot check out any new books
		if((d[std]).number_of_books >= 5){
				cout << "Student has reached max number of books to borrow." << endl;
			}

		// checking out!
		else{ 

			// user input
			cout << "Enter ISBN# of book: ";
				cin >> book.isbn;

			stream_in_books(insBk);
				b = new Book [numbooks]; // create pointer array for reading in the books

				// read in data from books.txt to b
				for (int i = 0; i < numbooks; ++i){
					getline(insBk, (b[i]).author, '\t');
					getline(insBk, (b[i]).title, '\t');
					insBk >> (b[i]).isbn >> (b[i]).euid >> (b[i]).borrowed.month >> (b[i]).borrowed.day >> (b[i]).borrowed.year;
				} // end for (reading in data for current position array struct)
			insBk.close();
			
			// check where ISBN exists in books.txt (read in b)
			for (int i = 0; i < numbooks; ++i){

				if(b[i].isbn == book.isbn){ // at point where exists, changes data for the euid and date checked out
					b[i].euid = d[std].euid;
					get_date(b[i].borrowed.month, b[i].borrowed.day, b[i].borrowed.year);
					update_books(b, numbooks, ofsBk);
					d[std].number_of_books += 1; // increments # of books checked out by user by 1 (updated below)
					break;
				} // end if

			} //end for (checking where isbn exists)

			update_students(d, numstudents, ofsStu); // update with the student's number of books changed above
			delete [] b; // clear memory

			} // end else

		} // end if

	delete [] d; // clear memory
	return;

}

void return_book(){

	bool validISBN = false; // check if isbn is in books.txt
	numbooks = number_of_books(); // count books
	numstudents = number_of_students(); // count students

	stream_in_books(insBk);
		b = new Book [numbooks]; // create pointer array for reading in the books
		// read in data from books.txt to array b
		for (int i = 0; i < numbooks; ++i){
				getline(insBk, (b[i]).author, '\t');
				getline(insBk, (b[i]).title, '\t');
				insBk >> (b[i]).isbn >> (b[i]).euid >> (b[i]).borrowed.month >> (b[i]).borrowed.day >> (b[i]).borrowed.year;
			} // end for
	insBk.close();

	// user input
	cout << "Enter ISBN# of book returning: ";
		cin >> book.isbn;

	// search book.txt array (b) for user input isbn
	for (int i = 0; i < numbooks; ++i){

		// when user input isbn is found
		if(b[i].isbn == book.isbn){

			stream_in_students(insStu);
				d = new Student [numstudents]; // create pointer array for reading in the students
				// read in data from students.txt to array d
				for (int j = 0; j < numstudents; ++j){ 
					insStu >> (d[j]).euid >> (d[j]).number_of_books;
				} // end for
			insStu.close();

			// cycle through array of students for the euid that matches the checked in book's corresponding euid
			for (int j = 0; j < numstudents; ++j){
				
				// when euid is found
				if(b[i].euid.compare(d[j].euid) == 0){
					
					// decrement user number of books by 1
					(d[j]).number_of_books -= 1; 

					// change respective book struct variables
					(b[i]).euid = "NA";
					(b[i]).borrowed.month = 0;
					(b[i]).borrowed.day = 0;
					(b[i]).borrowed.year = 0;
					validISBN = true;

					// update students.txt with updated user array d
					update_students(d, numstudents, ofsStu);		
					break;

				} // end if

			} // end for (cycle through array of students for corresponding euid)
			
			delete [] d; // empty memory

			break;

		} // end if (isbn # is found)

	} // end for (cycling through array for user input isbn)

	// send updated b data to update file
	if(validISBN == true){
		update_books(b, numbooks, ofsBk);
	}

	// input isbn doesn't exist, error message
	if(validISBN == false){
		cout << "Book not found in database." << endl;
	}

	delete [] b;
	return;

}

/**************************************** print in main ****************************************/

void cases(int choice, bool success){ // called by menu function
	switch(choice)
			{
			case 1:
				enter_book();
				success=true;
				break;
			case 2:
				check_out();
				success=true;
				break;
			case 3: 
				return_book();
				success=true;
				break;
			case 4: 
				search_book();
				success=true;
				break;
			default:
				cout << "Wrong Choice. Enter again." << endl;
				success=false;
				break;
			}

			return;
}

void menu(int *choice, bool *success){ // called by main
	cout<<"1. Add"<<endl;

	cout<<"2. Check Out"<<endl;
	
	cout<<"3. Return"<<endl;
	
	cout<<"4. Search"<<endl;
	
	cout<<"Enter your choice, 0 to Quit: ";
	
	cin >> *choice;
	cin.ignore();
		
	do{
		cases(*choice, *success);
			
		}while(*success);
		
}

void meInfo(){ // called by main
	cout << "+----------------------------------------------+" << endl;
	cout << "|       Computer Science and Engineering       |" << endl;
	cout << "|        CSCE 1030 - Computer Science I        |" << endl;
	cout << "|   Alice Zhu   az0144   alicezhu@my.unt.edu   |" << endl;
	cout << "+----------------------------------------------+" << endl;
	cout << endl;
	return;
}

int main()
{
	
	meInfo();
	
	int choice;
	bool success;
	do
	{
	
		menu(&choice, &success);

	}while(choice!=0);

	return 0;
}




	