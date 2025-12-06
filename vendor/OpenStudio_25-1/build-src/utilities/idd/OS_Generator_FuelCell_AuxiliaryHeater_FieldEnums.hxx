/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_GENERATOR_FUELCELL_AUXILIARYHEATER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_FUELCELL_AUXILIARYHEATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_FuelCell_AuxiliaryHeaterFields
 *  \brief Enumeration of OS:Generator:FuelCell:AuxiliaryHeater's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_FuelCell_AuxiliaryHeaterFields, )
#else
class OS_Generator_FuelCell_AuxiliaryHeaterFields: public ::EnumBase<OS_Generator_FuelCell_AuxiliaryHeaterFields> {
 public: 
  enum domain 
  {
Handle, Name, ExcessAirRatio, AncillaryPowerConstantTerm, AncillaryPowerLinearTerm, SkinLossUFactorTimesAreaValue, SkinLossDestination, ZoneNametoReceiveSkinLosses, HeatingCapacityUnits, MaximumHeatingCapacityinWatts, MinimumHeatingCapacityinWatts, MaximumHeatingCapacityinKmolperSecond, MinimumHeatingCapacityinKmolperSecond,   };
  OS_Generator_FuelCell_AuxiliaryHeaterFields()
   : EnumBase<OS_Generator_FuelCell_AuxiliaryHeaterFields>(Handle) {} 
  OS_Generator_FuelCell_AuxiliaryHeaterFields(const std::string &t_name) 
   : EnumBase<OS_Generator_FuelCell_AuxiliaryHeaterFields>(t_name) {} 
  OS_Generator_FuelCell_AuxiliaryHeaterFields(int t_value) 
   : EnumBase<OS_Generator_FuelCell_AuxiliaryHeaterFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_FuelCell_AuxiliaryHeaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_FuelCell_AuxiliaryHeaterFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Generator_FuelCell_AuxiliaryHeaterFields>;
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
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::Handle, "Handle", "Handle"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::Name, "Name", "Name"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::ExcessAirRatio, "ExcessAirRatio", "Excess Air Ratio"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::AncillaryPowerConstantTerm, "AncillaryPowerConstantTerm", "Ancillary Power Constant Term"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::AncillaryPowerLinearTerm, "AncillaryPowerLinearTerm", "Ancillary Power Linear Term"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::SkinLossUFactorTimesAreaValue, "SkinLossUFactorTimesAreaValue", "Skin Loss U-Factor Times Area Value"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::SkinLossDestination, "SkinLossDestination", "Skin Loss Destination"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::ZoneNametoReceiveSkinLosses, "ZoneNametoReceiveSkinLosses", "Zone Name to Receive Skin Losses"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::HeatingCapacityUnits, "HeatingCapacityUnits", "Heating Capacity Units"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::MaximumHeatingCapacityinWatts, "MaximumHeatingCapacityinWatts", "Maximum Heating Capacity in Watts"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::MinimumHeatingCapacityinWatts, "MinimumHeatingCapacityinWatts", "Minimum Heating Capacity in Watts"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::MaximumHeatingCapacityinKmolperSecond, "MaximumHeatingCapacityinKmolperSecond", "Maximum Heating Capacity in Kmol per Second"},
{ OS_Generator_FuelCell_AuxiliaryHeaterFields::MinimumHeatingCapacityinKmolperSecond, "MinimumHeatingCapacityinKmolperSecond", "Minimum Heating Capacity in Kmol per Second"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_FuelCell_AuxiliaryHeaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_FuelCell_AuxiliaryHeaterFields> OptionalOS_Generator_FuelCell_AuxiliaryHeaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_FUELCELL_AUXILIARYHEATER_FIELDENUMS_HXX
