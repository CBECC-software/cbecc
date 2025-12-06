/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_FOURPIPEBEAM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_FOURPIPEBEAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields
 *  \brief Enumeration of OS:AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields, )
#else
class OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields: public ::EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields> {
 public: 
  enum domain 
  {
Handle, Name, PrimaryAirAvailabilityScheduleName, CoolingAvailabilityScheduleName, HeatingAvailabilityScheduleName, PrimaryAirInletNodeName, PrimaryAirOutletNodeName, CoolingCoilName, HeatingCoilName, DesignPrimaryAirVolumeFlowRate, DesignChilledWaterVolumeFlowRate, DesignHotWaterVolumeFlowRate, ZoneTotalBeamLength, RatedPrimaryAirFlowRateperBeamLength,   };
  OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields()
   : EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields>(Handle) {} 
  OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields(const std::string &t_name) 
   : EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields>(t_name) {} 
  OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields(int t_value) 
   : EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields>;
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
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::Handle, "Handle", "Handle"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::Name, "Name", "Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName, "PrimaryAirAvailabilityScheduleName", "Primary Air Availability Schedule Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName, "CoolingAvailabilityScheduleName", "Cooling Availability Schedule Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName, "HeatingAvailabilityScheduleName", "Heating Availability Schedule Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirInletNodeName, "PrimaryAirInletNodeName", "Primary Air Inlet Node Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirOutletNodeName, "PrimaryAirOutletNodeName", "Primary Air Outlet Node Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, "DesignPrimaryAirVolumeFlowRate", "Design Primary Air Volume Flow Rate"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, "DesignChilledWaterVolumeFlowRate", "Design Chilled Water Volume Flow Rate"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, "DesignHotWaterVolumeFlowRate", "Design Hot Water Volume Flow Rate"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, "ZoneTotalBeamLength", "Zone Total Beam Length"},
{ OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength, "RatedPrimaryAirFlowRateperBeamLength", "Rated Primary Air Flow Rate per Beam Length"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields> OptionalOS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRTERMINAL_SINGLEDUCT_CONSTANTVOLUME_FOURPIPEBEAM_FIELDENUMS_HXX
