// Copyright (c) XiaoGang.2023.All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class XGLoginClient : ModuleRules
{
    public XGLoginClient(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {

        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicDependencyModuleNames.Add("Launch");
            PublicDependencyModuleNames.Add("ApplicationCore");
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "XGLoginClient_APL.xml"));
        }


        PublicIncludePaths.AddRange(
            new string[] {
             "$(ModuleDir)/Public/AsyncAction",
             "$(ModuleDir)/Public/AsyncAction/ActiveCode",
             "$(ModuleDir)/Public/Type",
             "$(ModuleDir)/Public/Type/Common",
             "$(ModuleDir)/Public/Type/Common/ActiveCode",
             "$(ModuleDir)/Public/Type/Common/CheckVersion",
             "$(ModuleDir)/Public/Type/Common/Login",
             "$(ModuleDir)/Public/Type/Common/LoginM",
             "$(ModuleDir)/Public/Type/Common/Money",
            }
            );
    

        PrivateIncludePaths.AddRange(
            new string[] {
               "XGLoginClient/Public/AsyncAction",
               "XGLoginClient/Public/AsyncAction/ActiveCode",
               "XGLoginClient/Public/Config",
               "XGLoginClient/Public/Log",
               "XGLoginClient/Public/Subsystem",
               "XGLoginClient/Public/Type",
               "XGLoginClient/Public/Type/Common",
               "XGLoginClient/Public/Type/Common/ActiveCode",
               "XGLoginClient/Public/Type/Common/CheckVersion",
               "XGLoginClient/Public/Type/Common/Login",
               "XGLoginClient/Public/Type/Common/LoginM",
               "XGLoginClient/Public/Type/Common/Money",
               "XGLoginClient/Public/Util",
            }
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "HTTP",
                "DeveloperSettings"

            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "JsonUtilities",
                "Json",
                "Projects"
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {

			}
            );
    }
}
