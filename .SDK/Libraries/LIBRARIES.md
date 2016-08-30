
# 3rd Party Static Libraries #

Currently Coconut2D generates portable C++11 code for **iOS**, **Android** and **x86**, and can export an **XCode Project** and a **Microsoft Visual Studio 2013 Project**.

The `libs.json` file is a simple **Static Libraries Registry** that generates the proper linker bindings in makefiles and exported project files.


**The following libraries are required and are [INCLUDED] in Coconut2D Frameworks:**

1. **Boost** - General Purpose Library
2. **cURL** - HTTP requests
3. **Freetype** - Truetype font loading
4. **GLew** - OpenGL utilities for Windows
5. **libJPEG** - JPEG image loading
7. **OpenAL** - OGG audio file Loading and playback using Vorbis / Tremolo decoding
8. **png** - PNG image loading
9. **libz** - Zip file loading
10. **SQLite** - Portable RDBMS

**Typical Download Locations and Versions:**

	curl -L -o boost.tar.gz 	"http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz/download"
	curl -L -o curl.zip 		"http://curl.haxx.se/download/curl-7.47.1.zip"
	curl -L -o freetype.tar.gz 	"http://download.savannah.gnu.org/releases/freetype/freetype-2.6.3.tar.gz"
	curl -L -o glew.zip 		"https://sourceforge.net/projects/glew/files/glew/1.13.0/glew-1.13.0.zip/download"
	curl -L -o jpeg.zip 		"http://www.ijg.org/files/jpegsr9b.zip"
	curl -L -o libogg.tar.gz 	"http://downloads.xiph.org/releases/ogg/libogg-1.3.2.tar.gz"
	curl -L -o libpng.tar.gz 	"http://prdownloads.sourceforge.net/libpng/libpng-1.6.21.tar.gz?download"
	curl -L -o libtheora.zip 	"http://downloads.xiph.org/releases/theora/libtheora-1.1.1.zip"
	curl -L -o libvorbis.tar.gz "http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.5.tar.gz"
	curl -L -o openal.tar.bz2 	"http://kcat.strangesoft.net/openal-releases/openal-soft-1.17.2.tar.bz2"
	curl -L -o openssl.tar.gz 	"https://www.openssl.org/source/openssl-1.0.2g.tar.gz"
	curl -L -o sqlite.tar.gz 	"http://www.sqlite.org/2016/sqlite-autoconf-3110100.tar.gz"
	curl -L -o tremor.tar.gz 	"https://git.xiph.org/?p=tremor.git;a=snapshot;h=b56ffce0c0773ec5ca04c466bc00b1bbcaf65aef;sf=tgz"
	curl -L -o zlib.tar.gz 		"http://prdownloads.sourceforge.net/libpng/zlib-1.2.8.tar.gz?download"


# Compiling Static Libraries #

## 1. Compiling iOS Static Libraries ##

If you want to compile for older iOS devices your libraries should include the following architectures:
`armv6` `armv7` `armv7s` `arm64` `i386` `x86_64`

- The standard (minimum) iOS architectures for iOS devices are **armv7** and **arm64**.

- The standard iOS architectures for iOS Simulator are **i386** and **x86_64**.

**So typically an iOS Static Library should include at least 4 architectures (armv7 arm64 i386 x86_64)**

Prebuilt versions of most libraries are available on several **GitHub** repositories such as this one:

[https://github.com/cocos2d/cocos2d-x-3rd-party-libs-bin](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-bin "https://github.com/cocos2d/cocos2d-x-3rd-party-libs-bin")

[https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src](https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src "https://github.com/cocos2d/cocos2d-x-3rd-party-libs-src")

To build Static Libraries required by Coconut2D from Cocos2D-X use the following script:

    $ ./build.sh -p=ios --libs=png,jpeg,freetype,curl --arch=armv7,armv7s,arm64,i386,x86_64 --mode=release

**Combining iOS Device and iOS Simulator Libraries**

If you are not very familiar with XCode, you need to this bit of information:

![](../../../Documentation/Introduction/XCode_scr01.png)

XCode can be set to build device architectures by selecting **Generic iOS Device** Scheme.
XCode can be set to build simulator architectures by selecting a simulator device (eg. iPhone6).

You can combine iOS device libraries with simulator libraries by renaming the libraries to `libXXX-arm.a` and `libXXX-i386.a` entering this command:

	$ lipo -create -output libTremolo.a libTremolo-arm.a libTremolo-x86.a

You can view the architectures inside a library by entering this command:

	$ file libTreamolo.a
	libtremolo.a: Mach-O universal binary with 4 architectures
	libtremolo.a (for architecture armv7):	current ar archive random library
	libtremolo.a (for architecture i386):	current ar archive random library
	libtremolo.a (for architecture x86_64):	current ar archive random library
	libtremolo.a (for architecture arm64):	current ar archive random library

For libraries please use the following Build Settings:

- Architecture: **$(ARCHS_STANDARD)**
- Valid Architectures: **armv6 armv7 armv7s arm64 i386**

Boost is a pain to get it right so you should better look for prebuilt binaries. A good place to search is GitHub.

## 2. Compiling Android Static Libraries ##

The easiest way to do it is from a Mac or Linux computer. You will need Android NDK and Android SDK installed and their environment paths properly configured.

Nice to have information is the following Cocos2D-X build script:

	#!/bin/bash

	source `pwd`/main.ini
	#
	# A script to build static library for Android
	#

	build_arches=""
	build_mode=""
	build_library=""
	build_api=""
	build_gcc_version=""
	build_platform=""
	build_list_all_libraries=no
	build_show_help_message=no

	function contains() {
	    local n=$#
	    local value=${!n}
	    for ((i=1;i < $#;i++)) {
	            if [ "${!i}" == "${value}" ]; then
	                echo "y"
	                return 0
	            fi
	        }
	        echo "n"
	        return 1
	}

	function usage()
	{
	    echo "Helper to build all the 3rd party libraries for Cocos2D-X on various platform."
	    echo ""
	    echo "Usage:"
	    echo "    ./build.sh  -p=PLATFORM [--libs=LIBRARY...] [-a=ARCH...] [-mode=MODE]"
	    echo "    ./build.sh  --platform=PLATFORM [--libs=LIBRARY...] [--arch=ARCH...] [--mode=MODE]"
	    echo "    ./build.sh  -p=PLATFORM (-h | --help)"
	    echo "    ./build.sh  -p=PLATFORM (-l | --list)"
	    echo ""
	    echo "Arguments:"
	    echo "    PLATFORM:    Platform names, valid values are: mac,ios,tvos,android,tizen,linux"
	    echo "    LIBRARY:     Library names, valid values are platform dependent(png,jpeg,lua,chipmunk,etc)"
	    echo "    ARCH:        Build arches, valid values are platform dependent(arm,arm64,armv7,i386,mips,etc)"
	    echo "    MODE:        Build mode, valid values are: release and debug"
	    echo ""
	    echo "Options:"
	    echo "    --platform   Specify a target platform, one platform a time."
	    echo "    --libs:      Specify a few target libraries,all the libraries should be comma separated.[default: all]"
	    echo "    --arch:      Specify a few arches to build,all the arches should be comma separated. [default: all]"
	    echo "    --mode:      Specify the build mode.[default: release]"
	}

	while [ "$1" != "" ]; do
	    PARAM=`echo $1 | awk -F= '{print $1}'`
	    VALUE=`echo $1 | awk -F= '{print $2}'`
	    case $PARAM in
	        --help | -h)
	            build_show_help_message=yes
	            ;;
	        --platform | -p)
	            build_platform=$VALUE
	            ;;
	        --libs)
	            build_library=$VALUE
	            ;;
	        --arch | -a)
	            build_arches=$VALUE
	            ;;
	        --mode | -m)
	            build_mode=$VALUE
	            ;;
	        --list | -l)
	            build_list_all_libraries=yes
	            ;;
	        *)
	            echo "ERROR: unknown parameter \"$PARAM\""
	            usage
	            exit 1
	            ;;
	    esac
	    shift
	done

	#check invalid platform
	function check_invalid_platform()
	{
	    # echo "checking ${build_platform} is in ${cfg_all_valid_platforms[@]}"
	    if [ $(contains "${cfg_all_valid_platforms[@]}" $build_platform) == "n" ]; then
	        usage
	        exit 1
	    fi
	}

	check_invalid_platform

	##load platform config files
	for p in ${cfg_all_valid_platforms[@]}
	do
	    if [ $(contains "${cfg_all_valid_platforms[@]}" $build_platform) == "y" ];then
	        platform_config_file=${build_platform}.ini
	        if [ ! -f $platform_config_file ];then
	            echo "platform config file is not exists!"
	            exit;
	        fi
	        source $platform_config_file
	        [[ -z "${build_api}" ]] && build_api=$cfg_default_build_api
	        [[ -z "${build_gcc_version}" ]] && build_gcc_version=$cfg_default_gcc_version
	    fi
	done

	function list_all_supported_libraries()
	{

	    echo "Supported libraries and versions:"

	    for lib in ${cfg_all_supported_libraries[@]}
	    do
	        all_supported_libraries=$(find  ../contrib/src -type f | grep SHA512SUMS | xargs cat | awk 'match ($0, /.tgz|.tar.gz|.zip|.tar.xz/) { print substr($2,0,length($2)-RLENGTH)}' | grep -i $lib | awk '{print $1}')
	        echo $all_supported_libraries | awk '{ print $1}'
	    done
	}

	if [ $build_list_all_libraries = "yes" ];then
	    list_all_supported_libraries
	    exit 1
	fi

	if [ $build_show_help_message = "yes" ];then
	    usage
	    exit 1
	fi


	if test -z "$build_arches"
	then
	    build_arches=$cfg_default_build_arches
	fi

	if test -z "$build_library"
	then
	    while true; do
	        read -p "Do you wish to build with all the libraries?[yes|no]" yn
	        case $yn in
	            [Yy]* ) build_library=$cfg_default_build_libraries; break;;
	            [Nn]* ) usage;exit;;
	            * ) echo "Please answer yes or no.";;
	        esac
	    done
	fi

	if test -z "$build_mode"
	then
	    echo "You don't specify a valid build mode, use release mode"
	    build_mode=$cfg_default_build_mode
	fi


	if [ $cfg_platform_name = "android" ];then
	    echo "build api is $build_api."
	    if [[ ! $build_api =~ ^[0-9]+$ ]]; then
	        echo "Android API should be integers!"
	        usage
	        exit 1
	    fi

	    if [[ ! $build_gcc_version =~ ^[0-9]\.[0-9]+$ ]]; then
	        echo "Invalid gcc version number! Gcc version should be numerical numbers."
	        usage
	        exit 1
	    fi

	fi

	current_dir=`pwd`
	top_dir=$current_dir/..

	all_arches=(${cfg_all_supported_arches[@]})
	all_libraries=(${cfg_all_supported_libraries[@]})

	if [ $build_arches = $cfg_default_build_arches ]; then
	    build_arches=(${cfg_default_arches_all[@]})
	else
	    build_arches=(${build_arches//,/ })
	fi

	if [ $build_library = $cfg_default_build_libraries ]; then
	    build_library=(${cfg_default_libraries_all[@]})
	else
	    build_library=(${build_library//,/ })
	fi

	#check invalid arch type
	function check_invalid_arch_type()
	{
	    for arch in ${build_arches[@]}
	    do
	        echo "checking ${arch} is in ${all_arches[@]}"
	        if [ $(contains "${all_arches[@]}" $arch) == "n" ]; then
	            echo "Invalid arch! Only ${all_arches[@]} is acceptable."
	            exit 1
	        fi
	    done
	}

	check_invalid_arch_type

	#check invalid library name
	function check_invalid_library_name()
	{
	    for lib in "${build_library[@]}"
	    do
	        echo "checking ${lib} is in ${all_libraries[@]}"
	        if [ $(contains "${all_libraries[@]}" $lib) == "n" ]; then
	            echo "Invalid library names! Only ${all_libraries[@]} is acceptable!"
	            exit 1
	        fi
	    done
	}

	check_invalid_library_name

	#check invalid build mode, only debug and release is acceptable
	function check_invalid_build_mode() {
	    if [ $(contains ${cfg_valid_build_mode[@]} $1) == "n" ];then
	        echo "invalid build mode, only: ${cfg_valid_build_mode[@]} is allowed!"
	        usage
	        exit 1
	    fi
	}

	check_invalid_build_mode $build_mode

	function create_fat_library()
	{
	    library_name=$1
	    #strip & create fat library
	    LIPO="xcrun -sdk iphoneos lipo"
	    STRIP="xcrun -sdk iphoneos strip"

	    if [ -f $cfg_platform_name/$library_name/prebuilt/lib$library_name.a ]; then
	        echo "removing old fat library..."
	        rm $cfg_platform_name/$library_name/prebuilt/lib$library_name.a
	    fi

	    all_static_libs=$(find $cfg_platform_name/$library_name/prebuilt -type f -name "lib$library_name.a")

	    echo "create fat library lib$library_name for $all_static_libs"
	    $LIPO -create  $all_static_libs \
	          -output $cfg_platform_name/$library_name/prebuilt/lib$library_name.a

	    # rm $all_static_libs

	    # remove debugging info don't strip
	    # $STRIP -S $library_name/prebuilt/lib$library_name.a
	    $LIPO -info $cfg_platform_name/$library_name/prebuilt/lib$library_name.a
	}

	function set_build_mode_cflags()
	{
	    build_flag=cfg_build_${build_mode}_mode
	    OPTIM=${!build_flag}

	    export OPTIM
	}

	if [ $cfg_platform_name = "mac" ];then
	    export MIN_MACOSX_TARGET=$cfg_min_macosx_deoply_tartget
	fi

	# build all the libraries for different arches
	for lib in "${build_library[@]}"
	do
	    library_name=$lib

	    parser_lib_archive_alias=${lib}_archive_alias
	    archive_name=${!parser_lib_archive_alias}
	    if [ -z $archive_name ];then
	        archive_name=$lib
	    fi


	    mkdir -p $cfg_platform_name/$archive_name/include/

	    for arch in "${build_arches[@]}"
	    do
	        #skip build libraries with certain arch
	        ignore_arch_library=${lib}_ignore_arch_list
	        ignore_arch_list=(${!ignore_arch_library})
	        ignore_arch_list_array=(${ignore_arch_list//,/ })
	        if [ ! -z ${ignore_arch_list} ]; then
	            echo ${ignore_arch_list}
	            if [ $(contains "${ignore_arch_list_array[@]}" $arch) == "y" ];then
	                echo "ingore $lib for $arch"
	                continue
	            fi
	        fi

	        #set build mode flags -- debug or release
	        set_build_mode_cflags

	        #determine wether use mthumb or not
	        parse_use_mthumb=cfg_${lib}_${arch}_use_mthumb
	        use_mthumb=${!parse_use_mthumb}
	        echo $use_mthumb
	        if [ -z $use_mthumb ];then
	            use_mthumb=yes
	        fi

	        export ANDROID_USE_MTHUMB=$use_mthumb
	        export ANDROID_STL_VERSION=$cfg_default_build_stl

	        install_library_path="install-${cfg_platform_name}"
	        build_library_path=$cfg_platform_name

	        echo "build $arch for $lib in $cfg_platform_name"

	        parse_arch_folder_name=cfg_${arch}_alias_folder_name
	        original_arch_name=${!parse_arch_folder_name}
	        if [ -z $original_arch_name ];then
	            original_arch_name=$arch
	        fi

	        MY_TARGET_ARCH=$original_arch_name
	        export MY_TARGET_ARCH

	        if [ ${cfg_is_cross_compile} = "yes" ];then
	            cross_compile_toolchain_path=cfg_${arch}_toolchain_bin
	            echo "toolchain path is ${!cross_compile_toolchain_path}"
	            export PATH="${!cross_compile_toolchain_path}:${PATH}"
	        fi

	        # TODO: add more build and target options here
	        if [ $cfg_platform_name = "ios" ];then
	            export BUILDFORIOS="yes"
	        fi

	        if [ $cfg_platform_name = "tvos" ];then
	            export BUILDFORTVOS="yes"
	        fi

	        if [ $cfg_platform_name = "android" ];then
	            export ANDROID_GCC_VERSION=$build_gcc_version
	            export ANDROID_API=android-$build_api
	        fi


	        mkdir -p "${top_dir}/contrib/${cfg_platform_name}-${arch}"
	        cd "${top_dir}/contrib/${cfg_platform_name}-${arch}"

	        PREFIX="${top_dir}/contrib/install-${cfg_platform_name}/${arch}"

	        my_target_host=cfg_${arch}_host_machine
	        if [ $cfg_is_cross_compile = "no" ];then
	            cfg_build_machine=${!my_target_host}
	        fi

	        ../bootstrap --enable-$lib \
	                     --build=$cfg_build_machine \
	                     --host=${!my_target_host} \
	                     --prefix=${PREFIX}


	        echo "MY_TARGET_ARCH := ${MY_TARGET_ARCH}" >> config.mak
	        echo "OPTIM := ${OPTIM}" >> config.mak
	        ENABLE_BITCODE=$cfg_build_bitcode
	        export ENABLE_BITCODE
	        echo "ENABLE_BITCODE := ${cfg_build_bitcode}" >> config.mak

	        make

	        cd -

	        local_library_install_path=$cfg_platform_name/$archive_name/prebuilt/$original_arch_name
	        if [ ! -d $local_library_install_path ]; then
	            echo "create folder for library with specify arch. $local_library_install_path"
	            mkdir -p $local_library_install_path
	        fi

	        #determine the .a achive name with a specified libraries
	        parse_original_lib_name=${lib}_original_name
	        original_archive_name=${!parse_original_lib_name}
	        if [ -z $original_archive_name ];then
	            original_archive_name=$archive_name
	        fi

	        #copy .a archive from install-platform folder
	        cp $top_dir/contrib/$install_library_path/$arch/lib/lib$original_archive_name.a $local_library_install_path/lib$archive_name.a

	        #copy dependent .a archive
	        parse_dependent_archive_list=${lib}_dependent_archive_list
	        original_dependent_archive_list=${!parse_dependent_archive_list}
	        if [ ! -z $original_dependent_archive_list ];then
	            echo "copying dependent archives..."
	            original_dependent_archive_list=(${original_dependent_archive_list//,/ })

	            for dep_archive in ${original_dependent_archive_list[@]}
	            do
	                local_library_install_path=$cfg_platform_name/${dep_archive}/prebuilt/$original_arch_name
	                mkdir -p $local_library_install_path
	                cp $top_dir/contrib/$install_library_path/$arch/lib/lib${dep_archive}.a $local_library_install_path/lib${dep_archive}.a

	            done
	        fi


	        echo "Copying needed heder files"
	        copy_include_file_path=${lib}_header_files
	        cp  -r $top_dir/contrib/$install_library_path/$arch/include/${!copy_include_file_path} $cfg_platform_name/$archive_name/include


	        echo "cleaning up"
	        if [ $cfg_is_cleanup_after_build = "yes" ];then
	            rm -rf $top_dir/contrib/$install_library_path
	            rm -rf $top_dir/contrib/$build_library_path-$arch
	        fi
	    done

	    echo $cfg_build_fat_library
	    if [ $cfg_build_fat_library = "yes" ];then

	        create_fat_library $archive_name

	        parse_dependent_archive_list=${lib}_dependent_archive_list
	        original_dependent_archive_list=${!parse_dependent_archive_list}
	        if [ ! -z $original_dependent_archive_list ];then
	            echo "create fat library for dependent archives..."
	            original_dependent_archive_list=(${original_dependent_archive_list//,/ })

	            for dep_archive in ${original_dependent_archive_list[@]}
	            do
	                create_fat_library $dep_archive
	            done
	        fi
	    fi

	done

To build Static Libraries required by Coconut2D from Cocos2D-X use the following script:

    $ ./build.sh -p=android --libs=png,jpeg,freetype,curl --arch=armv7,armv7s,arm64,i386,x86_64 --mode=release



## 3. Compiling Windows MinGW Static Libraries ##

You need to install MinGW and MSys and then create a file and paste this bash script:

	#!/bin/sh
	echo "Bash Version: $BASH_VERSION"

	# ==================================================================================================================================
	#	   _____      __                 ______           _                                       __
	#	  / ___/___  / /___  ______     / ____/___ _   __(_)________  ____  ____ ___  ___  ____  / /_
	#	  \__ \/ _ \/ __/ / / / __ \   / __/ / __ \ | / / / ___/ __ \/ __ \/ __ `__ \/ _ \/ __ \/ __/
	#	 ___/ /  __/ /_/ /_/ / /_/ /  / /___/ / / / |/ / / /  / /_/ / / / / / / / / /  __/ / / / /_
	#	/____/\___/\__/\__,_/ .___/  /_____/_/ /_/|___/_/_/   \____/_/ /_/_/ /_/ /_/\___/_/ /_/\__/
	#	                   /_/
	# ==================================================================================================================================

	# make sure you edit msys/etc/fstab
	# add: C:/<path_to_MinGW>		/mingw

	LIBRARY_SOURCES="$(PWD)"
	cd $LIBRARY_SOURCES
	echo "Libraries Sources Folder: $LIBRARY_SOURCES"

	NASM="/d/mobileFX/Projects/Software/Coconut/IDE/Studio/etc/3rd_party/nasm/nasm.exe"

	# ==================================================================================================================================
	#	   __  ____  _ __
	#	  / / / / /_(_) /____
	#	 / / / / __/ / / ___/
	#	/ /_/ / /_/ / (__  )
	#	\____/\__/_/_/____/
	#
	# ==================================================================================================================================

	function move_head
	{
		count=`ls $1 | wc -l`
		if [ "$count" -eq "1" ]
		then
			t=`ls $1/* -1 -d`
			for s in `ls -d -1 $1/**/*`
			do
				mv $s $1
			done
			rm -rf $t
		fi
	}

	# ==================================================================================================================================
	#	   __  __          __      __          __  ____       _______       __
	#	  / / / /___  ____/ /___ _/ /____     /  |/  (_)___  / ____/ |     / /
	#	 / / / / __ \/ __  / __ `/ __/ _ \   / /|_/ / / __ \/ / __ | | /| / /
	#	/ /_/ / /_/ / /_/ / /_/ / /_/  __/  / /  / / / / / / /_/ / | |/ |/ /
	#	\____/ .___/\__,_/\__,_/\__/\___/  /_/  /_/_/_/ /_/\____/  |__/|__/
	#	    /_/
	# ==================================================================================================================================

	function update_mingw
	{
		mingw-get install msys-wget-bin
		mingw-get install libtool
		mingw-get install unzip

		# Download package config and copy executable to mingw/bin
		wget -c http://ftp.gnome.org/pub/gnome/binaries/win32/dependencies/pkg-config_0.23-3_win32.zip
		7z x ./pkg-config_0.23-3_win32.zip -o./pkg-config -y >& /dev/null
		rm -f ./pkg-config_0.23-3_win32.zip
		cp ./pkg-config/bin/pkg-config.exe $MINGW/bin/
		rm -rf ./pkg-config

		# Download glib
		wget -c http://ftp.gnome.org/pub/gnome/binaries/win32/glib/2.28/glib_2.28.1-1_win32.zip
		7z x ./glib_2.28.1-1_win32.zip -o./glib -y >& /dev/null
		rm -f ./glib_2.28.1-1_win32.zip
		cp ./glib/bin/libglib-2.0-0.dll $MINGW/bin/
		rm -rf ./glib

		# Fixes pkg-config
		curl -L -s -o gettext-runtime_0.18.1.1-2_win32.zip "http://ftp.gnome.org/pub/gnome/binaries/win32/dependencies/gettext-runtime_0.18.1.1-2_win32.zip"
		7z x ./gettext-runtime_0.18.1.1-2_win32.zip -o./gettext -y >& /dev/null
		rm -f ./gettext-runtime_0.18.1.1-2_win32.zip
		cp ./gettext/bin/intl.dll $MINGW/bin/
		rm -rf ./gettext

		# NASM
		rm -rf $NASM >& /dev/null
		curl -L -s -o nasm-2.07-win32.zip "https://sourceforge.net/projects/nasm/files/Win32%20binaries/2.07/nasm-2.07-win32.zip/download"
		7z x ./nasm-2.07-win32.zip -o$NASM -y >& /dev/null
		rm -f nasm-2.07-win32.zip
		t=`ls $NASM/* -1 -d`
		for i in `ls -d -1 $NASM/**/*`; do mv $i $NASM; done
		rm -rf $t

	}

	# ==================================================================================================================================
	#	    ____                      __                __   __    _ __                    _
	#	   / __ \____ _      ______  / /___  ____ _____/ /  / /   (_) /_  _________ ______(_)__  _____
	#	  / / / / __ \ | /| / / __ \/ / __ \/ __ `/ __  /  / /   / / __ \/ ___/ __ `/ ___/ / _ \/ ___/
	#	 / /_/ / /_/ / |/ |/ / / / / / /_/ / /_/ / /_/ /  / /___/ / /_/ / /  / /_/ / /  / /  __(__  )
	#	/_____/\____/|__/|__/_/ /_/_/\____/\__,_/\__,_/  /_____/_/_.___/_/   \__,_/_/  /_/\___/____/
	#
	# ==================================================================================================================================

	function download_libraries_sources
	{
		# IMPORTANT: Make sure you download files as <library_name>.tar.gz

		echo "Download common libraries (stable versions 21 Mar 2016), please wait..."

		curl -L -o boost.tar.gz 			"http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz/download"
		curl -L -o curl.zip 				"http://curl.haxx.se/download/curl-7.47.1.zip"
		curl -L -o freetype.tar.gz 			"http://download.savannah.gnu.org/releases/freetype/freetype-2.6.3.tar.gz"
		curl -L -o glew.zip 				"https://sourceforge.net/projects/glew/files/glew/1.13.0/glew-1.13.0.zip/download"
		curl -L -o jpeg.zip 				"http://www.ijg.org/files/jpegsr9b.zip"
		curl -L -o libogg.tar.gz 			"http://downloads.xiph.org/releases/ogg/libogg-1.3.2.tar.gz"
		curl -L -o libpng.tar.gz 			"http://prdownloads.sourceforge.net/libpng/libpng-1.6.21.tar.gz?download"
		curl -L -o libtheora.zip 			"http://downloads.xiph.org/releases/theora/libtheora-1.1.1.zip"
		curl -L -o libvorbis.tar.gz 		"http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.5.tar.gz"
		curl -L -o openal.tar.bz2 			"http://kcat.strangesoft.net/openal-releases/openal-soft-1.17.2.tar.bz2"
		curl -L -o openssl.tar.gz 			"https://www.openssl.org/source/openssl-1.0.2g.tar.gz"
		curl -L -o sqlite.tar.gz 			"http://www.sqlite.org/2016/sqlite-autoconf-3110100.tar.gz"
		curl -L -o tremor.tar.gz 			"https://git.xiph.org/?p=tremor.git;a=snapshot;h=b56ffce0c0773ec5ca04c466bc00b1bbcaf65aef;sf=tgz"
		curl -L -o zlib.tar.gz 				"http://prdownloads.sourceforge.net/libpng/zlib-1.2.8.tar.gz?download"
	}

	# ==================================================================================================================================
	#	    ______     __                  __     ___ __
	#	   / ____/  __/ /__________ ______/ /_   / (_) /_  _________ ________  __   _________  __  _______________  _____
	#	  / __/ | |/_/ __/ ___/ __ `/ ___/ __/  / / / __ \/ ___/ __ `/ ___/ / / /  / ___/ __ \/ / / / ___/ ___/ _ \/ ___/
	#	 / /____>  </ /_/ /  / /_/ / /__/ /_   / / / /_/ / /  / /_/ / /  / /_/ /  (__  ) /_/ / /_/ / /  / /__/  __(__  )
	#	/_____/_/|_|\__/_/   \__,_/\___/\__/  /_/_/_.___/_/   \__,_/_/   \__, /  /____/\____/\__,_/_/   \___/\___/____/
	#	                                                                /____/
	# ==================================================================================================================================

	function delete_sources
	{
		# Delete all library foldes
		echo "Deleting old sources, please wait..."
		for i in `ls -d */`; do
			t=$(basename "$i")
			echo "+ deleting $t, please wait..."
			rm -rf $t >& /dev/null
		done
	}

	function extract_library_sources
	{
		# Save sources
		mkdir ./.src >& /dev/null

		# Extract all library sources
		echo "Extracting sources, please wait..."

		for i in `ls *.zip`; do
			echo + extracting $i...
			7z x $i -o$(basename "$i" .zip) >& /dev/null
			mv $i ./.src
		done

		for i in `ls *.gz *.xz *.bz2`; do
			n=`( tar -tf "$i" | head -1 | cut -f1 -d"/" ) 2>/dev/null`
			t=$(basename "$i" .tar.gz)
			t=$(basename "$t" .tar.xz)
			t=$(basename "$t" .tar.bz2)
			echo "+ extracting $i to $t ($n) ..."
			tar xf $i >& /dev/null
			mv $n $t
			mv $i ./.src
		done

		# Detect master folders within library root and move them to root
		for i in `ls -d */`; do	move_head $i; done
	}

	# ==================================================================================================================================
	#	   ______                      _ __        __    _ __                    _
	#	  / ____/___  ____ ___  ____  (_) /__     / /   (_) /_  _________ ______(_)__  _____
	#	 / /   / __ \/ __ `__ \/ __ \/ / / _ \   / /   / / __ \/ ___/ __ `/ ___/ / _ \/ ___/
	#	/ /___/ /_/ / / / / / / /_/ / / /  __/  / /___/ / /_/ / /  / /_/ / /  / /  __(__  )
	#	\____/\____/_/ /_/ /_/ .___/_/_/\___/  /_____/_/_.___/_/   \__,_/_/  /_/\___/____/
	#	                    /_/
	# ==================================================================================================================================

	function compile_libraries
	{
		export "INCLUDE_PATH=/usr/local/include"
		export "LIBRARY_PATH=/usr/local/lib"
		export "BINARY_PATH=/usr/local/bin"
		export "CFLAGS=-I/usr/local/include"
		export "CPPFLAGS=-I/usr/local/include"
		export "LDFLAGS=-L/usr/local/lib"
		export "PKG_CONFIG_PATH=/usr/local/lib/pkgconfig"

		if false; then

		# ==================================================================================================================================
		# libz - OK
		# libz is a popular library implementing the compression algorithm used by gzip and zip.
		# Depends on: nothing
		#Required by: libpng, libtiff
		# ==================================================================================================================================

		cd $LIBRARY_SOURCES/zlib
		make -f win32/Makefile.gcc
		make install -f win32/Makefile.gcc

		# ==================================================================================================================================
		# glew - OK
		# glew (OpenGL Extension Wrangler Library (GLEW)) is a cross-platform open-source C/C++ extension loading library
		# Depends on: nothing
		# Required by: OpenGL / WebGL
		# ==================================================================================================================================

		cd $LIBRARY_SOURCES/glew
		make
		make install GLEW_DEST=/usr/local

		# ==================================================================================================================================
		# jpeg - OK
		# libjpeg is a popular library supporting the JPEG image compression.
		# Depends on: nothing
		# Required by: libtiff, librasterlite2
		# ==================================================================================================================================

		cd $LIBRARY_SOURCES/jpeg
		autoheader
		./configure --prefix=/usr/local
		make
		make install-strip

		# ==================================================================================================================================
		# libpng - OK
		# libpng is a popular library supporting the PNG image compression.
		# Depends on: libz
		# Required by: librasterlite2
		# ==================================================================================================================================

		cd $LIBRARY_SOURCES/libpng
		./configure --prefix=/usr/local --with-zlib-prefix=/usr/local
		make
		make install

		# ==================================================================================================================================
		# sqlite - OK
		# libsqlite is the library implementing the SQLite DBMS engine
		# Depends on: nothing
		# Required by: nothing
		# ==================================================================================================================================

		cd $LIBRARY_SOURCES/sqlite
		export "CFLAGS=-DSQLITE_ENABLE_STAT3=1 -DSQLITE_ENABLE_TREE_EXPLAIN=1 -DSQLITE_ENABLE_UPDATE_DELETE_LIMIT=1 -DSQLITE_ENABLE_FTS3_PARENTHESIS=1 -DSQLITE_ENABLE_COLUMN_METADATA=1"
		./configure --prefix=/usr/local
		make
		make install-strip

		# ==================================================================================================================================
		# openssl - OK
		# OpenSSL is a well known standard library supporting SSL, i.e. the encrypted HTTPS web protocol.
		# Depends on: nothing
		# Required by: libcurl
		# ==================================================================================================================================

		cd $LIBRARY_SOURCES/openssl
		./Configure mingw --prefix=/usr/local shared
		make depend
		make
		make install

		# ==================================================================================================================================
		# libcurl - OK
		# libcurl is a well known library supporting URLs (networking, web protocols)
		# Depends on: libz, OpenSSL
		# Required by: XMLHttp
		# ==================================================================================================================================

		cd $LIBRARY_SOURCES/curl
		./configure --prefix=/usr/local --enable-shared=no --with-zlib=/usr/local
		make
		make install-strip
		make distclean
		./configure --prefix=/usr/local --enable-shared=yes --with-zlib=/usr/local
		make
		make install-strip

		# ==================================================================================================================================
		# freetype - OK
		# libfreetype is a standard library supporting TrueType fonts.
		# Depends on: nothing
		# Required by: libcairo
		# ==================================================================================================================================

		cd $LIBRARY_SOURCES/freetype
		./configure --prefix=/usr/local --enable-static
		make
		make install

		# ==================================================================================================================================
		# libogg - OK
		# libogg is a multimedia container format, and the native file and stream format for the Xiph.org multimedia codecs.
		# Depends on: nothing
		# Required by: libvorbis
		# ==================================================================================================================================

		cd $LIBRARY_SOURCES/libogg
		LDFLAGS='-mwindows' ./configure --prefix=/usr/local
		make
		make install

		# ==================================================================================================================================
		# libvorbis - OK
		# libvorbis produces an audio coding format and software reference encoder/decoder (codec) for lossy audio compression.
		# Depends on: nothing
		# Required by: nothing
		# ==================================================================================================================================

		cd $LIBRARY_SOURCES/libvorbis
		LDFLAGS='-mwindows' ./configure --prefix=/usr/local
		make
		make install

		# ==================================================================================================================================
		# openal
		# ==================================================================================================================================

		fi

		wget http://kcat.strangesoft.net/openal-binaries/openal-soft-1.17.2-bin.zip
		unzip openal-soft-1.17.2-bin.zip
		cp openal-soft-1.17.2-bin/lib/Win32/* /usr/local/lib
		cp openal-soft-1.17.2-bin/Win32/soft_oal.dll /usr/local/bin/OpenAL32.dll
		cp openal-soft-1.17.2-bin/openal-info.exe /usr/local/bin
		cp -R openal-soft-1.17.2-bin/include /usr/local

		cd $LIBRARY_SOURCES/openal
		export OPENAL_SOFT_SRC="$(PWD)"
		export INSTALLDIR=/usr/local
		export PATH=$INSTALLDIR/bin:$PATH
		export TARGETMACH=arm-none-linux-gnueabi
		export BUILDMACH=i686-pc-linux-gnu
		export CROSS=mingw32
		export CC=${CROSS}-gcc
		export LD=${CROSS}-ld
		export AS=${CROSS}-as
		export CXX=${CROSS}-g++
		SET(CMAKE_SYSTEM_NAME Windows)
		SET(CMAKE_SYSTEM_VERSION 1)
		SET(CMAKE_C_COMPILER   /mingw/bin/mingw32-gcc)
		SET(CMAKE_CXX_COMPILER /mingw/bin/mingw32-g++)
		SET(CMAKE_FIND_ROOT_PATH  /home/<your user>/workbench/gcc-g++-4.8.2/arm)
		SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
		SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
		SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

		cmake -DCMAKE_TOOLCHAIN_FILE=cross.cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr/local
		make
		make install

		cd build
		cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr/local -G "MSYS Makefiles" ..
		make
		make install

	}

	update_mingw
	download_libraries_sources
	delete_sources
	extract_library_sources
	compile_libraries


## 4. Compiling Windows Visual Studio 2013 Static Libraries ##

All the above libraries are very easily compiled for Microsoft Visual Studio 2013 using CMake.

Most libraries will work straight as .a files and you can save the pain of creating .lib files.


# Other Libraries #

	curl -L -o boost.tar.gz 			"http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz/download"
	curl -L -o cairo.tar.xz 			"http://cairographics.org/releases/cairo-1.14.6.tar.xz"
	curl -L -o curl.zip 				"http://curl.haxx.se/download/curl-7.47.1.zip"
	curl -L -o expat.tar.bz2 			"http://downloads.sourceforge.net/project/expat/expat/2.1.1/expat-2.1.1.tar.bz2?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fexpat%2Ffiles%2Fexpat%2F2.1.1%2F&ts=1458561636&use_mirror=vorboss"
	curl -L -o fontconfig.tar.gz 		"http://fontconfig.org/release/fontconfig-2.11.1.tar.gz"
	curl -L -o freeglut.tar.gz 			"http://downloads.sourceforge.net/project/freeglut/freeglut/3.0.0/freeglut-3.0.0.tar.gz?r=http%3A%2F%2Ffreeglut.sourceforge.net%2Findex.php&ts=1458518838&use_mirror=kent"
	curl -L -o freetype.tar.gz 			"http://download.savannah.gnu.org/releases/freetype/freetype-2.6.3.tar.gz"
	curl -L -o freexl.zip 				"http://www.gaia-gis.it/gaia-sins/freexl-1.0.2.zip"
	curl -L -o glew.zip 				"https://sourceforge.net/projects/glew/files/glew/1.13.0/glew-1.13.0.zip/download"
	curl -L -o jpeg.zip 				"http://www.ijg.org/files/jpegsr9b.zip"
	curl -L -o libjpeg-turbo.tar.gz 	"http://sourceforge.net/projects/libjpeg-turbo/files/1.4.2/libjpeg-turbo-1.4.2.tar.gz/download"
	curl -L -o liblzma.tar.gz 			"http://tukaani.org/xz/xz-5.2.2.tar.gz"
	curl -L -o libogg.tar.gz 			"http://downloads.xiph.org/releases/ogg/libogg-1.3.2.tar.gz"
	curl -L -o libpng.tar.gz 			"http://prdownloads.sourceforge.net/libpng/libpng-1.6.21.tar.gz?download"
	curl -L -o libtheora.zip 			"http://downloads.xiph.org/releases/theora/libtheora-1.1.1.zip"
	curl -L -o libvorbis.tar.gz 		"http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.5.tar.gz"
	curl -L -o libwebsockets.zip 		"https://github.com/warmcat/libwebsockets/archive/master.zip"
	curl -L -o libxml2.tar.gz 			"ftp://xmlsoft.org/libxml2/libxml2-2.9.3.tar.gz"
	curl -L -o openal.tar.bz2 			"http://kcat.strangesoft.net/openal-releases/openal-soft-1.17.2.tar.bz2"
	curl -L -o openssl.tar.gz 			"https://www.openssl.org/source/openssl-1.0.2g.tar.gz"
	curl -L -o pixman.tar.gz 			"http://cairographics.org/releases/pixman-0.34.0.tar.gz"
	curl -L -o proj.tar.gz 				"http://download.osgeo.org/proj/proj-4.9.2.tar.gz"
	curl -L -o sqlite.tar.gz 			"http://www.sqlite.org/2016/sqlite-autoconf-3110100.tar.gz"
	curl -L -o tremor.tar.gz 			"https://git.xiph.org/?p=tremor.git;a=snapshot;h=b56ffce0c0773ec5ca04c466bc00b1bbcaf65aef;sf=tgz"
	curl -L -o v8.zip 					"https://github.com/v8/v8/archive/master.zip"
	curl -L -o zlib.tar.gz 				"http://prdownloads.sourceforge.net/libpng/zlib-1.2.8.tar.gz?download"
	curl -L -o xzing.zip                "https://github.com/glassechidna/zxing-cpp/archive/master.zip"

