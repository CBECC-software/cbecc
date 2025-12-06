/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_COIL_HEATING_FUEL_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_FUEL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_FuelFields
 *  \brief Enumeration of Coil:Heating:Fuel's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_FuelFields, )
#else
class Coil_Heating_FuelFields: public ::EnumBase<Coil_Heating_FuelFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, FuelType, BurnerEfficiency, NominalCapacity, AirInletNodeName, AirOutletNodeName, TemperatureSetpointNodeName, OnCycleParasiticElectricLoad, PartLoadFractionCorrelationCurveName, OffCycleParasiticFuelLoad,   };
  Coil_Heating_FuelFields()
   : EnumBase<Coil_Heating_FuelFields>(Name) {} 
  Coil_Heating_FuelFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_FuelFields>(t_name) {} 
  Coil_Heating_FuelFields(int t_value) 
   : EnumBase<Coil_Heating_FuelFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_FuelFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_FuelFields>::integer_value()); }
   private:
    friend class EnumBase<Coil_Heating_FuelFields>;
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
{ Coil_Heating_FuelFields::Name, "Name", "Name"},
{ Coil_Heating_FuelFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Heating_FuelFields::FuelType, "FuelType", "Fuel Type"},
{ Coil_Heating_FuelFields::BurnerEfficiency, "BurnerEfficiency", "Burner Efficiency"},
{ Coil_Heating_FuelFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Coil_Heating_FuelFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Heating_FuelFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Heating_FuelFields::TemperatureSetpointNodeName, "TemperatureSetpointNodeName", "Temperature Setpoint Node Name"},
{ Coil_Heating_FuelFields::OnCycleParasiticElectricLoad, "OnCycleParasiticElectricLoad", "On Cycle Parasitic Electric Load"},
{ Coil_Heating_FuelFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ Coil_Heating_FuelFields::OffCycleParasiticFuelLoad, "OffCycleParasiticFuelLoad", "Off Cycle Parasitic Fuel Load"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_FuelFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_FuelFields> OptionalCoil_Heating_FuelFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_FUEL_FIELDENUMS_HXX
