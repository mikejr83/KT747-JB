#!/bin/sh
export KERNELDIR=`readlink -f .`
export PARENT_DIR=`readlink -f ..`
export INITRAMFS_DEST=$KERNELDIR/kernel/usr/initramfs
export INITRAMFS_SOURCE=`readlink -f ..`/initramfs
export CONFIG_SAMMY_BUILD=y
#Enable FIPS mode
export USE_SEC_FIPS_MODE=true
export ARCH=arm
# export CROSS_COMPILE=$PARENT_DIR/linaro4.5/bin/arm-eabi-
# export CROSS_COMPILE=/home/ktoonsez/kernel/siyah/arm-2011.03/bin/arm-none-eabi-
# export CROSS_COMPILE=/home/ktoonsez/android/system/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-
# export CROSS_COMPILE=/home/ktoonsez/androidjb/system/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-
export CROSS_COMPILE=$PARENT_DIR/linaro4.7/bin/arm-eabi-

echo "Remove old Package Files"
rm -rf ./Package/*

echo "Setup Package Directory"
mkdir -p Package/system/lib/modules
mkdir -p Package/system/etc/init.d

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
make cyanogen_d2_defconfig
make -j`grep 'processor' /proc/cpuinfo | wc -l`

echo "Copy modules to Package"
cp ../lib/modules/* ./Package/system/lib/modules/
cp -a $(find . -name *.ko -print |grep -v initramfs) Package/system/lib/modules/
cp 00post-init ./Package/system/etc/init.d/00post-init

echo "Copy zImage to Package"
cp arch/arm/boot/zImage Package/zImage

echo "Make CPIO initramfs"
# cd $INITRAMFS_DEST
# find . | cpio -o -H newc | gzip > ../../../Package/ramdisk.cpio.gz
# cd $KERNELDIR

# gzip -9 ramdisk.cpio
# Make boot.img
# --board qcom --base 0x10000000 --pagesize 2048 --ramdiskaddr 0x11000000 
# ./mkbootimg --kernel zImage --ramdisk ramdisk.cpio.gz --output $KERNELDIR/boot.img
# MSM8960
echo "Make boot.img"
./mkbootfs $INITRAMFS_DEST | gzip > ./Package/ramdisk.gz
./mkbootimg --cmdline 'console = null androidboot.hardware=qcom user_debug = 31' --kernel Package/zImage --ramdisk Package/ramdisk.gz --base 0x80200000 --pagesize 2048 --ramdiskaddr 0x81500000 --output Package/boot.img 

