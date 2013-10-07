echo "Switching to Cherry Branch"
git checkout cherry

echo "Make Clean"
make clean
echo "Make Mrproper"
make mrproper
./build_d2vzw_aosp.sh
