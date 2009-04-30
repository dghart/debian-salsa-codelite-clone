@echo off

xcopy config\*.default "%ProgramFiles%\CodeLite\config\" /E /I /H /Y /EXCLUDE:excludes
xcopy config\build_settings.xml.default.win "%ProgramFiles%\CodeLite\config\build_settings.xml.default" /E /I /H /Y /EXCLUDE:excludes
xcopy debuggers\*.dll "%ProgramFiles%\CodeLite\debuggers\" /E /I /H /Y /EXCLUDE:excludes
xcopy images\* "%ProgramFiles%\CodeLite\images\" /E /I /H /Y /EXCLUDE:excludes
xcopy lexers\*.xml "%ProgramFiles%\CodeLite\lexers\" /E /I /H /Y /EXCLUDE:excludes
xcopy plugins\*.dll "%ProgramFiles%\CodeLite\plugins\" /E /I /H /Y /EXCLUDE:excludes
xcopy plugins\resources\*.* "%ProgramFiles%\CodeLite\plugins\resources\" /E /I /H /Y /EXCLUDE:excludes
xcopy rc\*.xrc "%ProgramFiles%\CodeLite\rc\" /E /I /H /Y /EXCLUDE:excludes
xcopy templates\ "%ProgramFiles%\CodeLite\templates\" /E /I /H /Y /EXCLUDE:excludes
xcopy templates\formbuilder\* "%ProgramFiles%\CodeLite\templates\formbuilder\" /E /I /H /Y /EXCLUDE:excludes
xcopy *.html "%ProgramFiles%\CodeLite\" /H /Y /EXCLUDE:excludes
:: Copy the misc files
copy codelite_indexer.exe "%ProgramFiles%\CodeLite\" /Y
copy makedir.exe "%ProgramFiles%\CodeLite\" /Y
copy le_exec.exe "%ProgramFiles%\CodeLite\" /Y
copy CodeLite.exe "%ProgramFiles%\CodeLite\" /Y
copy patch.exe "%ProgramFiles%\CodeLite\" /Y
copy astyle.sample "%ProgramFiles%\CodeLite\" /Y
copy ..\sdk\wxconfig\wx-config.exe "%ProgramFiles%\CodeLite\" /Y
copy ..\sdk\curl\lib\libcurl-4.dll "%ProgramFiles%\CodeLite\" /Y
copy ..\sdk\curl\lib\libcurl-4.dll . /Y