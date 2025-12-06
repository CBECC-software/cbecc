/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_COOLING_DX_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_DX_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_DXFields
 *  \brief Enumeration of OS:Coil:Cooling:DX's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_DXFields, )
#else
class OS_Coil_Cooling_DXFields: public ::EnumBase<OS_Coil_Cooling_DXFields> {
 public: 
  enum domain 
  {
Handle, Name, EvaporatorInletNode, EvaporatorOutletNode, AvailabilitySchedule, CondenserZone, CondenserInletNodeName, CondenserOutletNodeName, PerformanceObject, CondensateCollectionWaterStorageTankName, EvaporativeCondenserSupplyWaterStorageTankName,   };
  OS_Coil_Cooling_DXFields()
   : EnumBase<OS_Coil_Cooling_DXFields>(Handle) {} 
  OS_Coil_Cooling_DXFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_DXFields>(t_name) {} 
  OS_Coil_Cooling_DXFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_DXFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_DXFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_DXFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_DXFields>;
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
{ OS_Coil_Cooling_DXFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_DXFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_DXFields::EvaporatorInletNode, "EvaporatorInletNode", "Evaporator Inlet Node"},
{ OS_Coil_Cooling_DXFields::EvaporatorOutletNode, "EvaporatorOutletNode", "Evaporator Outlet Node"},
{ OS_Coil_Cooling_DXFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_Coil_Cooling_DXFields::CondenserZone, "CondenserZone", "Condenser Zone"},
{ OS_Coil_Cooling_DXFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ OS_Coil_Cooling_DXFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ OS_Coil_Cooling_DXFields::PerformanceObject, "PerformanceObject", "Performance Object"},
{ OS_Coil_Cooling_DXFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
{ OS_Coil_Cooling_DXFields::EvaporativeCondenserSupplyWaterStorageTankName, "EvaporativeCondenserSupplyWaterStorageTankName", "Evaporative Condenser Supply Water Storage Tank Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_DXFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_DXFields> OptionalOS_Coil_Cooling_DXFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_DX_FIELDENUMS_HXX
