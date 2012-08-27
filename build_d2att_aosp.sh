#!/bin/sh
export KERNELDIR=`readlink -f .`
export PARENT_DIR=`readlink -f ..`
export INITRAMFS_DEST=$KERNELDIR/kernel/usr/initramfs
export INITRAMFS_SOURCE=`readlink -f ..`/initramfs_aokp_jb
export CONFIG_AOSP_BUILD=y
#Enable FIPS mode
export USE_SEC_FIPS_MODE=true
export ARCH=arm
# export CROSS_COMPILE=$PARENT_DIR/linaro4.5/bin/arm-eabi-
# export CROSS_COMPILE=/home/ktoonsez/kernel/siyah/arm-2011.03/bin/arm-none-eabi-
# export CROSS_COMPILE=/home/ktoonsez/android/system/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-
# export CROSS_COMPILE=/home/ktoonsez/androidjb/system/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-
export CROSS_COMPILE=$PARENT_DIR/linaro4.7/bin/arm-eabi-

echo "Remove old PackageATT Files"
rm -rf ./PackageATT/*

echo "Setup PackageATT Directory"
mkdir -p PackageATT/system/app
mkdir -p PackageATT/system/lib/modules
mkdir -p PackageATT/system/etc/init.d

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
make KT747_d2att_defconfig
make -j`grep 'processor' /proc/cpuinfo | wc -l`

echo "Copy modules to PackageATT"
cp -a $(find . -name *.ko -print |grep -v initramfs) PackageATT/system/lib/modules/
cp 00post-init.sh ./PackageATT/system/etc/init.d/00post-init.sh
cp enable-oc.sh ./PackageATT/system/etc/init.d/enable-oc.sh
cp /home/ktoonsez/workspace/com.ktoonsez.KTweaker.apk ./PackageATT/system/app/com.ktoonsez.KTweaker.apk

echo "Copy zImage to PackageATT"
cp arch/arm/boot/zImage PackageATT/zImage

echo "Make boot.img"
./mkbootfs $INITRAMFS_DEST | gzip > ./PackageATT/ramdisk.gz
./mkbootimg --cmdline 'console = null androidboot.hardware=qcom user_debug = 31' --kernel PackageATT/zImage --ramdisk PackageATT/ramdisk.gz --base 0x80200000 --pagesize 2048 --ramdiskaddr 0x81500000 --output PackageATT/boot.img 

