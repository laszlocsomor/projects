del /q _outs\*
md _outs

cl.exe /c lib_a\a.cc /Fo_outs\a.obj
@if "%errorlevel%" neq "0" (echo FAILED >&2 & exit /b 1)

cl.exe /c lib_b\b.cc /Fo_outs\b.obj
@if "%errorlevel%" neq "0" (echo FAILED >&2 & exit /b 1)

cl.exe /c cc_app\main.cc /Fo_outs\main.obj
@if "%errorlevel%" neq "0" (echo FAILED >&2 & exit /b 1)

link.exe /OUT:_outs\a.dll /IMPLIB:_outs\a.lib /DLL /MACHINE:X64 _outs\a.obj
@if "%errorlevel%" neq "0" (echo FAILED >&2 & exit /b 1)

link.exe /OUT:_outs\b.dll /IMPLIB:_outs\b.lib /DLL /MACHINE:X64 _outs\b.obj _outs\a.lib
@if "%errorlevel%" neq "0" (echo FAILED >&2 & exit /b 1)

link.exe /OUT:_outs\main.exe /MACHINE:X64 _outs\main.obj _outs\b.lib _outs\a.lib
@if "%errorlevel%" neq "0" (echo FAILED >&2 & exit /b 1)

cl.exe /c lib_alice\alice.cc /Fo_outs\alice.obj /Ic:\python37\include
@if "%errorlevel%" neq "0" (echo FAILED >&2 & exit /b 1)

link.exe /OUT:_outs\alice.pyd /IMPLIB:_outs\alice.lib /DLL /MACHINE:X64 /LIBPATH:C:\python37\libs _outs\alice.obj _outs\b.lib
@if "%errorlevel%" neq "0" (echo FAILED >&2 & exit /b 1)

copy py_app\main.py _outs\main.py
