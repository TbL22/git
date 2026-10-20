//使用链栈实现表达式求值，操作数为0到9的单个数字
#include<iostream>
#include<string>
using namespace std;
typedef int Status;
#define Ok 1
#define ERROR 0

//date用int类型，既可以保存数字，也可以保存运算符的字符编码
typedef struct LNode{
    int date;
    struct LNode *next;
}LNode,*LinkStack;

Status InitLinkStack(LinkStack &S){
    S=NULL;
    return Ok;
}

int GetLinkTop(LinkStack S){
    if(S==NULL)
        return '\0';
    return S->date;
}

Status LinkPush(LinkStack &S,int e){
    LNode *p=new LNode;
    p->date=e;
    p->next=S;
    S=p;
    return Ok;
}

Status LinkPop(LinkStack &S,int &e){
    if(S==NULL)
        return ERROR;
    LNode *p=S;
    e=p->date;
    S=S->next;
    delete p;
    return Ok;
}

Status DestroyLinkStack(LinkStack &S){
    LNode *p;
    while(S!=NULL){
        p=S;
        S=S->next;
        delete p;
    }
    return Ok;
}

//返回运算符在优先级表中的下标
int GetIndex(char ch){
    switch(ch){
        case '+':return 0;
        case '-':return 1;
        case '*':return 2;
        case '/':return 3;
        case '(':return 4;
        case ')':return 5;
        case '#':return 6;
    }
    return -1;
}

char Precede(char a,char b){
    //行是栈顶运算符，列是当前读入的运算符，空格表示不能匹配
    char c[7][7]={
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=',' '},
        {' ',' ',' ',' ',' ',' ',' '},
        {'<','<','<','<','<',' ','='}
    };
    int i=GetIndex(a),j=GetIndex(b);
    if(i==-1||j==-1)
        return ' ';
    return c[i][j];
}

Status Operate(int a,char ch,int b,int &e){
    switch(ch){
        case '+':e=a+b;break;
        case '-':e=a-b;break;
        case '*':e=a*b;break;
        case '/':
            if(b==0)
                return ERROR;
            e=a/b;
            break;
        default:return ERROR;
    }
    return Ok;
}

Status EvaluateExpression(string s,int &e){
    LinkStack OPTR,OPND;
    InitLinkStack(OPTR);
    InitLinkStack(OPND);
    LinkPush(OPTR,'#');
    int a,b,x,t;
    string::size_type i=0;
    //flag为1表示此处需要数字或左括号，为0表示需要运算符或右括号
    int flag=1;
    Status result=ERROR;
    while(i<s.size()){
        char ch=s[i];
        if(ch==' '||ch=='\t'||ch=='\r'){
            i++;
            continue;
        }
        if(ch>='0'&&ch<='9'){
            if(flag==0)
                break;
            LinkPush(OPND,ch-'0');
            flag=0;
            i++;
        }
        else{
            if(GetIndex(ch)==-1)
                break;
            if(ch=='#'&&GetLinkTop(OPTR)=='#'){
                if(flag==0&&OPND!=NULL&&OPND->next==NULL){
                    i++;
                    while(i<s.size()&&(s[i]==' '||s[i]=='\t'||s[i]=='\r'))
                        i++;
                    if(i==s.size()){
                        e=GetLinkTop(OPND);
                        if(e>=0&&e<=9)
                            result=Ok;
                    }
                }
                break;
            }
            if((flag==1&&ch!='(')||(flag==0&&ch=='('))
                break;
            char c=Precede(char(GetLinkTop(OPTR)),ch);
            if(c=='<'){
                LinkPush(OPTR,ch);
                flag=1;
                i++;
            }
            else if(c=='>'){
                if(LinkPop(OPTR,t)==ERROR||LinkPop(OPND,b)==ERROR||LinkPop(OPND,a)==ERROR)
                    break;
                //先弹出右操作数b，再弹出左操作数a
                if(Operate(a,char(t),b,x)==ERROR)
                    break;
                LinkPush(OPND,x);
            }
            else if(c=='='){
                LinkPop(OPTR,t);
                i++;
            }
            else
                break;
        }
    }
    DestroyLinkStack(OPTR);
    DestroyLinkStack(OPND);
    return result;
}

int main(){
    string s;
    int e;
    cout<<"请输入表达式（操作数和结果都在0-9的范围内，以#结束）："<<endl;
    getline(cin,s);
    if(EvaluateExpression(s,e)==Ok)
        cout<<"计算结果："<<e<<endl;
    else
        cout<<"表达式不合法、除数为0或结果不在0-9范围内！"<<endl;
    return 0;
}
