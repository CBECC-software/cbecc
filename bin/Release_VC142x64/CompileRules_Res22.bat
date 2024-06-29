echo off
  echo --------------------------------------------
  echo Compiling 2022 ruleset...
BEMCompiler22r.exe --bemBaseTxt="../Res/Rules/src/CAR13 BEMBase.txt" --bemEnumsTxt="../Res/Rules/src/CAR22 BEMEnums.txt" --bemBaseBin="../Res/Rules/CA Res 2022/CAR22 BEMBase.bin" --rulesTxt="../Res/Rules/src/Rules/Rules-2022.txt" --rulesBin="../Res/Rules/CA Res 2022.bin" --rulesLog="../Res/Rules/src/Rules/Rules-2022 Log.out" --compileDM --compileRules
echo BEMCompiler19r.exe returned (%ERRORLEVEL%) for CA Res 2022
if %ERRORLEVEL%==0 goto :copyfiles2
goto :error2
:copyfiles2
copy "..\Res\Rules\src\CAR22 Screens.txt"  "..\Res\Rules\CA Res 2022\*.*"
copy "..\Res\Rules\src\CAR13 ToolTips.txt" "..\Res\Rules\CA Res 2022\CAR22 ToolTips.txt"
rem copy "..\Res\Rules\src\RTF\*.*" "..\Res\Rules\CA Res 2022\RTF\*.*"
rem copy "..\Res\Rules\src\DHWDU2.txt" "CSE\*.*"
goto :finalDone
:error2
  echo --------------------------------------------
  echo Rule compilation errors occurred.
  echo See log file for details:  RulesetDev/Rulesets/CA Res/Rules/Rules-2022 Log.out
  echo --------------------------------------------
  pause
:finalDone
