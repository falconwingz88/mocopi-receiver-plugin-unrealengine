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

#include "MocopiLiveLinkSourceSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MocopiLiveLinkSourceSettings)

UMocopiLiveLinkSourceSettings::UMocopiLiveLinkSourceSettings()
{
	// Keep enough history for Live Link's animation interpolation to bridge
	// ordinary Wi-Fi jitter while accepting a small, predictable delay.
	Mode = ELiveLinkSourceMode::EngineTime;
	BufferSettings.EngineTimeOffset = 0.12f;
	BufferSettings.MaxNumberOfFrameToBuffered = 120;
	BufferSettings.bValidEngineTimeEnabled = true;
	BufferSettings.ValidEngineTime = 2.0f;
	BufferSettings.bKeepAtLeastOneFrame = true;
}
