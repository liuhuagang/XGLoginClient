// Copyright (c) XiaoGang.2023.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "XGLoginServerHttpType.h"

struct  FXGLoginServerUtil
{

public:
	/**
	 * 用户名规则6到18 只允许数字和字母
	 * 密码6到18 只允许数字和字母
	 * 手机号11位的数字
	 * 邮箱只允许数字，字母，@，“.”
	 */

	static bool CheckUserName(FString InStr);
	static bool CheckPassword(FString InStr);
	static bool CheckPhone(FString InStr);
	static bool CheckEMail(FString InStr);
	static bool CheckMachineID(FString InStr);

	static bool CheckActiveCode(FString InStr);

	static bool CheckConsumeMoney(float InConsumeMoney);
	static bool CheckChargeMoney(float InChargeMoney);

	static bool CheckLegalStr(FString InStr);
	static bool CheckPureNum(FString InStr);


	static FString XGLoginServerResultToString(EXGLoginServerResult InServerResult);



};


