#pragma once
#include <string>

#define BLACK "\x1B[30m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define BRIGHT_BLACK "\x1B[90m"
#define BRIGHT_RED "\x1B[91m"
#define BRIGHT_GREEN "\x1B[92m"
#define BRIGHT_YELLOW "\x1B[93m"
#define BRIGHT_BLUE "\x1B[94m"
#define BRIGHT_MAGENTA "\x1B[95m"
#define BRIGHT_CYAN "\x1B[96m"
#define BRIGHT_WHITE "\x1B[97m"
#define BG_BLACK "\x1B[40m"
#define BG_RED "\x1B[41m"
#define BG_GREEN "\x1B[42m"
#define BG_YELLOW "\x1B[43m"
#define BG_BLUE "\x1B[44m"
#define BG_MAGENTA "\x1B[45m"
#define BG_CYAN "\x1B[46m"
#define BG_WHITE "\x1B[47m"
#define BG_BRIGHT_BLACK "\x1B[100m"
#define BG_BRIGHT_RED "\x1B[101m"
#define BG_BRIGHT_GREEN "\x1B[102m"
#define BG_BRIGHT_YELLOW "\x1B[103m"
#define BG_BRIGHT_BLUE "\x1B[104m"
#define BG_BRIGHT_MAGENTA "\x1B[105m"
#define BG_BRIGHT_CYAN "\x1B[106m"
#define BG_BRIGHT_WHITE "\x1B[107m"

class Util
{
public:
	static void Clear();

	static void Continue(const bool _withClear = true);

	static void PrintTitle(const std::string& _toPrint, const std::string& _color = "", const bool _withLineBreak = true);

	static void PrintEmbed(const std::string& _toPrint, const std::string& _color = "", const bool _withLineBreak = true);

	static void LineBreak();

	static void Separation();

	static void Debug(const std::string& _toPrint, const bool _withLineBreak = true);

	static void Error(const std::string& _toPrint, const bool _withLineBreak = true);

	static bool Contains(const std::string& _string, const std::string& _contains, const bool _respectCase = false);

	static std::string ToLower(const std::string& _string);

	/// <summary>
	/// returns an integer number selected element from the specified range
	/// min and max inclusive
	/// </summary>
	/// <returns></returns>
	static int Randint(const int _min, const int _max);
};

