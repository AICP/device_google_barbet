/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "Hardware.h"
#include "Vibrator.h"

#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <log/log.h>

using aidl::android::hardware::vibrator::HwApi;
using aidl::android::hardware::vibrator::HwCal;
using aidl::android::hardware::vibrator::Vibrator;

int main() {
    auto hwapi = HwApi::Create();

    if (!hwapi) {
        return EXIT_FAILURE;
    }

#if (VIBRATOR_FACTORY_MODE)
    // In facotry mode, we skip motionAwareness feature.
    // So we don't need extra thread for listening Gsensor
    ABinderProcess_setThreadPoolMaxThreadCount(0);
#else
    // One thread for vibrator APIs and one for sensor callback
    // WARN: there could be an issue if two vibrator APIs are called simultaneously
    ABinderProcess_setThreadPoolMaxThreadCount(1);
#endif
    std::shared_ptr<Vibrator> vib =
        ndk::SharedRefBase::make<Vibrator>(std::move(hwapi), std::make_unique<HwCal>());

    const std::string instance = std::string() + Vibrator::descriptor + "/default";
    binder_status_t status = AServiceManager_addService(vib->asBinder().get(), instance.c_str());
    LOG_ALWAYS_FATAL_IF(status != STATUS_OK);

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
