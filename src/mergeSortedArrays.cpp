/*
OVERVIEW: You are given 2 bank statements that are ordered by date - 
Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction {
	int amount;
	char date[11];
	char description[20];
};
struct converteddate
{
	int year;
	int month;
	int day;
};
void convertstring1(char*, struct converteddate *);
int compare2(struct converteddate, struct converteddate);
int convert2(char);
int split2(char *, int, int);

struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	int i, ja=0,jb=0;
	struct  converteddate cdA[100], cdB[100];
	struct transaction answer[100];
	if (A == NULL || B == NULL || ALen <= 0 || BLen <= 0)
	{
		return NULL;
	}
	for (i = 0; i < ALen; i++)
	{
		convertstring1(A[i].date, &cdA[i]);
	}
	for (i = 0; i < BLen; i++)
	{
		convertstring1(B[i].date, &cdB[i]);
	}
	
	for (i = 0; i < (ALen + BLen); i++)
	{
		if (ja > ALen-1)
		{
			answer[i] = B[jb];
			jb++;
		}
		else if (jb > BLen-1)
		{
			answer[i] = A[ja];
			ja++;
		}
		else if (compare2(cdA[ja], cdB[jb]) == 1)
		{
			answer[i] = A[ja];
			ja++;
		}
		else
		{
			answer[i] = B[jb];
			jb++;
		}
	}
	return answer;
}
void convertstring1(char *dob1, struct converteddate *y)
{
	int day1, month1, year1;

	year1 = split2(dob1, 6, 9);
	month1 = split2(dob1, 3, 4);
	day1 = split2(dob1, 0, 1);

	y->year = year1;
	y->month = month1;
	y->day = day1;

}
int split2(char *dob, int j, int n)
{
	int i, temp, num = 0;

	for (i = j; i <= n; i++)
	{
		if (dob[i] >= 48 && dob[i] <= 57)
		{
			temp = convert2(dob[i]);
			num = num * 10 + temp;
		}
		else
		{
			return -1;
		}
	}
	return num;
}

int convert2(char c)
{
	int a;
	a = c - '0';
	return a;
}
int compare2(struct converteddate a, struct converteddate b)
{

	if (a.year > b.year)
	{
		return -1;
	}
	else if (b.year > a.year)
	{
		return 1;
	}
	if (a.month > b.month)
	{
		return -1;
	}
	if (b.month > a.month)
	{
		return 1;
	}
	if (a.day > b.day)
	{
		return -1;
	}
	if (b.day > a.day)
	{
		return 1;
	}
	return 0;
}