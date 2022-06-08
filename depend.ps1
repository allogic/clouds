# PATHS
$bin_dir = (Join-Path $PSScriptRoot "\bin\");
$glad_dir = (Join-Path $PSScriptRoot "\glad\")
$glfw_dir = (Join-Path $PSScriptRoot "\glfw\")
$cglm_dir = (Join-Path $PSScriptRoot "\cglm\")
$openal_dir = (Join-Path $PSScriptRoot "\openal\")
$alut_dir = (Join-Path $PSScriptRoot "\alut\")

# BIN
New-Item -ItemType Directory -Force -Path $bin_dir

# GLAD
if (Test-Path -Path $glad_dir) { Remove-Item $glad_dir -Recurse -Force }
git clone "https://github.com/allogic/glad"

# GLFW
if (Test-Path -Path $glfw_dir) { Remove-Item $glfw_dir -Recurse -Force }
git clone "https://github.com/allogic/glfw"
cd glfw
cmake -DBUILD_SHARED_LIBS=ON
cmake -DGLFW_BUILD_EXAMPLES=OFF
cmake -DGLFW_BUILD_TESTS=OFF
cmake -DGLFW_BUILD_DOCS=OFF
cmake -DGLFW_INSTALL=OFF
cmake -G "Visual Studio 17" .
. "C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MsBuild.exe" GLFW.sln /property:Configuration=MinSizeRel
Copy-Item (Join-Path $glfw_dir "\src\MinSizeRel\glfw3dll.lib") (Join-Path $bin_dir "\glfw.lib") -Force
Copy-Item (Join-Path $glfw_dir "\src\MinSizeRel\glfw3.dll") (Join-Path $bin_dir "\glfw.dll") -Force
cd ..

# CGLM
if (Test-Path -Path $cglm_dir) { Remove-Item $cglm_dir -Recurse -Force }
git clone "https://github.com/allogic/cglm"
cd cglm
cmake -DCGLM_SHARED=ON
cmake -DCGLM_STATIC=OFF
cmake -DCGLM_USE_C99=OFF
cmake -DCGLM_USE_TEST=OFF
cmake -G "Visual Studio 17" .
. "C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MsBuild.exe" cglm.sln /property:Configuration=MinSizeRel
Copy-Item (Join-Path $cglm_dir "\MinSizeRel\cglm.lib") (Join-Path $bin_dir "\cglm.lib") -Force
Copy-Item (Join-Path $cglm_dir "\MinSizeRel\cglm-0.dll") (Join-Path $bin_dir "\cglm.dll") -Force
cd ..

# OPENAL
if (Test-Path -Path $openal_dir) { Remove-Item $openal_dir -Recurse -Force }
git clone "https://github.com/allogic/openal"
cd openal
cmake -DALSOFT_INSTALL=OFF
cmake -DALSOFT_EXAMPLES=OFF
cmake -DALSOFT_UTILS=OFF
cmake -DALSOFT_UPDATE_BUILD_VERSION=OFF
cmake -G "Visual Studio 17" .
. "C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MsBuild.exe" OpenAL.sln /property:Configuration=MinSizeRel
Copy-Item (Join-Path $openal_dir "\MinSizeRel\OpenAL32.lib") (Join-Path $bin_dir "\openal.lib") -Force
Copy-Item (Join-Path $openal_dir "\MinSizeRel\OpenAL32.dll") (Join-Path $bin_dir "\openal.dll") -Force
cd ..

# ALUT
if (Test-Path -Path $alut_dir) { Remove-Item $alut_dir -Recurse -Force }
git clone "https://github.com/allogic/alut"