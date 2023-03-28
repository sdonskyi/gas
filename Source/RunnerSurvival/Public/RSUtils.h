#pragma once

class RSUtils
{

public:
	static FText FormatTime(int32 Time)
	{
		const int32 Minuts = Time / static_cast<int32>(60);
		const int32 Seconds = Time % static_cast<int32>(60);
		const FString PrefixZero = "0";
		const FString PrefixDoubleZero = "00";
		const char Separator = ':';

		FString ResultStr;
		if (Minuts == 0)
		{
			ResultStr = PrefixDoubleZero;
		}
		else if (Minuts < 10)
		{
			ResultStr = PrefixZero;
		}

		if (Minuts != 0)
		{
			ResultStr = ResultStr.Append(FString::FromInt(Minuts));
		}
		ResultStr = ResultStr.AppendChar(Separator);

		if (Seconds == 0)
		{
			ResultStr.Append(PrefixDoubleZero);
		}
		else if (Seconds < 10)
		{
			ResultStr.Append(PrefixZero);
		}

		if (Seconds != 0)
		{
			ResultStr = ResultStr.Append(FString::FromInt(Seconds));
		}
		return FText::FromString(ResultStr);
	}

	static bool CheckSimple(int64 Number)
	{
		for (int64 i = 2; i <= Number / 2; ++i) 
		{
			if (Number % i == 0) 
			{
				return false;
			}
		}
		return true;
	}
};