[toc]

# 系统需求分析

## 项目简介

本课程设计选题为**学生成绩管理系统**，项目名称为`GPAWizard`，在 C++14 标准下编写，使用了部分现代 c++ 特性(如 lambda 表达式、 auto 类型推导等)。

在编译方面，本项目拥有四个`*.hpp`文件、五个`*.cpp`文件，故编写了`CMakeLists.txt`以使用`cmake`进行编译，在 Linux 以及 Windows 10 平台下编译通过，且无特殊说明时，后续文档均为 Linux 下的运行情况， Windows 与之类似。

本项目主要分为四个文件夹，结构如下：

- `include`：放置头文件
- `src`：放置源文件
- `shared`：放置初始学生和课程信息、保存导出的各种文件
- `test`：放置测试文件

```bash
$ tree THU-GPAWizard
THU-GPAWizard
├── CMakeLists.txt
├── compile.sh
├── include
│   ├── Course.hpp
│   ├── GradeManager.hpp
│   ├── IOUtils.hpp
│   └── Student.hpp
├── LICENSE
├── README.md
├── run.sh
├── shared
│   ├── courses.txt
│   └── students.txt
├── src
│   ├── Course.cpp
│   ├── GradeManager.cpp
│   ├── IOUtils.cpp
│   ├── main.cpp
│   └── Student.cpp
├── test
│   ├── 1.ans
│   ├── 1.in
│   ├── 2.ans
│   └── 2.in
└── test.sh

4 directories, 21 files
```

## 需求分析

本项目模拟了清华大学一个学期的教学流程，分为选课阶段、教师赋分、成绩复议、展示最终成绩、保存相关信息等环节。

按照流程，本程序可分为如下过程：

- 学生首先选择自己想要上的课程，也可以不选课(那么成绩单就为空)。
- 经过一学期的学习后经教师给出百分制成绩，待所有教师为选课同学赋分完毕后，成绩会提交至教务系统，由教务系统进行整合再推送给学生，学生最终看到的是等级制成绩。

- 如果学生对自己的成绩有所疑惑，可以提交课程复议让教师重新打分，最后得到最终的成绩单。

- 在程序的最后，可以保存所有学生信息、保存某一门课程的学生信息、保存某个学生选择课程的信息等，可以按照姓名、学号(课程号)、成绩进行排序，默认为不排序。

本课程管理系统将学生、教师(课程)、教务系统分开来写，分别在`Students.hpp/Students.cpp`、`Course.hpp/Course.cpp`以及`GradeManager.hpp/GradeManager.cpp`中进行完成。教师与学生彼此独立，通过友元类`GradeManager`进行通讯，一定程度上保证了程序的合理性。

初始的课程信息存储在`courses.txt`，第一行为课程数目`N`，后续`N`行为每种课程的信息，从前到后为课程名、课程号、学分，用空格分开。初始的学生信息存储在`students.txt`，第一行从前到后为本科生数目N和研究生数目M，第2行到第N+1行为本科生信息，从前到后为姓名、学号、性别(1为男性，2为女性~~，暂不支持Transgender~~)、出生年、月、日、入学年份；第N+2到第N+M+1行为研究生信息，从前到后为姓名、学号、性别、出生年、月、日、导师姓名，均以空格隔开。

# 总体设计

# 详细设计

# 系统调试

# 结果分析

# 总结

# 附录1：源程序清单
