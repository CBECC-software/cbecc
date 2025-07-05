/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_COOLINGTOWERPERFORMANCE_COOLTOOLS_FIELDENUMS_HXX
#define UTILITIES_IDD_COOLINGTOWERPERFORMANCE_COOLTOOLS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CoolingTowerPerformance_CoolToolsFields
 *  \brief Enumeration of CoolingTowerPerformance:CoolTools's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CoolingTowerPerformance_CoolToolsFields, )
#else
class CoolingTowerPerformance_CoolToolsFields: public ::EnumBase<CoolingTowerPerformance_CoolToolsFields> {
 public: 
  enum domain 
  {
Name, MinimumInletAirWetBulbTemperature, MaximumInletAirWetBulbTemperature, MinimumRangeTemperature, MaximumRangeTemperature, MinimumApproachTemperature, MaximumApproachTemperature, MinimumWaterFlowRateRatio, MaximumWaterFlowRateRatio, Coefficient1, Coefficient2, Coefficient3, Coefficient4, Coefficient5, Coefficient6, Coefficient7, Coefficient8, Coefficient9, Coefficient10, Coefficient11, Coefficient12, Coefficient13, Coefficient14, Coefficient15, Coefficient16, Coefficient17, Coefficient18, Coefficient19, Coefficient20, Coefficient21, Coefficient22, Coefficient23, Coefficient24, Coefficient25, Coefficient26, Coefficient27, Coefficient28, Coefficient29, Coefficient30, Coefficient31, Coefficient32, Coefficient33, Coefficient34, Coefficient35,   };
  CoolingTowerPerformance_CoolToolsFields()
   : EnumBase<CoolingTowerPerformance_CoolToolsFields>(Name) {} 
  CoolingTowerPerformance_CoolToolsFields(const std::string &t_name) 
   : EnumBase<CoolingTowerPerformance_CoolToolsFields>(t_name) {} 
  CoolingTowerPerformance_CoolToolsFields(int t_value) 
   : EnumBase<CoolingTowerPerformance_CoolToolsFields>(t_value) {} 
  static std::string enumName() 
  { return "CoolingTowerPerformance_CoolToolsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CoolingTowerPerformance_CoolToolsFields>::value()); }
   private:
    friend class EnumBase<CoolingTowerPerformance_CoolToolsFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ CoolingTowerPerformance_CoolToolsFields::Name, "Name", "Name"},
{ CoolingTowerPerformance_CoolToolsFields::MinimumInletAirWetBulbTemperature, "MinimumInletAirWetBulbTemperature", "Minimum Inlet Air Wet-Bulb Temperature"},
{ CoolingTowerPerformance_CoolToolsFields::MaximumInletAirWetBulbTemperature, "MaximumInletAirWetBulbTemperature", "Maximum Inlet Air Wet-Bulb Temperature"},
{ CoolingTowerPerformance_CoolToolsFields::MinimumRangeTemperature, "MinimumRangeTemperature", "Minimum Range Temperature"},
{ CoolingTowerPerformance_CoolToolsFields::MaximumRangeTemperature, "MaximumRangeTemperature", "Maximum Range Temperature"},
{ CoolingTowerPerformance_CoolToolsFields::MinimumApproachTemperature, "MinimumApproachTemperature", "Minimum Approach Temperature"},
{ CoolingTowerPerformance_CoolToolsFields::MaximumApproachTemperature, "MaximumApproachTemperature", "Maximum Approach Temperature"},
{ CoolingTowerPerformance_CoolToolsFields::MinimumWaterFlowRateRatio, "MinimumWaterFlowRateRatio", "Minimum Water Flow Rate Ratio"},
{ CoolingTowerPerformance_CoolToolsFields::MaximumWaterFlowRateRatio, "MaximumWaterFlowRateRatio", "Maximum Water Flow Rate Ratio"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient1, "Coefficient1", "Coefficient 1"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient2, "Coefficient2", "Coefficient 2"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient3, "Coefficient3", "Coefficient 3"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient4, "Coefficient4", "Coefficient 4"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient5, "Coefficient5", "Coefficient 5"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient6, "Coefficient6", "Coefficient 6"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient7, "Coefficient7", "Coefficient 7"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient8, "Coefficient8", "Coefficient 8"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient9, "Coefficient9", "Coefficient 9"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient10, "Coefficient10", "Coefficient 10"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient11, "Coefficient11", "Coefficient 11"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient12, "Coefficient12", "Coefficient 12"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient13, "Coefficient13", "Coefficient 13"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient14, "Coefficient14", "Coefficient 14"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient15, "Coefficient15", "Coefficient 15"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient16, "Coefficient16", "Coefficient 16"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient17, "Coefficient17", "Coefficient 17"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient18, "Coefficient18", "Coefficient 18"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient19, "Coefficient19", "Coefficient 19"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient20, "Coefficient20", "Coefficient 20"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient21, "Coefficient21", "Coefficient 21"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient22, "Coefficient22", "Coefficient 22"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient23, "Coefficient23", "Coefficient 23"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient24, "Coefficient24", "Coefficient 24"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient25, "Coefficient25", "Coefficient 25"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient26, "Coefficient26", "Coefficient 26"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient27, "Coefficient27", "Coefficient 27"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient28, "Coefficient28", "Coefficient 28"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient29, "Coefficient29", "Coefficient 29"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient30, "Coefficient30", "Coefficient 30"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient31, "Coefficient31", "Coefficient 31"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient32, "Coefficient32", "Coefficient 32"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient33, "Coefficient33", "Coefficient 33"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient34, "Coefficient34", "Coefficient 34"},
{ CoolingTowerPerformance_CoolToolsFields::Coefficient35, "Coefficient35", "Coefficient 35"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const CoolingTowerPerformance_CoolToolsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CoolingTowerPerformance_CoolToolsFields> OptionalCoolingTowerPerformance_CoolToolsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COOLINGTOWERPERFORMANCE_COOLTOOLS_FIELDENUMS_HXX
