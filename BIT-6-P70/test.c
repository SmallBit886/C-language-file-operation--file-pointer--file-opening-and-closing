#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
//BIT-6-C�����ļ�����

//int main()
//{
//	int a = 10000;
//	FILE* pf = fopen("test.txt", "wb");//���ļ����Զ����Ƶķ�ʽд
//	fwrite(&a, 4, 1, pf);//�Զ����Ƶ���ʽд��fpָ����ļ���	//10 27 00 00 = 0x27 10 00 00=10000
//	fclose(pf);//�ر��ļ�
//	pf = NULL;//�ͷ�ָ���ڴ�
//	return 0;
//}


//8. �ļ�������
//ϵͳ�Զ������ڴ���Ϊ������ÿһ������ʹ�õ��ļ�����һ�顰�ļ���������
//�ڴ������������ݻ����͵��ڴ��еĻ�������װ�����������һ���͵�������
//�Ӵ����ļ��ж�ȡ���������뵽�ڴ滺���������������������ٴӻ���������ؽ������͵���������������������ȣ�
//#include <windows.h>
////VS2013 WIN10��������
//int main()
//{
//	FILE* pf = fopen("test.txt", "w");
//	fputs("abcdef", pf);//�Ƚ�����������������
//	printf("˯��10��-�Ѿ�д�����ˣ���test.txt�ļ��������ļ�û������\n");
//	Sleep(10000);
//	printf("ˢ�»�����\n");
//	fflush(pf);//ˢ�»�����ʱ���Ž����������������д���ļ������̣�
//	//ע��fflush �ڸ߰汾��VS�ϲ���ʹ����
//	printf("��˯��10��-��ʱ���ٴδ�test.txt�ļ����ļ���������\n");
//	Sleep(10000);
//	fclose(pf);
//	//ע��fclose�ڹر��ļ���ʱ��Ҳ��ˢ�»�����
//	pf = NULL;
//	return 0;
//}
//���ۣ�
//��Ϊ�л������Ĵ��ڣ�C�����ڲ����ļ���ʱ����Ҫ��ˢ�»������������ļ�����������ʱ��ر��ļ�

//3.1 �ļ�ָ��
//�����ļ�ϵͳ�У��ؼ��ĸ����ǡ��ļ�����ָ�롱����ơ��ļ�ָ��
//ÿ����ʹ�õ��ļ������ڴ��п�����һ����Ӧ���ļ���Ϣ������������ļ��������Ϣ�����ļ������֣��ļ�״̬���ļ���ǰ��λ�õȣ�
//��Щ��Ϣ�Ǳ�����һ���ṹ������еġ��ýṹ����������ϵͳ�����ģ�ȡ��FILE.
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
//ÿ����һ���ļ���ʱ��ϵͳ������ļ�������Զ�����һ��FILE�ṹ�ı�������������е���Ϣ��ʹ���߲��ع���ϸ��
//һ�㶼��ͨ��һ��FILE��ָ����ά�����FILE�ṹ�ı���������ʹ���������ӷ���

//���ǿ��Դ���һ��FILE*��ָ�����
//FILE* pf;//�ļ�ָ�����
/*
����pf��һ��ָ��FILE�������ݵ�ָ�������
����ʹpfָ��ĳ���ļ����ļ���Ϣ������һ���ṹ���������
ͨ�����ļ���Ϣ���е���Ϣ���ܹ����ʸ��ļ���
Ҳ����˵��ͨ���ļ�ָ������ܹ��ҵ������������ļ���
*/

//3.2 �ļ��Ĵ򿪺͹ر�
//�ļ��ڶ�д֮ǰӦ���ȴ��ļ�����ʹ�ý���֮��Ӧ�ùر��ļ�
//���ļ���ͬʱ�����᷵��һ��FILE*��ָ�����ָ����ļ���Ҳ�൱�ڽ�����ָ����ļ��Ĺ�ϵ

//���ļ�
//FILE* fopen(const char* filename, const char* mode);
//�ر��ļ�
//int fclose(FILE* stream);
//�򿪷�ʽ����
/*
�ļ�ʹ�÷�ʽ		����											���ָ���ļ�������
��r����ֻ����		Ϊ���������ݣ���һ���Ѿ����ڵ��ı��ļ�		����
��w����ֻд��		Ϊ��������ݣ���һ���ı��ļ�					����һ���µ��ļ�
��a����׷�ӣ�		���ı��ļ�β��������							����һ���µ��ļ�
��rb����ֻ����		Ϊ���������ݣ���һ���������ļ�				����
��wb����ֻд��		Ϊ��������ݣ���һ���������ļ�				����һ���µ��ļ�
��ab����׷�ӣ�		��һ���������ļ�β��������						����һ���µ��ļ�
��r+������д��		Ϊ�˶���д����һ���ı��ļ�					����
��w+������д��		Ϊ�˶���д������һ���µ��ļ�					����һ���µ��ļ�
��a+������д��		��һ���ļ������ļ�β���ж�д					����һ���µ��ļ�
��rb+������д��		Ϊ�˶���д��һ���������ļ�					����
��wb+������д��		Ϊ�˶���д���½�һ���µĶ������ļ�				����һ���µ��ļ�
��ab+������д��		��һ���������ļ������ļ�β���ж���д			����һ���µ��ļ�
*/
//int main()
//{
//	FILE* pFile;
//	//���ļ�
//	pFile = fopen("myfile.txt", "w");
//	//�ļ�����
//	if (pFile != NULL)
//	{
//		fputs("fopen example", pFile);
//		//�ر��ļ�
//		fclose(pFile);
//	}
//	return 0;
//}


//4. �ļ���˳���д
//4.1 ˳���д��������

/*
����			������		������
�ַ����뺯��	fgetc		����������
�ַ��������	fputc		���������
�ı������뺯��	fgets		����������
�ı����������  fputs		���������
��ʽ�����뺯��  fscanf		����������
��ʽ���������  fprintf		���������
����������		fread		�ļ�
���������		fwrite		�ļ�
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
//	//д�ļ�
//	fputc('b', pfWrite);
//	fputc('i', pfWrite);
//	fputc('t', pfWrite);
//	//�ر��ļ�
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
//	//���ļ�
//	printf("%c\n",fgetc(pfRead));//b
//	printf("%c\n",fgetc(pfRead));//i
//	printf("%c\n",fgetc(pfRead));//t
//	//�ر��ļ�
//	fclose(pfRead);
//	pfRead = NULL;
//	return 0;
//}


//�Ӽ�������
// �������Ļ��
// ����&��Ļ�����ⲿ�豸
// 
// ����--��׼�����豸
// ��Ļ��׼����豸
// ��һ������Ĭ�ϴ򿪵��������豸
// 
//stdin FILE*
//stdout FILE*
//stderr FILE*

int main()
{
	int ch = fgetc(stdin);//�Ӽ��̶�ȡ
	fputc(ch, stdout);//�ŵ���Ļ��

	return 0;
}