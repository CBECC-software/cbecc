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

#ifndef UTILITIES_IDD_GENERATOR_WINDTURBINE_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_WINDTURBINE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_WindTurbineFields
 *  \brief Enumeration of Generator:WindTurbine's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_WindTurbineFields, )
#else
class Generator_WindTurbineFields: public ::EnumBase<Generator_WindTurbineFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, RotorType, PowerControl, RatedRotorSpeed, RotorDiameter, OverallHeight, NumberofBlades, RatedPower, RatedWindSpeed, CutInWindSpeed, CutOutWindSpeed, FractionsystemEfficiency, MaximumTipSpeedRatio, MaximumPowerCoefficient, AnnualLocalAverageWindSpeed, HeightforLocalAverageWindSpeed, BladeChordArea, BladeDragCoefficient, BladeLiftCoefficient, PowerCoefficientC1, PowerCoefficientC2, PowerCoefficientC3, PowerCoefficientC4, PowerCoefficientC5, PowerCoefficientC6,   };
  Generator_WindTurbineFields()
   : EnumBase<Generator_WindTurbineFields>(Name) {} 
  Generator_WindTurbineFields(const std::string &t_name) 
   : EnumBase<Generator_WindTurbineFields>(t_name) {} 
  Generator_WindTurbineFields(int t_value) 
   : EnumBase<Generator_WindTurbineFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_WindTurbineFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_WindTurbineFields>::value()); }
   private:
    friend class EnumBase<Generator_WindTurbineFields>;
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
{ Generator_WindTurbineFields::Name, "Name", "Name"},
{ Generator_WindTurbineFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Generator_WindTurbineFields::RotorType, "RotorType", "Rotor Type"},
{ Generator_WindTurbineFields::PowerControl, "PowerControl", "Power Control"},
{ Generator_WindTurbineFields::RatedRotorSpeed, "RatedRotorSpeed", "Rated Rotor Speed"},
{ Generator_WindTurbineFields::RotorDiameter, "RotorDiameter", "Rotor Diameter"},
{ Generator_WindTurbineFields::OverallHeight, "OverallHeight", "Overall Height"},
{ Generator_WindTurbineFields::NumberofBlades, "NumberofBlades", "Number of Blades"},
{ Generator_WindTurbineFields::RatedPower, "RatedPower", "Rated Power"},
{ Generator_WindTurbineFields::RatedWindSpeed, "RatedWindSpeed", "Rated Wind Speed"},
{ Generator_WindTurbineFields::CutInWindSpeed, "CutInWindSpeed", "Cut In Wind Speed"},
{ Generator_WindTurbineFields::CutOutWindSpeed, "CutOutWindSpeed", "Cut Out Wind Speed"},
{ Generator_WindTurbineFields::FractionsystemEfficiency, "FractionsystemEfficiency", "Fraction system Efficiency"},
{ Generator_WindTurbineFields::MaximumTipSpeedRatio, "MaximumTipSpeedRatio", "Maximum Tip Speed Ratio"},
{ Generator_WindTurbineFields::MaximumPowerCoefficient, "MaximumPowerCoefficient", "Maximum Power Coefficient"},
{ Generator_WindTurbineFields::AnnualLocalAverageWindSpeed, "AnnualLocalAverageWindSpeed", "Annual Local Average Wind Speed"},
{ Generator_WindTurbineFields::HeightforLocalAverageWindSpeed, "HeightforLocalAverageWindSpeed", "Height for Local Average Wind Speed"},
{ Generator_WindTurbineFields::BladeChordArea, "BladeChordArea", "Blade Chord Area"},
{ Generator_WindTurbineFields::BladeDragCoefficient, "BladeDragCoefficient", "Blade Drag Coefficient"},
{ Generator_WindTurbineFields::BladeLiftCoefficient, "BladeLiftCoefficient", "Blade Lift Coefficient"},
{ Generator_WindTurbineFields::PowerCoefficientC1, "PowerCoefficientC1", "Power Coefficient C1"},
{ Generator_WindTurbineFields::PowerCoefficientC2, "PowerCoefficientC2", "Power Coefficient C2"},
{ Generator_WindTurbineFields::PowerCoefficientC3, "PowerCoefficientC3", "Power Coefficient C3"},
{ Generator_WindTurbineFields::PowerCoefficientC4, "PowerCoefficientC4", "Power Coefficient C4"},
{ Generator_WindTurbineFields::PowerCoefficientC5, "PowerCoefficientC5", "Power Coefficient C5"},
{ Generator_WindTurbineFields::PowerCoefficientC6, "PowerCoefficientC6", "Power Coefficient C6"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_WindTurbineFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_WindTurbineFields> OptionalGenerator_WindTurbineFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_WINDTURBINE_FIELDENUMS_HXX
