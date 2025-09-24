#include "utils.h"

Shape* init_random_shape(bool is_current)
{
	Shape* result = nullptr;
	int random_factor = rand() % 7;
	if (developer_mode)
	{
		random_factor = 0;
	}
	switch (random_factor)
	{
	case 0:
		result = new ShapeLine(is_current);
		break;
	case 1:
		result = new ShapeL(is_current);
		break;
	case 2:
		result = new ShapeLB(is_current);
		break;
	case 3:
		result = new ShapeZ(is_current);
		break;
	case 4:
		result = new ShapeZB(is_current);
		break;
	case 5:
		result = new ShapeT(is_current);
		break;
	case 6:
		result = new ShapeBlock(is_current);
		break;
	default:
		result = new ShapeBlock(is_current);
		break;
	}
	random_factor = rand() % color_list.size();
	result->set_blocks_color(color_list[random_factor]);
	return result;
}

void init_color_list()
{
	//绯色
	color_list.push_back(RGB(204, 84, 58));
	//萱草
	color_list.push_back(RGB(259, 159, 77));
	//菜花
	color_list.push_back(RGB(247, 217, 76));
	//苗
	color_list.push_back(RGB(134, 193, 102));
	//白群
	color_list.push_back(RGB(120, 194, 196));
	//楝
	color_list.push_back(RGB(155, 144, 194));
}

void putimage_alpha(int dst_x, int dst_y, IMAGE* img)

{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h, GetImageHDC(img), 0, 0,
		w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

int get_highest_score()
{
	ifstream highest_score_file("data/highest_score.data");
	int highest_score = 0;
	highest_score_file >> highest_score;
	return highest_score;
}

void set_highest_score(int val)
{
	ofstream highest_score_file("data/highest_score.data");
	highest_score_file << val;
}

std::wstring string_to_wstring(const std::string& str) 
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	std::wstring wstr(len, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], len);
	return wstr;
}
