/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_HEATING_DX_MULTISPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_HEATING_DX_MULTISPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Heating_DX_MultiSpeedFields
 *  \brief Enumeration of OS:Coil:Heating:DX:MultiSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Heating_DX_MultiSpeedFields, )
#else
class OS_Coil_Heating_DX_MultiSpeedFields: public ::EnumBase<OS_Coil_Heating_DX_MultiSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, MinimumOutdoorDryBulbTemperatureforCompressorOperation, OutdoorDryBulbTemperaturetoTurnOnCompressor, CrankcaseHeaterCapacity, CrankcaseHeaterCapacityFunctionofTemperatureCurveName, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, DefrostEnergyInputRatioFunctionofTemperatureCurveName, MaximumOutdoorDryBulbTemperatureforDefrostOperation, DefrostStrategy, DefrostControl, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity, ApplyPartLoadFractiontoSpeedsGreaterthan1, FuelType, RegionnumberforCalculatingHSPF,   };
  OS_Coil_Heating_DX_MultiSpeedFields()
   : EnumBase<OS_Coil_Heating_DX_MultiSpeedFields>(Handle) {} 
  OS_Coil_Heating_DX_MultiSpeedFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Heating_DX_MultiSpeedFields>(t_name) {} 
  OS_Coil_Heating_DX_MultiSpeedFields(int t_value) 
   : EnumBase<OS_Coil_Heating_DX_MultiSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Heating_DX_MultiSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Heating_DX_MultiSpeedFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Heating_DX_MultiSpeedFields>;
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
{ OS_Coil_Heating_DX_MultiSpeedFields::Handle, "Handle", "Handle"},
{ OS_Coil_Heating_DX_MultiSpeedFields::Name, "Name", "Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ OS_Coil_Heating_DX_MultiSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor, "OutdoorDryBulbTemperaturetoTurnOnCompressor", "Outdoor Dry-Bulb Temperature to Turn On Compressor"},
{ OS_Coil_Heating_DX_MultiSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ OS_Coil_Heating_DX_MultiSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, "CrankcaseHeaterCapacityFunctionofTemperatureCurveName", "Crankcase Heater Capacity Function of Temperature Curve Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ OS_Coil_Heating_DX_MultiSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, "DefrostEnergyInputRatioFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Function of Temperature Curve Name"},
{ OS_Coil_Heating_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, "MaximumOutdoorDryBulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-Bulb Temperature for Defrost Operation"},
{ OS_Coil_Heating_DX_MultiSpeedFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ OS_Coil_Heating_DX_MultiSpeedFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ OS_Coil_Heating_DX_MultiSpeedFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ OS_Coil_Heating_DX_MultiSpeedFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
{ OS_Coil_Heating_DX_MultiSpeedFields::ApplyPartLoadFractiontoSpeedsGreaterthan1, "ApplyPartLoadFractiontoSpeedsGreaterthan1", "Apply Part Load Fraction to Speeds Greater than 1"},
{ OS_Coil_Heating_DX_MultiSpeedFields::FuelType, "FuelType", "Fuel Type"},
{ OS_Coil_Heating_DX_MultiSpeedFields::RegionnumberforCalculatingHSPF, "RegionnumberforCalculatingHSPF", "Region number for Calculating HSPF"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Heating_DX_MultiSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Heating_DX_MultiSpeedFields> OptionalOS_Coil_Heating_DX_MultiSpeedFields ;
#endif

/** \class OS_Coil_Heating_DX_MultiSpeedExtensibleFields
 *  \brief Enumeration of OS:Coil:Heating:DX:MultiSpeed's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Heating_DX_MultiSpeedExtensibleFields, )
#else
class OS_Coil_Heating_DX_MultiSpeedExtensibleFields: public ::EnumBase<OS_Coil_Heating_DX_MultiSpeedExtensibleFields> {
 public: 
  enum domain 
  {
Stage,   };
  OS_Coil_Heating_DX_MultiSpeedExtensibleFields()
   : EnumBase<OS_Coil_Heating_DX_MultiSpeedExtensibleFields>(Stage) {} 
  OS_Coil_Heating_DX_MultiSpeedExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Heating_DX_MultiSpeedExtensibleFields>(t_name) {} 
  OS_Coil_Heating_DX_MultiSpeedExtensibleFields(int t_value) 
   : EnumBase<OS_Coil_Heating_DX_MultiSpeedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Heating_DX_MultiSpeedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Heating_DX_MultiSpeedExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Heating_DX_MultiSpeedExtensibleFields>;
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
{ OS_Coil_Heating_DX_MultiSpeedExtensibleFields::Stage, "Stage", "Stage"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Heating_DX_MultiSpeedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Heating_DX_MultiSpeedExtensibleFields> OptionalOS_Coil_Heating_DX_MultiSpeedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_HEATING_DX_MULTISPEED_FIELDENUMS_HXX
