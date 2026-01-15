tsu build-cpp "g++" "src" "xarch-origin-x64.xwm_img" "-std=c++17 -O0 -Iinclude -Wall" "-shared -fPIC" ; if ($LASTEXITCODE -eq 0) { xwm load .\build\xarch-origin-x64.xwm_img }
