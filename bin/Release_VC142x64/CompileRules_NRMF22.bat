echo off
  echo --------------------------------------------
  echo Compiling 2022 ruleset...
BEMCompiler22c.exe --sharedPath1="../Com/Rules64/src/shared/" --bemBaseTxt="../Com/Rules64/src/BEMBase.txt" --bemEnumsTxt="../Com/Rules64/src/T24N_2022 BEMEnums.txt" --bemBaseBin="../Com/Rules64/T24N_2022/T24N_2022 BEMBase.bin" --rulesTxt="../Com/Rules64/src/Rules/T24N_2022.txt" --rulesBin="../Com/Rules64/T24N_2022.bin" --rulesLog="../Com/Rules64/src/Rules/T24N-2022 Rules Log.out" --compileDM --compileRules
echo OFF
echo BEMCompiler22c.exe returned (%ERRORLEVEL%) for T24N_2022
if %ERRORLEVEL%==0 goto :copyfiles
goto :error
:copyfiles
copy "..\Com\Rules64\src\T24N_2022 Screens.txt"  "..\Com\Rules64\T24N_2022\T24N_2022 Screens.txt"
copy "..\Com\Rules64\src\T24N ToolTips.txt" "..\Com\Rules64\T24N_2022\T24N_2022 ToolTips.txt"
copy "..\Com\Rules64\src\*.jpg" "..\Com\Rules64\T24N_2022\*.*"
rem copy "..\Com\Rules64\src\RTF\*.*" "..\Com\Rules64\T24N_2022\RTF\*.*"
copy "..\Com\Rules64\src\shared\Screens*.txt" "..\Com\Rules64\T24N_2022\*.*"
copy "..\Com\Rules64\src\shared\*.jpg" "..\Com\Rules64\T24N_2022\*.*"
rem copy "..\RulesetDev\Rulesets\CEC 2013 Nonres\CEC 2013 NonRes Defaults.dbd" "..\CBECC-Com\Data\Rulesets\T24N_2022\T24N_2022 Defaults.dbd"
rem copy "..\RulesetDev\Rulesets\T24N\DHWDU2.txt" "..\CBECC-Com64\CSE\*.*"
goto :done
:error
echo -
echo ----------------------------------
echo --- Errors occurred.
echo --- For more information, review:
echo ---   ../Com/Rules64/src/Rules/T24N-2022 Rules Log.out
echo ----------------------------------
echo -
  pause
:done
