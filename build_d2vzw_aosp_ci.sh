#!/bin/sh
export KERNELDIR=`readlink -f .`
export PARENT_DIR=`readlink -f ..`
export INITRAMFS_DEST=$KERNELDIR/kernel/usr/initramfs
export INITRAMFS_SOURCE=`readlink -f ..`/KT747-JB-RAMDISKS/AOSP_JB_4.4
export CONFIG_AOSP_BUILD=y
export PACKAGEDIR=$PARENT_DIR/Packages/AOSP_JB_MR1_VZW
#Enable FIPS mode
export USE_SEC_FIPS_MODE=true
export ARCH=arm
# export CROSS_COMPILE=$PARENT_DIR/linaro4.5/bin/arm-eabi-
# export CROSS_COMPILE=/home/ktoonsez/kernel/siyah/arm-2011.03/bin/arm-none-eabi-
# export CROSS_COMPILE=/home/ktoonsez/android/system/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-
# export CROSS_COMPILE=/home/ktoonsez/androidjb/system/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-
export CROSS_COMPILE=$PARENT_DIR/linaro4.7/bin/arm-eabi-

echo "Remove old Package Files"
rm -rf $PACKAGEDIR/*
echo "Remove META-INF"
rm -R $PARENT_DIR/Packages/META-INF

echo "Setup Package Directory"
mkdir -p $PACKAGEDIR/system/app
mkdir -p $PACKAGEDIR/system/lib/modules
mkdir -p $PACKAGEDIR/system/etc/init.d

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

echo "Remove old zImage"
rm $PACKAGEDIR/zImage
rm arch/arm/boot/zImage

echo "Make the kernel"
# make KT747_d2vzw_defconfig
make VARIANT_DEFCONFIG=cyanogen_d2vzw_defconfig SELINUX_DEFCONFIG=m2selinux_defconfig KT747_d2_defconfig

HOST_CHECK=`uname -n`
if [ $HOST_CHECK = 'ktoonsez-VirtualBox' ] || [ $HOST_CHECK = 'task650-Underwear' ]; then
	echo "Ktoonsez/task650 24!"
	make -j24
else
	echo "Others! - " + $HOST_CHECK
	make -j`grep 'processor' /proc/cpuinfo | wc -l`
fi;

echo "Copy modules to Package"
cp -a $(find . -name *.ko -print |grep -v initramfs) $PACKAGEDIR/system/lib/modules/
cp 00post-init.sh $PACKAGEDIR/system/etc/init.d/00post-init.sh
cp enable-oc.sh $PACKAGEDIR/system/etc/init.d/enable-oc.sh

#Copy the META-INF folder if it's in the kernel directory, ie it's in source control
if [ -e $KERNELDIR/META-INF/com/google/android/update-binary ]; then
	echo "Removing META-INF folder"
	rm $PACKAGEDIR/META-INF
	echo "Copying META-INF folder"
	cp -r $KERNELDIR/META-INF $PACKAGEDIR/META-INFO/
#check the parent folder of the package directory for the META-INF folder
elif [-e $PACKAGEDIR/../META-INF/com/google/android/update-binary ]; then
	echo "Copying META-INF folder"
	cp -r $PACKAGEDIR/../META-INF $PACKAGEDIR/META-INF 
else
	echo "META-INF" folder not found
fi;

#Copy the KTweaker app if it's in source control
if [ -e $KERNELDIR/system/app/com.ktoonsez.KTweaker.apk ]; then
	echo "Copying KTweaker"
	cp $KERNELDIR/system/app/com.ktoonsez.KTweaker.apk $PACKAGEDIR/system/app/com.ktoonsez.KTweaker.apk
#if running on KToonsez's machine copy it from the workspace
elif [ -e /home/ktoonsez/workspace/com.ktoonsez.KTweaker.apk ]; then
	cp /home/ktoonsez/workspace/com.ktoonsez.KTweaker.apk $PACKAGEDIR/system/app/com.ktoonsez.KTweaker.apk
else
	echo "KTweaker was not found"
fi;

# cp ../Ramdisks/libsqlite.so $PACKAGEDIR/system/lib/libsqlite.so

if [ -e $KERNELDIR/arch/arm/boot/zImage ]; then
	echo "Copy zImage to Package"
	cp arch/arm/boot/zImage $PACKAGEDIR/zImage

	echo "Make boot.img"
	./mkbootfs $INITRAMFS_DEST | gzip > $PACKAGEDIR/ramdisk.gz
	./mkbootimg --cmdline 'console = null androidboot.hardware=qcom user_debug=31 zcache' --kernel $PACKAGEDIR/zImage --ramdisk $PACKAGEDIR/ramdisk.gz --base 0x80200000 --pagesize 2048 --ramdiskaddr 0x81500000 --output $PACKAGEDIR/boot.img 
	export curdate=`date "+%m-%d-%Y"`
	cd $PACKAGEDIR
	find . -type f -name '*~' -exec rm -f '{}' \;
	rm ramdisk.gz
	rm zImage
	rm ../KT747-AOSP-JB-MR2-3.4-VZW*.zip
	zip -r ../KT747-AOSP-JB-MR2-3.4-VZW-$curdate.zip .
	cd $KERNELDIR
	exit 0
else
	echo "KERNEL DID NOT BUILD! no zImage exist"
	exit 1
fi;
