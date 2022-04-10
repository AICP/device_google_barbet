#
# Copyright (C) 2021 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit some common AICP stuff.
$(call inherit-product, vendor/aicp/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/google/barbet/aosp_barbet.mk)

include device/google/barbet/device-lineage.mk

# Device identifier. This must come after all inclusions
PRODUCT_BRAND := google
PRODUCT_MODEL := Pixel 5a
PRODUCT_NAME := aicp_barbet

# Boot animation
TARGET_SCREEN_HEIGHT := 2340
TARGET_SCREEN_WIDTH := 1080

PRODUCT_BUILD_PROP_OVERRIDES += \
    DEVICE_MAINTAINERS="Ron H. (Siluxsept)" \
    TARGET_PRODUCT=barbet \
    PRIVATE_BUILD_DESC="barbet-user 12   release-keys"

BUILD_FINGERPRINT := google/barbet/barbet:12/SP2A.220305.012/8177914:user/release-keys

PRODUCT_OVERRIDE_INFO := true
PRODUCT_OVERRIDE_FINGERPRINT := google/walleye/walleye:8.1.0/OPM1.171019.011/4448085:user/release-keys

$(call inherit-product, vendor/google/barbet/barbet-vendor.mk)
