echo off
  echo --------------------------------------------
  echo Compiling 2025 ruleset...
BEMCompiler25.exe --sharedPath1="../Com/Rules64/src/shared/" --bemBaseTxt="../Com/Rules64/src/BEMBase-SFam.txt" --bemEnumsTxt="../Com/Rules64/src/T24SFam/CAR25 BEMEnums.txt" --bemBaseBin="../Com/Rules64/CA Res 2025/CAR25 BEMBase.bin" --rulesTxt="../Com/Rules64/src/T24SFam/Rules-2025.txt" --rulesBin="../Com/Rules64/CA Res 2025.bin" --rulesLog="../Com/Rules64/src/Rules-SFam-2025 Log.out" --compileDM --compileRules
echo BEMCompiler25.exe returned (%ERRORLEVEL%) for CA Res 2025
if %ERRORLEVEL%==0 goto :copyfiles2
goto :error2
:copyfiles2
copy "..\Com\Rules64\src\T24SFam\CAR25 Screens.txt"  "..\Com\Rules64\CA Res 2025\*.*"
copy "..\Com\Rules64\src\T24SFam\T24R ToolTips.txt" "..\Com\Rules64\CA Res 2025\CAR25 ToolTips.txt"
rem copy "..\Com\Rules64\src\RTF\*.*" "..\Com\Rules64\CA Res 2022\RTF\*.*"
copy "..\Com\Rules64\src\shared\*.jpg" "..\Com\Rules64\CA Res 2025\*.*"
copy "..\Com\Rules64\src\shared\*.png" "..\Com\Rules64\CA Res 2025\*.*"
rem copy "..\Com\Rules64\src\DHWDU2.txt" "CSE\*.*"
goto :finalDone
:error2
  echo --------------------------------------------
  echo Rule compilation errors occurred.
  echo See log file for details:  ../Com/Rules64/src/Rules-SFam-2025 Log.out
  echo --------------------------------------------
  pause
:finalDone
