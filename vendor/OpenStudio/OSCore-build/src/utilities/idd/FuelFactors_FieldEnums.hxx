/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

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
ExistingFuelResourceName, UnitsofMeasure, EnergyperUnitFactor, SourceEnergyFactor, SourceEnergyScheduleName, CO2EmissionFactor, CO2EmissionFactorScheduleName, COEmissionFactor, COEmissionFactorScheduleName, CH4EmissionFactor, CH4EmissionFactorScheduleName, NOxEmissionFactor, NOxEmissionFactorScheduleName, N2OEmissionFactor, N2OEmissionFactorScheduleName, SO2EmissionFactor, SO2EmissionFactorScheduleName, PMEmissionFactor, PMEmissionFactorScheduleName, PM10EmissionFactor, PM10EmissionFactorScheduleName, PM25EmissionFactor, PM25EmissionFactorScheduleName, NH3EmissionFactor, NH3EmissionFactorScheduleName, NMVOCEmissionFactor, NMVOCEmissionFactorScheduleName, HgEmissionFactor, HgEmissionFactorScheduleName, PbEmissionFactor, PbEmissionFactorScheduleName, WaterEmissionFactor, WaterEmissionFactorScheduleName, NuclearHighLevelEmissionFactor, NuclearHighLevelEmissionFactorScheduleName, NuclearLowLevelEmissionFactor, NuclearLowLevelEmissionFactorScheduleName,   };
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
{ FuelFactorsFields::UnitsofMeasure, "UnitsofMeasure", "Units of Measure"},
{ FuelFactorsFields::EnergyperUnitFactor, "EnergyperUnitFactor", "Energy per Unit Factor"},
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
