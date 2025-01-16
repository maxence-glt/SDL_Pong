cmake:
	rm -rf build
	mkdir build
	cd build; cmake .. -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug -DVCPKG_TARGET_TRIPLET=arm64-osx

run:
	cd build; make; ./Pong
