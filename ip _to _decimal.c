//Program to convert the 2 different IPs into hash value. 
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct iptolint
{
	char ip_src1[16];
	unsigned int  n;
	int shrip;
};

struct iptolint2
{
	char ip_dst1[16];
	unsigned int  m;
	int shrip2;
	int shrip3;
};

struct Flow
{
	char ip_src1[16];
	char ip_dst1[16];
};

struct Heavy_Hitter
{
	struct Flow flow;
	int count ;
};


long  conv(char[]);
long conv2(char[]);

void main()
{

	int minimum;
	int x = 0;
	//int count = 0;
	int arr[3][1024] = { 0 };
	unsigned long final_sum;
	unsigned long final_sub;
	unsigned long final_xor;
	struct iptolint ipl;
	struct iptolint2 ipl2;
	struct Heavy_Hitter hh;
	hh.count = 0;

	while (x < 3)
	{
		printf(" Read the source IP Address to be converted\n");
		scanf("%s", ipl.ip_src1);
		printf("Read the destination IP Address to be converted\n");
		scanf("%s", ipl2.ip_dst1);

		char* ip_dupsrc = _strdup(ipl.ip_src1);
		char* ip_dupdst = _strdup(ipl2.ip_dst1);

		ipl.n = conv(ip_dupsrc);
		ipl2.m = conv2(ip_dupdst);

		printf(" Equivalent 32-bit long int value of Source IP: %lu \n", ipl.n);
		printf(" Equivalent 32-bit long int value of Destination IP: %lu \n", ipl2.m);
		final_sum = ipl.n + ipl2.m;
		printf("Final sum = %lu\n", final_sum);
		ipl.shrip = final_sum % 1024;
		printf(" Equivalent first hash function hv1: %d\n", ipl.shrip);
		arr[0][ipl.shrip]++;
		printf("value of the matrix for first hash function is: %u\n", arr[0][ipl.shrip]);

		final_sub = ipl.n - ipl2.m;
		printf("Final sub = %lu\n", final_sub);
		ipl2.shrip2 = final_sub % 1024;
		printf(" Equivalent second hash function hv2: %d\n", ipl2.shrip2);
		arr[1][ipl2.shrip2]++;
		printf("value of the matrix for second hash function is: %u\n", arr[1][ipl2.shrip2]);

		final_xor = ipl.n ^ ipl2.m;
		printf(" Final xor = %lu\n", final_xor);
		ipl2.shrip3 = final_xor % 1024;
		printf(" Equivalent third hash function hv3: %d\n", ipl2.shrip3);
		arr[2][ipl2.shrip3]++;
		printf("value of the matrix for third hash function is: %u\n", arr[2][ipl2.shrip3]);

		if ((arr[0][ipl.shrip] < arr[1][ipl2.shrip2]) && (arr[0][ipl.shrip] < arr[2][ipl2.shrip3]))
		{
			minimum = arr[0][ipl.shrip];
		}
		else if ((arr[1][ipl2.shrip2] < arr[0][ipl.shrip]) && (arr[1][ipl2.shrip2]) < arr[2][ipl2.shrip3])
		{
			minimum = arr[1][ipl2.shrip2];
		}
		else
		{
			minimum = arr[2][ipl2.shrip3];
		}

		printf("Minimum of the three matrix table values is = %d\n\n", minimum);

		if (minimum > hh.count)
		{
			hh.count = minimum;

		    memcpy(hh.flow.ip_src1, ipl.ip_src1, 16);
			memcpy(hh.flow.ip_dst1, ipl2.ip_dst1, 16);
		}

		printf(" The highest occupancy source packet is: %s\n", hh.flow.ip_src1);
		printf(" The highest occupancy source packet is: %s\n", hh.flow.ip_dst1);
		x++;
	}
}
	unsigned int conv(char* ip_dupsrc)
	{
		unsigned int num = 0, val;
		int p = 24;
		char *tok, *ptr;
		tok = strtok(ip_dupsrc, ".");
		printf("IP = %s", ip_dupsrc);
		while (tok != NULL)
		{
			val = strtol(tok, &ptr, 10);
			//	printf("val is %d\n",val);
			num += val * (1 << p);
			//	printf("num is %u\n", num);
			p = p - 8;
			tok = strtok(NULL, ".");
		}
		return(num);
	}

	unsigned int conv2(char* ip_dupdst)
	{
		unsigned int num2 = 0, val;
		int p = 24;
		char *tok, *ptr;
		tok = strtok(ip_dupdst, ".");
		while (tok != NULL)
		{
			val = strtol(tok, &ptr, 10);
			//	printf("val is %d\n",val);
			num2 += val * (1 << p);
			//	printf("num is %u\n", num);
			p = p - 8;
			tok = strtok(NULL, ".");
		}
		return(num2);
	}
