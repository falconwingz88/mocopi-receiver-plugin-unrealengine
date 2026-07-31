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

#pragma once

#include "CoreMinimal.h"
#include "LiveLinkSourceSettings.h"

#include "MocopiLiveLinkSourceSettings.generated.h"

/** Reliability and smoothing controls for a mocopi Live Link source. */
UCLASS()
class MOCOPILIVELINK_API UMocopiLiveLinkSourceSettings : public ULiveLinkSourceSettings
{
	GENERATED_BODY()

public:
	UMocopiLiveLinkSourceSettings();

	/** Operating-system UDP receive buffer. Larger values tolerate short CPU and network bursts. */
	UPROPERTY(EditAnywhere, Category = "Mocopi Reliability", meta = (ClampMin = "64", ClampMax = "4096", UIMin = "64", UIMax = "2048", ForceUnits = "KB"))
	int32 UdpReceiveBufferSizeKB = 512;

	/** Time without packets before the source requests a fresh skeleton definition. */
	UPROPERTY(EditAnywhere, Category = "Mocopi Reliability", meta = (ClampMin = "0.4", ClampMax = "10.0", UIMin = "0.4", UIMax = "5.0", ForceUnits = "s"))
	float ConnectionTimeoutSeconds = 2.0f;

	/** Ignore duplicate and late out-of-order packets that can make a pose jump backwards. */
	UPROPERTY(EditAnywhere, Category = "Mocopi Reliability")
	bool bRejectDuplicateAndOutOfOrderFrames = true;

	/** Use the timestamp embedded in each mocopi packet so Live Link can interpolate across missing packets. */
	UPROPERTY(EditAnywhere, Category = "Mocopi Reliability")
	bool bUsePacketTimestampRecovery = true;

	/** Apply a lightweight low-pass filter before frames enter Live Link's delayed interpolation buffer. */
	UPROPERTY(EditAnywhere, Category = "Mocopi Smoothing")
	bool bEnablePoseSmoothing = true;

	/** Higher values reduce rotational jitter but respond more slowly. Zero disables rotation filtering. */
	UPROPERTY(EditAnywhere, Category = "Mocopi Smoothing", meta = (EditCondition = "bEnablePoseSmoothing", ClampMin = "0.0", ClampMax = "0.95", UIMin = "0.0", UIMax = "0.8"))
	float RotationSmoothingStrength = 0.20f;

	/** Higher values reduce root-position jitter but respond more slowly. Zero disables translation filtering. */
	UPROPERTY(EditAnywhere, Category = "Mocopi Smoothing", meta = (EditCondition = "bEnablePoseSmoothing", ClampMin = "0.0", ClampMax = "0.95", UIMin = "0.0", UIMax = "0.8"))
	float TranslationSmoothingStrength = 0.15f;

	/** Frames accepted from mocopi since this source was created. */
	UPROPERTY(VisibleAnywhere, Transient, Category = "Mocopi Diagnostics")
	uint64 ReceivedFrames = 0;

	/** Missing frame IDs observed in the mocopi stream. Live Link interpolation bridges short gaps within the configured delay. */
	UPROPERTY(VisibleAnywhere, Transient, Category = "Mocopi Diagnostics")
	uint64 EstimatedLostFrames = 0;

	/** Duplicate or late packets rejected to prevent backwards pose jumps. */
	UPROPERTY(VisibleAnywhere, Transient, Category = "Mocopi Diagnostics")
	uint64 RejectedFrames = 0;
};
