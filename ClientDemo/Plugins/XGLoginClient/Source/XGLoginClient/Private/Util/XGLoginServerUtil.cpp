// Copyright (c) XiaoGang.2023.All Rights Reserved.
#include "XGLoginServerUtil.h"
#include "cwctype"


bool FXGLoginServerUtil::CheckUserName(FString InStr)
{
	if (InStr.Len() < 6 || InStr.Len() > 18)
	{
		return false;
	}
	if (!CheckLegalStr(InStr))
	{
		return false;
	}

	return true;
}

bool FXGLoginServerUtil::CheckPassword(FString InStr)
{
#if WITH_ENGINE
	if (InStr.Len() < 6 || InStr.Len() > 18)
	{
		return false;
	}
#else
	if (InStr.Len() != 32)
	{
		return false;
	}

#endif


	if (!CheckLegalStr(InStr))
	{
		return false;
	}

	return true;
}



bool FXGLoginServerUtil::CheckPhone(FString InStr)
{
	if (InStr.Len() != 11)
	{
		return false;
	}

	if (!CheckPureNum(InStr))
	{
		return false;
	}


	return true;
}

bool FXGLoginServerUtil::CheckEMail(FString InStr)
{
	if (InStr.IsEmpty() || InStr.Len() == 0)
	{
		return false;
	}
	InStr.ReplaceInline(TEXT("@"), TEXT(""));
	InStr.ReplaceInline(TEXT("."), TEXT(""));
	if (InStr.IsEmpty() || InStr.Len() == 0)
	{
		return false;
	}

	if (!CheckLegalStr(InStr))
	{
		return false;
	}


	return true;
}

bool FXGLoginServerUtil::CheckMachineID(FString InStr)
{
	if (InStr.Len() == 0||InStr.Len()>32)
	{
		return false;
	}
	if (!CheckLegalStr(InStr))
	{
		return false;
	}

	return true;
}
bool FXGLoginServerUtil::CheckActiveCode(FString InStr)
{
	if (InStr.Len() != 32)
	{
		return false;
	}
	if (!CheckLegalStr(InStr))
	{
		return false;
	}

	return true;
}

bool FXGLoginServerUtil::CheckConsumeMoney(float InConsumeMoney)
{
	if (InConsumeMoney>0&& InConsumeMoney< FLT_MAX)
	{
		return true;
	}
	return false;

}

bool FXGLoginServerUtil::CheckChargeMoney(float InChargeMoney)
{
	if (InChargeMoney > 0 && InChargeMoney < FLT_MAX)
	{
		return true;
	}
	return false;
}

bool FXGLoginServerUtil::CheckLegalStr(FString InStr)
{

	if (InStr.Len() == 0)
	{
		return false;
	}

	for (int32 Index = 0; Index < InStr.Len(); Index++)
	{

		/*
			1.isalpha()，用来判断一个字符是否为字母，如果是字符则返回非零，否则返回零。

			2.isalnum()，用来判断一个字符是否为数字或者字母，也就是说判断一个字符是否属于a~z||A~Z||0~9。是返回非零，不是返回0。

			3.islower()，用来判断一个字符是否为小写字母，也就是是否属于a~z。是返回非零，不是返回0。

			4.isupper()，用来判断一个字符是否为大写字母。是返回非零，不是返回0。

			5. char c = toupper(a)，a为字符时，如果a是小写字母则将其转换为大写字母，否则不变。a为数字则将其按ASCLL码转换为对应字符。（其实即使a是字符，输入之后还是会将其转换为int类型）

			6.char c=tolower(a)，a为字符时，如果a是大写字母则将其转换为小写字母，否则不变。a为数字则将其按ASCLL码转换为对应字符。

			7.isdigit()，用来判断一个字符是否为数字，如果是数字则返回非零，否则返回零。

			8.to_string()，将数字转换为字符串，这里注意如果是浮点型数转字符，会将精度范围内小数点后的数全部显示出来,比如：
		*/
		/*
			FString TextString = "12345ABCDEFGHIJKLMN";

			FRegexPattern TestPattern(TEXT("[0-9, a-z]"));

			FRegexMatcher TestMatcher(TestPattern, TextString);

			if (TestMatcher.FindNext())
			{
				UE_LOG(LogTemp, Warning, TEXT("找到匹配内容了%d - %d"),TestMatcher.GetMatchBeginning(),TestMatcher.GetMatchEnding());

			}
			else
			{

			}

		*/
		bool bChar = (bool)std::iswalpha(InStr[Index]);

		bool bNum = (bool)std::iswdigit(InStr[Index]);

		if (bChar || bNum)
		{
			continue;

		}
		return false;
	}
	return true;
}

bool FXGLoginServerUtil::CheckPureNum(FString InStr)
{
	if (InStr.Len() == 0)
	{
		return false;
	}
	for (int32 Index = 0; Index < InStr.Len(); Index++)
	{
		bool bNum = (bool)std::iswdigit(InStr[Index]);
		if (bNum)
		{
			continue;
		}
		return false;
	}
	return true;
}

FString FXGLoginServerUtil::XGLoginServerResultToString(EXGLoginServerResult InServerResult)
{
	FString ResponseMessage = StaticEnum<EXGLoginServerResult>()->GetNameStringByValue((int32)InServerResult);

	return ResponseMessage;
}
