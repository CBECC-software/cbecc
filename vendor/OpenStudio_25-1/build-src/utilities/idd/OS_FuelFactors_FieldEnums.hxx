/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_FUELFACTORS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_FUELFACTORS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_FuelFactorsFields
 *  \brief Enumeration of OS:FuelFactors's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_FuelFactorsFields, )
#else
class OS_FuelFactorsFields: public ::EnumBase<OS_FuelFactorsFields> {
 public: 
  enum domain 
  {
Handle, ExistingFuelResourceName, SourceEnergyFactor, SourceEnergyScheduleName, CO2EmissionFactor, CO2EmissionFactorScheduleName, COEmissionFactor, COEmissionFactorScheduleName, CH4EmissionFactor, CH4EmissionFactorScheduleName, NOxEmissionFactor, NOxEmissionFactorScheduleName, N2OEmissionFactor, N2OEmissionFactorScheduleName, SO2EmissionFactor, SO2EmissionFactorScheduleName, PMEmissionFactor, PMEmissionFactorScheduleName, PM10EmissionFactor, PM10EmissionFactorScheduleName, PM25EmissionFactor, PM25EmissionFactorScheduleName, NH3EmissionFactor, NH3EmissionFactorScheduleName, NMVOCEmissionFactor, NMVOCEmissionFactorScheduleName, HgEmissionFactor, HgEmissionFactorScheduleName, PbEmissionFactor, PbEmissionFactorScheduleName, WaterEmissionFactor, WaterEmissionFactorScheduleName, NuclearHighLevelEmissionFactor, NuclearHighLevelEmissionFactorScheduleName, NuclearLowLevelEmissionFactor, NuclearLowLevelEmissionFactorScheduleName,   };
  OS_FuelFactorsFields()
   : EnumBase<OS_FuelFactorsFields>(Handle) {} 
  OS_FuelFactorsFields(const std::string &t_name) 
   : EnumBase<OS_FuelFactorsFields>(t_name) {} 
  OS_FuelFactorsFields(int t_value) 
   : EnumBase<OS_FuelFactorsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_FuelFactorsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_FuelFactorsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_FuelFactorsFields>;
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
{ OS_FuelFactorsFields::Handle, "Handle", "Handle"},
{ OS_FuelFactorsFields::ExistingFuelResourceName, "ExistingFuelResourceName", "Existing Fuel Resource Name"},
{ OS_FuelFactorsFields::SourceEnergyFactor, "SourceEnergyFactor", "Source Energy Factor"},
{ OS_FuelFactorsFields::SourceEnergyScheduleName, "SourceEnergyScheduleName", "Source Energy Schedule Name"},
{ OS_FuelFactorsFields::CO2EmissionFactor, "CO2EmissionFactor", "CO2 Emission Factor"},
{ OS_FuelFactorsFields::CO2EmissionFactorScheduleName, "CO2EmissionFactorScheduleName", "CO2 Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::COEmissionFactor, "COEmissionFactor", "CO Emission Factor"},
{ OS_FuelFactorsFields::COEmissionFactorScheduleName, "COEmissionFactorScheduleName", "CO Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::CH4EmissionFactor, "CH4EmissionFactor", "CH4 Emission Factor"},
{ OS_FuelFactorsFields::CH4EmissionFactorScheduleName, "CH4EmissionFactorScheduleName", "CH4 Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::NOxEmissionFactor, "NOxEmissionFactor", "NOx Emission Factor"},
{ OS_FuelFactorsFields::NOxEmissionFactorScheduleName, "NOxEmissionFactorScheduleName", "NOx Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::N2OEmissionFactor, "N2OEmissionFactor", "N2O Emission Factor"},
{ OS_FuelFactorsFields::N2OEmissionFactorScheduleName, "N2OEmissionFactorScheduleName", "N2O Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::SO2EmissionFactor, "SO2EmissionFactor", "SO2 Emission Factor"},
{ OS_FuelFactorsFields::SO2EmissionFactorScheduleName, "SO2EmissionFactorScheduleName", "SO2 Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::PMEmissionFactor, "PMEmissionFactor", "PM Emission Factor"},
{ OS_FuelFactorsFields::PMEmissionFactorScheduleName, "PMEmissionFactorScheduleName", "PM Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::PM10EmissionFactor, "PM10EmissionFactor", "PM10 Emission Factor"},
{ OS_FuelFactorsFields::PM10EmissionFactorScheduleName, "PM10EmissionFactorScheduleName", "PM10 Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::PM25EmissionFactor, "PM25EmissionFactor", "PM2.5 Emission Factor"},
{ OS_FuelFactorsFields::PM25EmissionFactorScheduleName, "PM25EmissionFactorScheduleName", "PM2.5 Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::NH3EmissionFactor, "NH3EmissionFactor", "NH3 Emission Factor"},
{ OS_FuelFactorsFields::NH3EmissionFactorScheduleName, "NH3EmissionFactorScheduleName", "NH3 Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::NMVOCEmissionFactor, "NMVOCEmissionFactor", "NMVOC Emission Factor"},
{ OS_FuelFactorsFields::NMVOCEmissionFactorScheduleName, "NMVOCEmissionFactorScheduleName", "NMVOC Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::HgEmissionFactor, "HgEmissionFactor", "Hg Emission Factor"},
{ OS_FuelFactorsFields::HgEmissionFactorScheduleName, "HgEmissionFactorScheduleName", "Hg Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::PbEmissionFactor, "PbEmissionFactor", "Pb Emission Factor"},
{ OS_FuelFactorsFields::PbEmissionFactorScheduleName, "PbEmissionFactorScheduleName", "Pb Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::WaterEmissionFactor, "WaterEmissionFactor", "Water Emission Factor"},
{ OS_FuelFactorsFields::WaterEmissionFactorScheduleName, "WaterEmissionFactorScheduleName", "Water Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::NuclearHighLevelEmissionFactor, "NuclearHighLevelEmissionFactor", "Nuclear High Level Emission Factor"},
{ OS_FuelFactorsFields::NuclearHighLevelEmissionFactorScheduleName, "NuclearHighLevelEmissionFactorScheduleName", "Nuclear High Level Emission Factor Schedule Name"},
{ OS_FuelFactorsFields::NuclearLowLevelEmissionFactor, "NuclearLowLevelEmissionFactor", "Nuclear Low Level Emission Factor"},
{ OS_FuelFactorsFields::NuclearLowLevelEmissionFactorScheduleName, "NuclearLowLevelEmissionFactorScheduleName", "Nuclear Low Level Emission Factor Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_FuelFactorsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_FuelFactorsFields> OptionalOS_FuelFactorsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_FUELFACTORS_FIELDENUMS_HXX
