#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MUST_SAME_MAX_LEN 20
#define g_MAX_LEN 80
//문자열을 특정 위치에 삽입하는 함수 구현한 c언어 코드
int strist(char* src, char(* insert)[MUST_SAME_MAX_LEN], int index);
int strcmpprinciple(char* p1, char* p2);
int main(void)
{
	char message[] = "Java is oriented language!";
	//공백이 하나 이상 연속으로 입력되어있다면 한 개만 남기고 모두 제거
	char* p1 = NULL, * p2 = NULL;
	int result = strcmpprinciple(p1, p2);
	printf("%d\n", result);
	char ins[20] = { 0, };//문제조건
	fputs((char*)"보내고 싶은 문자열을 입력해주세요:", stdout);
	fgets(ins, 20, stdin);//object입력
	//ins문자열을 그대로 보내면 엔터까지 같이 보내집니다.
	//그래서 '\n'자리를 공백문자로 바꾸었습니다
	int len = strlen(ins);
	ins[len] = 0;
	printf("%s:ins\n", ins);
	//배열을 매개변수로 보내는 방법은 배열포인터를 이용하는것이 원칙입니다
	//배열포인터를 이용해야하는 경우는 char형 1,다차원 배열 모두 해당하고
	//1차원char형배열은주소연산자를배열명에붙여서보내야합니다
	//하지만 char형 1차원배열은 const char*로 배열명을 넘기는 것도 가능합니다
	strist(message, &ins, 8);
	return 0;
}
//int strist(char* src, const char* insert, int index)가능
//int strist(char* src, char* insert, int index)가능
int strist(char* src, char(* insert)[MUST_SAME_MAX_LEN], int index)
{
	int len,i;
	const int ORI_SIZE = 80;//문제조건
	char ori[ORI_SIZE] = { 0, };
	if(src==NULL){//시작주소가 NULL인지 점검해서 할당안된 메모리인지 확인
		printf("문자열을 입력해주세요 : ");
		fgets(ori, ORI_SIZE, stdin);//최대 입력길이를 fgets의 두 번째 인자로 넣어주면 되요
		len = strlen(ori)+1;
		//char형 배열을 빈 char*형 변수에 이렇게 복사 가능합니다
		//strcpy_s(src, ori, len);
		memcpy(src, ori, len);
		printf("%s\n", src);
	}
	char temp_left[100] = { 0, };//이 배열에 삽입문자열까지 넣어서 반환할 것임
	//초기화
	for (i = 0; i < index; i++) {
		temp_left[i] = *(src + i);
	}
	//temp_left에는 index값의 인덱스전까지 저장하기 때문에 index위치에 널문자 넣어줍니다
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
	//temp_left[strlen(src)] = 0;도 가능

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
		//strcmpprinciple구현
		len = strlen(p1);
		if (len > strlen(p2))
			len = strlen(p2);
	}
	else {
		/*fputs첫번째인자const char*이라서 문자열상수보낼시
		char* 캐스팅해주면 const char*은 char*이든 const char*이든
		모두 받을 수 있어 첫번째인자가 const char*이고
		포인터변수를 보내려면
		char str[]="~적고";const char*ptr=str;
		ptr을 보내기(이 한줄은 제가 적은 내용)
		fputs관련 내용;https://blog.naver.com/tipsware/221859230675
		*/
		fputs((char*)"입력해주세요: ", stdout);
		/*fgets로 크기MAX_LEN으로 선언한 빈 char형 배열에 받는 방법*/
		/*https://blog.naver.com/raspmldlgycchang8753/222592154073이 포스팅에서 fgets키워드로 찾아주세요!*/
		fgets(str1,MAX_LEN, stdin);
		fputs((char*)"입력해주세요: ", stdout);
		fgets(str2, MAX_LEN, stdin);
		len = strlen(str1) + 1;
		p1 = str1;
		printf("%s : p1\t포인터변수에 동적메모리할당안하고 변수가리키기 가능하네요\n", p1);
		len = strlen(str2)+1;
		p2 = (char*)malloc(len);
		memcpy(p2, str2, len);;
		printf("이번엔 동적메모리할당한뒤 길이를 알고 있는 문자열을 memcpy로 포인터가\
가리키는 주소에 넣었어요\n");
		printf("%s : p2\n", p2);
		len = (strlen(p1)<len) ? strlen(p1) : len;
		len += 1;
	
	}
	//strcmpprinciple구현
	for (unsigned int i = 0; i < len; i++) {
		int ascii_diff;//아스키코드반환값은 int형이므로 
		//첫번째인자가 더 작으면(ascii코드값이) strcmp함수는 음수반환이라서 아래처럼 빼기 순서 작성
		ascii_diff = p1[i] - p2[i];
		if (ascii_diff < 0)	return -1;
		else if (ascii_diff > 0)	return 1;
		else {
			continue;
		}
	}
	return 0;

}