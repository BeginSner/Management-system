#ifndef __SYSTEM_STRUCTURE_H__
#define __SYSTEM_STRUCTURE_H__
#include <iostream>
using namespace std;
//学生生日日期的类
class BirthDate
{
public:
    int year;  //出生年
    int month; //月
    int day;   //日
    //两种类的构造函数
    //参数无，返回值无
    BirthDate();
    //参数年，月，日，返回值无
    BirthDate(int y, int m, int d) : year(y), month(m), day(d) {}
    //重载输入输出运算符，可以对BirthDate所有属性（年月日）进行输入输出
    //参数istream对象，生日日期类对象，返回值istream对象
    friend istream &operator>>(istream &in, BirthDate &b);
    //参数ostream对象，生日日期类对象，返回值ostream对象
    friend ostream &operator<<(ostream &out, BirthDate &b);
    //修改生日，修改年月日属性
    //参数年，月，日，返回值无
    void change(int y, int m, int d);
};

class Person
{
protected:
    string name;     //姓名
    string sex;      //性别
    BirthDate birth; //出生日期

public:
    Person();
    //参数姓名，性别，年，月，日，并将年，月，日传递给birth进行初始化
    Person(string n, string s, int y, int m, int d) : birth(y, m, d), name(n), sex(s){};
    ~Person();
    //输出所有Person类属性，按照构造函数参数顺序进行排序
    //参数无，返回值无
    virtual void display() {}
    //输入Person类对象的所有属性，按照构造函数参数顺序进行排序
    //参数无，返回值无
    void input();
};

//继承Person类的学生类
class Student : public Person
{
protected:
    string id;        //学号
    string course[5]; //五门课的名字
    double score[5];  //五门课对应的成绩
    double total;     //总分
    int stu_num;      //学生总人数
    int added_num;    //增加的学生人数
public:
    Student();
    //按照参数顺序取首字母的构造函数参数
    //参数姓名，性别，年，月，日，学号，课程名数组，分数数组，总分
    Student(string n, string s, int y, int m, int d, string i, string course[5], double score[5], double t);
    ~Student();
    //对于学生类的输入输出符号重载，输入输出学生类对象中的所有属性，按照构造函数中的顺序
    //参数istream对象，学生类对象，返回值istream对象
    friend istream &operator>>(istream &in, Student &s);
    //参数ostream对象，学生类对象，返回值ostream对象
    friend ostream &operator<<(ostream &out, Student &s);
    //显示学生类的所有属性，按照构造函数中参数顺序输出
    //参数无，返回值无
    void display(){}
    //输入学生类所有属性
    //参数学生类指针，返回值无
    void input(Student *s){}
};
//大学生类继承学生类
class Undergraduate : public Student
{
private:
    string major; //专业
    double gpa;   //绩点
public:
    Undergraduate();
    //参数姓名，性别，年，月，日，学号，课程数组，分数数组，总分，专业名。其中姓名，性别，年月日，学号，课程名数组，分数数组，总分传递给学生类构造函数初始化，gpa初始化为0
    Undergraduate(string n, string s, int y, int m, int d, string i, string course[5], double score[5], double t, string major) : Student(n, s, y, m, d, i, course, score, t), major(major) { gpa = 0; };
    ~Undergraduate();
    //对大学生类的输入输出
    //参数istream对象，大学生类对象，返回值istream对象
    friend istream &operator>>(istream &in, Undergraduate &u);
    //参数ostream对象，大学生类对象，返回值ostream对象
    friend ostream &operator<<(ostream &out, Undergraduate &u);
    //参数无，返回值无
    void load(Undergraduate *u); //将文件中大学生类所有属性加载到内存
    //参数无，返回值无
    void display(Undergraduate *u); //显示大学生类的所有属性，按照构造函数中参数顺序输出
    //参数大学生类对象指针，返回值无
    int input(Undergraduate *u); //从键盘输入大学生类所有属性
    //参数无，返回值无
    void save(Undergraduate *u); //将大学生类所有属性存入文件
    //参数大学生类对象指针，返回值无
    void add(Undergraduate *u); //添加学生
    //参数大学生类对象指针，返回值无
    void remove(Undergraduate *u); //移除学生
    //参数大学生类对象指针，返回值无
    void change(Undergraduate *u); //修改学生信息
    //参数大学生类对象指针，返回值无
    void search(Undergraduate *u); //查询学生信息
    //参数指向常量大学生类对象指针，学号常量，返回值布尔值，学号唯一返回1，学号不唯一返回0
    bool unique(const Undergraduate *u, const string id); //判断该学号是否重复
    //参数指向常量大学生类对象指针，布尔值判断升序还是降序，1为升序，0为降序，返回值无
    void sort_by_grade(Undergraduate *u, bool up_or_down); //排名（升序或降序）
    //参数指向常量大学生类对象指针，返回值无
    void fail(Undergraduate *u); //判断是否挂科，所有课程成绩中分数低于60即为挂科，将课程与分数输出
    //选择界面函数，显示所有可供选择的对大学生类对象的操作，根据键盘输入选择不同的函数进行操作
    //参数指向常量大学生类对象指针，返回值无
    void panel(Undergraduate *u);
};
#endif