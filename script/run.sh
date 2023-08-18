buildSystem=""
buildType=$2
project=""

#########################################
#				  Clean 				#
#########################################
function Clean()
{
	rm ./build/* -rf
}

#########################################
#				Build lib				#
#########################################
function Lib()
{
	project="libjuice.a"
	rm ./build/${buildSystem}/${project}
	cmake ./source/ -B ./build/${buildSystem} -DCMAKE_BUILD_TYPE=${buildType} -G "Ninja"
	ninja -C ./build/${buildSystem}
}

#########################################
#			Build Playground			#
#########################################
function Playground()
{
	project="Playground"
	rm ./build/${buildSystem}/${project}
	cmake ./Playground/ -B ./build/${buildSystem} -DCMAKE_BUILD_TYPE=${buildType} -G "Ninja"
	ninja -C ./build/${buildSystem}

	if [[ -f "./build/${buildSystem}/Playground" ]]; then
			xfce4-terminal -T "${project}" -e "/usr/bin/cb_console_runner ./build/${buildSystem}/Playground" --show-borders --hide-menubar --hide-toolbar  --geometry=50x15+5+10&
	fi
}

#########################################
#				Build SQ				#
#########################################
function juice()
{
	project="sandbox"
	rm ./build/${buildSystem}/sandbox/sandbox
	cmake -B ./build/${buildSystem} -DCMAKE_BUILD_TYPE=${buildType} -G "Ninja"
	ninja -C ./build/${buildSystem}
}

function Run()
{
	if [[ -f "./build/${buildSystem}/sandbox/sandbox" ]]; then
			xfce4-terminal -T "${project}" -e "/usr/bin/cb_console_runner ./build/${buildSystem}/sandbox/sandbox" --show-borders --hide-menubar --hide-toolbar  --geometry=50x15+5+10&
	fi
}

function perftool()
{
	Run
	sleep 5
	echo "Starting performance testing tools..."
	perf record -o ./perf.data --call-graph dwarf --aio -z --sample-cpu --pid $(pidof Sandbox)
	hotspot ./perf.data
}

if [[ $1 == "Clean" ]]; then
	Clean
elif [[ $1 == "lib" ]]; then
	buildSystem="lib"
	Lib
	Run
elif [[ $1 == "Playground" ]]; then
	buildSystem="Playground"
	Playground
elif [[ $1 == "juice" ]]; then
	buildSystem="juice"
    juice
	Run
elif [[ $1 == "Perf" ]]; then
	buildSystem="SQ"
	SQ
	perftool
fi
