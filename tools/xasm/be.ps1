tsu build-cpp "g++" "src" "xasmc" "-std=c++17 -O0 -Iinclude -Wall" ; if ($LASTEXITCODE -eq 0) { .\build\xasmc .\test.xasm }
