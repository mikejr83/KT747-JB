#!/bin/sh
export KERNELDIR=`readlink -f .`
export PARENT_DIR=`readlink -f ..`
export INITRAMFS_DEST=$KERNELDIR/kernel/usr/initramfs
export INITRAMFS_SOURCE=`readlink -f ..`/initramfs_aokp_spr_jb
export CONFIG_AOSP_BUILD=y
#Enable FIPS mode
export USE_SEC_FIPS_MODE=true
export ARCH=arm
# export CROSS_COMPILE=$PARENT_DIR/linaro4.5/bin/arm-eabi-
# export CROSS_COMPILE=/home/ktoonsez/kernel/siyah/arm-2011.03/bin/arm-none-eabi-
# export CROSS_COMPILE=/home/ktoonsez/android/system/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-
# export CROSS_COMPILE=/home/ktoonsez/androidjb/system/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-
export CROSS_COMPILE=$PARENT_DIR/linaro4.7/bin/arm-eabi-

echo "Remove old PackageSPR Files"
rm -rf ./PackageSPR/*

echo "Setup PackageSPR Directory"
mkdir -p PackageSPR/system/app
mkdir -p PackageSPR/system/lib/modules
mkdir -p PackageSPR/system/etc/init.d

echo "Create initramfs dir"
mkdir -p $INITRAMFS_DEST

echo "Remove old initramfs dir"
rm -rf $INITRAMFS_DEST/*

echo "Copy new initramfs dir"
cp -R $INITRAMFS_SOURCE/* $INITRAMFS_DEST

echo "chmod initramfs dir"
chmod -R g-w $INITRAMFS_DEST/*
rm $(find $INITRAMFS_DEST -name EMPTY_DIRECTORY -print)
rm -rf $(find $INITRAMFS_DEST -name .git -print)

echo "Make the kernel"
make KT747_d2spr_defconfig
make -j`grep 'processor' /proc/cpuinfo | wc -l`

echo "Copy modules to PackageSPR"
cp -a $(find . -name *.ko -print |grep -v initramfs) PackageSPR/system/lib/modules/
cp 00post-init.sh ./PackageSPR/system/etc/init.d/00post-init.sh
cp enable-oc.sh ./PackageSPR/system/etc/init.d/enable-oc.sh
cp /home/ktoonsez/workspace/com.ktoonsez.KTweaker.apk ./PackageSPR/system/app/com.ktoonsez.KTweaker.apk

echo "Copy zImage to PackageSPR"
cp arch/arm/boot/zImage PackageSPR/zImage

echo "Make boot.img"
./mkbootfs $INITRAMFS_DEST | gzip > ./PackageSPR/ramdisk.gz
./mkbootimg --cmdline 'console = null androidboot.hardware=qcom user_debug = 31' --kernel PackageSPR/zImage --ramdisk PackageSPR/ramdisk.gz --base 0x80200000 --pagesize 2048 --ramdiskaddr 0x81500000 --output PackageSPR/boot.img 

