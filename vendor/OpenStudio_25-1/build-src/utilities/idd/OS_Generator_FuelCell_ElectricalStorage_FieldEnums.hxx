/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_GENERATOR_FUELCELL_ELECTRICALSTORAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_FUELCELL_ELECTRICALSTORAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_FuelCell_ElectricalStorageFields
 *  \brief Enumeration of OS:Generator:FuelCell:ElectricalStorage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_FuelCell_ElectricalStorageFields, )
#else
class OS_Generator_FuelCell_ElectricalStorageFields: public ::EnumBase<OS_Generator_FuelCell_ElectricalStorageFields> {
 public: 
  enum domain 
  {
Handle, Name, ChoiceofModel, NominalChargingEnergeticEfficiency, NominalDischargingEnergeticEfficiency, SimpleMaximumCapacity, SimpleMaximumPowerDraw, SimpleMaximumPowerStore, InitialChargeState,   };
  OS_Generator_FuelCell_ElectricalStorageFields()
   : EnumBase<OS_Generator_FuelCell_ElectricalStorageFields>(Handle) {} 
  OS_Generator_FuelCell_ElectricalStorageFields(const std::string &t_name) 
   : EnumBase<OS_Generator_FuelCell_ElectricalStorageFields>(t_name) {} 
  OS_Generator_FuelCell_ElectricalStorageFields(int t_value) 
   : EnumBase<OS_Generator_FuelCell_ElectricalStorageFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_FuelCell_ElectricalStorageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_FuelCell_ElectricalStorageFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Generator_FuelCell_ElectricalStorageFields>;
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
{ OS_Generator_FuelCell_ElectricalStorageFields::Handle, "Handle", "Handle"},
{ OS_Generator_FuelCell_ElectricalStorageFields::Name, "Name", "Name"},
{ OS_Generator_FuelCell_ElectricalStorageFields::ChoiceofModel, "ChoiceofModel", "Choice of Model"},
{ OS_Generator_FuelCell_ElectricalStorageFields::NominalChargingEnergeticEfficiency, "NominalChargingEnergeticEfficiency", "Nominal Charging Energetic Efficiency"},
{ OS_Generator_FuelCell_ElectricalStorageFields::NominalDischargingEnergeticEfficiency, "NominalDischargingEnergeticEfficiency", "Nominal Discharging Energetic Efficiency"},
{ OS_Generator_FuelCell_ElectricalStorageFields::SimpleMaximumCapacity, "SimpleMaximumCapacity", "Simple Maximum Capacity"},
{ OS_Generator_FuelCell_ElectricalStorageFields::SimpleMaximumPowerDraw, "SimpleMaximumPowerDraw", "Simple Maximum Power Draw"},
{ OS_Generator_FuelCell_ElectricalStorageFields::SimpleMaximumPowerStore, "SimpleMaximumPowerStore", "Simple Maximum Power Store"},
{ OS_Generator_FuelCell_ElectricalStorageFields::InitialChargeState, "InitialChargeState", "Initial Charge State"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_FuelCell_ElectricalStorageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_FuelCell_ElectricalStorageFields> OptionalOS_Generator_FuelCell_ElectricalStorageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_FUELCELL_ELECTRICALSTORAGE_FIELDENUMS_HXX
