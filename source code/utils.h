#pragma once
#include <vector>
#include <graphics.h>
#include <random>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <string>
#include "class_shape.h"

#pragma comment(lib, "MSIMG32.LIB")
using namespace std;

extern bool developer_mode;

extern std::vector<COLORREF> color_list;

// 随机生成形状
Shape* init_random_shape(bool is_current);

void init_color_list();

// 渲染png
void putimage_alpha(int dst_x, int dst_y, IMAGE* img);

int get_highest_score();
void set_highest_score(int val);


std::wstring string_to_wstring(const std::string& str);