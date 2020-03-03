#include <iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

using namespace std;
/**
    视频全长219s
    帧率30FPS
    共30*219 = 6570帧
    每一帧的播放时间约等于100/3(ms) ≈ 33(ms)
    每播放30帧就会多出(1/3)*30 = 10(ms)空档
    因此要对视频的时间轴进行修正，每播放30帧修正一次
    播放时的控制台小黑窗要设置为79*24的尺寸来契合字符动画的尺寸
*/
/*
    目前发现不能用Sleep()函数来修正时间轴，因为程序每次执行的
    startTime和finishTime会稍有差别，因此会导致调用Sleep函数的
    判决门限不准，因此导致的结果是虽然时间轴能对准，但是会导致
    画面时快时慢导致轻微的画音不同步，因此还是采用通过计算帧率
    获得标准修正时间来修正时间轴的方法。
*/

//光标归位左上角
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
    void recursur();    //光标归位左上角

    clock_t startTime = 0, finishTime = 0;  //字符动画开始时间，字符动画播放完一帧后用的时间
    int i = 0, delaytime = 33;   //计算得的标准修正时间
    char fileName[22] = {"baascii\\ba(0).txt"}; //文件名数组初始化
    string str; //控制台缓存
    ifstream File("baascii\\ba(0).txt");    //以读入方式打开文件


    cin.get();  //回车开始播放
    system("cls");  //清屏
    PlaySound("BadApple.wav", NULL, SND_FILENAME | SND_ASYNC);
    startTime = clock();    //记录开始播放的时间

    while(i <= 6570)
    {
        if(i % 30 == 0)   //每30帧修正一次时间轴
            delaytime = 43;    //记录时间轴修正次数
        else
            delaytime = 33;
        sprintf(fileName, "%s%d%s", "baascii\\ba(", i, ").txt");    //文件名更新
        finishTime = clock();   //准备完成后的耗时

        //如果时间轴不用修正，则输出字符；否则while进入暂时的死循环来修正时间轴
        if((finishTime - startTime) >= delaytime)
        {
            i++;
            File.open(fileName);    //打开文件
            while(File.good())
            {
                getline(File, str); //文件一行一行读入缓存
                cout << str;    //输出整个文件
            }
            File.close();
            startTime += delaytime;
            cout << "Frame No." << i << "    Delay Time:" << delaytime;
            recursur(); //光标归位
        }
    }
    system("cls");
    cin.get();
    return 0;
}
