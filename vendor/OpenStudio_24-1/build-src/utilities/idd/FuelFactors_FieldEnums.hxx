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

#ifndef UTILITIES_IDD_FUELFACTORS_FIELDENUMS_HXX
#define UTILITIES_IDD_FUELFACTORS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FuelFactorsFields
 *  \brief Enumeration of FuelFactors's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FuelFactorsFields, )
#else
class FuelFactorsFields: public ::EnumBase<FuelFactorsFields> {
 public: 
  enum domain 
  {
ExistingFuelResourceName, SourceEnergyFactor, SourceEnergyScheduleName, CO2EmissionFactor, CO2EmissionFactorScheduleName, COEmissionFactor, COEmissionFactorScheduleName, CH4EmissionFactor, CH4EmissionFactorScheduleName, NOxEmissionFactor, NOxEmissionFactorScheduleName, N2OEmissionFactor, N2OEmissionFactorScheduleName, SO2EmissionFactor, SO2EmissionFactorScheduleName, PMEmissionFactor, PMEmissionFactorScheduleName, PM10EmissionFactor, PM10EmissionFactorScheduleName, PM25EmissionFactor, PM25EmissionFactorScheduleName, NH3EmissionFactor, NH3EmissionFactorScheduleName, NMVOCEmissionFactor, NMVOCEmissionFactorScheduleName, HgEmissionFactor, HgEmissionFactorScheduleName, PbEmissionFactor, PbEmissionFactorScheduleName, WaterEmissionFactor, WaterEmissionFactorScheduleName, NuclearHighLevelEmissionFactor, NuclearHighLevelEmissionFactorScheduleName, NuclearLowLevelEmissionFactor, NuclearLowLevelEmissionFactorScheduleName,   };
  FuelFactorsFields()
   : EnumBase<FuelFactorsFields>(ExistingFuelResourceName) {} 
  FuelFactorsFields(const std::string &t_name) 
   : EnumBase<FuelFactorsFields>(t_name) {} 
  FuelFactorsFields(int t_value) 
   : EnumBase<FuelFactorsFields>(t_value) {} 
  static std::string enumName() 
  { return "FuelFactorsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FuelFactorsFields>::value()); }
   private:
    friend class EnumBase<FuelFactorsFields>;
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
{ FuelFactorsFields::ExistingFuelResourceName, "ExistingFuelResourceName", "Existing Fuel Resource Name"},
{ FuelFactorsFields::SourceEnergyFactor, "SourceEnergyFactor", "Source Energy Factor"},
{ FuelFactorsFields::SourceEnergyScheduleName, "SourceEnergyScheduleName", "Source Energy Schedule Name"},
{ FuelFactorsFields::CO2EmissionFactor, "CO2EmissionFactor", "CO2 Emission Factor"},
{ FuelFactorsFields::CO2EmissionFactorScheduleName, "CO2EmissionFactorScheduleName", "CO2 Emission Factor Schedule Name"},
{ FuelFactorsFields::COEmissionFactor, "COEmissionFactor", "CO Emission Factor"},
{ FuelFactorsFields::COEmissionFactorScheduleName, "COEmissionFactorScheduleName", "CO Emission Factor Schedule Name"},
{ FuelFactorsFields::CH4EmissionFactor, "CH4EmissionFactor", "CH4 Emission Factor"},
{ FuelFactorsFields::CH4EmissionFactorScheduleName, "CH4EmissionFactorScheduleName", "CH4 Emission Factor Schedule Name"},
{ FuelFactorsFields::NOxEmissionFactor, "NOxEmissionFactor", "NOx Emission Factor"},
{ FuelFactorsFields::NOxEmissionFactorScheduleName, "NOxEmissionFactorScheduleName", "NOx Emission Factor Schedule Name"},
{ FuelFactorsFields::N2OEmissionFactor, "N2OEmissionFactor", "N2O Emission Factor"},
{ FuelFactorsFields::N2OEmissionFactorScheduleName, "N2OEmissionFactorScheduleName", "N2O Emission Factor Schedule Name"},
{ FuelFactorsFields::SO2EmissionFactor, "SO2EmissionFactor", "SO2 Emission Factor"},
{ FuelFactorsFields::SO2EmissionFactorScheduleName, "SO2EmissionFactorScheduleName", "SO2 Emission Factor Schedule Name"},
{ FuelFactorsFields::PMEmissionFactor, "PMEmissionFactor", "PM Emission Factor"},
{ FuelFactorsFields::PMEmissionFactorScheduleName, "PMEmissionFactorScheduleName", "PM Emission Factor Schedule Name"},
{ FuelFactorsFields::PM10EmissionFactor, "PM10EmissionFactor", "PM10 Emission Factor"},
{ FuelFactorsFields::PM10EmissionFactorScheduleName, "PM10EmissionFactorScheduleName", "PM10 Emission Factor Schedule Name"},
{ FuelFactorsFields::PM25EmissionFactor, "PM25EmissionFactor", "PM2.5 Emission Factor"},
{ FuelFactorsFields::PM25EmissionFactorScheduleName, "PM25EmissionFactorScheduleName", "PM2.5 Emission Factor Schedule Name"},
{ FuelFactorsFields::NH3EmissionFactor, "NH3EmissionFactor", "NH3 Emission Factor"},
{ FuelFactorsFields::NH3EmissionFactorScheduleName, "NH3EmissionFactorScheduleName", "NH3 Emission Factor Schedule Name"},
{ FuelFactorsFields::NMVOCEmissionFactor, "NMVOCEmissionFactor", "NMVOC Emission Factor"},
{ FuelFactorsFields::NMVOCEmissionFactorScheduleName, "NMVOCEmissionFactorScheduleName", "NMVOC Emission Factor Schedule Name"},
{ FuelFactorsFields::HgEmissionFactor, "HgEmissionFactor", "Hg Emission Factor"},
{ FuelFactorsFields::HgEmissionFactorScheduleName, "HgEmissionFactorScheduleName", "Hg Emission Factor Schedule Name"},
{ FuelFactorsFields::PbEmissionFactor, "PbEmissionFactor", "Pb Emission Factor"},
{ FuelFactorsFields::PbEmissionFactorScheduleName, "PbEmissionFactorScheduleName", "Pb Emission Factor Schedule Name"},
{ FuelFactorsFields::WaterEmissionFactor, "WaterEmissionFactor", "Water Emission Factor"},
{ FuelFactorsFields::WaterEmissionFactorScheduleName, "WaterEmissionFactorScheduleName", "Water Emission Factor Schedule Name"},
{ FuelFactorsFields::NuclearHighLevelEmissionFactor, "NuclearHighLevelEmissionFactor", "Nuclear High Level Emission Factor"},
{ FuelFactorsFields::NuclearHighLevelEmissionFactorScheduleName, "NuclearHighLevelEmissionFactorScheduleName", "Nuclear High Level Emission Factor Schedule Name"},
{ FuelFactorsFields::NuclearLowLevelEmissionFactor, "NuclearLowLevelEmissionFactor", "Nuclear Low Level Emission Factor"},
{ FuelFactorsFields::NuclearLowLevelEmissionFactorScheduleName, "NuclearLowLevelEmissionFactorScheduleName", "Nuclear Low Level Emission Factor Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const FuelFactorsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FuelFactorsFields> OptionalFuelFactorsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FUELFACTORS_FIELDENUMS_HXX
