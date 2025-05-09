
/*  call_stack

    ���� �ý��ۿ����� ������ �޸𸮿� ���������, �� ���������� `int` �迭�� �̿��Ͽ� �޸𸮸� �����մϴ�.
    ������ SFP�� Return Address�� ���� ���� �޸� �ּҰ� ��������, �̹� ���������� -1�� ��ü�մϴ�.

    int call_stack[]      : ���� ������(`int ��`) �Ǵ� `-1` (��Ÿ������ ���п�)�� �����ϴ� int �迭
    char stack_info[][]   : call_stack[]�� ���� ��ġ(index)�� ���� ������ �����ϴ� ���ڿ� �迭

    ==========================call_stack ���� ��Ģ==========================
    �Ű� ���� / ���� ������ push�� ���   : int �� �״��
    Saved Frame Pointer �� push�� ���  : call_stack������ index
    ��ȯ �ּҰ��� push�� ���       : -1
    =======================================================================


    ==========================stack_info ���� ��Ģ==========================
    �Ű� ���� / ���� ������ push�� ���        : ������ ���� ����
    Saved Frame Pointer �� push�� ���  : � �Լ��� SFP����
    ��ȯ �ּҰ��� push�� ���                 : "Return Address"
    ========================================================================
*/
#include <stdio.h>
#define STACK_SIZE 50 // �ִ� ���� ũ��

int     call_stack[STACK_SIZE];         // Call Stack�� �����ϴ� �迭
char    stack_info[STACK_SIZE][20];     // Call Stack ��ҿ� ���� ������ �����ϴ� �迭

/*  SP (Stack Pointer), FP (Frame Pointer)

    SP�� ���� ������ �ֻ�� �ε����� ����ŵ�ϴ�.
    ������ ������� �� SP = -1, �ϳ��� ���̸� `call_stack[0]` -> SP = 0, `call_stack[1]` -> SP = 1, ...

    FP�� ���� �Լ��� ���� ������ �������Դϴ�.
    ���� ���� �Լ� ���� �������� sfp�� ����ŵ�ϴ�.
*/
int SP = -1;
int FP = -1;

void push(int var);
void func1(int arg1, int arg2, int arg3);
void func2(int arg1, int arg2);
void func3(int arg1);

/*
    ���� call_stack ��ü�� ����մϴ�.
    �ش� �Լ��� ��� ������� �������� ���� �ϼ����� ���� �����Դϴ�.
*/
void push(int var, const char *info) {

    if (SP >= STACK_SIZE - 1) {
        printf("Stack is full.\n");
        return;
    }

    SP++;
    call_stack[SP] = var;
    
    snprintf(stack_info[SP], sizeof(stack_info[SP]), "%s", info); 
 
}
void pop() {

    call_stack[SP] = 0;
    snprintf(stack_info[SP], sizeof(stack_info[SP]), "");
    
    SP--;

}
void print_stack()
{
    if (SP == -1)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("====== Current Call Stack ======\n");

    for (int i = SP; i >= 0; i--)
    {
        if (call_stack[i] != -1)
            printf("%d : %s = %d", i, stack_info[i], call_stack[i]);
        else
            printf("%d : %s", i, stack_info[i]);

        if (i == SP)
            printf("    <=== [esp]\n");
        else if (i == FP)
            printf("    <=== [ebp]\n");
        else
            printf("\n");
    }
    printf("================================\n\n");
}


//func ���δ� �����Ӱ� �߰��ص� ��������, �Ʒ��� ������ �ٲ����� ������
void func1(int arg1, int arg2, int arg3)
{
    int var_1 = 100;

    // func1�� ���� ������ ���� (�Լ� ���ѷα� + push)
    //1. �Ű� ����
    push(arg3, "arg3");
    push(arg2, "arg2");
    push(arg1, "arg1");
    //2. Return Address
    push(-1, "Return Address");
    //3. SFP
    push(FP, "func1 SFP");
    //4. FP ����
    FP = SP;
    //5. ���� ����
    push(var_1, "var_1");

    print_stack();
    func2(11, 13);
    // func2�� ���� ������ ���� (�Լ� ���ʷα� + pop)
    //1. ���� ���� ����
    pop(); //var_2
    //2. FP ����
    FP = call_stack[FP];
    //3. SFP ����
    pop(); // func2 SFP;
    //4.return address ����
    pop();
    //5. �Ű� ���� ����
    pop(); // arg1
    pop(); // arg2

    print_stack();
}


void func2(int arg1, int arg2)
{
    int var_2 = 200;

    // func2�� ���� ������ ���� (�Լ� ���ѷα� + push)
    //1. �Ű� ����
    push(arg2, "arg2");
    push(arg1, "arg1");
    //2. Return Address
    push(-1, "Return Address");
    //3. SFP
    push(FP, "func2 SFP");
    //4. FP ����
    FP = SP;
    //5. ���� ����
    push(var_2, "var_2");

  
    print_stack();
    func3(77);

    // func3�� ���� ������ ���� (�Լ� ���ʷα� + pop)
    //1. ���� ���� ����
    pop(); //var_4
    pop(); //var_3
    //2. FP ����
    FP = call_stack[FP]; 
    //3. SFP ����
    pop(); // func3 SFP;
    //4.return address ����
    pop();
    //5. �Ű� ���� ����
    pop(); // arg1

    print_stack();
}


void func3(int arg1)
{
    int var_3 = 300;
    int var_4 = 400;

    // func3�� ���� ������ ���� (�Լ� ���ѷα� + push)
    //1. �Ű� ����
    push(arg1, "arg1");
    //2. Return Address
    push(-1, "Return Address");
    //3. SFP
    push(FP, "func3 SFP");
    //4. FP ����
    FP = SP;
    //5. ���� ����
    push(var_3, "var_3");
    push(var_4, "var_4");

    print_stack();
}


//main �Լ��� ���õ� stack frame�� �������� �ʾƵ� �˴ϴ�.
int main()
{
    func1(1, 2, 3);
    // func1�� ���� ������ ���� (�Լ� ���ʷα� + pop)
    //1. ���� ���� ����
    pop(); //var_1
    //2. FP ����
    FP = call_stack[FP];
    //3. SFP ����
    pop(); // func1 SFP;
    //4.return address ����
    pop();
    //5. �Ű� ���� ����
    pop(); // arg1
    pop(); // arg2
    pop(); // arg3

    print_stack();
    return 0;
}