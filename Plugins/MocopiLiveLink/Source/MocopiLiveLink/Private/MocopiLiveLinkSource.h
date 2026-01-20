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

#include <ILiveLinkSource.h>
#include "Roles/LiveLinkAnimationTypes.h"
#include "HAL/Runnable.h"
#include "MocopiDataHandler.h"
#include "Modules/ModuleManager.h"
#include "Sockets.h"

#include <chrono>

class FMocopiLiveLinkSource : public ILiveLinkSource, public FRunnable
{
public:

  FMocopiLiveLinkSource(uint16 inputPort, FName subjectName);
  virtual ~FMocopiLiveLinkSource();

  // ILiveLinkSource Interface 
  virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;
  virtual bool IsSourceStillValid() const;
  virtual bool RequestSourceShutdown();

  virtual FText GetSourceType() const;
  virtual FText GetSourceMachineName() const;
  virtual FText GetSourceStatus() const;

  // FRunnable Interface
  virtual bool Init() override { return true; }
  virtual uint32 Run() override;
  virtual void Stop() override;
  virtual void Exit() override { }


private:

  MocopiDataHandler mDataHandler;

  // Udp Thread variables
  FString mUdpThreadName;
  FRunnableThread* mUdpThread;
  std::atomic_bool mIsStopping;
  std::atomic_bool mIsThreadFinished;

  // Udp Socket & buffer
  FSocket* mSocket;
  TArray<uint8> mRecvBuffer;
  ISocketSubsystem* mSocketSubSystem;
  uint16 mInputPort;

  // LiveLink Client & its ID
  ILiveLinkClient* mClient;
  FGuid mSourceGuid;

  // Helpers 
  void UpdateFrameData(FLiveLinkAnimationFrameData& outFrame);

  void HandleReceivedData(TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> receivedData);

  void OpenConnection();

  void StartUdpThread();

  bool ShutdownThreadAndSocket();

  void SetUpNewMocopiSubject();

  FName GetNewSubjectName();

  void DefineNewMocopiSubject();

  FQualifiedFrameTime GetQualifiedFrameTime(MocopiFrameMetaData& frameMetaData);

  FName mSubjectName; // This instance's LiveLink subject

  std::chrono::steady_clock::time_point mPreviousFrameArrivalTime;
  const double TIMEOUT_MS = 400;

  double mPreviousFrameTimestamp_ms; // Helps determine mocopi FPS. Temporary Fix. Will Receive FPS from the App in the future.
  int mCurrentMocopiFPS;

  bool mNeedsToProcessSkelDef;

};

