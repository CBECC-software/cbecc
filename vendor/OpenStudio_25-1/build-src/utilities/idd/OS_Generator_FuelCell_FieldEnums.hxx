/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_GENERATOR_FUELCELL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_FUELCELL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_FuelCellFields
 *  \brief Enumeration of OS:Generator:FuelCell's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_FuelCellFields, )
#else
class OS_Generator_FuelCellFields: public ::EnumBase<OS_Generator_FuelCellFields> {
 public: 
  enum domain 
  {
Handle, Name, PowerModuleName, AirSupplyName, FuelSupplyName, WaterSupplyName, AuxiliaryHeaterName, HeatExchangerName, ElectricalStorageName, InverterName, StackCoolerName,   };
  OS_Generator_FuelCellFields()
   : EnumBase<OS_Generator_FuelCellFields>(Handle) {} 
  OS_Generator_FuelCellFields(const std::string &t_name) 
   : EnumBase<OS_Generator_FuelCellFields>(t_name) {} 
  OS_Generator_FuelCellFields(int t_value) 
   : EnumBase<OS_Generator_FuelCellFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_FuelCellFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_FuelCellFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Generator_FuelCellFields>;
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
{ OS_Generator_FuelCellFields::Handle, "Handle", "Handle"},
{ OS_Generator_FuelCellFields::Name, "Name", "Name"},
{ OS_Generator_FuelCellFields::PowerModuleName, "PowerModuleName", "Power Module Name"},
{ OS_Generator_FuelCellFields::AirSupplyName, "AirSupplyName", "Air Supply Name"},
{ OS_Generator_FuelCellFields::FuelSupplyName, "FuelSupplyName", "Fuel Supply Name"},
{ OS_Generator_FuelCellFields::WaterSupplyName, "WaterSupplyName", "Water Supply Name"},
{ OS_Generator_FuelCellFields::AuxiliaryHeaterName, "AuxiliaryHeaterName", "Auxiliary Heater Name"},
{ OS_Generator_FuelCellFields::HeatExchangerName, "HeatExchangerName", "Heat Exchanger Name"},
{ OS_Generator_FuelCellFields::ElectricalStorageName, "ElectricalStorageName", "Electrical Storage Name"},
{ OS_Generator_FuelCellFields::InverterName, "InverterName", "Inverter Name"},
{ OS_Generator_FuelCellFields::StackCoolerName, "StackCoolerName", "Stack Cooler Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_FuelCellFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_FuelCellFields> OptionalOS_Generator_FuelCellFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_FUELCELL_FIELDENUMS_HXX
