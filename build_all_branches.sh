echo "Switch to JellyBean"
git checkout jellybean

echo "Make Clean"
make clean
echo "Make Mrproper"
make mrproper
./build_d2att_aosp.sh
echo "Make Clean"
make clean
echo "Make Mrproper"
make mrproper
./build_d2spr_aosp.sh
echo "Make Clean"
make clean
echo "Make Mrproper"
make mrproper
./build_d2vzw_aosp.sh
echo "Make Clean"
make clean
echo "Make Mrproper"
make mrproper
./build_d2usc_aosp.sh

echo "Switch to ICS"
git checkout ics

echo "Make Clean"
make clean
echo "Make Mrproper"
make mrproper
./build_d2att_aosp.sh
echo "Make Clean"
make clean
echo "Make Mrproper"
make mrproper
./build_d2att_sammy.sh

echo "Switch to Sammy Jellybean"
git checkout sammy_jb

echo "Make Clean"
make clean
echo "Make Mrproper"
make mrproper
./build_d2att_sammy.sh
echo "Make Clean"
make clean
echo "Make Mrproper"
make mrproper
./build_d2spr_sammy.sh

echo "Switch to JellyBean"
git checkout jellybean
