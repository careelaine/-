#include <iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

using namespace std;
/**
    ��Ƶȫ��219s
    ֡��30FPS
    ��30*219 = 6570֡
    ÿһ֡�Ĳ���ʱ��Լ����100/3(ms) �� 33(ms)
    ÿ����30֡�ͻ���(1/3)*30 = 10(ms)�յ�
    ���Ҫ����Ƶ��ʱ�������������ÿ����30֡����һ��
    ����ʱ�Ŀ���̨С�ڴ�Ҫ����Ϊ79*24�ĳߴ��������ַ������ĳߴ�
*/
/*
    Ŀǰ���ֲ�����Sleep()����������ʱ���ᣬ��Ϊ����ÿ��ִ�е�
    startTime��finishTime�����в����˻ᵼ�µ���Sleep������
    �о����޲�׼����˵��µĽ������Ȼʱ�����ܶ�׼�����ǻᵼ��
    ����ʱ��ʱ��������΢�Ļ�����ͬ������˻��ǲ���ͨ������֡��
    ��ñ�׼����ʱ��������ʱ����ķ�����
*/

//����λ���Ͻ�
void recursur()
{
    HANDLE hout;
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout,coord);
}

int main()
{
    void recursur();    //����λ���Ͻ�

    clock_t startTime = 0, finishTime = 0;  //�ַ�������ʼʱ�䣬�ַ�����������һ֡���õ�ʱ��
    int i = 0, delaytime = 33;   //����õı�׼����ʱ��
    char fileName[22] = {"baascii\\ba(0).txt"}; //�ļ��������ʼ��
    string str; //����̨����
    ifstream File("baascii\\ba(0).txt");    //�Զ��뷽ʽ���ļ�


    cin.get();  //�س���ʼ����
    system("cls");  //����
    PlaySound("BadApple.wav", NULL, SND_FILENAME | SND_ASYNC);
    startTime = clock();    //��¼��ʼ���ŵ�ʱ��

    while(i <= 6570)
    {
        if(i % 30 == 0)   //ÿ30֡����һ��ʱ����
            delaytime = 43;    //��¼ʱ������������
        else
            delaytime = 33;
        sprintf(fileName, "%s%d%s", "baascii\\ba(", i, ").txt");    //�ļ�������
        finishTime = clock();   //׼����ɺ�ĺ�ʱ

        //���ʱ���᲻��������������ַ�������while������ʱ����ѭ��������ʱ����
        if((finishTime - startTime) >= delaytime)
        {
            i++;
            File.open(fileName);    //���ļ�
            while(File.good())
            {
                getline(File, str); //�ļ�һ��һ�ж��뻺��
                cout << str;    //��������ļ�
            }
            File.close();
            startTime += delaytime;
            cout << "Frame No." << i << "    Delay Time:" << delaytime;
            recursur(); //����λ
        }
    }
    system("cls");
    cin.get();
    return 0;
}
