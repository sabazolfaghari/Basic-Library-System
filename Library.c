#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
int count_registery = 0001;
int book_count;
int member_count;
FILE *fpersonel;
FILE *fbookinfo;
void welcome();
void switch_case (int num);
int find_free_member();
int find_free_book();
int find_free_borrowed_book(int i);
void addmember();
void addbook();
void lendbook();
void show_borrowed_books();
void return_book();
void show_member_list();
void show_book_list();
void convertor(char str[]);
void define_return_date();
void show_all_books();
void bubblesort();
struct book
{
	char name[30];
	char author[30];
	char ISBN[20];
	int number_of_books;
	int number_of_existing_books;
}book[10000], temp;
struct date
{
	int year;
	int month;
	int day;
}today;
struct student
{
	char name[30];
	char family[30];
	int regdnum;
	int year_birth;
	int number_of_borrowed_books;
	struct book borrowed[5];
	struct date lend_date[5];
	struct date return_date[5];
}s[1000];
int main()
{
	int i,num;
	for (i = 0; i < 1000; i++)
	{
		s[i].name[0] = '\0';
		s[i].number_of_borrowed_books = 0;
	}

	for (i = 0; i < 10000; i++)
	{
		book[i].name[0] = '\0';
		book[i].number_of_books = 0;
		book[i].number_of_existing_books = 0;
	}
	for (;;)
	{
		welcome();
		printf("1)add member 2)add books 3)lend books 4)show borrowed books 5)return books 6)show members 7)show books 8)exit\n");
		scanf("%d", &num);
		switch_case(num);
	}
	return 0;
}
void welcome()
{
	time_t t = time(NULL);
	struct tm*tm = localtime(&t);
	char s[64];
	strftime(s, sizeof(s), "%c", tm);
	printf("%s\n", s);
	printf("the number of books:%d\n", book_count);
	printf("the number of members:%d\n", member_count);
	
}
void switch_case(int num)
{
		switch (num)
		{
		case 1:
			addmember();
			break;
		case 2:
			addbook();
			break;
		case 3:
			lendbook();
			break;
		case 4:
			show_borrowed_books();
			break;
		case 5:
			return_book();
			break;
		case 6:
			show_member_list();
			break;
		case 7:
			show_book_list();
			break;
		case 8:
			exit(1);
			break;
		default:
			printf("Invalid Input!\n");
			break;
		}
}
void addmember()
{
	system("cls");
	int i, num, flag = 0;
	for (;;)
	{
		if (flag == 1)
			break;
		else
		{
			welcome();
			printf("1)add new member 2)exit\n");
			scanf("%d", &num);
			switch (num)
			{
			case 1:
				i = find_free_member();
				if (i == -1)
					printf("full space!\n");
				else
				{
					fpersonel = fopen("C:\Users\Ehsan\Desktop", "a");
					if (fpersonel == NULL)
					{
						printf("cannot open the file!\n");
						exit(1);
					}
					printf("File opened!\n");
					printf("enter a name!\n");
					scanf("%s", s[i].name);
					printf("enter a family name!\n");
					scanf("%s", s[i].family);
					printf("enter the year of birth!\n");
					scanf("%d", &s[i].year_birth);
					s[i].regdnum = count_registery;
					printf("the registry number of this person is:%d\n", s[i].regdnum);
					count_registery++;
					member_count++;
					fprintf(fpersonel, "%s", s[i].name);
					fprintf(fpersonel, "%s", s[i].family);
					fprintf(fpersonel, "%d", s[i].year_birth);
					fprintf(fpersonel, "%d", s[i].regdnum);
					if(fclose(fpersonel)==0)
						printf("information successfully saved!\npress enter to continue!\n");
					_getch();
					system("cls");
				}
				break;
			case 2:
				flag = 1;
				system("cls");
				//for clearing the data!!!
				break;
			default:
				printf("invalid input!\n");
				break;
			}
		}
	}
}
int find_free_member()
{
	int i;
	for (i = 0; i < 1000; i++)
	{
		if (s[i].name[0] == '\0')
			return i;
	}
	return -1;
}
int find_free_book()
{
	int i;
	for (i = 0; i < 10000; i++)
	{
		if (book[i].name[0] == '\0')
			return i;
	}
	return -1;
}
int find_free_borrowed_book(int i)
{
	//i is an argument becuase s[i] can go as far as 1000 for students and each student can borrow 5 books!
	int j;
	for (j = 0; j < 5; j++)
		if (s[i].borrowed[j].name[0] == '\0')
			return j;
	//we empty the five books one person can borrow!
	return -1;
}
void addbook()
{
	system("cls");
	int i, num, k, flag_switch = 0, flag_repeatedbook = 0;
	for (;;)
	{
		if (flag_switch == 1)
			break;
		else
		{
			welcome();
			printf("1)add new book 2)exit\n");
			scanf("%d", &num);
			switch (num)
			{
			case 1:
				i = find_free_book();
				if (i == -1)
					printf("full space!\n");
				else
				{
					fbookinfo = fopen("C:\Users\Ehsan\Desktop", "a");
					if (fbookinfo == NULL)
					{
						printf("cannot open the file!\n");
						exit(1);
					}
					printf("File opened!\n");
					printf("enter the name of a book!\n");
					scanf("%s", temp.name);
					printf("enter the author`s name!\n");
					scanf("%s", temp.author);
					printf("enter the ISBN of the book!\n");
					scanf("%s", temp.ISBN);
					book_count++;
					//global variable for the number of all books!
					if (flag_repeatedbook == 0)
					{
						strcpy(book[i].name, temp.name);
						//this is the i we found with find_free_book()!
						strcpy(book[i].author, temp.author);
						strcpy(book[i].ISBN, temp.ISBN);
						book[i].number_of_books++;
						book[i].number_of_existing_books++;
					}
					for (k = 0; k < book_count; k++)
					{
						//checks if the entered book already exists or not!
						if (strcmp(temp.name, book[k].name) == 0 && strcmp(temp.author, book[k].author) == 0 && strcmp(temp.ISBN, book[k].ISBN) == 0)
						{
							if (book[k].number_of_books <= 5)
								{
								book[k].number_of_books++;
								//number of the same books!
								book[k].number_of_existing_books++;
								// existing books are for the books that haven`t been lended yet!
								flag_repeatedbook = 1;
								}
							else
								printf("you can`t add this book because there are already five of this book in the library!\n");
						}
					}	
					
					fprintf(fbookinfo, "%s", book[i].name);
					fprintf(fbookinfo, "%s", book[i].author);
					fprintf(fbookinfo, "%s", book[i].ISBN);
					fprintf(fbookinfo, "%s", book[i].number_of_books);
					fprintf(fbookinfo, "%s", book[i].number_of_existing_books);
					if(fclose(fbookinfo)==0)
						printf("information successfully saved!\n");
					_getch();
					system("cls");
				}
				break;
			case 2:
				flag_switch = 1;
				system("cls");
				break;
			default:
				printf("invalid input!\n");
				break;
			}
		}
	}
}
void lendbook()
{
	system("cls");
	int i, j, k, m, num, regdnum, flag = 0;
	for (;;)
	{
		if (flag == 1)
			break;
		else
		{
			welcome();
			printf("1)lend books 2)exit\n");
			scanf("%d", &num);
			switch (num)
			{
			case 1:
				printf("enter your registry number!\n");
				scanf("%d", &regdnum);
				for (i = 0; i < member_count; i++)
				{
					if (regdnum == s[i].regdnum)
					{
						printf("list of all books in the library:\n");
						show_all_books();
						printf("enter the number of book you wish to borrow!\n");
						scanf("%d", &k);
						for (j = 0; j < book_count; j++)
						{
							if (k == j && book[j].number_of_existing_books != 0)
							{
								printf("book`s name:%s\n", book[j].name);
								m = find_free_borrowed_book(i);
								s[i].number_of_borrowed_books++;
								strcpy(s[i].borrowed[m].name, book[j].name);
								strcpy(s[i].borrowed[m].author, book[j].author);
								strcpy(s[i].borrowed[m].ISBN, book[j].ISBN);
								book[j].number_of_existing_books--;
								s[i].lend_date[m].day = today.day;
								s[i].lend_date[m].month = today.month;
								s[i].lend_date[m].year = today.year;
								printf("you have borrowed book number %d", j + 1);
								printf("date of borrowed book: %d/%d/%d", today.day, today.month, today.year);
								define_return_date(i, m, 7);
								printf("your due date for returning the book number %d is:%d/%d/%d\n", j + 1, s[i].return_date[m].day, s[i].return_date[m].month, s[i].return_date[m].year);
								fpersonel = fopen("C:\identity.txt", "a");
								fprintf(fpersonel, "%s", s[i].borrowed[m].name);
								fprintf(fpersonel, "%s", s[i].borrowed[m].author);
								fprintf(fpersonel, "%d/%d/%d", s[i].lend_date[m].day, s[i].lend_date[m].month, s[i].lend_date[m].year);
								fprintf(fpersonel, "%d/%d/%d", s[i].return_date[m].day, s[i].return_date[m].month, s[i].return_date[m].year);
								if (fclose(fpersonel) == 0)
									printf("the information has successfully been saved to the student`s record");
							}
						}
					}
					else
					{
						// else for if regdnum==s[i].regdnum!
						printf("this registry number doesn`t exist! Try Again!\n");
						printf("enter your registry number!\n");
						scanf("%d", &regdnum);
						continue;
					}
					_getch();
				}
				system("cls");
				break;
			case 2:
				flag = 1;
				system("cls");
				break;
			default:
				printf("invalid input!\n");
				break;
			}
		}
	}
}
void convertor(char str[])
{
	char month_name[4];
	int day, month, year;
	if (str[8] != ' ')
		day = (str[8] - 48) * 10 + (str[9] - 48);
	// if statement checks if the day is two digits and 48 is for converting it to binary!
	else
		day = str[9] - 48;
	// day is a one digit number!
	year = (str[20] - 48) * 1000 + (str[21] - 48) * 100 + (str[22] - 48) * 10 + (str[23] - 48);
	//because year is a 4 digit number!
	str[7] = '\0';
	//after e.g. wed jan all the dates will be removed!
	strcpy(month_name, &str[4]);
	//str[4] copies all of the string to month_name till it reaches NULL which in here is str[7]!
	if (strcmp(month_name, "Jan") == 0)
		month = 1;
	else if (strcmp(month_name, "Feb") == 0)
		month = 2;
	else if (strcmp(month_name, "Mar") == 0)
		month = 3;
	else if (strcmp(month_name, "Apr") == 0)
		month = 4;
	else if (strcmp(month_name, "May") == 0)
		month = 5;
	else if (strcmp(month_name, "Jun") == 0)
		month = 6;
	else if (strcmp(month_name, "Jul") == 0)
		month = 7;
	else if (strcmp(month_name, "Agu") == 0)
		month = 8;
	else if (strcmp(month_name, "Sep") == 0)
		month = 9;
	else if (strcmp(month_name, "Oct") == 0)
		month = 10;
	else if (strcmp(month_name, "Nov") == 0)
		month = 11;
	else if (strcmp(month_name, "Dec") == 0)
		month = 12;
	today.day = day;
	today.month = month;
	today.year = year;
}
void define_return_date(int i, int j, int d)
{
	//d is the days you can have the book you borrowed which is a week!
	if ((s[i].lend_date[j].month == 12 || s[i].lend_date[j].month == 10 || s[i].lend_date[j].month == 8 || s[i].lend_date[j].month == 7 || s[i].lend_date[j].month == 5 || s[i].lend_date[j].month == 3 || s[i].lend_date[j].month == 1) && s[i].lend_date[j].day > 24)
	{
		// months with 31 days so if the borrowed date is more than 24, it enters the next month!
		s[i].return_date[j].month = s[i].lend_date[j].month + 1;
		s[i].return_date[j].day = (s[i].lend_date[j].day + d) % 31;
		s[i].return_date[j].year = s[i].lend_date[j].year;
		if (s[i].lend_date[j].day == 12)
		{
			s[i].return_date[j].month = 1;
			s[i].return_date[j].year++;
		}
	}
	else if ((s[i].lend_date[j].month == 11 || s[i].lend_date[j].month == 9 || s[i].lend_date[j].month == 6 || s[i].lend_date[j].month == 4) && s[i].lend_date[j].day > 23)
	{
		// months with 30 days!
		s[i].return_date[j].month = s[i].lend_date[j].month + 1;
		s[i].return_date[j].day = (s[i].lend_date[j].day + d) % 31;
		s[i].return_date[j].year = s[i].lend_date[j].year;
		// we don`t have an if statement for month == 12 here because the 12th month is 31 days long!
	}
	else if (s[i].lend_date[j].month == 2)
	{
		// February is 28 days long and 29 days in a leap year!
		if (s[i].lend_date[j].year % 4 != 0 && s[i].lend_date[j].day > 21)
		{
			s[i].return_date[j].month = s[i].lend_date[j].month + 1;
			s[i].return_date[j].day = (s[i].lend_date[j].day + d) % 28;
			s[i].return_date[j].year = s[i].lend_date[j].year;
		}
		else if (s[i].lend_date[j].year % 4 == 0 && s[i].lend_date[j].day > 22)
		{
			s[i].return_date[j].month = s[i].lend_date[j].month + 1;
			s[i].return_date[j].day = (s[i].lend_date[j].day + d) % 29;
			s[i].return_date[j].year = s[i].lend_date[j].year;
		}
	}
	else
	{
		// if none of the above statements are true and there are no limits to days or months:
		s[i].return_date[j].day = s[i].lend_date[j].day + d;
		s[i].return_date[j].month = s[i].lend_date[j].month;
		s[i].return_date[j].year = s[i].lend_date[j].year;
	}
}
void show_all_books()
{
	int i;
	for (i = 0; i < book_count; i++)
	{
		if (book[i].name[0] != '\0')
		{
			system("cls");
			fbookinfo = fopen("C:\book.txt", "a");
			fscanf(fbookinfo, "%s", book[i].name);
			fscanf(fbookinfo, "%s", book[i].author);
			fscanf(fbookinfo, "%s", book[i].ISBN);
			fscanf(fbookinfo, "%d", book[i].number_of_books);
			fscanf(fbookinfo, "%d", book[i].number_of_existing_books);
			printf("the name of book number %d : %s\n", i+1, book[i].name);
			printf("the author of book number %d : %s\n", i+1, book[i].author);
			printf("the ISBN of book number %d : %s\n", i+1, book[i].ISBN);
			printf("the number of book number %d in the library : %s\n", i+1, book[i].number_of_books);
			printf("the number of book number %d available at the moment : %s\n", i + 1, book[i].number_of_existing_books);
			fclose(fbookinfo);
		}
	}
}
void show_borrowed_books()
{
	system("cls");
	int i, j, num, regdnum, flag = 0;
	for (;;)
	{
		if (flag == 1)
			break;
		else
		{
			welcome();
			printf("1)show list of all borrowed books 2)exit\n");
			scanf("%d", &num);
			switch (num)
			{
			case 1:
				printf("enter your registry number!\n");
				scanf("%d", &regdnum);
				for (i = 0; i < member_count; i++)
				{
					if (regdnum == s[i].regdnum)
					{
						fpersonel = fopen("C:\identity.txt", "a");
						for (j = 0; j < 5; j++)
							if (s[i].borrowed[j].name[0] != '\0')
							{
								fscanf(fpersonel, "%s", s[i].borrowed[j].name);
								printf("%d)%s\n", j + 1, s[i].borrowed[j].name);
								fscanf(fpersonel, "%s", s[i].borrowed[j].author);
								printf("%d)%s\n", j + 1, s[i].borrowed[j].author);
								fscanf(fpersonel, "%s", s[i].borrowed[j].ISBN);
								printf("%d)%s\n", j + 1, s[i].borrowed[j].ISBN);
								fclose(fpersonel);
							}
					}
					else
					{
						// else for if regdnum==s[i].regdnum!
						printf("this registry number doesn`t exist! Try Again!\n");
						printf("enter your registry number!\n");
						scanf("%d", &regdnum);
						continue;
					}
					_getch();
				}
				system("cls");
				break;
			case 2:
				flag = 1;
				system("cls");
				break;
			default:
				printf("invalid input!\n");
				break;
			}
		}
	}
}
void return_book()
{
	system("cls");
	int i, j, k, num, regdnum, flag = 0;
	char ISBN[20];
	for (;;)
	{
		if (flag == 1)
			break;
		else
		{
			welcome();
			printf("1)return books 2)exit\n");
			scanf("%d", &num);
			switch (num)
			{
			case 1:
				printf("enter your registry number!\n");
				scanf("%d", &regdnum);
				for (i = 0; i < member_count; i++)
					if (regdnum == s[i].regdnum)
					{
						printf("enter the ISBN of the book you wish to return!\n");
						scanf("%s", ISBN);
						for (j = 0; j < 5; j++)
							if (strcmp(ISBN, s[i].borrowed[j].ISBN) == 0)
							{
								for (k = 0; k < book_count; k++)
									if (strcmp(s[i].borrowed[j].ISBN, book[k].ISBN) == 0)
										book[k].number_of_existing_books++;
								fpersonel = fopen("C:\identity.txt", "r");
								s[i].borrowed[j].name[0] = '\0';
								s[i].borrowed[j].author[0] = '\0';
								s[i].borrowed[j].ISBN[0] = '\0';
								printf("your book has been successfully returned!\n");
								fscanf(fpersonel, "%d/%d/%d", s[i].return_date[j].day, s[i].return_date[j].month, s[i].return_date[j].year);
								printf("your due date was %d/%d/%d", s[i].return_date[j].day, s[i].return_date[j].month, s[i].return_date[j].year);
								if (today.day == s[i].return_date[j].day && today.month == s[i].return_date[j].month && today.year == s[i].return_date[j].year)
									printf("you have returned the book in time!\n");
								else
									printf("you have been late for returning the book!\n");
							}
					}
					else
					{
						// else for if regdnum==s[i].regdnum!
						printf("this registry number doesn`t exist! Try Again!\n");
						printf("enter your registry number!\n");
						scanf("%d", &regdnum);
						continue;
					}
				_getch();
				system("cls");
				break;
			case 2:
				flag = 1;
				system("cls");
				break;
			default:
				printf("invalid input!\n");
				break;
			}
		}
	}
}
void show_member_list()
{
system("cls");
int num, i, flag = 0;
for (;;)
{
	if (flag == 1)
		break;
	else
	{
		welcome();
		printf("1)show list of all members  2)exit\n");
		scanf("%d", &num);
		switch (num)
		{
		case 1:
			bubblesort();
			for (i = 0; i < member_count; i++)
			{
				fpersonel = fopen("C:\identity.txt","a");
				fscanf(fpersonel, "%s", s[i].name);
				fscanf(fpersonel, "%s", s[i].family);
				fscanf(fpersonel, "%s", s[i].regdnum);
				printf("name:%s\n", s[i].name);
				printf("family:%s\n", s[i].family);
				printf("registery number:%d\n", s[i].regdnum);
				fclose(fpersonel);
			}
			_getch();
			system("cls");
			break;
		case 2:
			flag = 1;
			system("cls");
			break;
		default:
			printf("invalid input!\n");
			break;
		}
	}
}
}
void bubblesort()
{
	int i, j, temp1;
	char temp2[1000];
	for(i=member_count-1;i>0;i--)
		for(j=0;j<i;j++)
			if (s[j].regdnum > s[j + 1].regdnum)
			{
				temp1= s[j].regdnum;
				s[j].regdnum = s[j + 1].regdnum;
				s[j + 1].regdnum = temp1;
				strcpy(temp2, s[j].name);
				strcpy(s[j].name, s[j + 1].name);
				strcpy(s[j + 1].name, temp2);
				strcpy(temp2, s[j].family);
				strcpy(s[j].family, s[j + 1].family);
				strcpy(s[j + 1].family, temp2);
			}
}
void show_book_list()
{
	system("cls");
	int num, flag = 0;
	for (;;)
	{
		if (flag == 1)
			break;
		else
		{
			welcome();
			printf("1)show list of all books  2)exit\n");
			scanf("%d", &num);
			switch (num)
			{
			case 1:
				show_all_books();
				_getch();
				system("cls");
				break;
			case 2:
				flag = 1;
				system("cls");
				break;
			default:
				printf("invalid input!\n");
				break;
			}
		}
	}
}



