#include<iostream>
#include<iomanip>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<string>
#include<cstring>
#include<stack>
#include<list>
using namespace std;
stack<char>st;
string str2;
list<double>st2;
string judge(string str) {//删除空格 
	int len=str.length();
	for(int i=0;i<len;i++) {
		if(str[i]==' ') {
			str.erase(i,1);
			i--;
		}
		len=str.length();
	}
	return str;
}
int prior(char x) {//优先级排序 
	switch(x) {
		case'(':
			return 1;
		case')':
			return 2;
		case'+':
		case'-':
			return 3;
		case'*':
		case'/':
			return 4;
		case'^':
		case's':
		case'c':
		case'l':
		case't':
			return 5;
	}
}
string change(string str) {//将特殊字符简化 
	int len=str.length();
	for(int i=0;i<len;i++) {
		if(str[i]=='l') {
			str.erase(i+1,1);
		}
		if(str[i]=='p') {
			str.erase(i+1,1);
		}
		if(str[i]=='c') {
			str.erase(i+1,2);
		}
		if(str[i]=='s') {
			str.erase(i+1,2);
		}
		if(str[i]=='t') {
			str.erase(i+1,2);
		}
	}
	return str;
} 
string search(string str) {//将多位数转为乘法便于压栈计算 
	int len=str.length();
	int time;
	string strlen="";
	for(int i=0;i<len;i++) {
		time=0;
		if(str[i]>='0'&&str[i]<='9') {
			for(int j=i+1;j<len;j++) {
				if(str[j]<'0'||str[j]>'9') {
					if(j!=i+1) {
						str.erase(i,j-i);
						str.insert(i,strlen);
					}
					break;
				}
				time++;
				string strlen1="(";
				strlen.insert(0,strlen1);
				if(j==i+1)
					strlen+=str[j-1];
				strlen+="*2*5+";
				strlen+=str[j];
				strlen+=")";
				if(j+1==len) {
					str.erase(i,j-i+1);
					str.insert(i,strlen);
					break;
				}
			}
			i+=time*8;
			strlen.clear();
			len=str.length();
		}
	}
	return str;
}
void adjust(string str) {//中缀表达式转后缀表达式 
	int len=str.length();
	for(int i=0;i<len;i++) {
		if(str[i]>='0'&&str[i]<='9')
			str2+=str[i];
		else 
			if(str[i]=='x'||str[i]=='e'||str[i]=='p'||str[i]=='y') 
				str2+=str[i];
			else
				if(str[i]=='(')
					st.push('(');
				else 
					if(str[i]==')') {
						while(st.top()!='(') {
							str2+=st.top();
							st.pop();
						}
						st.pop();
					}
					else {
						while(!st.empty()&&prior(st.top())>=prior(str[i])) {
							str2+=st.top();
							st.pop();
						}
						st.push(str[i]);
					}		
	}
	while(!st.empty()) {
		str2+=st.top();
		st.pop();
	}
}
inline double calculate(double a,char cal,double b) {//运算符操作 
	if(cal=='+')
		return b+a;
	if(cal=='-')
		return b-a;
	if(cal=='*')
		return b*a;
	if(cal=='/')
		return b/a;
	if(cal=='^')
		return pow(b,a); 
	if(cal=='c')
		return cos(b);
	if(cal=='s')
		return sin(b);
	if(cal=='l')
		return log(b);
	if(cal=='t')
		return tan(b);	
}
double work(double x,double y) {//计算 
	int len=str2.length();
	double sum;
	if(len==1&&str2[0]=='x') {
		return x;
	}
	for(int i=0;i<len;i++) {
		if(str2[i]>='0'&&str2[i]<='9')
			st2.push_back(str2[i]-'0');
		else
			if(str2[i]=='x')
				st2.push_back(x);
			else
				if(str2[i]=='y')
					st2.push_back(y);
				else
					if(str2[i]=='e')
						st2.push_back(2.718281828);
					else
						if(str2[i]=='p')
							st2.push_back(3.141592653);
						else {
							if(str2[i]=='c'||str2[i]=='s'||str2[i]=='l'||str2[i]=='t') {
								double b;
								b=st2.back();
								st2.pop_back();
								st2.push_back(calculate(0,str2[i],b));
								for(list<double>::iterator it=st2.begin();it!=st2.end();it++) {
					 				sum=*it;
						 	//		cout<<*it; 
								}
							//	for(int j=i+1;j<len;j++) {
							//		cout<<str2[j]<<" ";
							//	}
							//	cout<<endl;
							}
							else {
								double a,b;
								a=st2.back();
								st2.pop_back();
								b=st2.back();
								st2.pop_back();
								st2.push_back(calculate(a,str2[i],b));
								for(list<double>::iterator it=st2.begin();it!=st2.end();it++) {
								//	cout<<*it;
					 				sum=*it;
								}
							//	for(int j=i+1;j<len;j++) {
							//		cout<<str2[j]<<" ";
							//	}
							//	cout<<endl;
							}
		}
	}
	if(sum<=1e-9&&sum>=0)
		return 0;
	else
		return sum;
}
int main(int argc,char *argv[]) {
	freopen("trans.txt","w",stdout); 
	string s1=argv[1];
	if(argc==4) {
		s1=judge(s1);
		s1=change(s1);
		s1=search(s1);
		adjust(s1);
		cout<<work(atof(argv[2]),atof(argv[3]))<<endl;
		//system("pause");
	}
	fclose(stdout);
	return 0;
}
