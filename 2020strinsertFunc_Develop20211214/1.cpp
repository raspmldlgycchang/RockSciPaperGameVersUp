#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MUST_SAME_MAX_LEN 20
#define g_MAX_LEN 80
//���ڿ��� Ư�� ��ġ�� �����ϴ� �Լ� ������ c��� �ڵ�
int strist(char* src, char(* insert)[MUST_SAME_MAX_LEN], int index);
int strcmpprinciple(char* p1, char* p2);
int main(void)
{
	char message[] = "Java is oriented language!";
	//������ �ϳ� �̻� �������� �ԷµǾ��ִٸ� �� ���� ����� ��� ����
	char* p1 = NULL, * p2 = NULL;
	int result = strcmpprinciple(p1, p2);
	printf("%d\n", result);
	char ins[20] = { 0, };//��������
	fputs((char*)"������ ���� ���ڿ��� �Է����ּ���:", stdout);
	fgets(ins, 20, stdin);//object�Է�
	//ins���ڿ��� �״�� ������ ���ͱ��� ���� �������ϴ�.
	//�׷��� '\n'�ڸ��� ���鹮�ڷ� �ٲپ����ϴ�
	int len = strlen(ins);
	ins[len] = 0;
	printf("%s:ins\n", ins);
	//�迭�� �Ű������� ������ ����� �迭�����͸� �̿��ϴ°��� ��Ģ�Դϴ�
	//�迭�����͸� �̿��ؾ��ϴ� ���� char�� 1,������ �迭 ��� �ش��ϰ�
	//1����char���迭���ּҿ����ڸ��迭���ٿ����������մϴ�
	//������ char�� 1�����迭�� const char*�� �迭���� �ѱ�� �͵� �����մϴ�
	strist(message, &ins, 8);
	return 0;
}
//int strist(char* src, const char* insert, int index)����
//int strist(char* src, char* insert, int index)����
int strist(char* src, char(* insert)[MUST_SAME_MAX_LEN], int index)
{
	int len,i;
	const int ORI_SIZE = 80;//��������
	char ori[ORI_SIZE] = { 0, };
	if(src==NULL){//�����ּҰ� NULL���� �����ؼ� �Ҵ�ȵ� �޸����� Ȯ��
		printf("���ڿ��� �Է����ּ��� : ");
		fgets(ori, ORI_SIZE, stdin);//�ִ� �Է±��̸� fgets�� �� ��° ���ڷ� �־��ָ� �ǿ�
		len = strlen(ori)+1;
		//char�� �迭�� �� char*�� ������ �̷��� ���� �����մϴ�
		//strcpy_s(src, ori, len);
		memcpy(src, ori, len);
		printf("%s\n", src);
	}
	char temp_left[100] = { 0, };//�� �迭�� ���Թ��ڿ����� �־ ��ȯ�� ����
	//�ʱ�ȭ
	for (i = 0; i < index; i++) {
		temp_left[i] = *(src + i);
	}
	//temp_left���� index���� �ε��������� �����ϱ� ������ index��ġ�� �ι��� �־��ݴϴ�
	temp_left[index] = 0;
	printf("%s: temp_left\n", temp_left);
	/*for (; i < strlen(*insert); i++) {
		temp_left[i] = *(*(insert+0)+i-index);
	}*/
	strcat_s(temp_left, *insert);
	printf("%s: temp_left after insert\n", temp_left);
	for (i = strlen(*insert) + index - 1; i < strlen(src); i++) {
		*(temp_left + i) = src[i];
	}
	temp_left[i] = 0;
	//temp_left[strlen(src)] = 0;�� ����

	printf("%s: temp_left after all strcat complete\n", temp_left);
	return 0;
}
int strcmpprinciple(char* p1, char* p2)
{
	int len;
	const int MAX_LEN = 256;
	char str1[MAX_LEN] = { 0, };
	char str2[MAX_LEN] = { 0, };
	if (p1 != NULL && p2 != NULL) {
		//strcmpprinciple����
		len = strlen(p1);
		if (len > strlen(p2))
			len = strlen(p2);
	}
	else {
		/*fputsù��°����const char*�̶� ���ڿ����������
		char* ĳ�������ָ� const char*�� char*�̵� const char*�̵�
		��� ���� �� �־� ù��°���ڰ� const char*�̰�
		�����ͺ����� ��������
		char str[]="~����";const char*ptr=str;
		ptr�� ������(�� ������ ���� ���� ����)
		fputs���� ����;https://blog.naver.com/tipsware/221859230675
		*/
		fputs((char*)"�Է����ּ���: ", stdout);
		/*fgets�� ũ��MAX_LEN���� ������ �� char�� �迭�� �޴� ���*/
		/*https://blog.naver.com/raspmldlgycchang8753/222592154073�� �����ÿ��� fgetsŰ����� ã���ּ���!*/
		fgets(str1,MAX_LEN, stdin);
		fputs((char*)"�Է����ּ���: ", stdout);
		fgets(str2, MAX_LEN, stdin);
		len = strlen(str1) + 1;
		p1 = str1;
		printf("%s : p1\t�����ͺ����� �����޸��Ҵ���ϰ� ��������Ű�� �����ϳ׿�\n", p1);
		len = strlen(str2)+1;
		p2 = (char*)malloc(len);
		memcpy(p2, str2, len);;
		printf("�̹��� �����޸��Ҵ��ѵ� ���̸� �˰� �ִ� ���ڿ��� memcpy�� �����Ͱ�\
����Ű�� �ּҿ� �־����\n");
		printf("%s : p2\n", p2);
		len = (strlen(p1)<len) ? strlen(p1) : len;
		len += 1;
	
	}
	//strcmpprinciple����
	for (unsigned int i = 0; i < len; i++) {
		int ascii_diff;//�ƽ�Ű�ڵ��ȯ���� int���̹Ƿ� 
		//ù��°���ڰ� �� ������(ascii�ڵ尪��) strcmp�Լ��� ������ȯ�̶� �Ʒ�ó�� ���� ���� �ۼ�
		ascii_diff = p1[i] - p2[i];
		if (ascii_diff < 0)	return -1;
		else if (ascii_diff > 0)	return 1;
		else {
			continue;
		}
	}
	return 0;

}