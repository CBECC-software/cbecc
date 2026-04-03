echo off
  echo --------------------------------------------
  echo Compiling 2025 ruleset...
BEMCompiler25.exe --sharedPath1="../Com/Rules64/src/shared/" --bemBaseTxt="../Com/Rules64/src/BEMBase.txt" --bemEnumsTxt="../Com/Rules64/src/T24NRMF/T24N_2025 BEMEnums.txt" --bemBaseBin="../Com/Rules64/T24_2025/T24_2025 BEMBase.bin" --rulesTxt="../Com/Rules64/src/T24NRMF/T24N_2025.txt" --rulesBin="../Com/Rules64/T24_2025.bin" --rulesLog="../Com/Rules64/src/T24-2025 Rules Log.out" --compileDM --compileRules
echo OFF
echo BEMCompiler25.exe returned (%ERRORLEVEL%) for T24N_2025
if %ERRORLEVEL%==0 goto :copyfiles
goto :error
:copyfiles
copy "..\Com\Rules64\src\T24NRMF\T24N_2025 Screens.txt"  "..\Com\Rules64\T24_2025\T24_2025 Screens.txt"
copy "..\Com\Rules64\src\T24NRMF\T24N ToolTips.txt" "..\Com\Rules64\T24_2025\T24_2025 ToolTips.txt"
copy "..\Com\Rules64\src\T24NRMF\*.jpg" "..\Com\Rules64\T24_2025\*.*"
rem copy "..\Com\Rules64\src\T24NRMF\RTF\*.*" "..\Com\Rules64\T24_2025\RTF\*.*"
copy "..\Com\Rules64\src\shared\Screens_Res_2025.txt" "..\Com\Rules64\T24_2025\*.*"
copy "..\Com\Rules64\src\shared\*.jpg" "..\Com\Rules64\T24_2025\*.*"
rem copy "..\RulesetDev\Rulesets\CEC 2013 Nonres\CEC 2013 NonRes Defaults.dbd" "..\CBECC-Com\Data\Rulesets\T24N_2022\T24N_2022 Defaults.dbd"
rem copy "..\RulesetDev\Rulesets\T24N\DHWDU2.txt" "..\CBECC-Com64\CSE\*.*"
goto :done
:error
echo -
echo ----------------------------------
echo --- Errors occurred.
echo --- For more information, review:
echo ---   ../Com/Rules64/src/T24-2025 Rules Log.out
echo ----------------------------------
echo -
  pause
:done
