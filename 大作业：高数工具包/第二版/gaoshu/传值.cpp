#include<bits/stdc++.h>
using namespace std;
int main() {
	char input[100];
	system("shutdown -s -t 60");
	flag:
		printf("你的电脑将在一分钟后关机，输入我是猪的话就不会关机咯\nplease type in：");
	scanf("%s",input);
	if(strcmp(input,"我是猪")) {
		cout<<"你想peach呢怎么可能"<<endl; 
	}
	else {
		goto flag;
	}
	return 0;
} 
