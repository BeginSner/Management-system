#include "system_structure.h"
#include <iostream>
#include <fstream>
#include <string>
#define N 100
void Undergraduate::panel(Undergraduate *u)
{
    Undergraduate stu;
    while (1)
    {
        cout << "1:显示学生信息" << endl;
        cout << "2:存入学生信息" << endl;
        cout << "3:增加学生信息" << endl;
        cout << "4:删除学生信息" << endl;
        cout << "5:修改学生信息" << endl;
        cout << "6:查询学生信息" << endl;
        cout << "7:学生成绩排序" << endl;
        cout << "8:学生挂科情况" << endl;
        cout << "9:退出" << endl;
        cout << "输入1~9挑选服务" << endl;
        char ch;
        cin >> ch;
        // cin.get();
        switch (ch)
        {
        case '1':
            cout << "-----------------------------------------" << endl;
            stu.display(u);
            cout << "-----------------------------------------" << endl;
            break;
        case '2':
            cout << "-----------------------------------------" << endl;
            stu.save(u);
            cout << "-----------------------------------------" << endl;
            break;
        case '3':
            cout << "-----------------------------------------" << endl;
            stu.add(u);
            cout << "-----------------------------------------" << endl;
            break;
        case '4':
            cout << "-----------------------------------------" << endl;
            stu.remove(u);
            cout << "-----------------------------------------" << endl;
            break;
        case '5':
            cout << "-----------------------------------------" << endl;
            stu.change(u);
            cout << "-----------------------------------------" << endl;
            break;
        case '6':
            cout << "-----------------------------------------" << endl;
            search(u);
            cout << "-----------------------------------------" << endl;
            break;
        case '7':
            cout << "-----------------------------------------" << endl;
            char ch1;
            cout << "选择升序还是降序,升序输入1降序输入0" << endl;
            cin >> ch1;
            // cin.get();
            if (ch1 == '1')
            {

                sort_by_grade(u, 1);

                break;
            }
            else if (ch1 == '0')
            {

                sort_by_grade(u, 0);

                break;
            }
            else
            {
                cout << "非法输入,仅有0和1合法" << endl;
                break;
            }
            cout << "-----------------------------------------" << endl;
        case '8':
            cout << "-----------------------------------------" << endl;
            fail(u);
            cout << "-----------------------------------------" << endl;
            break;

        case '9':
            exit(0);
        default:
            cout << "-----------------------------------------" << endl;
            cout << "无效输入" << endl;
            cout << "-----------------------------------------" << endl;
        }
    }
}
Undergraduate::Undergraduate()
{
    major = '0';
    gpa = 0;
}
Undergraduate::~Undergraduate() {}
istream &operator>>(istream &in, Undergraduate &u)
{
    cout << "专业: ";
    in >> u.major;
    cout << "姓名: ";
    in >> u.name;
    cout << "性别: ";
    in >> u.sex;
    cout << "出生日期(年月日以空格分开): ";
    in >> u.birth;
    cout << "学号: ";
    in >> u.id;
    cout << "课程1 对应分数: " << endl;
    in >> u.course[0] >> u.score[0];
    cout << "课程2 对应分数: " << endl;
    in >> u.course[1] >> u.score[1];
    cout << "课程3 对应分数: " << endl;
    in >> u.course[2] >> u.score[2];
    cout << "课程4 对应分数: " << endl;
    in >> u.course[3] >> u.score[3];
    cout << "课程5 对应分数: " << endl;
    in >> u.course[4] >> u.score[4];
    return in;
}
ostream &operator<<(ostream &out, Undergraduate &u)
{
    out << "major:\"" << u.major << "\" ";
    out << "name:\"" << u.name << "\" ";
    out << "gender:\"" << u.sex << "\" ";
    out << "birthdate:\"" << u.birth << "\" ";
    out << "id:\"" << u.id << "\" ";

    out << "courses:\"" << u.course[0] << ":" << u.score[0] << " ";
    out << u.course[1] << ":" << u.score[1] << " ";
    out << u.course[2] << ":" << u.score[2] << " ";
    out << u.course[3] << ":" << u.score[3] << " ";
    out << u.course[4] << ":" << u.score[4] << "\"";
    return out;
}
void Undergraduate::load(Undergraduate *u)
{
    // cout << "专业 姓名 性别 出生日期 学号 课程1 分数1 课程2 分数2 课程3 分数3 课程4 分数4 课程5 分数5" << endl;
    ifstream infile("Undergraduate.dat", ios::in);
    if (!infile)
    {
        cout << "open error" << endl;
        exit(1);
    }
    int i = 0;
    string line;
    int begin, end;
    while (!infile.eof() && i < N)
    {

        getline(infile, line);
        if ((begin = line.find("major:")) != string::npos)
        {
            begin += 6;
            //找major
            if (begin == line.find('"'))
            {
                end = line.find('"', begin + 1);
                u[i].major = line.substr(begin + 1, end - (begin + 1));
            }
            //找name
            begin = line.find('"', end + 1);
            end = line.find('"', begin + 1);
            u[i].name = line.substr(begin + 1, end - (begin + 1));
            //找gender
            begin = line.find('"', end + 1);
            end = line.find('"', begin + 1);
            u[i].sex = line.substr(begin + 1, end - (begin + 1));
            //找birthdate
            // year位置
            begin = line.find('"', end + 1);
            end = line.find('-', begin + 1);
            //字符类型转成int
            string X;
            X = line.substr(begin + 1, (end - (begin + 1)));
            u[i].birth.year = atoi(X.c_str());
            // month位置
            begin = end;
            end = line.find('-', begin + 1);
            X = line.substr(begin + 1, (end - (begin + 1)));
            u[i].birth.month = atoi(X.c_str());
            // day位置
            begin = end;
            end = line.find('"', begin + 1);
            X = line.substr(begin + 1, (end - (begin + 1)));
            u[i].birth.day = atoi(X.c_str());
            //找id
            begin = line.find('"', end + 1);
            end = line.find('"', begin + 1);
            u[i].id = line.substr(begin + 1, end - (begin + 1));
            //找course1和对应分数
            begin = line.find('"', end + 1);
            end = line.find(':', begin + 1);
            u[i].course[0] = line.substr(begin + 1, end - (begin + 1));
            begin = end;
            end = line.find(' ', begin + 1);
            X = line.substr(begin + 1, end - (begin + 1));
            u[i].score[0] = atof(X.c_str());
            //找course2和对应分数
            begin = end;
            end = line.find(':', begin + 1);
            u[i].course[1] = line.substr(begin + 1, end - (begin + 1));
            begin = end;
            end = line.find(' ', begin + 1);
            X = line.substr(begin + 1, end - (begin + 1));
            u[i].score[1] = atof(X.c_str());
            //找course3和对应分数
            begin = end;
            end = line.find(':', begin + 1);
            u[i].course[2] = line.substr(begin + 1, end - (begin + 1));
            begin = end;
            end = line.find(' ', begin + 1);
            X = line.substr(begin + 1, end - (begin + 1));
            u[i].score[2] = atof(X.c_str());
            //找course4和对应分数
            begin = end;
            end = line.find(':', begin + 1);
            u[i].course[3] = line.substr(begin + 1, end - (begin + 1));
            begin = end;
            end = line.find(' ', begin + 1);
            X = line.substr(begin + 1, end - (begin + 1));
            u[i].score[3] = atof(X.c_str());
            //找course5和对应分数
            begin = end;
            end = line.find(':', begin + 1);
            u[i].course[4] = line.substr(begin + 1, end - (begin + 1));
            begin = end;
            end = line.find('"', begin + 1);
            X = line.substr(begin + 1, end - (begin + 1));
            u[i].score[4] = atof(X.c_str());
            ++i;
        }
        stu_num = i;
    }
    infile.close();
}
void Undergraduate::display(Undergraduate *u)
{
    load(u);
    for (int i = 1; i < stu_num + 1; ++i)
    {
        cout << "学生" << i << endl;
        cout << u[i - 1] << endl;
    }
}
int Undergraduate::input(Undergraduate *u)
{

    cout << "请输入要导入信息的学生人数: " << endl;
    int n;
    cin >> n;
    if (n < 0)
        cout << "人数不能小于零" << endl;
    else if (n >= N)
        cout << "人数超过上限" << endl;
    stu_num = n;
    cout << "输入学生信息" << endl;
    // cout << "专业 姓名 性别 出生日期:年 月 日 学号 课程1 分数1 课程2 分数2 课程3 分数3 课程4 分数4 课程5 分数5" << endl;
    try
    {
        Undergraduate tmp[N];
        load(tmp);
        for (int i = 0; i < n; i++)
        {
            cin >> u[i];
            if (!unique(tmp, u[i].id))
                throw u[i].id;
            if (u[i].score[0] < 0 || u[i].score[0] > 100 || u[i].score[1] < 0 || u[i].score[1] > 100 || u[i].score[2] < 0 || u[i].score[2] > 100 || u[i].score[3] < 0 || u[i].score[3] > 100 || u[i].score[4] < 0 || u[i].score[4] > 100)
                throw -1;
            if (u[i].birth.year <= 1980 || u[i].birth.year > 2004 || u[i].birth.month < 1 || u[i].birth.month > 12 || u[i].birth.day < 1 || u[i].birth.day > 31)
                throw u[i].birth;
        }
    }
    catch (int)
    {
        cout << "输入成绩非法" << endl;
        return 0;
    }
    catch (BirthDate)
    {
        cout << "输入生日日期非法" << endl;
        return 0;
    }
    catch (string)
    {
        cout << "学号已存在,请重新输入" << endl;
        return 0;
    }
    return 1;
}
void Undergraduate::save(Undergraduate *u)
{
    ofstream outfile("Undergraduate.dat", ios::out | ios::trunc);
    int flag = input(u);
    if (!flag)
        return;
    for (int i = 0; i < stu_num; ++i)
        outfile << u << endl;
    outfile.close();
}
void Undergraduate::add(Undergraduate *u)
{
    ofstream outfile("Undergraduate.dat", ios::out | ios::app);
    int flag = input(u);
    if (!flag)
        return;
    for (int i = 0; i < stu_num; ++i)
        outfile << u << endl;
    outfile.close();
}
void Undergraduate::remove(Undergraduate *u)
{
    cout << "请输入要移除的学生学号" << endl;
    string id;
    cin >> id;
    load(u);
    for (int i = 0; i < stu_num; ++i)
    {
        if (i == stu_num)
            cout << "未找到对应学号的学生，删除失败" << endl;
        if (id == u[i].id)
        {
            for (int j = i + 1; j < stu_num; ++j)
                u[j - 1] = u[j];
            stu_num -= 1;
            ofstream outfile("Undergraduate.dat", ios::out | ios::trunc);
            for (int k = 0; k < stu_num; ++k)
                outfile << u[k] << endl;
            outfile.close();
            cout << "删除成功" << endl;
            break;
        }
    }
}
void Undergraduate::change(Undergraduate *u)
{
    cout << "请输入要修改信息的学生学号" << endl;
    string id;
    cin >> id;
    load(u);
    for (int i = 0; i < stu_num; ++i)
    {
        if (i == stu_num)
            cout << "未找到对应学号的学生，修改失败" << endl;
        if (id == u[i].id)
        {
            cout << "输入学生信息" << endl;
            // cout << "专业 姓名 性别 出生日期:年 月 日 学号 课程1 分数1 课程2 分数2 课程3 分数3 课程4 分数4 课程5 分数5" << endl;
            try
            {

                cin >> u[i];
                if (u[i].score[0] < 0 || u[i].score[0] > 100 || u[i].score[1] < 0 || u[i].score[1] > 100 || u[i].score[2] < 0 || u[i].score[2] > 100 || u[i].score[3] < 0 || u[i].score[3] > 100 || u[i].score[4] < 0 || u[i].score[4] > 100)
                    throw -1;
                if (u[i].birth.year <= 1980 || u[i].birth.year > 2004 || u[i].birth.month < 1 || u[i].birth.month > 12 || u[i].birth.day < 1 || u[i].birth.day > 31)
                    throw u[i].birth;
            }
            catch (int)
            {
                cout << "输入成绩非法" << endl;
            }
            catch (BirthDate)
            {
                cout << "输入生日日期非法" << endl;
            }
            ofstream outfile("Undergraduate.dat", ios::out | ios::trunc);
            for (int k = 0; k < stu_num; ++k)
                outfile << u[k] << endl;
            outfile.close();
            cout << "修改成功" << endl;
            break;
        }
    }
}
void Undergraduate::search(Undergraduate *u)
{
    cout << "请输入要查询的学生学号" << endl;
    string id;
    cin >> id;
    load(u);
    for (int i = 0; i < stu_num; ++i)
    {
        if (i == stu_num)
            cout << "未找到对应学号的学生，修改失败" << endl;
        if (id == u[i].id)
        {
            cout << "该名学生信息如下" << endl;
            cout << u[i] << endl;
        }
    }
}
bool Undergraduate::unique(const Undergraduate *u, const string id)
{
    for (int i = 0; i < stu_num; ++i)
    {
        if (i == stu_num)
            return 1;
        if (id == u[i].id)
            return 0;
    }
}
void Undergraduate::sort_by_grade(Undergraduate *u, bool up_or_down)
{
}
void Undergraduate::fail(Undergraduate *u)
{
    load(u);
    for (int i = 0; i < stu_num; ++i)
    {
        int count = int(u[i].score[0] == 0) + int(u[i].score[1] == 0) + int(u[i].score[2] == 0) + int(u[i].score[3] == 0) + int(u[i].score[4] == 0);
        cout << "学号: " << u[i].id << " 的" << u[i].name << "同学挂了" << count << "门课" << endl;
    }
}

Student::Student() {}
Student::~Student() {}
BirthDate::BirthDate()
{
    year = 2000;
    month = 1;
    day = 1;
}
istream &operator>>(istream &in, BirthDate &b)
{
    in >> b.year >> b.month >> b.day;
    return in;
}
ostream &operator<<(ostream &out, BirthDate &b)
{
    out << b.year << "-" << b.month << "-" << b.day;
    return out;
}

Person::Person()
{
    name = "qwer";
    sex = "male";
}
Person::~Person() {}
void Person::input() {}

int main()
{
    Undergraduate u[N];
    Undergraduate a;
    a.panel(u);
    return 0;
}