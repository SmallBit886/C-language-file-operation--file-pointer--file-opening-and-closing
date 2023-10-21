#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
//BIT-6-C语言文件操作

//int main()
//{
//	int a = 10000;
//	FILE* pf = fopen("test.txt", "wb");//打开文件，以二进制的方式写
//	fwrite(&a, 4, 1, pf);//以二进制的形式写入fp指向的文件里	//10 27 00 00 = 0x27 10 00 00=10000
//	fclose(pf);//关闭文件
//	pf = NULL;//释放指针内存
//	return 0;
//}


//8. 文件缓冲区
//系统自动地在内存中为程序中每一个正在使用的文件开辟一块“文件缓冲区”
//内存向磁盘输出数据会先送到内存中的缓冲区，装满缓冲区后才一起送到磁盘上
//从磁盘文件中读取数据先输入到内存缓冲区（充满缓冲区），再从缓冲区逐个地将数据送到程序数据区（程序变量等）
//#include <windows.h>
////VS2013 WIN10环境测试
//int main()
//{
//	FILE* pf = fopen("test.txt", "w");
//	fputs("abcdef", pf);//先将代码放在输出缓冲区
//	printf("睡眠10秒-已经写数据了，打开test.txt文件，发现文件没有内容\n");
//	Sleep(10000);
//	printf("刷新缓冲区\n");
//	fflush(pf);//刷新缓冲区时，才将输出缓冲区的数据写到文件（磁盘）
//	//注：fflush 在高版本的VS上不能使用了
//	printf("再睡眠10秒-此时，再次打开test.txt文件，文件有内容了\n");
//	Sleep(10000);
//	fclose(pf);
//	//注：fclose在关闭文件的时候，也会刷新缓冲区
//	pf = NULL;
//	return 0;
//}
//结论：
//因为有缓冲区的存在，C语言在操作文件的时候，需要做刷新缓冲区或者在文件操作结束的时候关闭文件

//3.1 文件指针
//缓冲文件系统中，关键的概念是“文件类型指针”，简称“文件指针
//每个被使用的文件都在内存中开辟了一个相应的文件信息区，用来存放文件的相关信息（如文件的名字，文件状态及文件当前的位置等）
//这些信息是保存在一个结构体变量中的。该结构体类型是由系统声明的，取名FILE.
//struct _iobuf {
//	char* _ptr;
//	int _cnt;
//	char* _base;
//	int _flag;
//	int _file;
//	int _charbuf;
//	int _bufsiz;
//	char* _tmpfname;
//};
//typedef struct _iobuf FILE;
//每当打开一个文件的时候，系统会根据文件的情况自动创建一个FILE结构的变量，并填充其中的信息，使用者不必关心细节
//一般都是通过一个FILE的指针来维护这个FILE结构的变量，这样使用起来更加方便

//我们可以创建一个FILE*的指针变量
//FILE* pf;//文件指针变量
/*
定义pf是一个指向FILE类型数据的指针变量。
可以使pf指向某个文件的文件信息区（是一个结构体变量）。
通过该文件信息区中的信息就能够访问该文件。
也就是说，通过文件指针变量能够找到与它关联的文件。
*/

//3.2 文件的打开和关闭
//文件在读写之前应该先打开文件，在使用结束之后应该关闭文件
//打开文件的同时，都会返回一个FILE*的指针变量指向该文件，也相当于建立了指针和文件的关系

//打开文件
//FILE* fopen(const char* filename, const char* mode);
//关闭文件
//int fclose(FILE* stream);
//打开方式如下
/*
文件使用方式		含义											如果指定文件不存在
“r”（只读）		为了输入数据，打开一个已经存在的文本文件		出错
“w”（只写）		为了输出数据，打开一个文本文件					建立一个新的文件
“a”（追加）		向文本文件尾添加数据							建立一个新的文件
“rb”（只读）		为了输入数据，打开一个二进制文件				出错
“wb”（只写）		为了输出数据，打开一个二进制文件				建立一个新的文件
“ab”（追加）		向一个二进制文件尾添加数据						建立一个新的文件
“r+”（读写）		为了读和写，打开一个文本文件					出错
“w+”（读写）		为了读和写，建议一个新的文件					建立一个新的文件
“a+”（读写）		打开一个文件，在文件尾进行读写					建立一个新的文件
“rb+”（读写）		为了读和写打开一个二进制文件					出错
“wb+”（读写）		为了读和写，新建一个新的二进制文件				建立一个新的文件
“ab+”（读写）		打开一个二进制文件，在文件尾进行读和写			建立一个新的文件
*/
//int main()
//{
//	FILE* pFile;
//	//打开文件
//	pFile = fopen("myfile.txt", "w");
//	//文件操作
//	if (pFile != NULL)
//	{
//		fputs("fopen example", pFile);
//		//关闭文件
//		fclose(pFile);
//	}
//	return 0;
//}


//4. 文件的顺序读写
//4.1 顺序读写函数介绍

/*
功能			函数名		适用于
字符输入函数	fgetc		所有输入流
字符输出函数	fputc		所有输出流
文本行输入函数	fgets		所有输入流
文本行输出函数  fputs		所有输出流
格式化输入函数  fscanf		所有输入流
格式化输出函数  fprintf		所有输出流
二进制输入		fread		文件
二进制输出		fwrite		文件
*/
//#include <errno.h>
//int main()
//{
//	FILE* pfWrite = fopen("TEST.txt", "w");
//	if (pfWrite == NULL)
//	{
//		printf("%s\n", strerror(errno));
//		return 0;
//	}
//	//写文件
//	fputc('b', pfWrite);
//	fputc('i', pfWrite);
//	fputc('t', pfWrite);
//	//关闭文件
//	fclose(pfWrite);
//	pfWrite = NULL;
//	return 0;
//}

//#include <errno.h>
//int main()
//{
//	FILE* pfRead = fopen("TEST.txt", "r");
//	if (pfRead == NULL)
//	{
//		printf("%s\n", strerror(errno));
//		return 0;
//	}
//	//读文件
//	printf("%c\n",fgetc(pfRead));//b
//	printf("%c\n",fgetc(pfRead));//i
//	printf("%c\n",fgetc(pfRead));//t
//	//关闭文件
//	fclose(pfRead);
//	pfRead = NULL;
//	return 0;
//}


//从键盘输入
// 输出到屏幕上
// 键盘&屏幕都是外部设备
// 
// 键盘--标准输入设备
// 屏幕标准输出设备
// 是一个程序默认打开的两个流设备
// 
//stdin FILE*
//stdout FILE*
//stderr FILE*

int main()
{
	int ch = fgetc(stdin);//从键盘读取
	fputc(ch, stdout);//放到屏幕上

	return 0;
}