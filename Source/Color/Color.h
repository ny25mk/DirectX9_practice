#pragma once

namespace Color{

	constexpr unsigned int Color_White = 0xFFFFFFFF;	//白
	constexpr unsigned int Color_Black = 0xFF000000;	//黒
	constexpr unsigned int Color_Red = 0xFFFF0000;		//赤
	constexpr unsigned int Color_Green = 0xFF00FF00;	//緑
	constexpr unsigned int Color_Blue = 0xFF0000FF;		//青

	using Byte = unsigned char;	//ここで使用したいがために定義
	unsigned int GetColor(Byte r, Byte g, Byte b, Byte a = 255);

}