////
// Copyright (C) 2026 Sony Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
////
/// 
using UnrealBuildTool;
using System.Collections.Generic;

public class MocopiTarget : TargetRules
{
	public MocopiTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		ExtraModuleNames.AddRange(new string[] { "mocopi" });

		// Need to set this compile argument in order to compile in Mac
		// Issue is caused by using C++20 and clang compiler along with UnrealBuildTool
		if (Platform == UnrealTargetPlatform.Mac)
		{
			bOverrideBuildEnvironment = true;
			AdditionalCompilerArguments = "-Wno-deprecated-anon-enum-enum-conversion -Wno-error=macro-redefined";
		}
	}
}
