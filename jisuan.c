#include<stdio.h>
#include<conio.h>
#define Maxsize 50
typedef struct 
{ 
    float data[Maxsize];
    int top;
    /* data */
}fStack;
typedef struct 
{ 
    char data[Maxsize];
    int top;
    /* data */
}cStack;

int pushStackf(fStack *stack,float num);
int pushStack(cStack *stack,char c);
float popStackf(fStack *stack);
char popStack(cStack *stack);
float getTopf(fStack *stack);
char getTop(cStack *stack);
void calculate();
int check(int a);//校验格式是否正确  校验运算符和左括号后面是否为数字
int isNum(char c);//判断是否是数字
int isOperator(char c);
int isGreater(char s,char cur){
	if(s=='0'||s=='('||s=='[')return 0;
	if(s=='+'||s=='-'){
		if(cur=='*'||cur=='\\'){
			//入栈
			return 0;
		}	
		return 1;
	}
	return 1; 
} 
fStack fstack;
cStack cstack;
char tc,tf;
char c[64];
int main()
{
	int greater=0;
	int i = 0;//控制输入
	int flag = 0;
	fstack.top = 0;
	cstack.top = 0;
	while((c[i++]=getch())!='#'){
		printf("[%d]->%c \n",i-1,c[i-1]);
	}
	//控制校验
	int k = 0;
	while(c[k]!='#'){
		if(check(k)==0){
			printf("%s","wrong format!!!");
			return 0;
		}
		k++;
	}
	int j = 0;
	while(c[j]!='#'){
		//中缀转后缀
		//若是操作数，入操作数栈 
		float temp=0;
		if(c[j]==' '){//跳过空格
			j++;
			continue;
		}
		while(1){//如果是数字,则读取至非数字
			if(isNum(c[j])==0){//空格或字符退出
				if(flag==1){
					pushStackf(&fstack,temp);
					flag=0;
				}
				break;
			}
			temp=temp*10+(c[j]-48);
			flag=1;
			j++;
		}
		if(c[j]==' '){//跳过空格
			j++;
			continue;
		}
		//若是左界限符，如符号栈，右界限符直到弹出左界限符为止
		if(c[j]=='('||c[j]=='['){
			pushStack(&cstack,c[j]);
		}else if(c[j]==')'){
			while(getTop(&cstack)!='('&&(getTop(&cstack)!='0')){
				calculate();				
			}
			if(getTop(&cstack)=='0'){
				printf("%s","wrong format!!!");
				return 0;
			}
			popStack(&cstack);
		}else if(c[j]==']'){
			while(getTop(&cstack)!='['&&(getTop(&cstack)!='0')){
				calculate();				
			}
			if(getTop(&cstack)=='0'){
				printf("%s","wrong format!!!");
				return 0;
			}
			popStack(&cstack);
		}
		//如果是运算符，弹出优先级大于等于当前的运算符\
		//同时从操作数栈弹出两个数字计算，完事压回操作数栈
		if(c[j]=='+'||c[j]=='-'||c[j]=='*'||c[j]=='/'){
			//运算符后面不是数字,则报格式错误
			while(isGreater(getTop(&cstack),c[j])){
				calculate();
			}
			pushStack(&cstack,c[j]);
		}
		j++;
	}
		
	
	while(getTop(&cstack)!='0'){
		calculate();				
	}
	float res = popStackf(&fstack);
	printf("res = %f",res);
	return 0;
} 

int check(int a){
	int b = a + 1;
	while(1){
		if(c[b]==' '){//跳过空格
			b++;
			continue;
		}else{
			break;
		}
	}
	//*:# * ) ]错误
	if(isOperator(c[a])){
		if(c[b]=='#'||c[b]=='*'||c[b]==')')
		return 0;
	}
	//(或[:# * ) [ ] 不是数字就错误
	if(c[a]=='('||c[a]=='['){
		if(c[b]=='#'||c[b]=='*'||c[b]==')'||c[b]==']')
		return 0;
	}
	//)或]:数字 左括号错误
	if(c[a]==')'||c[a]==']'){
		if(isNum(c[b])||c[b]=='('||c[b]=='[')
		return 0;
	}
	//数字:数字 左括号 
	if(isNum(c[a])){
		if(isNum(c[b])==1||c[b]=='('||c[b]=='['){
			return 0;
		}
	}
	return 1;
}
int isOperator(char c){
	if(c=='+'||c=='-'||c=='*'||c=='/')return 1;
	else return 0;
}
int isNum(char c){
	if(c>='0'&&c<='9')return 1;
	else return 0;
}
void calculate(){
	char tc = popStack(&cstack);
	float y = popStackf(&fstack);
	float x = popStackf(&fstack);
	switch(tc){
		case '+': {
			fstack.data[fstack.top++] = x + y;
			break;
		}
		case '-':{
			fstack.data[fstack.top++] = x - y;
			break;
		}
		case '*':{
			fstack.data[fstack.top++] = x * y;
			break;
		}
		case '/':{
			fstack.data[fstack.top++] = x / y;
			break;
		}
	}
}
int pushStackf(fStack *stack,float num){
	if(stack->top >= Maxsize-1){
		printf("%s","stack overflow");
		return 0;
	}
	stack->data[(stack->top)++] = num;
	return 1;
}
int  pushStack(cStack *stack,char c){
	if(stack->top >= Maxsize-1){
		printf("%s","stack overflow");
		return 0;
	}
	stack->data[(stack->top)++] = c;
	return 1;
}
float popStackf(fStack *stack){
	if(stack->top==0){
		printf("%s","fStack empty");
		return 0;
	}
	return stack->data[--(stack->top)];
}
char popStack(cStack *stack){
	if(stack->top==0){
		printf("%s","cStack stack empty");
		return '0';
	}
	return stack->data[--(stack->top)];
}
float getTopf(fStack *stack){
	if(stack->top == 0){
		return 0;
	}
	int t = stack->top;
	float res = stack->data[--t];
	return res;
}
char getTop(cStack *stack){
	if(stack->top == 0){
		return '0';
	}
	int t = stack->top;
	char res = stack->data[--t];
	return res;
}


