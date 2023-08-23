p0=""
p1=""
p2=""
working_dir=""
machine=""


# user-profile start

pkg_name="build/juice"
lib_name="build/lib"

exec_path="${pkg_name}/sandbox"
exec_name="sandbox"

# user-profile end

if [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    machine="linux"
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    machine="win_x86"
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    machine="win_x64"
fi

err="ERR :: => run.sh (lib | exec) (cr | r) (Release | Debug)"

if [ "$#" -eq 0 ]; then
    echo $err
    exit
elif [ "$#" -eq 1 ]; then
    p0=$1
    p1="r"
    p2="Debug"
elif [ "$#" -eq 2 ]; then
    p0=$1
    p1=$2
    p2="Debug"
elif [ "$#" -eq 3 ]; then
    p0=$1
    p1=$2
    p2=$3
else
    echo $err
    exit
fi

if [[ $p2 != "Release" ]]; then
    if [[ $p2 != "Debug" ]]; then
        echo $err
        exit
    fi
fi

if [[ $1 == "lib" ]]; then
    working_dir=$lib_name
else
    working_dir=$pkg_name
fi

function build()
{
    cmake -B ./${working_dir} -DCMAKE_BUILD_TYPE=${p2} -G "Ninja"
    ninja -C ./${working_dir}
}

function clean()
{
    echo "[!] WARNING: cleaning build..."
    rm ./${working_dir}/* -r
}

function run()
{
    if [ $machine == "linux" ]; then
        exec ./${exec_path}/${exec_name}
    else
        exec ./${exec_path}/${exec_name}.exe
    fi
}

if [[ $p1 == "cr" ]]; then
    clean
fi
build
run
