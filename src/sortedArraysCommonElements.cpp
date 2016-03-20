/*
OVERVIEW: You are given 2 bank statements that are ordered by date. 
Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.


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
void convertstring(char*, struct converteddate *);
int compare1(struct converteddate, struct converteddate);
int binarysearch1(struct transaction *, int, int, struct transaction);
int convert1(char);
int split1(char *, int, int);

struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	int i, j=0,index;
	struct transaction answer[100];
	if (A==NULL||B==NULL||ALen<=0||BLen<=0)
		return NULL;
	else
	{
		for (i = 0; i < BLen; i++)
		{
			index=binarysearch1(A, 0, ALen-1, B[i]);
			if (index >=0)
			{
				answer[j] = B[index];
				j++;
			}
		}
	}
	if (j == 0)
	{
		return NULL;
	}
	return answer;
}
int binarysearch1(struct transaction *A, int first, int last, struct transaction dd)
{
	int mid, i;
	static struct converteddate cdA[100];
	struct converteddate cdB;
	convertstring(dd.date, &cdB);
	while (first <= last)
	{
		mid = (last + first) / 2;
		if (cdA[mid].day == 0)
		{
			convertstring(A[mid].date, &cdA[mid]);
		}
		
		i = compare1(cdA[mid], cdB);
		if (i == 0)
		{
			return mid;
		}
		else if (i == -1)
		{
			last = mid - 1;
		}
		else
		{
			first = mid + 1;
		}
	}
	return -1;
}
void convertstring(char *dob1, struct converteddate *y)
{
	int day1, month1, year1;

		year1 = split1(dob1, 6, 9);
		month1 = split1(dob1, 3, 4);
		day1 = split1(dob1, 0, 1);
		
		y->year = year1;
		y->month = month1;
		y->day = day1;	

}
int split1(char *dob, int j, int n)
{
	int i, temp, num = 0;

	for (i = j; i <= n; i++)
	{
		if (dob[i] >= 48 && dob[i] <= 57)
		{
			temp = convert1(dob[i]);
			num = num * 10 + temp;
		}
		else
		{
			return -1;
		}
	}
	return num;
}

int convert1(char c)
{
	int a;
	a = c - '0';
	return a;
}
int compare1(struct converteddate a, struct converteddate b)
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