/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

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
int checkndconvert(char*, struct converteddate *);
int compare(struct converteddate , struct converteddate );
int binarysearch(struct converteddate *,int, int, struct converteddate);
int convert(char);
int split(char *, int, int);
int isLeapyear(int);
int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	int i,index=0,first=0,last=len-1,invalid;
	
	struct converteddate cd[100];
	struct converteddate dd;	

	for (i = 0; i < len; i++)
	{
		invalid = checkndconvert(Arr[i].date,&cd[i]);
		if (invalid == -1)
		{
			return -1;
		}
	}
	invalid = checkndconvert(date,&dd);
	if (compare(cd[last], dd) == 1)
	{
		return 0;
	}
	else if (compare(cd[first], dd) == -1)
	{
		return len;
	}
	while (first <= last)
	{
		index = binarysearch(cd, first, last, dd);
		if (index > last)
		{
			return 0;
		}
		if (compare(cd[index], dd)==0)
		{
			first=index+1;
		}
		else
		{
			break;
		}

	}
	return (len - index);
}

int checkndconvert(char* dob1, struct converteddate *y)
{
	int day1, month1, year1, i, len = -1, lp;
	int a[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	for (i = 0; dob1[i] != '\0' ; i++)
	{
		len++;
	}
	if (len != 9)
	{
		return -1;
	}
	else
	{
		year1 = split(dob1, 6, 9);
		month1 = split(dob1, 3, 4);
		day1 = split(dob1, 0, 1);
		if (year1 < 0  || month1 < 0|| day1 < 0)
		{
			return -1;
		}
		if (dob1[2] != '-' || dob1[5] != '-')
		{
			return -1;
		}
		if (month1 > 12 || month1 == 0)
		{
			return -1;
		}
		if (day1 > a[month1 - 1])
		{
			return -1;
		}
	
		if (month1 == 2)
		{
			if (day1 == 29)
			{
				lp = isLeapyear(year1);
			}
			if (lp == 0)
			{
				return -1;
			}
		}

		y->year = year1;
		y->month = month1;
		y->day = day1;


	}
	return 1;

}
int split(char *dob, int j, int n)
{
	int i, temp, num = 0;

	for (i = j; i <= n; i++)
	{
		if (dob[i] >= 48 && dob[i] <= 57)
		{
			temp = convert(dob[i]);
			num = num * 10 + temp;
		}
		else
		{
			return -1;
		}
	}
	return num;
}

int convert(char c)
{
	int a;
	a = c - '0';
	return a;
}
int isLeapyear(int a)
{
	if (a % 400 == 0)
	{
		return 1;
	}
	else if (a % 100 == 0)
	{
		return 0;
	}
	else if (a % 4 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int compare(struct converteddate a, struct converteddate b)
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

int binarysearch(struct converteddate *cd, int first, int last, struct converteddate dd)
{
	int mid, i;
	while (first < last)
	{
		mid = (last + first) / 2;
		i = compare(cd[mid], dd);
		if (i==0)
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
	i = compare(cd[first], dd);
	if (i <0)
	{
		return (first);
	}
	else
	{
		return (first + 1);
	}
}