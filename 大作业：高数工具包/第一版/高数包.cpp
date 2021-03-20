#include<iostream>
#include<ctime>
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
const int maxn=1e8;
const int MAX=10;
const double minn=1e-8;
const double delta=0.98;
const double tmax=100;
const double tmin=1e-4;
const int times=100;
stack<char>st;
string str2;
list<double>st2;
double rom[MAX][MAX];
double x[1010],y[1010];
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
bool judge1(string str) {//括号配对 
	int judgement=0;
	for(int i=0;i<str.length();i++) {
		if(str[i]=='(') {
			judgement++;
		}
		if(str[i]==')') {
			judgement--;
		}
	}
	if(judgement)
		return 1;
	else
		return 0;
}
bool judge2(string str) {//判断是否除0 
	for(int i=0;i<str.length();i++)
		if(str[i]=='/'&&str[i+1]=='0')
			return 1;
	return 0;
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
bool judge3(string str) {//是否出现问题字符 
	for(int i=0;i<str.length();i++)
		if((str[i]<'0'||str[i]>'9')&&str[i]!='('&&str[i]!=')'&&str[i]!='+'&&str[i]!='-'&&str[i]!='*'&&str[i]!='/'&&str[i]!='^'&&str[i]!='s'&&str[i]!='c'&&str[i]!='l'&&str[i]!='t'&&str[i]!='e'&&str[i]!='p'&&str[i]!='x'&&str[i]!='y')
			return 1;
	return 0;
}
bool judge4(string str) {//错误的字符
	int len=str.length();
	for(int i=0;i<len;i++) {
		if(str[i]=='l'||str[i]=='c'||str[i]=='s'||str[i]=='t'||str[i]=='^'||str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')
			if(str[i+1]=='^'||str[i+1]=='+'||str[i+1]=='-'||str[i+1]=='*'||str[i+1]=='/'||str[i+1]==')')
	   			return 1;
	   	if(str[i]=='l'||str[i]=='c'||str[i]=='s'||str[i]=='t')
	   		if(str[i+1]=='l'||str[i+1]=='c'||str[i+1]=='s'||str[i+1]=='t')
	   			return 1;
	   	if((str[i]=='^'||str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')&&i==0)
	   		return 1;
		if(str[i]=='(')
			if(str[i+1]=='+'||str[i+1]=='-'||str[i+1]=='*'||str[i+1]=='/'||str[i+1]=='^')
				return 1;
		if((str[i]=='p'||str[i]=='y'||str[i]=='x'||str[i]=='e')&&i!=0)
			if((str[i-1]>='0'&&str[i-1]<='9')||str[i-1]=='y'||str[i-1]=='x'||str[i-1]=='e'||str[i-1]=='p')
				return 1;
		if(str[i]=='p'||str[i]=='y'||str[i]=='x'||str[i]=='e')
			if((str[i+1]>='0'&&str[i+1]<='9')||str[i+1]=='y'||str[i+1]=='x'||str[i+1]=='e'||str[i+1]=='p')
				return 1;
		if(str[i]=='s'||str[i]=='c'||str[i]=='t'||str[i]=='l')
			if(str[i+1]!='(')
				return 1;
		if((str[i]=='('||str[i]=='s'||str[i]=='c'||str[i]=='t'||str[i]=='l')&&i!=0)
			if(str[i-1]>='0'&&str[i-1]<='9')
				return 1;
	}
	if(str[len-1]=='+'||str[len-1]=='-'||str[len-1]=='*'||str[len-1]=='/'||str[len-1]=='t'||str[len-1]=='s'||str[len-1]=='l'||str[len-1]=='c'||str[len-1]=='^'||str[len-1]=='(')
		return 1;
	return 0;
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
double maxnum(double l,double r) {//模拟退火最大值 
	srand((unsigned)time(0));
	double ans=minn;
	double t=tmax;
	double x[times+10];
	while(t>tmin) {
		for(int i=0;i<times;i++) {
			double random=rand()%10000/(double)10000;
			x[i]=random*(r-l)+l;
			double funcold=work(x[i],0);
			double funcnew;
			double tempx=x[i]+(random*2-1)*t;
			if(tempx>=l&&tempx<=r) {
				funcnew=work(tempx,0);
				if(funcold<funcnew) 
					x[i]=tempx;
				else {
					double p=exp((funcold-funcnew)/t);
					if(p>random)
						x[i]=tempx;
				}
			//	cout<<x[i]<<endl;
			}
		}
		t=t*delta;
	//	cout<<"t"<<t<<endl;
	}
	for(int i=0;i<times;i++) {
		ans=max(ans,work(x[i],0));
	}
	if(ans+0.1>ceil(ans))
		return ceil(ans);
	else if(ans-0.1<floor(ans))
		return floor(ans);
	return ans;
}//计算区间最大值 
double minnum(double l,double r) {//模拟退火最小值 
	srand((unsigned)time(0));
	double ans=maxn;
	double t=tmax;
	double x[times+10];
	while(t>tmin) {
		for(int i=0;i<times;i++) {
			double random=rand()%10000/(double)10000;
			x[i]=random*(r-l)+l;
			double funcold=work(x[i],0);
			double funcnew;
			double tempx=x[i]+(random*2-1)*t;
			if(tempx>=l&&tempx<=r) {
				funcnew=work(tempx,0);
				if(funcold>funcnew) 
					x[i]=tempx;
				else {
					double p=exp((funcnew-funcold)/t);
					if(p>random)
						x[i]=tempx;
				}
			//	cout<<x[i]<<endl;
			}
		}
		t=t*delta;
	//	cout<<"t"<<t<<endl;
	}
	for(int i=0;i<times;i++) {
		ans=min(ans,work(x[i],0));
	}
	if(ans+0.1>ceil(ans))
		return ceil(ans);
	else if(ans-0.1<floor(ans))
		return floor(ans);
	return ans;
}//计算区间最小值 
void findans(double l,double r) {//二分求解实数根 
    if(r-l<=1e-3) {
        cout<<l<<" ";
        return ;
    }
    double mid=l+(r-l)/2;
    double ans_l,ans_r;
    ans_l=work(l,0)*work(mid,0);
    ans_r=work(mid,0)*work(r,0);
    if(work(mid,0)==0)
		cout<<mid<<" ";
    if(work(r,0)==0)
		cout<<r<<" ";
    if(ans_l<0)
		findans(l,mid);
    else 
		if(ans_r<0)
			findans(mid,r);
} 
void romberg(double l,double r) {//romberg求定积分 
	double len=r-l;
	rom[1][1]=len*(work(l,0)+work(r,0))/2;
	double h=0;
	for(int i=2;i<=8;i++) {
		h=len/pow(2,i-1);
		double sum=0;
		for(int j=1;j<=pow(2,i-2);j++)
			sum+=work(l+(2*j-1)*h,0)*h;
		rom[i][1]=rom[i-1][1]/2+sum;
		for(int k=2;k<=i;k++)
			rom[i][k]=(pow(4,k-1)*rom[i][k-1]-rom[i-1][k-1])/(pow(4,k-1)-1);
	}
	cout<<rom[8][8]<<endl;
}
void differential_equation(int n,double l,double r,double y0) {//微分方程 
	double h=(r-l)/n;
	x[0]=l;
	y[0]=y0;
	for(int i=1;i<=n;i++) {
		x[i]=x[i-1]+h;
		double k1=work(x[i-1],y[i-1]);
		double k2=work(x[i-1]+h/2,y[i-1]+h*k1/2.0);
		double k3=work(x[i-1]+h/2,y[i-1]+h*k2/2.0);
		double k4=work(x[i-1]+h,y[i-1]+h*k3);
		y[i]=y[i-1]+h*(k1+2*k2+2*k3+k4)/6.0;
	}
	for(int i=0;i<=n;i++)
		cout<<"x["<<i<<"]="<<x[i]<<endl;
	cout<<endl;
	for(int i=0;i<=n;i++)
		cout<<"y["<<i<<"]="<<y[i]<<endl;
	cout<<endl;
}
void output1() {//交互引导 
	cout<<"键入1可求函数某一点的函数值"<<endl;
	cout<<"键入2可求函数在某一点处的导数近似值"<<endl;
	cout<<"键入3可求函数在某一段区间内的最大值和最小值的近似值"<<endl;
	cout<<"键入4可求函数的实数解"<<endl;
	cout<<"键入5可求在某一段区间内的定积分"<<endl;
	cout<<"键入6可求一阶微分方程的解"<<endl; 
//	cout<<"键入7可求函数导数表达式"<<endl; 
}
bool decide(string str) {//判断为函数表达式还是计算式 
	int len=str.length();
	for(int i=0;i<len;i++) 
		if(str[i]=='x')
			return 1;
	return 0;
}
int main() {
	int sum=0;
	memset(rom,0,sizeof(rom)); 
	cout<<"请输入函数表达式，小数请用分数表示，微分方程输入y'等于的表达式（ps：不要搞我...我真想象不到能犯什么错）"<<endl; 
	string s1;
	one:	getline(cin,s1);
	if(!s1.length()) {
		cout<<"请输入表达式!!!!!"<<endl;
		sum++;
		if(sum>=10) {
			cout<<"不和你玩了 gun！！！"<<endl;
			system("pause");
			return 0;
		}
		goto one;
	}
	s1=judge(s1);
	if(judge1(s1)) {
		cout<<"括号输入不正确"<<endl;
		return 0; 
	}
	if(judge2(s1)) {
		cout<<"除以0无法计算"<<endl;
		return 0;
	}
	s1=change(s1);
	if(judge3(s1)) {
		cout<<"出现不合法字符"<<endl;
		return 0;
	}
//	cout<<s1;
	if(judge4(s1)) {
		cout<<"字符输入有误"<<endl;
		return 0;
	}
	s1=search(s1);
	adjust(s1);
//	for(int i=0;i<str2.length();i++) {
//		cout<<str2[i]<<" ";
//	}	
//	cout<<endl;
	if(decide(s1)) {
		output1();
		int a;
		cin>>a;
		if(a==1) {
			double x;
			cout<<"x的数值为";
			cin>>x;
			cout<<work(x,0)<<endl;
		}
		if(a==2) {
			double x;
			cout<<"x的数值为";
			cin>>x;
			if(work(x-minn,0)+work(x+minn,0)-2*work(x,0)<minn)
				cout<<"该点导数为"<<(work(x,0)-work(x-minn,0))/minn<<endl;
			else
				cout<<"该点不可导"<<endl; 
		}
		if(a==3) {
			double l,r;
			cout<<"提醒：！！！会非常非常慢！！速度类似打表！！慢慢等哈"<<endl; 
			cout<<"请输入区间端点"<<endl;	 
			cin>>l>>r; 
			double sum1=maxnum(l,r);
			double sum2=minnum(l,r);
			cout<<"最大值为"<<sum1<<endl;
			cout<<"最小值为"<<sum2<<endl;
		}
		if(a==4) {
			double l,r;
			cout<<"请输入区间端点"<<endl;
			cin>>l>>r;
			cout<<"（若无输出则为无解）该函数解为"; 
			for(double i=l;i<=r;i++)
        		if(work(i,0)*work(i+1.0,0)<=0)
            		findans(i,i+1.0);
		}
		if(a==5) {
			double l,r;
			cin>>l>>r;
			cout<<"该段积分为";
			romberg(l,r);
		}
		if(a==6) {
			double l,r,y0;
			int n;
			cout<<"请输入分段数为"; 
			cin>>n; 
			cout<<endl;
			cout<<"请输入y0(初始值)等于";
			cin>>y0;
			cout<<endl; 
			cout<<"请输入区间左右端点";
			cin>>l>>r;
			cout<<endl;
			differential_equation(n,l,r,y0);
		}
	}
	else
		cout<<"表达式求值为"<<work(0,0)<<endl;
	system("pause");
	return 0;
}
