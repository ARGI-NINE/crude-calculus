#include<bits/stdc++.h>
using namespace std;
int main() {
	char input[100];
	system("shutdown -s -t 60");
	flag:
		printf("��ĵ��Խ���һ���Ӻ�ػ�������������Ļ��Ͳ���ػ���\nplease type in��");
	scanf("%s",input);
	if(strcmp(input,"������")) {
		cout<<"����peach����ô����"<<endl; 
	}
	else {
		goto flag;
	}
	return 0;
} 
